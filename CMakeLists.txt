cmake_minimum_required(VERSION 3.14)
project(UNOGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(include)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/Card.cpp
    ${CMAKE_SOURCE_DIR}/src/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/PlayerDeck.cpp
    ${CMAKE_SOURCE_DIR}/src/DrawDeck.cpp
    ${CMAKE_SOURCE_DIR}/src/DiscardPile.cpp
    ${CMAKE_SOURCE_DIR}/src/Playloop.cpp
    ${CMAKE_SOURCE_DIR}/src/UNOGame.cpp
)

add_executable(cardgame
${CMAKE_SOURCE_DIR}/src/main.cpp
${SOURCES}
)

add_custom_target(run
COMMAND $<TARGET_FILE:cardgame>
DEPENDS cardgame
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
USES_TERMINAL
)

# Add Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(tests)