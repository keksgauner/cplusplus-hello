set(RestLib_SourceFiles
        include/Hello.h
        src/Hello.cpp)

add_library(RestLib ${RestLib_SourceFiles})

target_include_directories(RestLib
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(RestLib PRIVATE fmt::fmt fmt::fmt-header-only)
