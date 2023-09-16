install(TARGETS ${PROJECT_NAME} DESTINATION bin)

if(NOT WIN32)
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/qt.conf
        "[Paths]\n"
        "Prefix = ..\n"
        "Plugins = lib\n"
        "Library = lib\n"
        "Qml2Imports = qml"
    )
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/run.sh "#!/bin/sh\nLD_LIBRARY_PATH=lib bin/cmake_project \"$@\"")
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qt.conf DESTINATION bin)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/run.sh DESTINATION .)
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(DEBUG_INSTALL_SUFFIX "\.debug")
else()
    set(DEBUG_INSTALL_EXCLUDE "*debug")
endif()

if(NOT USE_EXTERNAL_QT)
    set(QT_INSTALL_LIBS "(Concurrent|Core|Gui|Network|OpenGL|PrintSupport|Qml|QmlModels|QmlWorkerScript|Quick|QuickControls2|QuickParticles|QuickShapes|QuickTemplates2|QuickWidgets|SerialPort|Sql|Svg|VirtualKeyboard|WebSockets|Widgets|XcbQpa)")
endif()


if(WIN32)
    install(DIRECTORY ${QT_DIR}/bin/ DESTINATION bin
    FILES_MATCHING
        REGEX "${Qt}${QT_INSTALL_LIBS}.dll"
        PATTERN "cmake" EXCLUDE
        PATTERN "metatypes" EXCLUDE
        PATTERN "${DEBUG_INSTALL_EXCLUDE}" EXCLUDE
    )
    install(DIRECTORY ${QML_IMPORT_PATH}/
        DESTINATION qml
        USE_SOURCE_PERMISSIONS
    )

    install(FILES ${QT_PLUGINS_PATH}/platforms/qwindows.dll
        DESTINATION bin/plugins/platforms)
else()
    install(DIRECTORY ${QT_DIR}/lib/ DESTINATION lib
    FILES_MATCHING
        REGEX "lib.*${QT_INSTALL_LIBS}.so.*${DEBUG_INSTALL_SUFFIX}"
        PATTERN "cmake" EXCLUDE
        PATTERN "metatypes" EXCLUDE
        PATTERN "${DEBUG_INSTALL_EXCLUDE}" EXCLUDE
    )
    install(DIRECTORY ${QML_IMPORT_PATH}/
        DESTINATION qml
        USE_SOURCE_PERMISSIONS
    )

    install(FILES ${QT_PLUGINS_PATH}/platforms/libqxcb.so
        DESTINATION lib/platforms)
    install(FILES ${QT_PLUGINS_PATH}/xcbglintegrations/libqxcb-glx-integration.so
        DESTINATION lib/xcbglintegrations)
    install(FILES ${QT_PLUGINS_PATH}/sqldrivers/libqsqlite.so
        DESTINATION lib/sqldrivers)
    install(FILES ${QT_PLUGINS_PATH}/imageformats/libqsvg.so
        DESTINATION lib/imageformats)
    install(FILES ${QT_PLUGINS_PATH}/platforminputcontexts/libqtvirtualkeyboardplugin.so
        DESTINATION lib/platforminputcontexts)
endif()