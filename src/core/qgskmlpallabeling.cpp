#include "qgskmlpallabeling.h"
#include "qgspalgeometry.h"

#include "pal/pointset.h"
#include "pal/labelposition.h"

QgsKMLPalLabeling::QgsKMLPalLabeling( QTextStream* outStream, const QgsRectangle& bbox, double scale, QGis::UnitType mapUnits ): mOutStream( outStream )
{
    mSettings = new QgsMapSettings;
    mSettings->setMapUnits( mapUnits );
    mSettings->setExtent( bbox );

    //todo: unify with QgsDXFLabelingEngine
    int dpi = 96;
    double factor = 1000 * dpi / scale / 25.4 * QGis::fromUnitToUnitFactor( mapUnits, QGis::Meters );
    mSettings->setOutputSize( QSize( bbox.width() * factor, bbox.height() * factor ) );
    mSettings->setOutputDpi( dpi );
    mSettings->setCrsTransformEnabled( false );
    init( *mSettings );

    mImage = new QImage( 10, 10, QImage::Format_ARGB32_Premultiplied );
    mImage->setDotsPerMeterX( 96 / 25.4 * 1000 );
    mImage->setDotsPerMeterY( 96 / 25.4 * 1000 );
    mPainter = new QPainter( mImage );
    mRenderContext.setPainter( mPainter );
    mRenderContext.setRendererScale( scale );
    mRenderContext.setExtent( bbox );
    mRenderContext.setScaleFactor( 96.0 / 25.4 );
    mRenderContext.setMapToPixel( QgsMapToPixel( 1.0 / factor, bbox.xMinimum(), bbox.yMinimum(), bbox.height() * factor ) );
}

QgsKMLPalLabeling::~QgsKMLPalLabeling()
{
    delete mPainter;
    delete mImage;
    delete mSettings;
}

void QgsKMLPalLabeling::drawLabel( pal::LabelPosition* label, QgsRenderContext& context, QgsPalLayerSettings& tmpLyr, DrawLabelType drawType, double dpiRatio )
{
    if( !mOutStream )
    {
        return;
    }

    QgsPalGeometry *g = dynamic_cast< QgsPalGeometry* >( label->getFeaturePart()->getUserGeometry() );
    if( !g )
    {
        return;
    }

    (*mOutStream) << QString( "<Placemark><name>%1</name><Style><LabelStyle><color>%2</color></LabelStyle></Style><Point><coordinates>%3,%4</coordinates></Point><Placemark>" )
                     .arg(  g->text( label->getPartId() ) ).arg("#ff0000"/*color*/).arg( QString::number( label->getX() ) ).arg( QString::number( label->getX() ) );
    (*mOutStream) << "\n";
}