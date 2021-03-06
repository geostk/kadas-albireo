IF(MSVC)
    SET(CRASHRPT_INCLUDE_DIR "" CACHE PATH "Path to CrashRpt headers")
    SET(CRASHRPT_LIBRARY "CrashRpt1403.lib" CACHE FILEPATH "Path to CrashRpt library")
ELSE(MSVC)
    SET(CRASHRPT_INCLUDE_DIR "" CACHE PATH "Path to CrashRpt headers")
    SET(CRASHRPT_LIBRARY "GdbCrashHandler" CACHE FILEPATH "Path to CrashRpt library")
ENDIF(MSVC)

SET(QGIS_APP_SRCS
  qgisapp.cpp
  qgsclassicapp.cpp
  qgisappinterface.cpp
  qgisappstylesheet.cpp
  qgsabout.cpp
  qgsapplayertreeviewmenuprovider.cpp
  qgssponsors.cpp
  qgsaddattrdialog.cpp
  qgsaddtaborgroup.cpp
  qgsaddjoindialog.cpp
  qgsattributeactiondialog.cpp
  qgsattributetypedialog.cpp
  qgsattributetabledialog.cpp
  qgsbookmarks.cpp
  qgsbrowserdockwidget.cpp
  qgsadvanceddigitizingdockwidget.cpp
  qgsadvanceddigitizingcanvasitem.cpp
  qgsconfigureshortcutsdialog.cpp
  qgscrashrpt.cpp
  qgscustomization.cpp
  qgscustomprojectiondialog.cpp
  qgsdecorationitem.cpp
  qgsdecorationcopyright.cpp
  qgsdecorationcopyrightdialog.cpp
  qgsdecorationnortharrow.cpp
  qgsdecorationnortharrowdialog.cpp
  qgsdecorationscalebar.cpp
  qgsdecorationscalebardialog.cpp
  qgsdecorationgrid.cpp
  qgsdecorationgriddialog.cpp
  qgsdxfexportdialog.cpp
  qgsdelattrdialog.cpp
  qgsdiagramproperties.cpp
  qgsdisplayangle.cpp
  qgsfieldcalculator.cpp
  qgsfieldsproperties.cpp
  qgsidentifyresultsdialog.cpp
  qgsfeatureaction.cpp
  qgsgpsrouteeditor.cpp
  qgsitemcouplingmanager.cpp
  qgsribbonlayertreeviewmenuprovider.cpp
  qgsribbonapp.cpp
  qgskmlexportdialog.cpp
  qgslabeldialog.cpp
  qgslabelpropertydialog.cpp
  qgslabelengineconfigdialog.cpp
  qgslabelinggui.cpp
  qgslabelpreview.cpp
  qgslegendgroupproperties.cpp
  qgsloadstylefromdbdialog.cpp
  qgsmaplayerstyleguiutils.cpp
  qgsmapmouseevent.cpp
  qgsprojecttemplateselectiondialog.cpp
  qgssavestyletodbdialog.cpp
  qgsguivectorlayertools.cpp
  qgsselectgrouplayerdialog.cpp
  qgscoordinatedisplayer.cpp
  qgscrsselection.cpp
  qgsmapcanvascontextmenu.cpp

  qgsmaptooladdfeature.cpp
  qgsmaptooladdpart.cpp
  qgsmaptooladdring.cpp
  qgsmaptoolfillring.cpp
  qgsmaptoolcapture.cpp
  qgsmaptoolchangelabelproperties.cpp
  qgsmaptooldeletering.cpp
  qgsmaptooldeletepart.cpp
  qgsmaptooledit.cpp
  qgsmaptoolfeatureaction.cpp
  qgsmaptoolformannotation.cpp
  qgsmaptoolhtmlannotation.cpp
  qgsmaptoolpinannotation.cpp
  qgsmaptoolpinlabels.cpp
  qgsmaptoolshowhidelabels.cpp
  qgsmaptoolidentifyaction.cpp
  qgsmaptoollabel.cpp
  qgsmaptooladvanceddigitizing.cpp
  qgsmaptoolmeasureangle.cpp
  qgsmaptoolmovefeature.cpp
  qgsmaptoolmovelabel.cpp
  qgsmaptooloffsetcurve.cpp
  qgsmaptoolreshape.cpp
  qgsmaptoolrotatefeature.cpp
  qgsmaptoolrotatelabel.cpp
  qgsmaptoolrotatepointsymbols.cpp
  qgsmaptoolselect.cpp
  qgsmaptoolselectrectangle.cpp
  qgsmaptoolselectfreehand.cpp
  qgsmaptoolselectpolygon.cpp
  qgsmaptoolselectradius.cpp
  qgsmaptoolselectutils.cpp
  qgsmaptoolsimplify.cpp
  qgsmaptoolsplitfeatures.cpp
  qgsmaptoolsplitparts.cpp
  qgsmaptoolsvgannotation.cpp
  qgsmaptooltextannotation.cpp
  qgsmaptoolsredlining.cpp
  qgsmaptoolhillshade.cpp
  qgsmaptoolslope.cpp
  qgsmaptoolviewshed.cpp

  nodetool/qgsmaptoolnodetool.cpp
  nodetool/qgsselectedfeature.cpp
  nodetool/qgsvertexentry.cpp
  nodetool/qgsnodeeditor.cpp

  qgsmeasuredialog.cpp
  qgsmeasureheightprofiledialog.cpp
  qgsmeasuretool.cpp
  qgsmeasuretoolv2.cpp
  qgsmeasurecircletool.cpp
  qgsmeasureheightprofiletool.cpp
  qgsmergeattributesdialog.cpp
  qgsoptions.cpp
  qgspointrotationitem.cpp
  qgspluginmetadata.cpp
  qgspluginregistry.cpp
  qgsprojectlayergroupdialog.cpp
  qgsprojectproperties.cpp
  qgsrastercalcdialog.cpp
  qgsrasterlayerproperties.cpp
  qgsredlining.cpp
  qgsredliningmanager.cpp
  qgsshortcutsmanager.cpp
  qgssnappingdialog.cpp
  qgsundowidget.cpp
  qgstipgui.cpp
  qgstipfactory.cpp
  qgsvectorlayerproperties.cpp
  qgsredlininglayerproperties.cpp
  qgsvisibilitypresets.cpp
  qgshandlebadlayers.cpp
  qgsmaptooladdcircularstring.cpp
  qgsmaptoolcircularstringcurvepoint.cpp
  qgsmaptoolcircularstringradius.cpp
  qgsvbsrasteridentify.cpp

  catalog/qgscatalogbrowser.cpp
  catalog/qgscatalogprovider.cpp
  catalog/qgsgeoadminrestcatalogprovider.cpp
  catalog/qgsarcgisrestcatalogprovider.cpp
  catalog/qgsvbscatalogprovider.cpp

  composer/qgsattributeselectiondialog.cpp
  composer/qgscomposer.cpp
  composer/qgscomposerarrowwidget.cpp
  composer/qgscomposerattributetablewidget.cpp
  composer/qgscomposerhtmlwidget.cpp
  composer/qgscomposeritemwidget.cpp
  composer/qgscomposerlabelwidget.cpp
  composer/qgscomposerpicturewidget.cpp
  composer/qgscomposermanager.cpp
  composer/qgscomposermapwidget.cpp
  composer/qgscomposerscalebarwidget.cpp
  composer/qgscomposershapewidget.cpp
  composer/qgscomposertablewidget.cpp
  composer/qgscomposerlegenditemdialog.cpp
  composer/qgscomposerlegendlayersdialog.cpp
  composer/qgscomposerlegendwidget.cpp
  composer/qgscompositionwidget.cpp
  composer/qgsatlascompositionwidget.cpp

  legend/qgsapplegendinterface.cpp

  ogr/qgsogrhelperfunctions.cpp
  ogr/qgsopenvectorlayerdialog.cpp
  ogr/qgsnewogrconnection.cpp
  ogr/qgsvectorlayersaveasdialog.cpp

  gps/qgsgpsinformationwidget.cpp

  openstreetmap/qgsosmdownloaddialog.cpp
  openstreetmap/qgsosmimportdialog.cpp
  openstreetmap/qgsosmexportdialog.cpp

  pluginmanager/qgspluginmanager.cpp
  pluginmanager/qgspluginmanager_texts.cpp
  pluginmanager/qgsapppluginmanagerinterface.cpp
  pluginmanager/qgspluginsortfilterproxymodel.cpp
  pluginmanager/qgspluginitemdelegate.cpp

  qgsnewspatialitelayerdialog.cpp
)

