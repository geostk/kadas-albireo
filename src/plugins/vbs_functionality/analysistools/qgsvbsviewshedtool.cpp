/***************************************************************************
 *  qgsvbsviewshedtool.cpp                                                 *
 *  -------------------                                                    *
 *  begin                : Nov 12, 2015                                    *
 *  copyright            : (C) 2015 by Sandro Mani / Sourcepole AG         *
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

#include "qgsvbsviewshedtool.h"
#include "qgscolorrampshader.h"
#include "qgisinterface.h"
#include "qgsmapcanvas.h"
#include "qgsmaplayer.h"
#include "qgsmaplayerregistry.h"
#include "qgsmaptoolfilter.h"
#include "qgsproject.h"
#include "qgsrasterlayer.h"
#include "qgsrubberband.h"
#include "qgstemporaryfile.h"
#include "raster/qgssinglebandpseudocolorrenderer.h"
#include "raster/qgsviewshed.h"

#include <QDialogButtonBox>
#include <QDir>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QProgressDialog>


QgsVBSViewshedTool::QgsVBSViewshedTool( QgisInterface *iface, QObject *parent )
    : QObject( parent ), mIface( iface )
{
  mRubberBand = new QgsRubberBand( mIface->mapCanvas(), QGis::Polygon );
  mRubberBand->setFillColor( QColor( 254, 178, 76, 63 ) );
  mRubberBand->setBorderColor( QColor( 254, 58, 29, 100 ) );

  QgsMapToolFilter* filterTool = new QgsMapToolFilter( mIface->mapCanvas(), QgsMapToolFilter::Circle, mRubberBand );
  connect( filterTool, SIGNAL( deactivated() ), this, SLOT( filterFinished() ) );
  connect( filterTool, SIGNAL( deactivated() ), this, SLOT( deleteLater() ) );
  mIface->mapCanvas()->setMapTool( filterTool );
}

QgsVBSViewshedTool::~QgsVBSViewshedTool()
{
  delete mRubberBand;
}

void QgsVBSViewshedTool::filterFinished()
{
  QString layerid = QgsProject::instance()->readEntry( "Heightmap", "layer" );
  QgsMapLayer* layer = QgsMapLayerRegistry::instance()->mapLayer( layerid );
  if ( !layer || layer->type() != QgsMapLayer::RasterLayer )
  {
    QMessageBox::warning( 0, tr( "Error" ), tr( "No heightmap is defined in the project. Right-click a raster layer in the layer tree and select it to be used as heightmap." ) );
    emit finished();
    return;
  }

  QDialog heightDialog;
  heightDialog.setWindowTitle( tr( "Viewshed setup" ) );
  QGridLayout* heightDialogLayout = new QGridLayout();
  heightDialogLayout->addWidget( new QLabel( tr( "Observer height:" ) ), 0, 0, 1, 1 );
  heightDialogLayout->addWidget( new QLabel( tr( "Target height:" ) ), 1, 0, 1, 1 );
  QDoubleSpinBox* spinObserverHeight = new QDoubleSpinBox();
  spinObserverHeight->setRange( 0, 8000 );
  spinObserverHeight->setDecimals( 1 );
  spinObserverHeight->setValue( 2. );
  spinObserverHeight->setSuffix( " m" );
  heightDialogLayout->addWidget( spinObserverHeight, 0, 1, 1, 1 );
  QDoubleSpinBox* spinTargetHeight = new QDoubleSpinBox();
  spinTargetHeight->setRange( 0, 8000 );
  spinTargetHeight->setDecimals( 1 );
  spinTargetHeight->setValue( 2. );
  spinTargetHeight->setSuffix( " m" );
  heightDialogLayout->addWidget( spinTargetHeight, 1, 1, 1, 1 );
  QDialogButtonBox* bbox = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal );
  connect( bbox, SIGNAL( accepted() ), &heightDialog, SLOT( accept() ) );
  connect( bbox, SIGNAL( rejected() ), &heightDialog, SLOT( reject() ) );
  heightDialogLayout->addWidget( bbox, 2, 0, 1, 2 );
  heightDialog.setLayout( heightDialogLayout );
  heightDialog.setFixedSize( heightDialog.sizeHint() );
  if ( heightDialog.exec() == QDialog::Rejected )
  {
    emit finished();
    return;
  }

  QgsGeometry* rubberBandGeom = mRubberBand->asGeometry();

  QgsRectangle rect = rubberBandGeom->boundingBox();
  QgsCoordinateReferenceSystem rectCrs = mIface->mapCanvas()->mapSettings().destinationCrs();

  QString outputFileName = QString( "viewshed_%1-%2_%3-%4.tif" ).arg( rect.xMinimum() ).arg( rect.xMaximum() ).arg( rect.yMinimum() ).arg( rect.yMaximum() );
  QString outputFile = QgsTemporaryFile::createNewFile( outputFileName );

  QProgressDialog p( tr( "Calculating viewshed..." ), tr( "Abort" ), 0, 0 );
  p.setWindowModality( Qt::WindowModal );
  bool success = QgsViewshed::computeViewshed( layer->source(), outputFile, "GTiff", rect.center(), rectCrs, spinObserverHeight->value(), spinTargetHeight->value(), .5 * rect.width(), QGis::Meters, &p );
  if ( success )
  {
    QgsRasterLayer* layer = mIface->addRasterLayer( outputFile, tr( "Viewshed [%1]" ).arg( rect.center().toString() ) );
    QgsColorRampShader* rampShader = new QgsColorRampShader();
    QList<QgsColorRampShader::ColorRampItem> colorRampItems = QList<QgsColorRampShader::ColorRampItem>()
        << QgsColorRampShader::ColorRampItem( 255, QColor( 0, 255, 0 ), tr( "Visible" ) );
    rampShader->setColorRampItemList( colorRampItems );
    QgsRasterShader* shader = new QgsRasterShader();
    shader->setRasterShaderFunction( rampShader );
    QgsSingleBandPseudoColorRenderer* renderer = new QgsSingleBandPseudoColorRenderer( 0, 1, shader );
    layer->setRenderer( renderer );
  }
  emit finished();
}