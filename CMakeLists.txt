#
# Test TimeServer
#
# Copyright (C) 2020, Hensoldt Cyber GmbH
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
        os_libs
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
        #os_core_api
        os_libs
)

DeclareAndCreateCamkESSystem(main.camkes)
GenerateSimulateScript()
