get_property(EXISTS GLOBAL PROPERTY _JSONCPP_INCLUDED)
if(EXISTS)
    return()
endif()


find_package(JSONCPP 1.6.2)
set_package_properties(JSONCPP PROPERTIES TYPE OPTIONAL)

if (JSONCPP_FOUND)
    set_package_properties(JSONCPP PROPERTIES TYPE OPTIONAL)
    mark_as_advanced(CLEAR JSONCPP_INCLUDE_DIR)
    mark_as_advanced(CLEAR JSONCPP_LIBRARY)
    include_directories(${JSONCPP_INCLUDE_DIR})
    set(PDAL_JSONCPP_LIB_NAME ${JSONCPP_LIBRARY})
    set(PDAL_JSONCPP_INCLUDE_DIR ${JSONCPP_INCLUDE_DIR})
    set(JSON_CPP_LINK_TYPE PUBLIC)
    set(PDAL_HAVE_JSONCPP 1)
else()
    set(PDAL_JSONCPP_LIB_NAME pdal_jsoncpp)
    set(PDAL_JSONCPP_INCLUDE_DIR ${PDAL_VENDOR_DIR}/jsoncpp-1.6.2/dist)
    set(PDAL_JSONCPP_SRC ${PDAL_JSONCPP_INCLUDE_DIR}/jsoncpp.cpp)
    set(JSON_CPP_LINK_TYPE PRIVATE)
endif()

set_property(GLOBAL PROPERTY _JSONCPP_INCLUDED TRUE)