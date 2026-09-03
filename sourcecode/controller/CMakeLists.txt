set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets)

add_library(ControllerLib 
            GameController.h 
            GameController.cpp
            LevelManager.h
            LevelManager.cpp)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED )
target_include_directories(ControllerLib PUBLIC 
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ../engine/)
target_link_libraries(ControllerLib PUBLIC 
                        ${REQUIRED_LIBS_QUALIFIED}
                        ../engine/TMLib)