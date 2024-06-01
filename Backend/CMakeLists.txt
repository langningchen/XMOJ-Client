cmake_minimum_required(VERSION 3.9)
project(XMOJ-Client)

if(NOT DEFINED ENV{CC})
    message(FATAL_ERROR "Environment variable \"CC\" is not set")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s -DNO_ASSERT")
# set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_STANDARD 17)
set(PERL_EXECUTABLE perl CACHE FILEPATH "" FORCE)
include_directories(Libraries)
include_directories(.)

set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
add_subdirectory(Libraries/SQLiteCpp)
include_directories(Libraries/SQLiteCpp/include)

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
    mbedtls
)

aux_source_directory(. SourceFiles)
aux_source_directory(API SourceFiles)
aux_source_directory(Classes SourceFiles)
aux_source_directory(Database SourceFiles)
aux_source_directory(Utilities SourceFiles)
add_executable(XMOJ-Client
    ${SourceFiles}
)

target_link_libraries(XMOJ-Client PRIVATE ${LIBS})
