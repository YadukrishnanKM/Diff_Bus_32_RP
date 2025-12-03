#include "df_tx.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "df_tx.pio.h"

void df_tx_init(df_tx_t *tx, PIO pio, uint sm, uint pin, float baudrate) {
    tx->pio = pio;
    tx->sm = sm;
    tx->pin = pin;
    tx->baudrate = baudrate;

    // Load PIO program
    tx->offset = pio_add_program(pio, &df_tx_program);
    pio_sm_config c = df_tx_program_get_default_config(tx->offset);

    // Configure TX pin (gpio reserved for PIO)
    pio_gpio_init(pio, pin);
    sm_config_set_out_pins(&c, pin, 1);
    sm_config_set_set_pins(&c, pin, 1);

    // Let the PIO program control direction; start as input (idle).
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, false);  // input by default
    gpio_pull_up(pin); // idle high

    // Configure data shifting: choose same direction on both sides
    // Use shift_right = true for UART LSB-first receive/shifts (keeps consistency)
    // For TX 'out' shifting we set shift_right = true to match RX; this is symmetric.
    sm_config_set_out_shift(&c, true, true, 32);   // shift_right=true, autopull, thresh=32

    // Baud timing: 8 PIO cycles per bit
    float clkdiv = (float)clock_get_hz(clk_sys) / (baudrate * 8.0f);
    sm_config_set_clkdiv(&c, clkdiv);

    // Initialize and enable
    pio_sm_init(pio, sm, tx->offset, &c);
    pio_sm_clear_fifos(pio, sm);
    pio_sm_set_enabled(pio, sm, true);
}

void df_tx_send(df_tx_t *tx, uint32_t data) {
    pio_sm_put_blocking(tx->pio, tx->sm, data);
}
