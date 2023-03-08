#ifndef T4_PING_1D_H
#define T4_PING_1D_H

#include <stdint.h>
#include "PING1D_CONSTANTS.h"

#ifndef PING1DBAUD
#define PING1DBAUD       115200
#endif

#ifndef PING1DSERIAL
#define PING1DSERIAL    Serial6
#endif

#define PING1D_TX_BUF_LEN    64
#define PING1D_RX_BUF_LEN    64

struct PING_1D_CONSTANTS_{
    float32_t gain_vals[PING1D_GAIN_VALS_CT] = PING1D_GAIN_VALS_ARR;
}

struct PING_1D_MSG_FORMAT_{
    uint8_t start1 = PING1D_START1;
    uint8_t start2 = PING1D_START2;
    uint16_t payload_length;
    uint16_t message_id;
    uint8_t src_device_id;
    uint8_t dst_device_id;
    // Payload handled externally
    uint16_t checksum;
}


struct PING_1D_SET_{

}


struct PING_1D_GET_{

}


struct PING_1D_CMDS_{
    PING_1D_GET_ get;
    PING_1D_SET_ set;
}


struct PING_1D_DEVICE_{
        uint8_t device_id;    
        uint8_t device_type;
        uint8_t device_revision;
        float32_t gain;
}

struct PING_1D_DATA_{
    uint32_t distance;
    uint16_t confidence;
    PING_1D_DEVICE_ device;
}

struct PING_1D_{
    PING_1D_CMDS_ commands;
    PING_1D_DATA_ data;
    PING_1D_MSG_FORMAT_ msg;
}

// Enable Hardware Serial Selected, dfl Serial6
//  Allocate TX and RX buffer space
void init_ping_1D_serial();        

// Return pointer to "private" data struct
PING_1D_ *init_ping_1d_data_struct();

// Clear serial RX buffer
void inline clear_PING1D_RX();

// Wait for TX buffer to have room
void inline p1d_check_buffer_for_tx_space();

// send byte
void inline p1d_serialSend(uint8_t val_2_send);

// All serial communication is done in little endian format

// Send 16 bit val over serial, LSB first
void p1d_send_uint16_over_serial(uint16_t val_2_send);

// Read 16 bit value over serial, LSB first
uint16_t p1d_read_uint16_over_serial();

// Send 32 bit val over serial, LSB first
void p1d_send_uint32_over_serial(uint32_t val_2_send);

// Read 32 bit val over serial, LSB first
uint32_t p1d_read_uint32_over_serial();

// Read to message payload,
//  fill out main struct with standard format message fields,
//  return ID that was read
uint16_t p1d_return_MSG_ID();

void P1D_READ_DISTANCE_SIMPLE();

#endif