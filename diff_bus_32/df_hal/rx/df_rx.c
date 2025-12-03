#include "df_rx.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "df_rx.pio.h"

void df_rx_init(df_rx_t *rx, PIO pio, uint sm, uint pin, float baudrate) {
    rx->pio = pio;
    rx->sm = sm;
    rx->pin = pin;
    rx->baudrate = baudrate;

    // Load RX PIO program
    rx->offset = pio_add_program(pio, &df_rx_program);
    pio_sm_config c = df_rx_program_get_default_config(rx->offset);

    // Configure RX pin
    pio_gpio_init(pio, pin);
    sm_config_set_in_pins(&c, pin);
    gpio_pull_up(pin); // UART idle state = high

    // Shift configuration: use same shift direction as TX
    sm_config_set_in_shift(&c, true, true, 32); // shift_right=true, autopush, thresh=32

    // Clock divider: 8 PIO cycles per bit
    float clkdiv = (float)clock_get_hz(clk_sys) / (baudrate * 8.0f);
    sm_config_set_clkdiv(&c, clkdiv);

    // Initialize SM
    pio_sm_init(pio, sm, rx->offset, &c);

    // Safety: clear FIFOs and ensure pin is input
    pio_sm_clear_fifos(pio, sm);
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, false);

    // Enable SM
    pio_sm_set_enabled(pio, sm, true);
}

uint32_t df_rx_receive(df_rx_t *rx) {
    return pio_sm_get_blocking(rx->pio, rx->sm);
}

bool df_rx_try_receive(df_rx_t *rx, uint32_t *data) {
    if (!pio_sm_is_rx_fifo_empty(rx->pio, rx->sm)) {
        *data = pio_sm_get(rx->pio, rx->sm);
        return true;
    }
    return false;
}
