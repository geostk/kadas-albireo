/***************************************************************************
      qgsafsfeatureiterator.h
      -----------------------
    begin                : Jun 03, 2015
    copyright            : (C) 2015 by Sandro Mani
    email                : smani@sourcepole.ch
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef QGSAFSFEATUREITERATOR_H
#define QGSAFSFEATUREITERATOR_H

#include "qgsfeatureiterator.h"
#include "qgsafsshareddata.h"
#include <QSharedPointer>

class QgsSpatialIndex;


class QgsAfsFeatureSource : public QObject, public QgsAbstractFeatureSource
{
    Q_OBJECT

  public:
    QgsAfsFeatureSource( const QSharedPointer<QgsAfsSharedData> &sharedData );
    QgsFeatureIterator getFeatures( const QgsFeatureRequest &request ) override;
    QgsAfsSharedData *sharedData() const;

  protected:
    QSharedPointer<QgsAfsSharedData> mSharedData;

    friend class QgsAfsFeatureIterator;
};

class QgsAfsFeatureIterator : public QgsAbstractFeatureIteratorFromSource<QgsAfsFeatureSource>
{
  public:
    QgsAfsFeatureIterator( QgsAfsFeatureSource* source, bool ownSource, const QgsFeatureRequest& request );
    ~QgsAfsFeatureIterator();
    bool rewind() override;
    bool close() override;

  protected:
    bool fetchFeature( QgsFeature& f ) override;

  private:
    QgsFeatureId mFeatureIterator;
};

#endif // QGSAFSFEATUREITERATOR_H
