set(RESTLIB_CURRENT_SOURCE
        include/Hello.h
        src/Hello.cpp)

add_library(RestLib ${RESTLIB_CURRENT_SOURCE})

target_include_directories(RestLib
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(RestLib PRIVATE fmt::fmt fmt::fmt-header-only)
target_link_libraries(RestLib PRIVATE Boost::boost)
target_link_libraries(RestLib PRIVATE jwt-cpp::jwt-cpp)
target_link_libraries(RestLib PRIVATE sqlpp11::sqlpp11 sqlpp11::mysql)
