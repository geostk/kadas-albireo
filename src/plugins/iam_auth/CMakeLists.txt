########################################################
# Files

SET (iamauth_SRCS
  qgsiamauth.cpp
)

SET (iamauth_HDRS
  iamauth_plugin.h
  webaxwidget.h
)

SET (iamauth_MOC_HDRS
  qgsiamauth.h
)

SET (iamauth_UIS
)

SET (iamauth_RCCS
  qgsiamauth.qrc
)

########################################################
# Build

IF(ENABLE_QT5)
	FIND_PACKAGE(Qt5AxContainer REQUIRED)
	SET(QT_QAXCONTAINER_LIBRARY ${Qt5AxContainer_LIBRARIES})
ENDIF(ENABLE_QT5)

QT4_WRAP_UI (iamauth_UIS_H  ${iamauth_UIS})

QT4_WRAP_CPP (iamauth_MOC_SRCS  ${iamauth_MOC_HDRS})

QT4_ADD_RESOURCES(iamauth_RCC_SRCS ${iamauth_RCCS})

ADD_LIBRARY (iamauth   SHARED ${iamauth_SRCS} ${iamauth_HDRS} ${iamauth_MOC_SRCS} ${iamauth_RCC_SRCS} ${iamauth_UIS_H})

INCLUDE_DIRECTORIES(
     ${CMAKE_CURRENT_BINARY_DIR}
     ${CMAKE_BINARY_DIR}/src/ui
     ${QJSON_INCLUDE_DIR}
     ${QUAZIP_INCLUDE_DIR}
     ${GDAL_INCLUDE_DIR}
     ${RSVGRENDERER_INCLUDE_DIR}
     ../../analysis
     ../../core
     ../../core/raster
     ../../core/geometry
     ../../gui
     ../
)

IF(WIN32)
    ADD_DEFINITIONS("\"-DQGS_IAM_EXPORT=${DLLEXPORT}\"")
ELSE(WIN32)
    ADD_DEFINITIONS("-DQGS_IAM_EXPORT=")
ENDIF(WIN32)

IF(MINGW)
  IF(ENABLE_QT5)
    SET(QT_QAXCONTAINER_LIBRARY "-Wl,-Bstatic -lQt5AxContainer -lQt5AxBase -Wl,-Bdynamic")
  ELSE(ENABLE_QT5)
    SET(QT_QAXCONTAINER_LIBRARY "-Wl,-Bstatic -lQAxContainer4 -Wl,-Bdynamic")
  ENDIF(ENABLE_QT5)
ENDIF(MINGW)

TARGET_LINK_LIBRARIES(iamauth
  qgis_core
  qgis_gui
  qgis_analysis
  ${QT_QAXCONTAINER_LIBRARY}
)

########################################################
# Install

INSTALL(TARGETS iamauth
  RUNTIME DESTINATION ${QGIS_PLUGIN_DIR}
  LIBRARY DESTINATION ${QGIS_PLUGIN_DIR})
