#
# Test TimeServer
#
# Copyright (C) 2020-2022, HENSOLDT Cyber GmbH
#

cmake_minimum_required(VERSION 3.7.2)

#-------------------------------------------------------------------------------
# use the SDK
find_package("os-sdk" REQUIRED)
os_sdk_set_defaults()
os_sdk_setup(CONFIG_FILE "system_config.h" CONFIG_PROJECT "system_config")


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

os_sdk_create_CAmkES_system("main.camkes")
