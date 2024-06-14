cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(DeePay-Backend)

set(CMAKE_CXX_STANDARD 17)


# vcpkg dependencies
find_package(fmt CONFIG REQUIRED)

add_subdirectory(lib)
add_subdirectory(app)

