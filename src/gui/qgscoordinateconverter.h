/***************************************************************************
 *  qgscoordinateconverter.h                                            *
 *  -------------------                                                    *
 *  begin                : Jul 13, 2015                                    *
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

#ifndef QGSCOORDINATECONVERTER_H
#define QGSCOORDINATECONVERTER_H

#include <QObject>

class QgsPoint;
class QgsCoordinateReferenceSystem;

class GUI_EXPORT QgsCoordinateConverter : public QObject
{
  public:
    QgsCoordinateConverter( QObject* parent ) : QObject( parent ) {}
    virtual ~QgsCoordinateConverter() {}
    virtual QString convert( const QgsPoint& p, const QgsCoordinateReferenceSystem& sSrs ) const = 0;
};


class GUI_EXPORT QgsEPSGCoordinateConverter : public QgsCoordinateConverter
{
  public:
    QgsEPSGCoordinateConverter( const QString& targetEPSG, QObject* parent );
    ~QgsEPSGCoordinateConverter();
    QString convert( const QgsPoint& p, const QgsCoordinateReferenceSystem& sSrs ) const override;
  private:
    QgsCoordinateReferenceSystem* mDestSrs;
};


class GUI_EXPORT QgsWGS84CoordinateConverter : public QgsCoordinateConverter
{
  public:
    enum Format { DegMinSec, DegMin, DecDeg };
    QgsWGS84CoordinateConverter( Format format, QObject* parent );
    ~QgsWGS84CoordinateConverter();
    QString convert( const QgsPoint& p, const QgsCoordinateReferenceSystem& sSrs ) const override;
  private:
    Format mFormat;
    QgsCoordinateReferenceSystem* mDestSrs;
};


class GUI_EXPORT QgsUTMCoordinateConverter : public QgsCoordinateConverter
{
  public:
    QgsUTMCoordinateConverter( QObject* parent );
    ~QgsUTMCoordinateConverter();
    QString convert( const QgsPoint& p, const QgsCoordinateReferenceSystem& sSrs ) const override;
  protected:
    QgsCoordinateReferenceSystem* mWgs84Srs;
};

class GUI_EXPORT QgsMGRSCoordinateConverter : public QgsUTMCoordinateConverter
{
  public:
    QgsMGRSCoordinateConverter( QObject* parent ) : QgsUTMCoordinateConverter( parent ) {}
    QString convert( const QgsPoint& p, const QgsCoordinateReferenceSystem& sSrs ) const override;
};

#endif // QGSCOORDINATECONVERTER_H