SET (QGIS_APP_MOC_HDRS
  qgisapp.h
  qgsclassicapp.h
  qgisappinterface.h
  qgisappstylesheet.h
  qgsabout.h
  qgsaddattrdialog.h
  qgsaddjoindialog.h
  qgsaddtaborgroup.h
  qgsattributeactiondialog.h
  qgsattributetypedialog.h
  qgsattributetabledialog.h
  qgsbookmarks.h
  qgsbrowserdockwidget.h
  qgsadvanceddigitizingdockwidget.h
  qgsconfigureshortcutsdialog.h
  qgscustomization.h
  qgscustomprojectiondialog.h
  qgsdecorationitem.h
  qgsdecorationcopyright.h
  qgsdecorationcopyrightdialog.h
  qgsdecorationnortharrow.h
  qgsdecorationnortharrowdialog.h
  qgsdecorationscalebar.h
  qgsdecorationscalebardialog.h
  qgsdecorationgrid.h
  qgsdecorationgriddialog.h
  qgsdelattrdialog.h
  qgsdiagramproperties.h
  qgsdisplayangle.h
  qgsdxfexportdialog.h
  qgsfeatureaction.h
  qgsfieldcalculator.h
  qgsfieldsproperties.h
  qgsgpsrouteeditor.h
  qgsguivectorlayertools.h
  qgsitemcouplingmanager.h
  qgscoordinatedisplayer.h
  qgscrsselection.h
  qgsmapcanvascontextmenu.h
  qgsmaptoolpinannotation.h
  qgsprojecttemplateselectiondialog.h

  qgsidentifyresultsdialog.h
  qgsribbonlayertreeviewmenuprovider.h
  qgsribbonapp.h
  qgskmlexportdialog.h
  qgslabeldialog.h
  qgslabelengineconfigdialog.h
  qgslabelinggui.h
  qgslabelpropertydialog.h
  qgslegendgroupproperties.h
  qgsloadstylefromdbdialog.h
  qgsmaplayerstyleguiutils.h
  qgssavestyletodbdialog.h
  qgsshortcutsmanager.h
  qgsapplayertreeviewmenuprovider.h
  qgsselectgrouplayerdialog.h

  qgsmaptooladdfeature.h
  qgsmaptoolcapture.h
  qgsmaptoolcircularstringradius.h
  qgsmaptooladdpart.h
  qgsmaptooladdring.h
  qgsmaptooledit.h
  qgsmaptoolfillring.h
  qgsmaptoolchangelabelproperties.h
  qgsmaptooldeletepart.h
  qgsmaptooldeletering.h
  qgsmaptoolfeatureaction.h
  qgsmaptoollabel.h
  qgsmaptoolpinlabels.h
  qgsmaptoolshowhidelabels.h
  qgsmaptoolidentifyaction.h
  qgsmaptooladvanceddigitizing.h
  qgsmaptoolmeasureangle.h
  qgsmaptoolmovefeature.h
  qgsmaptoolmovelabel.h
  qgsmaptooloffsetcurve.h
  qgsmaptoolreshape.h
  qgsmaptoolrotatefeature.h
  qgsmaptoolrotatelabel.h
  qgsmaptoolrotatepointsymbols.h
  qgsmaptoolselectfreehand.h
  qgsmaptoolselect.h
  qgsmaptoolselectpolygon.h
  qgsmaptoolselectradius.h
  qgsmaptoolselectrectangle.h
  qgsmaptoolsimplify.h
  qgsmaptoolsplitfeatures.h
  qgsmaptoolsplitparts.h
  qgsmaptoolsredlining.h
  qgsmaptooladdcircularstring.h
  qgsvbsrasteridentify.h

  qgsmaptoolhillshade.h
  qgsmaptoolslope.h
  qgsmaptoolviewshed.h

  nodetool/qgsmaptoolnodetool.h
  nodetool/qgsselectedfeature.h
  nodetool/qgsnodeeditor.h

  qgsmeasuredialog.h
  qgsmeasureheightprofiledialog.h
  qgsmeasuretool.h
  qgsmeasuretoolv2.h
  qgsmeasurecircletool.h
  qgsmeasureheightprofiletool.h
  qgsmergeattributesdialog.h
  qgsoptions.h
  qgsprojectlayergroupdialog.h
  qgsprojectproperties.h
  qgsrastercalcdialog.h
  qgsrasterlayerproperties.h
  qgsredlining.h
  qgsredliningmanager.h
  qgssnappingdialog.h
  qgssponsors.h
  qgstipgui.h
  qgstipfactory.h
  qgsundowidget.h
  qgsvectorlayerproperties.h
  qgsredlininglayerproperties.h
  qgsvisibilitypresets.h
  qgshandlebadlayers.h

  catalog/qgscatalogbrowser.h
  catalog/qgscatalogprovider.h
  catalog/qgsgeoadminrestcatalogprovider.h
  catalog/qgsarcgisrestcatalogprovider.h
  catalog/qgsvbscatalogprovider.h

  composer/qgsattributeselectiondialog.h
  composer/qgscomposer.h
  composer/qgscomposerarrowwidget.h
  composer/qgscomposerattributetablewidget.h
  composer/qgscomposerhtmlwidget.h
  composer/qgscomposeritemwidget.h
  composer/qgscomposerlabelwidget.h
  composer/qgscomposerlegendwidget.h
  composer/qgscomposermanager.h
  composer/qgscomposermapwidget.h
  composer/qgscomposerpicturewidget.h
  composer/qgscomposerscalebarwidget.h
  composer/qgscomposertablewidget.h
  composer/qgscomposershapewidget.h
  composer/qgscompositionwidget.h
  composer/qgsatlascompositionwidget.h

  legend/qgsapplegendinterface.h

  ogr/qgsopenvectorlayerdialog.h
  ogr/qgsnewogrconnection.h
  ogr/qgsvectorlayersaveasdialog.h

  gps/qgsgpsinformationwidget.h

  openstreetmap/qgsosmdownloaddialog.h
  openstreetmap/qgsosmimportdialog.h
  openstreetmap/qgsosmexportdialog.h

  pluginmanager/qgspluginmanager.h
  pluginmanager/qgsapppluginmanagerinterface.h
  pluginmanager/qgspluginsortfilterproxymodel.h
  pluginmanager/qgspluginitemdelegate.h

  qgsnewspatialitelayerdialog.h
  )

