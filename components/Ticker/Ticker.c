/*
 *  Ticker
 *
 *  Copyright (C) 2019-2021, HENSOLDT Cyber GmbH
 *
 */

#include "lib_debug/Debug.h"
#include "lib_compiler/compiler.h"
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
void timeServer_rpc_wait(void)
{
    // instead of the NULL parameter a seL4_Word could be passed that receives
    // a badge ID. This ID is equal to the value returned by
    // timeServer_rpc_notification_badge().
    seL4_Wait(timeServer_rpc_notification(), NULL);
}


//------------------------------------------------------------------------------
int run(void)
{
    uint64_t timestamp = timeServer_rpc_time();
    if (0 == timestamp) {
        Debug_LOG_WARNING("[%s] time is 0, testing if time passes...",
                       get_instance_name());
        for (int i = 0; i < 100; i++) {
            timestamp = timeServer_rpc_time();
            if (0 != timestamp) {
                break;
            }
        }
        if (0 == timestamp) {
            Debug_LOG_ERROR("[%s] time seems frozen", get_instance_name());
            return -1;
        }
    }

    // set up timer #0 to tick periodically based on CAmkES attribute
    int timeout_ms = ticker_timeout;
    Debug_LOG_DEBUG("[%s] %s, timeout %d ms",
                    get_instance_name(), __func__, timeout_ms);

    int ret = timeServer_rpc_periodic(0, timeout_ms * NS_IN_MS);
    if (0 != ret)
    {
        Debug_LOG_ERROR("timeServer_rpc_periodic() failed, code %d", ret);
        return -1;
    }

    timestamp = timeServer_rpc_time();

    for (;;)
    {
        // wait for tick event
        timeServer_rpc_wait();

        uint64_t timestamp_new = timeServer_rpc_time();

        uint64_t delta = timestamp_new - timestamp;
        DECL_UNUSED_VAR(int64_t jitter) = delta - (timeout_ms * NS_IN_MS);

        Debug_LOG_INFO(
            "[%s] %d ms tick, jitter %c%" PRIu64 ".%06" PRIu64 " ms",
            get_instance_name(),
            timeout_ms,
            (jitter < 0)?'-':'+',
            abs(jitter) / NS_IN_MS,
            abs(jitter) % NS_IN_MS );

        timestamp = timestamp_new;
    }
}
