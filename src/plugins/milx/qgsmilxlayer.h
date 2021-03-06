/***************************************************************************
 *  qgsmilxlayer.h                                                         *
 *  --------------                                                         *
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

#ifndef QGSMILXLAYER_H
#define QGSMILXLAYER_H

#include "qgspluginlayer.h"
#include "qgspluginlayerregistry.h"
#include "MilXClient.hpp"

class QgisInterface;
class QgsLayerTreeViewMenuProvider;

class QGS_MILX_EXPORT QgsMilXItem
{
  public:
    enum ControlPointState
    {
      HAVE_CONTROL_POINTS,
      NEED_CONTROL_POINTS_AND_INDICES,
      NEED_CONTROL_POINT_INDICES,
    };

    static bool validateMssString( const QString& mssString, QString &adjustedMssString, QString& messages );

    ~QgsMilXItem();
    void initialize( const QString& mssString, const QString& militaryName, const QList<QgsPoint> &points, const QList<int>& controlPoints = QList<int>(), const QList<QPair<int, double> > &attributes = QList< QPair<int, double> >(), const QPoint& userOffset = QPoint(), ControlPointState controlPointState = HAVE_CONTROL_POINTS, bool isCorridor = false );
    void initialize( const QString& mssString, const QString& militaryName, const QList<QgsPoint> &points, ControlPointState controlPointState )
    {
      initialize( mssString, militaryName, points, QList<int>(), QList<QPair<int, double> >(), QPoint(), controlPointState, false );
    }
    const QString& mssString() const { return mMssString; }
    const QString& militaryName() const { return mMilitaryName; }
    const QList<QgsPoint>& points() const { return mPoints; }
    QList<QPoint> screenPoints( const QgsMapToPixel& mapToPixel, const QgsCoordinateTransform *crst ) const;
    QList< QPair<int, double> > screenAttributes( const QgsMapToPixel& mapToPixel, const QgsCoordinateTransform *crst ) const;
    const QList<int>& controlPoints() const { return mControlPoints; }
    const QList< QPair<int, double> >& attributes() const { return mAttributes; }
    const QPoint& userOffset() const { return mUserOffset; }
    bool isMultiPoint() const { return mPoints.size() > 1 || !mAttributes.isEmpty(); }

    void writeMilx( QDomDocument& doc, QDomElement& graphicEl ) const;
    void readMilx( const QDomElement& graphicEl, const QgsCoordinateTransform *crst, int symbolSize );

  private:
    QString mMssString;
    QString mMilitaryName;
    QList<QgsPoint> mPoints; // Points as WGS84 coordinates
    QList< QPair<int, double> > mAttributes; // Attribute points as WGS84 coordinates
    QList<int> mControlPoints;
    QPoint mUserOffset; // In pixels
};


class QGS_MILX_EXPORT QgsMilXLayer : public QgsPluginLayer
{
    Q_OBJECT
  public:
    static QString layerTypeKey() { return "MilX_Layer"; }

    QgsMilXLayer( QgsLayerTreeViewMenuProvider *menuProvider, const QString& name = "MilX" );
    // This second variant is just because for some reason SIP mishandles QgsLayerTreeViewMenuProvider and the first variant is unusable from python...
    QgsMilXLayer( QgisInterface* iface, const QString& name = "MilX" );
    ~QgsMilXLayer();
    void addItem( QgsMilXItem* item );
    QgsMilXItem* takeItem( int idx ) { return mItems.takeAt( idx ); }
    const QList<QgsMilXItem*>& items() const { return mItems; }
    void setApproved( bool approved ) { mIsApproved = approved; emit approvedChanged( approved ); }
    bool isApproved() const { return mIsApproved; }
    QgsLegendSymbologyList legendSymbologyItems( const QSize& iconSize ) override;
    void exportToMilxly( QDomElement &milxLayerEl, int dpi );
    bool importMilxly( QDomElement &milxLayerEl, int dpi, QString &errorMsg );
    bool writeSymbology( QDomNode &/*node*/, QDomDocument& /*doc*/, QString& /*errorMessage*/ ) const override { return true; }
    bool readSymbology( const QDomNode &/*node*/, QString &/*errorMessage*/ ) override { return true; }
    QgsMapLayerRenderer* createMapRenderer( QgsRenderContext& rendererContext ) override;
    QgsRectangle extent() override;
    int margin() const override;

    bool testPick( const QgsPoint& mapPos, const QgsMapSettings& mapSettings, QVariant& pickResult, QRect &pickResultsExtent ) override;
    void handlePick( const QVariant& pick ) override;
    QVariantList getItems( const QgsRectangle& extent ) const override;
    void copyItems( const QVariantList& items, bool cut ) override;
    void deleteItems( const QVariantList& items ) override;

    void invalidateBillboards();

  signals:
    void symbolPicked( int symbolIdx );
    void copySymbols( QVector<int> symbolIndices );
    void approvedChanged( bool approved );

  protected:
    bool readXml( const QDomNode& layer_node ) override;
    bool writeXml( QDomNode & layer_node, QDomDocument & document ) override;

  private:
    class Renderer;

    QgsLayerTreeViewMenuProvider* mMenuProvider;
    QList<QgsMilXItem*> mItems;
    int mMargin;
    bool mIsApproved;
};

class QGS_MILX_EXPORT QgsMilXLayerType : public QgsPluginLayerType
{
  public:
    QgsMilXLayerType( QgsLayerTreeViewMenuProvider* menuProvider )
        : QgsPluginLayerType( QgsMilXLayer::layerTypeKey() ), mMenuProvider( menuProvider ) {}
    QgsPluginLayer* createLayer() override { return new QgsMilXLayer( mMenuProvider ); }
    int hasLayerProperties() const override { return 0; }

  private:
    QgsLayerTreeViewMenuProvider* mMenuProvider;
};

#endif // QGSMILXLAYER_H