SET (WITH_QWTPOLAR TRUE CACHE BOOL "Determines whether QwtPolar should be built")

IF (WITH_QWTPOLAR)
  ADD_DEFINITIONS(-DWITH_QWTPOLAR)
  # Try to find QwtPolar on the system
  FIND_PACKAGE(QwtPolar)
  # If not found on the system, offer the possibility to build QwtPolar
  # internally
  IF(NOT FOUND_QwtPolar)
    SET(DEFAULT_WITH_INTERNAL_QWTPOLAR TRUE)
  ELSE(NOT FOUND_QwtPolar)
    SET(DEFAULT_WITH_INTERNAL_QWTPOLAR FALSE)
  ENDIF(NOT FOUND_QwtPolar)
  SET (WITH_INTERNAL_QWTPOLAR DEFAULT_WITH_INTERNAL_QWTPOLAR CACHE BOOL "Use internal build of QwtPolar")

  IF(WITH_INTERNAL_QWTPOLAR)
    IF(QWT_VERSION_STR VERSION_LESS "6.0.0")
      SET(QGIS_APP_SRCS
        ${QGIS_APP_SRCS}
        gps/qwtpolar-0.1/qwt_polar_canvas.cpp
        gps/qwtpolar-0.1/qwt_polar_curve.cpp
        gps/qwtpolar-0.1/qwt_polar_fitter.cpp
        gps/qwtpolar-0.1/qwt_polar_grid.cpp
        gps/qwtpolar-0.1/qwt_polar_itemdict.cpp
        gps/qwtpolar-0.1/qwt_polar_item.cpp
        gps/qwtpolar-0.1/qwt_polar_layout.cpp
        gps/qwtpolar-0.1/qwt_polar_magnifier.cpp
        gps/qwtpolar-0.1/qwt_polar_marker.cpp
        gps/qwtpolar-0.1/qwt_polar_panner.cpp
        gps/qwtpolar-0.1/qwt_polar_plot.cpp
        gps/qwtpolar-0.1/qwt_polar_point.cpp
        gps/qwtpolar-0.1/qwt_polar_spectrogram.cpp
      )

      SET (QGIS_APP_MOC_HDRS
        ${QGIS_APP_MOC_HDRS}
        gps/qwtpolar-0.1/qwt_polar_canvas.h
        gps/qwtpolar-0.1/qwt_polar_magnifier.h
        gps/qwtpolar-0.1/qwt_polar_panner.h
        gps/qwtpolar-0.1/qwt_polar_plot.h
      )

      SET(QWTPOLAR_INCLUDE_DIR gps/qwtpolar-0.1)
    ELSE(QWT_VERSION_STR VERSION_LESS "6.0.0")
    SET(QGIS_APP_SRCS
      ${QGIS_APP_SRCS}
      gps/qwtpolar-1.1.1/qwt_polar_canvas.cpp
      gps/qwtpolar-1.1.1/qwt_polar_curve.cpp
      gps/qwtpolar-1.1.1/qwt_polar_fitter.cpp
      gps/qwtpolar-1.1.1/qwt_polar_grid.cpp
      gps/qwtpolar-1.1.1/qwt_polar_item.cpp
      gps/qwtpolar-1.1.1/qwt_polar_itemdict.cpp
      gps/qwtpolar-1.1.1/qwt_polar_layout.cpp
      gps/qwtpolar-1.1.1/qwt_polar_magnifier.cpp
      gps/qwtpolar-1.1.1/qwt_polar_marker.cpp
      gps/qwtpolar-1.1.1/qwt_polar_panner.cpp
      gps/qwtpolar-1.1.1/qwt_polar_picker.cpp
      gps/qwtpolar-1.1.1/qwt_polar_plot.cpp
      gps/qwtpolar-1.1.1/qwt_polar_renderer.cpp
      gps/qwtpolar-1.1.1/qwt_polar_spectrogram.cpp
    )

    SET (QGIS_APP_MOC_HDRS
      ${QGIS_APP_MOC_HDRS}
      gps/qwtpolar-1.1.1/qwt_polar_canvas.h
      gps/qwtpolar-1.1.1/qwt_polar_magnifier.h
      gps/qwtpolar-1.1.1/qwt_polar_panner.h
      gps/qwtpolar-1.1.1/qwt_polar_picker.h
      gps/qwtpolar-1.1.1/qwt_polar_plot.h
      gps/qwtpolar-1.1.1/qwt_polar_renderer.h
    )

      SET(QWTPOLAR_INCLUDE_DIR gps/qwtpolar-1.1.1)
    ENDIF(QWT_VERSION_STR VERSION_LESS "6.0.0")

    SET(QWTPOLAR_LIBRARY "")
  ENDIF(WITH_INTERNAL_QWTPOLAR)
