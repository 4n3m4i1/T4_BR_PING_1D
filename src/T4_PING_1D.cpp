#include "T4_PING_1D.h"
#include <stdint.h>
#include <HardwareSerial.h>
#include <IntervalTimer.h>
#include <Arduino.h>


uint8_t PING_1D_TX_BUF[PING1D_TX_BUF_LEN]  DMAMEM;
uint8_t PING_1D_RX_BUF[PING1D_RX_BUF_LEN]  DMAMEM;


PING_1D_ ping1d;


void init_ping_1D_serial(){
    // Initiate Serial hardware
    PING1DSERIAL.begin(PING1DBAUD);

    // Allocate buffer space for RX and TX messaging
    PING1DSERIAL.addMemoryForWrite(PING1D_TX_BUF_LEN, PING1D_TX_BUF_LEN);
    PING1DSERIAL.addMemoryForRead(PING1D_RX_BUF_LEN, PING1D_RX_BUF_LEN));
}

PING_1D_ *init_ping_1d_data_struct(){
    return &ping1d;
}

void inline clear_PING1D_RX(){
    PING1DSERIAL.clear();
}

void inline p1d_check_buffer_for_tx_space(){
    while(PING1DSERIAL.availableForWrite() < 16);
}

void inline p1d_serialSend(uint8_t val_2_send){
    PING1DSERIAL.write(val_2_send);
}

void p1d_send_uint16_over_serial(uint16_t val_2_send){
    while(!PING1DSERIAL.availableForWrite());
    PING1DSERIAL.write(val_2_send >> 8);
    PING1DSERIAL.write(val_2_send & 0xFF);
}

uint16_t p1d_read_uint16_over_serial(){
    while(!PING1DSERIAL.available());
    uint16_t val_2_ret = (uint16_t)PING1DSERIAL.read() << 8;
    val_2_ret |= (uint16_t)PING1DSERIAL.read();
    return val_2_ret;
}

void p1d_send_uint32_over_serial(uint32_t val_2_send){
    p1d_serialSend((val_2_send >> 24) & 0xFF);
    p1d_serialSend((val_2_send >> 16) & 0xFF);
    p1d_serialSend((val_2_send >> 8) & 0xFF);
    p1d_serialSend(val_2_send & 0xFF);
}

uint32_t p1d_read_uint32_over_serial(){
    while(!PING1DSERIAL.available());
    uint32_t val_2_ret = (uint32_t)PING1DSERIAL.read() << 24;
    val_2_ret |= (uint32_t)PING1DSERIAL.read() << 16;
    val_2_ret |= (uint32_t)PING1DSERIAL.read() << 8;
    val_2_ret |= (uint32_t)PING1DSERIAL.read() << 0;
    return val_2_ret;
}

uint16_t p1d_return_MSG_ID(){
    ping1d.msg.start1 = PING1DSERIAL.read();
    ping1d.msg.start2 = PING1DSERIAL.read();

    ping1d.msg.payload_length = p1d_read_uint16_over_serial();
    ping1d.msg.message_id = p1d_read_uint16_over_serial();

    ping1d.msg.src_device_id = PING1DSERIAL.read();
    ping1d.msg.dst_device_id = PING1DSERIAL.read();

    return ping1d.msg.message_id;
}

void P1D_READ_DISTANCE_SIMPLE(){
    if(PING1DSERIAL.available() < PING1D_STD_MSG_LEN + PING1D_GET_DISTANCE_SIMPLE_PAYLEN){
        return;
    }

    // Advance read pointer to the first valid start byte (dfl: 'B')
    while(PING1DSERIAL.peek() != PING1D_START1) PING1DSERIAL.read();

    // If we've read the wrong message, clear buffer and dip out
    if(p1d_return_MSG_ID() != PING1D_GET_DISTANCE_SIMPLE){
        clear_PING1D_RX();
        return;
    }

    // If we're here, everything is good so far and we've read to the payload

    ping1d.data.distance = p1d_read_uint32_over_serial();
    ping1d.data.confidence = (uint16_t)PING1DSERIAL.read();
}