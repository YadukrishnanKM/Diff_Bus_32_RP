#pragma once

#include "pico/stdlib.h"
#include "diff_bus_hal.h"
#include "hardware/pio.h"
#include "hardware/structs/pio.h"

bool DiffBusINIT (PIO Pio,uint Pin, float baud, uint16_t sys_addr, uint16_t before_sys_addr, uint16_t next_sys_addr) __attribute__((always_inline));

uint32_t ReadNonBlocking(void) __attribute__((always_inline));

uint32_t ReadBlocking (void) __attribute__((always_inline));

void Send (uint32_t data) __attribute__((always_inline));