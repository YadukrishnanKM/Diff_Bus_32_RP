#include "diff_bus_32.h"

RX Receiver;
TX Transmitter;

uint16_t _sys_addr, _before_sys_addr, _next_sys_addr;

bool DiffBusINIT(PIO Pio,uint Pin, float baud, uint16_t sys_addr, uint16_t before_sys_addr, uint16_t next_sys_addr) {

    _sys_addr = sys_addr;
    _before_sys_addr = before_sys_addr;
    _next_sys_addr = next_sys_addr;

    Receiver.pio = Pio;
    Receiver.sm = pio_claim_unused_sm(Receiver.pio, true);
    Receiver.pin = Pin;
    Receiver.baudrate = baud;
    Receiver.init_rx;

    Transmitter.pio = Pio;
    Transmitter.sm = pio_claim_unused_sm(Transmitter.pio, true);
    Transmitter.pin = Pin;
    Transmitter.baudrate = baud;
    Transmitter.init_tx;


    if (Receiver.sm >= 0 && Transmitter.sm >= 0) return false; 
    
    return true;
}

uint32_t ReadNonBlocking(void) {
    sleep_ms(250);
    return Receiver.read_non_blocking(&Receiver);
}

uint32_t ReadBlocking (void) {
    sleep_ms(250);
    return Receiver.read_blocking(&Receiver);
}

void Send (uint32_t data) {
    
    uint32_t rx_addr;
    absolute_time_t deadline = make_timeout_time_ms(600); // Create a timeout deadline: now + 3000 ms

    do
    {
        sleep_ms(50);
        uint32_t rx_data = ReadNonBlocking();
        sleep_ms(5);
        rx_addr = rx_data >> 16;

        if (absolute_time_reached(deadline)) {
            
            Transmitter.send(&Transmitter, data); // modify for future error handling
            break;
        }
        

    } while ((uint16_t) rx_addr != _before_sys_addr);
    
    Transmitter.send(&Transmitter, data);

   
}