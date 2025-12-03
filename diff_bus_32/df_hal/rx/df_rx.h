#pragma once
#include "hardware/pio.h"
#include "df_rx.pio.h"

// Structure to hold RX configuration
typedef struct {
    PIO pio;           // PIO instance (pio0 or pio1)
    uint sm;           // State machine index
    uint pin;          // RX pin
    float baudrate;    // Baud rate
    uint offset;       // Program offset in instruction memory
} df_rx_t;

// Initialize RX PIO state machine
void df_rx_init(df_rx_t *rx, PIO pio, uint sm, uint pin, float baudrate);

// Read a 32-bit word from RX FIFO (blocking)
uint32_t df_rx_receive(df_rx_t *rx);

// Try to read (non-blocking), returns true if data available
bool df_rx_try_receive(df_rx_t *rx, uint32_t *data);
