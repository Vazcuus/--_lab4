cmake_minimum_required(VERSION 3.15)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(lab4 VERSION ${PROJECT_VESRION})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(lab4_project lab4.cpp allocator.h SeqCont.cpp SeqCont.h factorial.h)
add_executable(test_version test_version.cpp)
add_library(lab4 lib.cpp)

set_target_properties(lab4_project lab4 test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_include_directories(lab4
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(lab4_project PRIVATE
    lab4
)
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    lab4
)




install(TARGETS lab4_project RUNTIME DESTINATION bin)

if (APPLE)
    set(CPACK_GENERATOR ZIP)
else()
    set(CPACK_GENERATOR DEB)
endif()



set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

enable_testing()

add_test(test_version test_version)
