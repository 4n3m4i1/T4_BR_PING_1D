#ifndef T4_PING_1D_H
#define T4_PING_1D_H

#include <stdint.h>
#include "PING1D_CONSTANTS.h"

#ifndef PING1DBAUD
#define PING1DBAUD       115200
#endif

#ifndef PING1DSERIAL
#define PING1DSERIAL    Serial7
#endif

#define PING1D_TX_BUF_LEN    64
#define PING1D_RX_BUF_LEN    64


void init_ping_1D_serial();

#endif