ENDIF(WITH_QWTPOLAR)

IF (POSTGRES_FOUND)
  IF(HAVE_PGCONFIG)
    ADD_DEFINITIONS(-DHAVE_PGCONFIG=1)
  ENDIF(HAVE_PGCONFIG)
ENDIF (POSTGRES_FOUND)

SET(IMAGE_RCCS ../../images/images.qrc)

QT4_ADD_RESOURCES(IMAGE_RCC_SRCS ${IMAGE_RCCS})

# add test resources, e.g. standard test font
SET(TEST_RCCS ../../tests/testdata/testdata.qrc)
QT4_ADD_RESOURCES(TEST_RCC_SRCS ${TEST_RCCS})

QT4_WRAP_CPP(QGIS_APP_MOC_SRCS ${QGIS_APP_MOC_HDRS})

IF(PEDANTIC)
  # disable deprecation warnings
  IF(MSVC)
    SET_SOURCE_FILES_PROPERTIES(
        qgisappinterface.cpp
        ${CMAKE_BINARY_DIR}/src/app/moc_qgisappinterface.cxx
    PROPERTIES COMPILE_FLAGS "/wd4996"
    )
  ELSE(MSVC)
    SET_SOURCE_FILES_PROPERTIES(
        qgisappinterface.cpp
        ${CMAKE_BINARY_DIR}/src/app/moc_qgisappinterface.cxx
        PROPERTIES COMPILE_FLAGS "-Wno-deprecated-declarations"
    )
  ENDIF(MSVC)
