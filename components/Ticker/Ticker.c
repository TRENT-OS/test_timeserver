/*
 *  Ticker
 *
 *  Copyright (C) 2019, Hensoldt Cyber GmbH
 *
 */

#include "LibDebug/Debug.h"
#include "TimeServer.h"
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

    // set up a tick every second
    int ret = timeServer_rpc_periodic(0, NS_IN_S);
    if (0 != ret)
    {
        Debug_LOG_ERROR("timeServer_rpc_periodic() failed, code %d", ret);
        return -1;
    }

    uint64_t timestamp = 0;
    timeServer_rpc_time(&timestamp);

    for (;;)
    {
        timeServer_notify_wait();

        uint64_t timestamp_new = 0;
        timeServer_rpc_time(&timestamp_new);

        uint64_t delta = timestamp_new - timestamp;
        Debug_LOG_INFO(
            "1 sec tick, delta %" PRIu64 ".%09" PRIu64 " msec",
            delta / NS_IN_S,
            delta % NS_IN_S);
        timestamp = timestamp_new;
    }
}
