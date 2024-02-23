/*
 * Worker component that creates additional load for the system
 *
 * Copyright (C) 2019-2024, HENSOLDT Cyber GmbH
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * For commercial licensing, contact: info.cyber@hensoldt.net
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
