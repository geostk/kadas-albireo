/***************************************************************************
                              qgsgeoimageannotationitem.h
                              ------------------------
  begin                : August, 2015
  copyright            : (C) 2015 by Sandro Mani
  email                : smani@sourcepole.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSGEOIMAGEANNOTATIONITEM_H
#define QGSGEOIMAGEANNOTATIONITEM_H

#include "qgsannotationitem.h"
#include <QSvgRenderer>

class GUI_EXPORT QgsGeoImageAnnotationItem: public QgsAnnotationItem
{
    Q_OBJECT
    QGS_ANNOTATION_ITEM( QgsGeoImageAnnotationItem, "GeoImageAnnotationItem" )

  public:
    static QgsGeoImageAnnotationItem* create( QgsMapCanvas* canvas, const QString& filePath , QString *errMsg = 0 );

    QgsGeoImageAnnotationItem( QgsMapCanvas* canvas );
    ~QgsGeoImageAnnotationItem();

    QgsGeoImageAnnotationItem* clone( QgsMapCanvas *canvas ) override { return new QgsGeoImageAnnotationItem( canvas, this ); }

    void setFilePath( const QString& filePath );

    void writeXML( QDomDocument& doc ) const override;
    void readXML( const QDomDocument& doc, const QDomElement& itemElem ) override;

    void paint( QPainter* painter ) override;
    QString filePath() const { return mFilePath; }

    void handleMoveAction( int moveAction, const QPointF &newPos, const QPointF &oldPos ) override;
    void showContextMenu( const QPoint& screenPos ) override;

  protected:
    QgsGeoImageAnnotationItem( QgsMapCanvas* canvas, QgsGeoImageAnnotationItem* source );

  private:
    mutable QString mFilePath;
    QImage mImage;

    static bool readGeoPos( const QString& filePath, QgsPoint& wgs84Pos , QString *errMsg = 0 );

    void updateImage();
    bool createBillboard() const override { return true; }
    QImage billboardImage() const override { return mImage; }

  private slots:
    void _showItemEditor() override;
    void toggleLocked();
};

#endif // QGSGEOIMAGEANNOTATIONITEM_H
