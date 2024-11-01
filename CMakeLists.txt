cmake_minimum_required(VERSION 3.15)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(lab4 VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

add_executable(lab4_project lab4.cpp allocator.h SeqCont.cpp SeqCont.h factorial.h)
add_library(lab4 lib.cpp)

set_target_properties(lab4_project lab4  PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(lab4
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(lab4_project PRIVATE
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