ENDIF(PEDANTIC)

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR} composer legend pluginmanager
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/../ui
  ${QWT_INCLUDE_DIR}
  ${QT_QTUITOOLS_INCLUDE_DIR}
  ${QSCINTILLA_INCLUDE_DIR}
  ${QEXTSERIALPORT_INCLUDE_DIR}
  ../analysis/raster
  ../analysis/openstreetmap
  ../core
  ../core/gps
  ../core/composer
  ../core/dxf
  ../core/geometry
  ../core/layertree
  ../core/raster
  ../core/symbology-ng
  ../gui
  ../gui/symbology-ng
  ../gui/attributetable
  ../gui/raster
  ../gui/editorwidgets
  ../gui/editorwidgets/core
  ../gui/layertree
  ../plugins
  ../python
  gps
  openstreetmap
  ${SPATIALITE_INCLUDE_DIR}
  ${SQLITE3_INCLUDE_DIR}
  ${PROJ_INCLUDE_DIR}
  ${GEOS_INCLUDE_DIR}
  ${GDAL_INCLUDE_DIR}
  ${QWTPOLAR_INCLUDE_DIR}
  ${CRASHRPT_INCLUDE_DIR}
  ${QJSON_INCLUDE_DIR}
  ${QUAZIP_INCLUDE_DIR}
  )

