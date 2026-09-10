cmake_minimum_required(VERSION 3.20)
project(fractal_explorer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optimize aggressively
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -mtune=native -flto")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fsanitize=address,undefined -fno-omit-frame-pointer")

# Find zlib for PNG output
find_package(ZLIB REQUIRED)

# Sources
set(SOURCES
    src/main.cpp
    src/image.cpp
    src/color.cpp
    src/fractal.cpp
    src/renderer.cpp
)

set(HEADERS
    include/image.hpp
    include/complex.hpp
    include/color.hpp
    include/fractal.hpp
    include/renderer.hpp
)

add_executable(fractal_explorer ${SOURCES} ${HEADERS})
target_include_directories(fractal_explorer PRIVATE include)

# Link zlib (PNG output) and pthread (async)
target_link_libraries(fractal_explorer PRIVATE ZLIB::ZLIB pthread)

# Install target
install(TARGETS fractal_explorer DESTINATION bin)