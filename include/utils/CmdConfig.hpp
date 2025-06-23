#ifndef CMD_CONFIGURATION_HPP_
#define CMD_CONFIGURATION_HPP_

#include <iostream>
#include <string>

//  
// -----------------------------------------------
// 

/**
 * Requests:
 * -----------
 * <ProjCode_JigNo> <action> <parameter> <value#if any> <range#if any>
 * ===================================================================
 * Requests Illustration
 * ----------------------
 * 1. <ProjectCode_JigNo> -> <ZE115_1> // Project "ZE115" and Jig number "1"
 * 2. <Action>      ->  <get>   | <set>  | <clear>   | <start> | <stop>
 * 3. <Parameter>   ->  <error> | <test> | <channel> | <debug>
 * 4. <Value>       ->  <value> | <range> : Value is optional and can be a single value or a range
 * ===================================================================
 * * Example:
 * -----------
 *      A. set channel 6 range 0 150
 *      B. set error 1
*/ 

#define ACTION_SEGMENT              0
#define PARAM_SEGMENT               1
#define VALUE_SEGMENT               2

#define MIN_ERROR_VALUE             1
#define MAX_ERROR_VALUE             128

#define MIN_TEST_VALUE              1 
#define MAX_TEST_VALUE              128

#define MIN_CHANNEL_VALUE           0
#define MAX_CHANNEL_VALUE           19

#define MIN_CHANNEL_RANGE_VALUE     0
#define MAX_CHANNEL_RANGE_VALUE     50000

#define MAX_NUM_OF_CHANNELS         20

#define ACTION_GET                  "get"
#define ACTION_SET                  "set"
#define ACTION_CLEAR                "clear"
#define ACTION_START                "start"
#define ACTION_STOP                 "stop"

#define PARAM_ERROR                 "error"
#define PARAM_TEST                  "test"
#define PARAM_CHANNEL               "channel"
#define PARAM_DEBUG                 "debug"

#define AT_CMD_SET_TEST           "AT+SETTST"
#define AT_CMD_SET_ERROR          "AT+SETERR"
#define AT_CMD_SET_CHANNEL        "AT+SETCH"
#define AT_CMD_GET_TEST           "AT+GETTST"
#define AT_CMD_GET_ERROR          "AT+GETERR"
#define AT_CMD_GET_CHANNEL        "AT+GETCH"
#define AT_CMD_CLEAR_TEST         "AT+CLRTST"
#define AT_CMD_CLEAR_ERROR        "AT+CLRERR"
#define AT_CMD_CLEAR_CHANNEL      "AT+CLRCH"
#define AT_CMD_START_DEBUG        "AT+STARTDBG"
#define AT_CMD_STOP_DEBUG         "AT+STOPDBG"

#define AT_CMD_EMPTY                ""
#define AT_CMD_EQUAL                '='
#define AT_CMD_DASH                 '-'
#define AT_CMD_CARRIAGE_RETURN      '\r'

// Topics
#define JIG_WIFI_TOPIC              "jig-wifi"
#define JIG_REQ_TOPIC               "jig-req"
#define JIG_RESP_TOPIC              "jig-resp"
#define JIG_DEBUG_TOPIC             "jig-debug"

#define REQUEST_MAP_INITIALIZER     \
{                                                  \
    { ACTION_SET, {                                \
        { PARAM_CHANNEL, ACTION_SET_PARAM_CHANNEL_VALUES_COUNT }, \
        { PARAM_TEST,   ACTION_SET_PARAM_TEST_VALUES_COUNT },     \
        { PARAM_ERROR,  ACTION_SET_PARAM_ERROR_VALUES_COUNT }     \
    } },                                            \
    { ACTION_GET, {                                \
        { PARAM_CHANNEL, ACTION_GET_PARAM_CHANNEL_VALUES_COUNT }, \
        { PARAM_TEST,   ACTION_GET_PARAM_TEST_VALUES_COUNT },     \
        { PARAM_ERROR,  ACTION_GET_PARAM_ERROR_VALUES_COUNT }     \
    } },                                            \
    { ACTION_CLEAR, {                              \
        { PARAM_CHANNEL, ACTION_CLEAR_PARAM_CHANNEL_VALUES_COUNT }, \
        { PARAM_TEST,   ACTION_CLEAR_PARAM_TEST_VALUES_COUNT },     \
        { PARAM_ERROR,  ACTION_CLEAR_PARAM_ERROR_VALUES_COUNT }     \
    } },                                            \
    { ACTION_START, {                              \
        { PARAM_DEBUG, ACTION_START_PARAM_DEBUG_VALUES_COUNT }     \
    } },                                            \
    { ACTION_STOP, {                               \
        { PARAM_DEBUG, ACTION_STOP_PARAM_DEBUG_VALUES_COUNT }     \
    } }                                             \
}

#endif // CMD_CONFIGURATION_HPP_