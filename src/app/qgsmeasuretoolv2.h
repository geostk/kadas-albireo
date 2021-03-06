/***************************************************************************
    qgsmeasuretoolv2.h
    ------------------
    begin                : January 2016
    copyright            : (C) 2016 Sandro Mani
    email                : manisandro@gmail.com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#ifndef QGSMEASURETOOLV2_H
#define QGSMEASURETOOLV2_H

#include "qgsmaptool.h"
#include "qgsmaptooldrawshape.h"
#include "qgsbottombar.h"

class QComboBox;
class QgsMapCanvas;
class QgsVectorLayer;
class QgsMeasureWidget;

class APP_EXPORT QgsMeasureToolV2 : public QgsMapTool
{
    Q_OBJECT
  public:
    enum MeasureMode { MeasureLine, MeasurePolygon, MeasureCircle, MeasureAngle, MeasureAzimuth };
    QgsMeasureToolV2( QgsMapCanvas* canvas , MeasureMode measureMode );
    ~QgsMeasureToolV2();
    void addGeometry( const QgsGeometry* geometry, const QgsVectorLayer* layer );

    void activate() override;
    void deactivate() override;
    void canvasPressEvent( QMouseEvent *e ) override;
    void canvasMoveEvent( QMouseEvent *e ) override;
    void canvasReleaseEvent( QMouseEvent *e ) override;
    void keyReleaseEvent( QKeyEvent *e ) override;
  private:
    QgsMeasureWidget* mMeasureWidget;
    bool mPickFeature;
    MeasureMode mMeasureMode;
    QgsMapToolDrawShape* mDrawTool;

  private slots:
    void close();
    void setUnits();
    void updateTotal();
    void requestPick();
};

class APP_EXPORT QgsMeasureWidget : public QgsBottomBar
{
    Q_OBJECT
  public:
    QgsMeasureWidget( QgsMapCanvas* canvas, QgsMeasureToolV2::MeasureMode measureMode );
    void updateMeasurement( const QString& measurement );
    QGis::UnitType currentUnit() const;
    QgsGeometryRubberBand::AngleUnit currentAngleUnit() const;
    QgsGeometryRubberBand::AzimuthNorth currentAzimuthNorth() const;

  signals:
    void clearRequested();
    void closeRequested();
    void pickRequested();
    void unitsChanged();

  private:
    QLabel* mMeasurementLabel;
    QComboBox* mUnitComboBox;
    QComboBox* mNorthComboBox;
    QgsMeasureToolV2::MeasureMode mMeasureMode;

  private slots:
    void saveDefaultUnits( int index );
    void saveAzimuthNorth( int index );
};

#endif // QGSMEASURETOOLV2_H
