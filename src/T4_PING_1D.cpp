#include "T4_PING_1D.h"
#include <stdint.h>
#include <HardwareSerial.h>
#include <Arduino.h>


uint8_t PING_1D_TX_BUF[PING1D_TX_BUF_LEN]  DMAMEM;
uint8_t PING_1D_RX_BUF[PING1D_RX_BUF_LEN]  DMAMEM;




void init_ping_1D_serial(){
    PING1DSERIAL.begin(PING1DBAUD);
}