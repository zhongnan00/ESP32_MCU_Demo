cmake_minimum_required(VERSION 3.13)
project(MyCppProject CXX)

set(CMAKE_CXX_STANDARD 17)

# Paths
set(CONFIG_HEADER "${CMAKE_CURRENT_BINARY_DIR}/include/config.h")
set(CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/.config")
set(KCONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Kconfig")

# Custom command: generate config.h from .config
add_custom_command(
    OUTPUT ${CONFIG_HEADER}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/include
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/gen_config_h.py ${CONFIG_FILE} ${CONFIG_HEADER}
    DEPENDS ${CONFIG_FILE} ${CMAKE_CURRENT_SOURCE_DIR}/gen_config_h.py
    COMMENT "Generating config.h from .config using Python"
)

# Build executable
add_executable(my_app main.cpp ${CONFIG_HEADER})
target_include_directories(my_app PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
