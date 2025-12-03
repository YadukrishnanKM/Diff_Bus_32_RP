#pragma once
#include "hardware/pio.h"
#include "df_tx.pio.h"

// Struct to hold TX configuration
typedef struct {
    PIO pio;           // PIO instance (pio0 or pio1)
    uint sm;           // State machine index
    uint pin;          // TX pin
    float baudrate;    // Desired baud rate
    uint offset;       // Program offset in PIO instruction memory
} df_tx_t;

// Initialize the TX PIO program and configure the state machine
void df_tx_init(df_tx_t *tx, PIO pio, uint sm, uint pin, float baudrate);

// Transmit a 32-bit word (blocking)
void df_tx_send(df_tx_t *tx, uint32_t data);
