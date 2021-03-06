cmake_minimum_required (VERSION 3.14)

project (oop2_project_akiva_stern)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options (/permissive-)
endif ()

add_executable (oop2_project_akiva_stern WIN32 "")

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources)


set (SFML_STATIC_LIBRARIES TRUE)
set (SFML_DIR "C:/SFML/SFML-2.5.1/lib/cmake/SFML")

find_package (SFML 2.5 COMPONENTS graphics REQUIRED)
find_package (SFML 2.5 COMPONENTS audio graphics REQUIRED)

set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

target_link_libraries (oop2_project_akiva_stern sfml-graphics sfml-main)
target_link_libraries (oop2_project_akiva_stern sfml-graphics sfml-audio sfml-main)