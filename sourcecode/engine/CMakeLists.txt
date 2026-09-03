add_library(TMLib 
    Symbol.h
    Tape.cpp
    Tape.h
    TuringMachine.cpp
    TuringMachine.h
    Transitions.h
    Transitionresults.h
    Puzzlelevel.h
    Puzzlelevel.cpp
)

target_include_directories(TMLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

