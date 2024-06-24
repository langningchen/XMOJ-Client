cmake_minimum_required(VERSION 3.10)
project(XMOJ-Client-Backend)

if(NOT DEFINED ENV{CC})
    message(FATAL_ERROR "Environment variable \"CC\" is not set")
endif()
find_program(PERL_EXECUTABLE perl REQUIRED COMMENT "Checking for Perl")
find_program(PYTHON_EXECUTABLE python REQUIRED COMMENT "Checking for Python")
function(CheckPythonModule ModuleName)
    execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import ${ModuleName}"
        RESULT_VARIABLE PIP_RESULT
        OUTPUT_QUIET
    )
    if(NOT PIP_RESULT EQUAL 0)
        message(WARNING "Python module ${ModuleName} not found, installing it")
        execute_process(COMMAND ${PYTHON_EXECUTABLE} -m pip install ${ModuleName}
            RESULT_VARIABLE PIP_RESULT
        )
        if(NOT PIP_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to install Python module ${ModuleName}")
        endif()
    endif()
endfunction()
CheckPythonModule(jsonschema)
CheckPythonModule(jinja2)
function(CheckSubmodule SubmoduleName)
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/${SubmoduleName}/CMakeLists.txt")
        message(FATAL_ERROR "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/${SubmoduleName}/CMakeLists.txt not found. Run `git submodule update --init --recursive` from the source tree to fetch the submodule contents.")
    endif()
endfunction()
CheckSubmodule(cpp-httplib)
CheckSubmodule(curl)
CheckSubmodule(json)
CheckSubmodule(libxml2)
CheckSubmodule(mbedtls)
CheckSubmodule(SQLiteCpp)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall)
add_compile_options("$<$<CONFIG:DEBUG>:-O0;-g>")
add_compile_options("$<$<CONFIG:RELEASE>:-O3;-s;-DNO_ASSERT>")
add_link_options("$<$<CONFIG:RELEASE>:-s>")

include_directories(Libraries)
include_directories(.)

set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
add_subdirectory(Libraries/SQLiteCpp)
include_directories(Libraries/SQLiteCpp/include)

set(LIBXML2_WITH_TESTS OFF CACHE BOOL "" FORCE)
set(LIBXML2_WITH_ICONV OFF CACHE BOOL "" FORCE)
add_subdirectory(Libraries/libxml2)
include_directories(Libraries/libxml2/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/Libraries/libxml2)

add_subdirectory(Libraries/json)
include_directories(Libraries/json/include)

set(GEN_FILES ON CACHE BOOL "" FORCE)
add_subdirectory(Libraries/mbedtls)
include_directories(Libraries/mbedtls/include)

set(CURL_USE_MBEDTLS ON CACHE BOOL "" FORCE)
set(MBEDTLS_INCLUDE_DIRS Libraries/mbedtls CACHE PATH "" FORCE)
set(MBEDTLS_LIBRARY ${CMAKE_BINARY_DIR}/Libraries/mbedtls/library/libmbedtls.a CACHE FILEPATH "" FORCE)
set(MBEDX509_LIBRARY ${CMAKE_BINARY_DIR}/Libraries/mbedtls/library/libmbedx509.a CACHE FILEPATH "" FORCE)
set(MBEDCRYPTO_LIBRARY ${CMAKE_BINARY_DIR}/Libraries/mbedtls/library/libmbedcrypto.a CACHE FILEPATH "" FORCE)
add_subdirectory(Libraries/curl)
include_directories(Libraries/curl/include)

set(LIBS
    SQLiteCpp
    libcurl
)

aux_source_directory(. SourceFiles)
aux_source_directory(API SourceFiles)
aux_source_directory(Classes SourceFiles)
aux_source_directory(Database SourceFiles)
aux_source_directory(Utilities SourceFiles)
add_executable(XMOJ-Client-Backend
    ${SourceFiles}
)

target_link_libraries(XMOJ-Client-Backend PRIVATE ${LIBS})
