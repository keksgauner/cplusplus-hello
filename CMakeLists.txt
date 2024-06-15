cmake_minimum_required(VERSION 3.15)


# Setup vcpkg toolchain (note: should be placed before project() call)
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
endif()

project(Rest VERSION 0.1.0)

# cmake module
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# vcpkg dependencies
find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS beast)
find_package(Sqlpp11 REQUIRED COMPONENTS PostgreSQL)

find_path(JWT_CPP_INCLUDE_DIRS "jwt-cpp/base.h")


add_subdirectory(lib)
add_subdirectory(app)

#install(FILES files/icon.png DESTINATION files)