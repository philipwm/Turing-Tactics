set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

add_library(UiLib  MainWindow.h 
                   MainWindow.cpp 
                   TapeViewWidget.h 
                   TapeViewWidget.cpp 
)


target_include_directories(UiLib 
PUBLIC
      ../controller/
      ../engine/
      ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(UiLib 
PUBLIC
     ${REQUIRED_LIBS_QUALIFIED}
     ControllerLib
)  
 