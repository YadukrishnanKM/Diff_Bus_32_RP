#include "diff_bus_hal.h"

void init_rx (RX *self) {

    self->rx.pio = self->pio;
    self->rx.sm = self->sm;
    self->rx.pin = self->pin;
    self->rx.baudrate = self->baudrate;

    df_rx_init(&self -> rx, self -> pio, self -> sm, self -> pin, self -> baudrate);
}

uint32_t read_non_blocking (RX *self) {

    uint32_t temp;

    if (df_rx_try_receive(&self->rx, &temp)) {
        return temp;
    }
    return temp;
}

uint32_t read_blocking (RX *self){
    return df_rx_receive(&self -> rx);
}

void init_tx (TX *self) {
    self->tx.pio = self->pio;
    self->tx.sm = self->sm;
    self->tx.pin = self->pin;
    self->tx.baudrate = self->baudrate;

    df_tx_init(&self -> tx, self-> pio, self-> sm, self-> pin, self-> baudrate);
}

void send (TX *self, uint32_t data) {
    df_tx_send(&self -> tx, data);

} 
