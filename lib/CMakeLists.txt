set(RESTLIB_CURRENT_SOURCE
        include/Hello.h
        src/Hello.cpp)

add_library(RestLib ${RESTLIB_CURRENT_SOURCE})

target_include_directories(RestLib
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${JWT_CPP_INCLUDE_DIRS}
        ${SQLPP11_INCLUDE_DIRS}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_include_directories(RestLib PRIVATE ${JWT_CPP_INCLUDE_DIRS})

target_link_libraries(RestLib PRIVATE fmt::fmt fmt::fmt-header-only Boost::beast)