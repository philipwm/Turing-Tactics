
add_executable(tmgame main.cpp)
target_link_libraries(tmgame 
PUBLIC
    UiLib 
    ControllerLib 
    TMLib
)

target_include_directories(tmgame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../engine/
                                        ${CMAKE_CURRENT_SOURCE_DIR}/../controller/
                                        ${CMAKE_CURRENT_SOURCE_DIR}/../ui/
                                        ${CMAKE_CURRENT_SOURCE_DIR}
)