IF(ENABLE_MODELTEST)
  INCLUDE_DIRECTORIES(../../tests/qt_modeltest)
ENDIF(ENABLE_MODELTEST)

IF (ANDROID)
  INCLUDE_DIRECTORIES(${ANDROID_NDK_TOOLCHAIN_ROOT}/sysroot/usr/include)
ENDIF (ANDROID)

IF (POSTGRES_FOUND)
  INCLUDE_DIRECTORIES(${POSTGRES_INCLUDE_DIR})
ENDIF (POSTGRES_FOUND)

#############
IF (ANDROID)
  ADD_LIBRARY(${QGIS_APP_NAME} SHARED main.cpp ${QGIS_APP_SRCS} ${QGIS_APP_MOC_SRCS} ${QGIS_APP_HDRS} ${QGIS_APP_MOC_HDRS} ${IMAGE_RCC_SRCS} ${TEST_RCC_SRCS})
ELSEIF(MSVC)
  SET (QGIS_APP_SRCS ${QGIS_APP_SRCS} main.cpp)
  ADD_EXECUTABLE(${QGIS_APP_NAME} WIN32 mainwin.cpp ${CMAKE_CURRENT_SOURCE_DIR}/qgis_win32.rc)
ELSE()
  IF(MINGW)
    ENABLE_LANGUAGE(RC)
    SET(CMAKE_RC_COMPILER_INIT ${CMAKE_GENERATOR_RC})
    SET(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> -O coff -i <SOURCE> -o <OBJECT>")
    SET(QGIS_RC_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/qgis_win32.rc)
  ENDIF(MINGW)
  ADD_EXECUTABLE(${QGIS_APP_NAME} MACOSX_BUNDLE WIN32 main.cpp ${QGIS_RC_SRCS} ${IMAGE_RCC_SRCS} ${TEST_RCC_SRCS})
ENDIF()

QT4_WRAP_CPP(tst_moc_srcs maprenderertest.h)
ADD_EXECUTABLE(maprenderertest maprenderertest.cpp ${tst_moc_srcs})
TARGET_LINK_LIBRARIES(maprenderertest qgis_core qgis_gui)

IF (WIN32)
  IF (MSVC)
    ADD_DEFINITIONS("-DAPP_EXPORT=${DLLEXPORT}")
    ADD_DEFINITIONS("\"-DSPLASH_IMPORT=__declspec(dllimport)\"")
  ELSE (MSVC)
    ADD_DEFINITIONS("-UAPP_EXPORT \"-DAPP_EXPORT=${DLLEXPORT}\"")
    ADD_DEFINITIONS("-USPLASH_IMPORT \"-DSPLASH_IMPORT=__declspec(dllimport)\"")
  ENDIF (MSVC)
ELSE(WIN32)
  ADD_DEFINITIONS("-DAPP_EXPORT=")
ENDIF (WIN32)

# shared library used by tests - TODO: use it also for qgis executable?
ADD_LIBRARY(qgis_app SHARED ${QGIS_APP_SRCS} ${QGIS_APP_MOC_SRCS} ${QGIS_APP_HDRS} ${QGIS_APP_MOC_HDRS} ${IMAGE_RCC_SRCS})

TARGET_LINK_LIBRARIES(qgis_app
  ${QWT_LIBRARY}
  ${QT_QTSQL_LIBRARY}
  ${QT_QTUITOOLS_LIBRARY}
  ${QT_QTWEBKIT_LIBRARY}
  #should only be needed for win
  ${QT_QTMAIN_LIBRARY}
  ${QWTPOLAR_LIBRARY}
  ${GDAL_LIBRARY}
  qgis_core
  qgis_gui
  qgis_analysis
  qgis_splash
  ${CRASHRPT_LIBRARY}
  ${QJSON_LIBRARIES}
  ${QUAZIP_LIBRARIES}

)

IF (APPLE)
  TARGET_LINK_LIBRARIES(qgis_app ${APP_SERVICES_LIBRARY})
ENDIF(APPLE)

if(MSVC AND CMAKE_SIZEOF_VOID_P EQUAL 8)
  SET_TARGET_PROPERTIES(qgis_app PROPERTIES STATIC_LIBRARY_FLAGS "/machine:x64")
ENDIF(MSVC AND CMAKE_SIZEOF_VOID_P EQUAL 8)

IF(NOT MSVC)
  TARGET_LINK_LIBRARIES(${QGIS_APP_NAME} qgis_app)
ENDIF(NOT MSVC)

IF (ANDROID)
  TARGET_LINK_LIBRARIES(${QGIS_APP_NAME} log)
ENDIF (ANDROID)

IF(MSVC)
  ADD_DEFINITIONS(-DQWT_DLL)
  TARGET_LINK_LIBRARIES(${QGIS_APP_NAME} DbgHelp)
  TARGET_LINK_LIBRARIES(qgis_app DbgHelp)
ENDIF(MSVC)

IF (APPLE)
  TARGET_LINK_LIBRARIES(${QGIS_APP_NAME} ${APP_SERVICES_LIBRARY} )

  SET_TARGET_PROPERTIES(${QGIS_APP_NAME} PROPERTIES
    INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${QGIS_LIB_DIR}
    INSTALL_RPATH_USE_LINK_PATH true
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/mac/app.info.plist.in")
ENDIF(APPLE)

IF (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
  FIND_LIBRARY(EXECINFO_LIBRARY NAMES execinfo)
  TARGET_LINK_LIBRARIES(${QGIS_APP_NAME} ${EXECINFO_LIBRARY})
ENDIF (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")

IF (POSTGRES_FOUND)
  TARGET_LINK_LIBRARIES (${QGIS_APP_NAME} ${POSTGRES_LIBRARY})
ENDIF (POSTGRES_FOUND)

IF(MSVC)
  INSTALL(FILES qgis.ico DESTINATION ${CMAKE_INSTALL_PREFIX}/icons)
ENDIF(MSVC)

INSTALL(TARGETS qgis_app
  BUNDLE DESTINATION ${QGIS_INSTALL_PREFIX}
  RUNTIME DESTINATION ${QGIS_BIN_DIR}
  LIBRARY DESTINATION ${QGIS_LIB_DIR}
  ARCHIVE DESTINATION ${QGIS_LIB_DIR}
  FRAMEWORK DESTINATION ${QGIS_FW_SUBDIR}
  PUBLIC_HEADER DESTINATION ${QGIS_INCLUDE_DIR})

INSTALL(TARGETS ${QGIS_APP_NAME}
  BUNDLE DESTINATION ${QGIS_INSTALL_PREFIX}
  RUNTIME DESTINATION ${QGIS_BIN_DIR}
  LIBRARY DESTINATION ${QGIS_LIB_DIR}
  ARCHIVE DESTINATION ${QGIS_LIB_DIR}
  FRAMEWORK DESTINATION ${QGIS_FW_SUBDIR}
  PUBLIC_HEADER DESTINATION ${QGIS_INCLUDE_DIR})
  

IF (APPLE)
  INSTALL(CODE "EXECUTE_PROCESS(COMMAND /bin/echo -n \"APPLQGIS\" OUTPUT_FILE \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/../PkgInfo\")")
ENDIF (APPLE)
