/***************************************************************************
 *  qgsmilxio.h                                                            *
 *  -----------                                                            *
 *  begin                : February 2016                                   *
 *  copyright            : (C) 2016 by Sandro Mani / Sourcepole AG         *
 *  email                : smani@sourcepole.ch                             *
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgisinterface.h"
#include "qgsclipboard.h"
#include "qgscrscache.h"
#include "qgsmapcanvas.h"
#include "qgsmaplayer.h"
#include "qgsmaplayerregistry.h"
#include "qgsmessagebar.h"
#include "qgsmilxio.h"
#include "qgsmilxannotationitem.h"
#include "qgsmilxlayer.h"
#include "qgsproject.h"
#include "layertree/qgslayertreeview.h"
#include <QApplication>
#include <QComboBox>
#include <QDesktopWidget>
#include <QDialogButtonBox>
#include <QDomDocument>
#include <QFileDialog>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QSettings>
#include <QGridLayout>
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <quazip/quazipfile.h>
#else
#include <quazip5/quazipfile.h>
#endif

bool QgsMilXIO::save( QgisInterface* iface )
{
  QDialog layerSelectionDialog( iface->mainWindow() );
  layerSelectionDialog.setWindowTitle( tr( "Export MilX layers" ) );
  QGridLayout* layout = new QGridLayout();
  layerSelectionDialog.setLayout( layout );
  layout->addWidget( new QLabel( tr( "Select MilX layers to export" ) ), 0, 0, 1, 2 );
  QListWidget* layerListWidget = new QListWidget();
  QComboBox* cartoucheCombo = new QComboBox();
  cartoucheCombo->addItem( tr( "Don't add" ) );
  foreach ( QgsMapLayer* layer, QgsMapLayerRegistry::instance()->mapLayers().values() )
  {
    if ( qobject_cast<QgsMilXLayer*>( layer ) )
    {
      QListWidgetItem* item = new QListWidgetItem( layer->name() );
      item->setData( Qt::UserRole, layer->id() );
      item->setCheckState( iface->mapCanvas()->layers().contains( layer ) ? Qt::Checked : Qt::Unchecked );
      layerListWidget->addItem( item );
      cartoucheCombo->addItem( layer->name(), layer->id() );
    }
  }
  layout->addWidget( layerListWidget, 1, 0, 1, 2 );
  layout->addWidget( new QLabel( tr( "Add cartouche to layer:" ) ), 2, 0, 1, 1 );
  layout->addWidget( cartoucheCombo, 2, 1, 1, 1 );
  layout->addWidget( new QLabel( tr( "MilX version:" ) ), 3, 0, 1, 1 );
  QComboBox* combo = new QComboBox();
  QStringList versionTags, versionNames;
  MilXClient::getSupportedLibraryVersionTags( versionTags, versionNames );
  for ( int i = 0, n = versionTags.size(); i < n; ++i )
  {
    combo->addItem( versionNames[i], versionTags[i] );
  }
  combo->setCurrentIndex( 0 );
  layout->addWidget( combo, 3, 1, 1, 1 );
  QDialogButtonBox* bbox = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel );
  layout->addWidget( bbox, 4, 0, 1, 2 );
  connect( bbox, SIGNAL( accepted() ), &layerSelectionDialog, SLOT( accept() ) );
  connect( bbox, SIGNAL( rejected() ), &layerSelectionDialog, SLOT( reject() ) );
  if ( layerSelectionDialog.exec() == QDialog::Rejected )
  {
    return false;
  }

  QStringList exportLayers;
  for ( int i = 0, n = layerListWidget->count(); i < n; ++i )
  {
    QListWidgetItem* item = layerListWidget->item( i );
    if ( item->checkState() == Qt::Checked )
    {
      exportLayers.append( item->data( Qt::UserRole ).toString() );
    }
  }

  QStringList filters;
  filters.append( tr( "Compressed MilX Layer (*.milxlyz)" ) );
  filters.append( tr( "MilX Layer (*.milxly)" ) );

  QString lastDir = QSettings().value( "/UI/lastImportExportDir", "." ).toString();
  QString selectedFilter;

  QString filename = QFileDialog::getSaveFileName( 0, tr( "Select Output" ), lastDir, filters.join( ";;" ), &selectedFilter );
  if ( filename.isEmpty() )
  {
    return false;
  }
  QSettings().setValue( "/UI/lastImportExportDir", QFileInfo( filename ).absolutePath() );
  if ( selectedFilter == filters[0] && !filename.endsWith( ".milxlyz", Qt::CaseInsensitive ) )
  {
    filename += ".milxlyz";
  }
  else if ( selectedFilter == filters[1] && !filename.endsWith( ".milxly", Qt::CaseInsensitive ) )
  {
    filename += ".milxly";
  }
  QString targetVersionTag = combo->itemData( combo->currentIndex() ).toString();
  QString currentVersionTag; MilXClient::getCurrentLibraryVersionTag( currentVersionTag );

  QIODevice* dev = 0;
  QuaZip* zip = 0;
  if ( selectedFilter == filters[0] )
  {
    zip = new QuaZip( filename );
    zip->open( QuaZip::mdCreate );
    dev = new QuaZipFile( zip );
    static_cast<QuaZipFile*>( dev )->open( QIODevice::WriteOnly, QuaZipNewInfo( "Layer.milxly" ) );
  }
  else
  {
    dev = new QFile( filename );
    dev->open( QIODevice::WriteOnly );
  }
  if ( !dev->isOpen() )
  {
    delete dev;
    delete zip;
    iface->messageBar()->pushMessage( tr( "Export Failed" ), tr( "Failed to open the output file for writing." ), QgsMessageBar::CRITICAL, 5 );
    return false;
  }

  int dpi = QApplication::desktop()->logicalDpiX();

  QDomDocument doc;
  doc.appendChild( doc.createProcessingInstruction( "xml", "version=\"1.0\" encoding=\"UTF-8\"" ) );
  QDomElement milxDocumentEl = doc.createElement( "MilXDocument_Layer" );
  milxDocumentEl.setAttribute( "xmlns", "http://gs-soft.com/MilX/V3.1" );
  milxDocumentEl.setAttribute( "xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance" );
  doc.appendChild( milxDocumentEl );

  QDomElement milxVersionEl = doc.createElement( "MssLibraryVersionTag" );
  milxVersionEl.appendChild( doc.createTextNode( currentVersionTag ) );
  milxDocumentEl.appendChild( milxVersionEl );

  QString cartoucheLayerId = cartoucheCombo->itemData( cartoucheCombo->currentIndex() ).toString();
  QString cartouche = QgsProject::instance()->readEntry( "VBS-Print", "cartouche" );

  // Replace custom texts by "Custom" since the MSS Schema Validator enforces this
  QStringList validClassifications = QStringList() << "None" << "Internal" << "Confidential" << "Secret";
  QDomDocument cartoucheDoc;
  cartoucheDoc.setContent( cartouche );
  QDomNodeList exClassifications = cartoucheDoc.elementsByTagName( "ExerciseClassification" );
  if ( !exClassifications.isEmpty() )
  {
    QDomElement el = exClassifications.at( 0 ).toElement();
    QString classification = el.text();
    if ( !validClassifications.contains( classification ) )
      el.replaceChild( cartoucheDoc.createTextNode( "Custom" ), el.firstChild() );
  }

  QDomNodeList missingClassifications = cartoucheDoc.elementsByTagName( "MissionClassification" );
  if ( !missingClassifications.isEmpty() )
  {
    QDomElement el = missingClassifications.at( 0 ).toElement();
    QString classification = el.text();
    if ( !validClassifications.contains( classification ) )
      el.replaceChild( cartoucheDoc.createTextNode( "Custom" ), el.firstChild() );
  }
  cartouche = cartoucheDoc.toString();

  foreach ( const QString& layerId, exportLayers )
  {
    QgsMapLayer* layer = QgsMapLayerRegistry::instance()->mapLayer( layerId );
    if ( qobject_cast<QgsMilXLayer*>( layer ) )
    {
      QDomElement milxLayerEl = doc.createElement( "MilXLayer" );
      milxDocumentEl.appendChild( milxLayerEl );
      static_cast<QgsMilXLayer*>( layer )->exportToMilxly( milxLayerEl, dpi );

      if ( cartoucheLayerId == layerId )
      {
        QDomDocument cartoucheDoc;
        cartoucheDoc.setContent( cartouche );
        milxLayerEl.appendChild( cartoucheDoc.documentElement() );
      }
    }
  }
  QString inputXml = doc.toString();
  QString outputXml;
  bool valid = false;
  QString messages;
  if ( !MilXClient::downgradeMilXFile( inputXml, outputXml, targetVersionTag, valid, messages ) )
  {
    delete dev;
    delete zip;
    iface->messageBar()->pushMessage( tr( "Export Failed" ), tr( "Failed to write output." ), QgsMessageBar::CRITICAL, 5 );
    return false;
  }
  if ( valid )
  {
    dev->write( outputXml.toUtf8() );
    iface->messageBar()->pushMessage( tr( "Export Completed" ), "", QgsMessageBar::INFO, 5 );
    if ( !messages.isEmpty() )
    {
      showMessageDialog( tr( "Export Messages" ), tr( "The following messages were emitted while exporting:" ), messages );
    }
  }
  else
  {
    iface->messageBar()->pushMessage( tr( "Export Failed" ), "", QgsMessageBar::CRITICAL, 5 );
    if ( !messages.isEmpty() )
    {
      showMessageDialog( tr( "Export Failed" ), tr( "The export failed:" ), messages );
    }
  }

  delete dev;
  delete zip;
  return true;
}

bool QgsMilXIO::load( QgisInterface* iface )
{
  QString lastDir = QSettings().value( "/UI/lastImportExportDir", "." ).toString();
  QString filter = tr( "MilX Layer Files (*.milxly *.milxlyz)" );
  QString filename = QFileDialog::getOpenFileName( 0, tr( "Select Milx Layer File" ), lastDir, filter );
  if ( filename.isEmpty() )
  {
    return false;
  }
  QSettings().setValue( "/UI/lastImportExportDir", QFileInfo( filename ).absolutePath() );

  QIODevice* dev = 0;
  if ( filename.endsWith( ".milxlyz", Qt::CaseInsensitive ) )
  {
    dev = new QuaZipFile( filename, "Layer.milxly", QuaZip::csInsensitive );
  }
  else
  {
    dev = new QFile( filename );
  }
  if ( !dev->open( QIODevice::ReadOnly ) )
  {
    delete dev;
    iface->messageBar()->pushMessage( tr( "Import Failed" ), tr( "Failed to open the input file for reading." ), QgsMessageBar::CRITICAL, 5 );
    return false;
  }
  QString inputXml = QString::fromUtf8( dev->readAll().data() );
  delete dev;
  QString outputXml;
  bool valid = false;
  QString messages;
  if ( !MilXClient::upgradeMilXFile( inputXml, outputXml, valid, messages ) )
  {
    iface->messageBar()->pushMessage( tr( "Import Failed" ), tr( "Failed to read input." ), QgsMessageBar::CRITICAL, 5 );
    return false;
  }
  if ( !valid )
  {
    iface->messageBar()->pushMessage( tr( "Import Failed" ), "", QgsMessageBar::CRITICAL, 5 );
    if ( !messages.isEmpty() )
    {
      showMessageDialog( tr( "Import Failed" ), tr( "The import failed:" ), messages );
    }
    return false;
  }

  QDomDocument doc;
  doc.setContent( outputXml );

  if ( doc.isNull() )
  {
    QString errorMsg = tr( "The file could not be parsed." );
    iface->messageBar()->pushMessage( tr( "Import Failed" ), errorMsg, QgsMessageBar::CRITICAL, 5 );
    return false;
  }

  QDomElement milxDocumentEl = doc.firstChildElement( "MilXDocument_Layer" );
  QDomElement milxVersionEl = milxDocumentEl.firstChildElement( "MssLibraryVersionTag" );
  QString fileMssVer = milxVersionEl.text();

  QString verTag;
  MilXClient::getCurrentLibraryVersionTag( verTag );
  if ( fileMssVer != verTag )
  {
    QString errorMsg = tr( "Unexpected MSS library version tag." );
    iface->messageBar()->pushMessage( tr( "Import Failed" ), errorMsg, QgsMessageBar::CRITICAL, 5 );
    return false;
  }
  int dpi = QApplication::desktop()->logicalDpiX();

  QDomNodeList milxLayerEls = milxDocumentEl.elementsByTagName( "MilXLayer" );
  QString errorMsg;
  QList<QgsMilXLayer*> importedLayers;
  QList< QPair<QString, QString> > cartouches;
  for ( int iLayer = 0, nLayers = milxLayerEls.count(); iLayer < nLayers; ++iLayer )
  {
    QDomElement milxLayerEl = milxLayerEls.at( iLayer ).toElement();
    QgsMilXLayer* layer = new QgsMilXLayer( iface->layerTreeView()->menuProvider() );
    if ( !layer->importMilxly( milxLayerEl, dpi, errorMsg ) )
    {
      break;
    }
    importedLayers.append( layer );
    QDomNodeList cartoucheEls = milxLayerEl.elementsByTagName( "Legend" );
    if ( !cartoucheEls.isEmpty() )
    {
      QString cartouche;
      QTextStream ts( &cartouche );
      cartoucheEls.at( 0 ).save( ts, 2 );
      cartouches.append( qMakePair( layer->name(), cartouche ) );
    }
  }

  if ( errorMsg.isEmpty() )
  {
    foreach ( QgsMilXLayer* layer, importedLayers )
    {
      QgsMapLayerRegistry::instance()->addMapLayer( layer );
    }
    if ( !cartouches.isEmpty() )
    {
      QDialog cartoucheSelectionDialog( iface->mainWindow() );
      cartoucheSelectionDialog.setWindowTitle( tr( "Import cartouche" ) );
      QGridLayout* layout = new QGridLayout();
      cartoucheSelectionDialog.setLayout( layout );
      layout->addWidget( new QLabel( tr( "Import cartouche from MilX layer:" ) ), 0, 0, 1, 1 );
      QComboBox* cartoucheCombo = new QComboBox();
      cartoucheCombo->addItem( tr( "Don't import" ) );
      typedef QPair<QString, QString> CartouchePair;
      foreach ( const CartouchePair& pair, cartouches )
      {
        cartoucheCombo->addItem( pair.first, pair.second );
      }
      layout->addWidget( cartoucheCombo, 0, 1, 1, 1 );
      QDialogButtonBox* bbox = new QDialogButtonBox( QDialogButtonBox::Ok );
      connect( bbox, SIGNAL( accepted() ), &cartoucheSelectionDialog, SLOT( accept() ) );
      connect( bbox, SIGNAL( rejected() ), &cartoucheSelectionDialog, SLOT( reject() ) );
      layout->addWidget( bbox, 1, 1, 1, 2 );
      if ( cartoucheSelectionDialog.exec() == QDialog::Accepted )
      {
        QString cartouche = cartoucheCombo->itemData( cartoucheCombo->currentIndex() ).toString();
        if ( !cartouche.isEmpty() )
        {
          QgsProject::instance()->writeEntry( "VBS-Print", "cartouche", cartouche );
        }
      }
    }
    iface->messageBar()->pushMessage( tr( "Import Completed" ), "", QgsMessageBar::INFO, 5 );
    if ( !messages.isEmpty() )
    {
      showMessageDialog( tr( "Import Messages" ), tr( "The following messages were emitted while importing:" ), messages );
    }
  }
  else
  {
    qDeleteAll( importedLayers );
    iface->messageBar()->pushMessage( tr( "Import Failed" ), errorMsg, QgsMessageBar::CRITICAL, 5 );
  }
  return true;
}

void QgsMilXIO::copyToClipboard( const QList<QgsMilXItem*>& milxItems, QgisInterface *iface )
{
  QgsVector center;
  foreach ( const QgsMilXItem* item, milxItems )
  {
    center += QgsVector( item->points()[0] );
  }
  center = center / double( milxItems.size() );

  QDomDocument doc;
  doc.appendChild( doc.createProcessingInstruction( "xml", "version=\"1.0\" encoding=\"utf-8\"" ) );

  QDomElement symbolGroup = doc.createElement( "SymbolGroup" );
  doc.appendChild( symbolGroup );

  int dpi = QApplication::desktop()->logicalDpiX();
  QDomElement symbolSizeEl = doc.createElement( "SymbolSize" );
  symbolSizeEl.appendChild( doc.createTextNode( QString::number(( MilXClient::getSymbolSize() * 25.4 ) / dpi ) ) );
  symbolGroup.appendChild( symbolSizeEl );

  QDomElement itemsEl = doc.createElement( "GraphicList" );
  foreach ( QgsMilXItem* milxItem, milxItems )
  {
    QDomElement graphicEl = doc.createElement( "MilXGraphic" );
    graphicEl.setAttribute( "offsetX", milxItem->points()[0].x() - center.x() );
    graphicEl.setAttribute( "offsetY", milxItem->points()[0].y() - center.y() );
    milxItem->writeMilx( doc, graphicEl );
    itemsEl.appendChild( graphicEl );
  }
  symbolGroup.appendChild( itemsEl );

  QString xml = doc.toString();
  QMimeData* mimeData = new QMimeData();
  mimeData->setData( "text/plain", xml.toUtf8() );
  mimeData->setData( QGSCLIPBOARD_MILXITEMS_MIME, xml.toUtf8() );
  iface->clipboard()->setMimeData( mimeData );
}

void QgsMilXIO::showMessageDialog( const QString& title, const QString& body, const QString& messages )
{
  QDialog dialog;
  dialog.setWindowTitle( title );
  dialog.setLayout( new QVBoxLayout );
  dialog.layout()->addWidget( new QLabel( body ) );
  QPlainTextEdit* textEdit = new QPlainTextEdit( messages );
  textEdit->setReadOnly( true );
  dialog.layout()->addWidget( textEdit );
  QDialogButtonBox* bbox = new QDialogButtonBox( QDialogButtonBox::Close );
  dialog.layout()->addWidget( bbox );
  connect( bbox, SIGNAL( accepted() ), &dialog, SLOT( accept() ) );
  connect( bbox, SIGNAL( rejected() ), &dialog, SLOT( reject() ) );
  dialog.exec();
}
