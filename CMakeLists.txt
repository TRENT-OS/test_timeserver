#
# Test TimeServer
#
# Copyright (C) 2020-2021, HENSOLDT Cyber GmbH
#

cmake_minimum_required(VERSION 3.7.2)

os_set_config_file(system_config.h)


#-------------------------------------------------------------------------------
project(system_config C)
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})


#-------------------------------------------------------------------------------
project(tests_timeserver C)

TimeServer_DeclareCAmkESComponent(
    TimeServer
)

DeclareCAmkESComponent(
    Ticker
    SOURCES
        components/Ticker/Ticker.c
    C_FLAGS
        -Wall
        -Werror
    LIBS
        os_core_api
        lib_compiler
        lib_debug
        TimeServer_client
)

DeclareCAmkESComponent(
    Worker
    SOURCES
        components/Worker/Worker.c
    C_FLAGS
        -Wall
        -Werror
    LIBS
        lib_debug
)

DeclareAndCreateCamkESSystem(main.camkes)
GenerateSimulateScript()
