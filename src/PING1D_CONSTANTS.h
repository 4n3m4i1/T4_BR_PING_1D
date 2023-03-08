
#include <stdint.h>

// Standard message + 2 byte checksum, no buffer
#define PING1D_STD_MSG_LEN  10

// Advance to message ID
// Start1 + Start2 + PayLen in bytes
#define PING1D_STD_MSG_L2ID 4

#define PING1D_START1       'B'
#define PING1D_START2       'R'

#define PING1D_DEVICE_ID    1       // Should be 1, 0 == unknown

#define PING1D_GAIN_VALS_CT     7
#define PING1D_GAIN_VALS_ARR    {0.6f, 1.8f, 5.5f, 12.9f, 30.2f, 66.1f, 144.0f}


#define PING1D_GET_DISTANCE_SIMPLE_PAYLEN   5

// u16 message ID field
enum PING1D_MESSAGE_ID_{
    // Common PING 1D and PING 360 IDs
    PING_COMMON_ACK = 1,                // 1
    PING_COMMON_NACK,                   // 2
    PING_COMMON_ASCII_TEXT,             // 3
    PING_GET_DEVICE_INFORMATION,        // 4
    PING_GET_PROTOCOL_VERSION,          // 5
    PING_COMMON_GENERAL_REQUEST,        // 6

    PING_SET_DEVICE_ID = 100,

    // Ping 1D Specific IDs
    PING1D_SET_DEVICE_ID = 1000,        // 1000
    PING1D_SET_RANGE,                   // 1001
    PING1D_SET_SPEED_OF_SOUND,          // 1002
    PING1D_SET_MODE_AUTO,               // 1003
    PING1D_SET_PING_INTERVAL,           // 1004
    PING1D_SET_GAIN_SETTING,            // 1005
    PING1D_SET_PING_ENABLE,             // 1006

    PING1D_CTRL_GOTO_BOOTLOADER = 1100, // 1100

    PING1D_GET_FIRMWARE_VERSION = 1200, // 1200
    PING1D_GET_DEVICE_ID,               // 1201
    PING1D_GET_VOLTAGE_5,               // 1202
    PING1D_GET_SPEED_OF_SOUND,          // 1203
    PING1D_GET_RANGE,                   // 1204
    PING1D_GET_MODE_AUTO,               // 1205
    PING1D_GET_PING_INTERVAL,           // 1206
    PING1D_GET_GAIN_SETTING,            // 1207
    PING1D_GET_TRANSMIT_DURATION,       // 1208

    PING1D_GET_GENERAL_INFO = 1210,     // 1210
    PING1D_GET_DISTANCE_SIMPLE,         // 1211, important
    PING1D_GET_DISTANCE,                // 1212
    PING1D_GET_PROCESSOR_TEMPERATURE,   // 1213
    PING1D_GET_PCB_TEMPERATURE,         // 1214
    PING1D_GET_PING_ENABLE,             // 1215
    
    PING1D_GET_PROFILE = 1300,          // 1300

    PING1D_CTRL_CONTINUOUS_START = 1400,
    PING1D_CTRL_CONTINUOUT_STOP         // 1401

};