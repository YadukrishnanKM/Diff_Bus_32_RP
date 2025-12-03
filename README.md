[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](./LICENCE)

# diff_bus_32 (DiffBus 32-bit)

This module provides a small API for using a PIO-based differential-style bus on the RP2040. The implementation targets 32-bit payloads and is intended as a simple example and starting point for an RP2040-based node on a multi-node bus.

Key files
- `diff_bus_32.c` — high-level wrapper implementing init/read/send flows.
- `diff_bus_32.h` — public API used by the application.
- `df_hal/` — hardware abstraction layer: `diff_bus_hal.h/.c`, plus `df_tx` and `df_rx` modules that manage PIO programs and FIFOs.

API reference

- `bool DiffBusINIT(PIO Pio, uint Pin, float baud, uint16_t sys_addr, uint16_t before_sys_addr, uint16_t next_sys_addr)`
  - Initialize RX and TX HAL objects and claim PIO state machines.
  - Returns `true` on successful initialization, `false` otherwise.
  - Example: `DiffBusINIT(pio0, 0, 115200.0f, 1, 0, 2);`

- `uint32_t ReadNonBlocking(void)`
  - Attempt to read a 32-bit word from the bus without blocking. If no data is available, the value is undefined (caller should check/ignore zero).

- `uint32_t ReadBlocking(void)`
  - Block until a 32-bit word is received and return it.

- `void Send(uint32_t data)`
  - Send a 32-bit word on the bus. The current behavior will poll for a frame from `_before_sys_addr` before sending, with a timeout fallback.

Internals (brief)
- `diff_bus_32.c` holds three module-scope addresses:
  - `_sys_addr` — this node's address
  - `_before_sys_addr` — address to wait for before sending
  - `_next_sys_addr` — next node address (for future use/logic)
- Two HAL structs are used: `RX Receiver` and `TX Transmitter`, each containing pointers to PIO, state machine index, pin and function pointers that wrap `df_rx`/`df_tx` operations.

Usage example

```c
#include "diff_bus_32.h"

int main() {
    stdio_init_all();

    // Initialize with pio0, pin 0, 115200 baud, node addresses
    if (!DiffBusINIT(pio0, 0, 115200.0f, 1, 0, 2)) {
        // Initialization failed
        while (1) tight_loop_contents();
    }

    // Send a payload
    Send(0x12345678);

    // Poll for new data
    uint32_t v = ReadNonBlocking();
    if (v) {
        // handle v
    }

    // Or block until a frame arrives
    uint32_t r = ReadBlocking();
    (void)r;
}
```

Design considerations and suggestions
- Error handling: `DiffBusINIT` returns a boolean; consider returning detailed error codes to make debugging easier.
- Thread-safety: the module is not explicitly re-entrant or interrupt-safe. If the implementation will be used from ISRs, add appropriate locking or use dedicated PIO IRQ handlers.
- Framing & reliability: the example uses raw 32-bit payloads and a simple waiting strategy in `Send`. Consider adding CRC, ACKs, retries, and backoff for a production protocol.

Where to look next
- `df_hal/` contains the PIO-based TX/RX implementations. Inspect `df_rx` and `df_tx` for framing and buffer details.

If you'd like, I can:
- expand the API with timeout configuration and return codes,
- add unit tests or an example `main.cpp` that demonstrates a simple two-node exchange,
- or create a sequence diagram showing send/receive timing and expected packet structure.

---

## 📜 License

GPL 3.0 [LICENSE](./LICENCE)