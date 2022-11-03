/*
 *  Ticker
 *
 *  Copyright (C) 2019-2021, HENSOLDT Cyber GmbH
 *
 */

#include "lib_debug/Debug.h"
#include "lib_compiler/compiler.h"
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
        DECL_UNUSED_VAR(int64_t jitter) = delta - NS_IN_S;

        Debug_LOG_INFO(
            "[%s] 1 sec tick, jitter %c%"PRIu64".%06"PRIu64" ms",
            get_instance_name(),
            (jitter < 0)?'-':'+',
            abs(jitter) / NS_IN_MS,
            abs(jitter) % NS_IN_MS );

        timestamp = timestamp_new;

    }
}
