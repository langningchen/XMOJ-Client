cmake_minimum_required(VERSION 3.10)
project(XMOJ-Client-Frontend)

find_program(NPM_EXECUTABLE npm)
find_program(NPX_EXECUTABLE npx)

add_custom_target(XMOJ-Client-Frontend-Install
    COMMAND ${NPM_EXECUTABLE} install
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Installing Frontend dependencies"
)

add_custom_target(XMOJ-Client-Frontend
    COMMAND ${NPX_EXECUTABLE} webpack
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Building Frontend"
    DEPENDS XMOJ-Client-Frontend-Install
)

add_custom_command(TARGET XMOJ-Client-Frontend
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Frontend built successfully"
)