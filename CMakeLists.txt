cmake_minimum_required(VERSION 3.21)
project(TrafficRacer)

set(CMAKE_CXX_STANDARD 17)

set(SFML_INCLUDE_DIR "./SFML/include")
set(SFML_LIBRARY_DIR "./SFML/build/lib")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(TrafficRacer main.cpp traffic_racer/engine.cpp traffic_racer/engine.h traffic_racer/state_machine.cpp traffic_racer/state_machine.h traffic_racer/state.cpp traffic_racer/state.h traffic_racer/intro_state.cpp traffic_racer/intro_state.h traffic_racer/menu_state.cpp traffic_racer/menu_state.h)
target_link_libraries (TrafficRacer sfml-graphics sfml-window sfml-system)

# Install executable
install(TARGETS TrafficRacer
        RUNTIME DESTINATION .)

# Install game data
install(DIRECTORY bin/img
        DESTINATION .)

# /opt/homebrew/bin/zsh