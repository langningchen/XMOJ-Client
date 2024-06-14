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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s -DNO_ASSERT")
# set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_STANDARD 17)

include_directories(Libraries)
include_directories(.)

set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
add_subdirectory(Libraries/SQLiteCpp)
include_directories(Libraries/SQLiteCpp/include)

add_subdirectory(Libraries/htmlparser)

add_subdirectory(Libraries/json)
include_directories(Libraries/json/include)

set(GEN_FILES ON CACHE BOOL "" FORCE)
set(DISABLE_PACKAGE_CONFIG_AND_INSTALL OFF CACHE BOOL "" FORCE)
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
    mbedtls
    htmlparser
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
