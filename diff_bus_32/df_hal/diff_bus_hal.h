#pragma once

#include "pico/stdlib.h"
#include "df_tx.h"
#include "df_rx.h"

#define RX_BUFFER_SIZE 256  // must be power of 2 for circular mode

typedef struct {
    df_rx_t rx;
    PIO pio; 
    uint sm; 
    uint pin; 
    float baudrate;

    inline void (* init_rx) (RX *self) __attribute__((always_inline));
    inline uint32_t (* read_non_blocking) (RX *self) __attribute__((always_inline));
    inline uint32_t (* read_blocking) (RX *self) __attribute__((always_inline));
} RX;


typedef struct {
    df_tx_t tx;
    PIO pio;
    uint sm;   
    uint pin;       
    float baudrate;
    uint offset;

    inline void (* init_tx) (TX *self)__attribute__((always_inline));
    inline void (* send) (TX *self,  uint32_t data) __attribute__((always_inline));
} TX;
