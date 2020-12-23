/*
 *  Worker component that creates additional load for the system
 *
 *  Copyright (C) 2019, Hensoldt Cyber GmbH
 *
 */

#include "lib_debug/Debug.h"
#include <camkes.h>

//==============================================================================
//
// CAmkES startup
//
//==============================================================================

//------------------------------------------------------------------------------
void pre_init(void)
{
    Debug_LOG_DEBUG("[%s] %s", get_instance_name(), __func__);
}


//------------------------------------------------------------------------------
void post_init(void)
{
    Debug_LOG_DEBUG("[%s] %s", get_instance_name(), __func__);
}


//------------------------------------------------------------------------------
int run(void)
{
    Debug_LOG_DEBUG("[%s] %s", get_instance_name(), __func__);

    volatile size_t cnt = 0;
    for (;;)
    {
        // Purposely waste CPU Time
        cnt++;
    }
}
