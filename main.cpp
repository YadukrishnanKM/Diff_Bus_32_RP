#include "pico/stdlib.h"
#include "diff_bus_32.h"
#include <stdio.h>

int main() {
    stdio_init_all();
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    
    DiffBusINIT(pio0, 15, 576000.0f,0x1010, 0x0101, 0xf0f0);

    uint32_t value = 0xA5A50f0f;
    uint32_t data = 0;

    while (true) {

        Send (value);

        sleep_ms(100); // Short delay to allow RX to process
        
        data = ReadNonBlocking();

        if (data == 0xa0a0a0a0) {
            gpio_put(25, 1);
            sleep_ms(500);
        }

        else gpio_put(25, 0);  
        printf("Sent: 0x%08x\n", value);
        sleep_ms(1000);
        


    }

}

// int main() {
//     stdio_init_all();
//     //gpio_init(25);
//     //gpio_set_dir(25, GPIO_OUT);

//     df_tx_t tx;
//     df_rx_t rx; 
//     df_tx_init(&tx, pio0, 0, 15, 576000.0f);
//     df_rx_init(&rx, pio0, 1, 15, 576000.0f);
//     uint32_t value = 0xa0a0a0a0;

//     while (true) {
//         uint32_t data;

//         df_tx_send(&tx, value);
//         sleep_ms(100); // Short delay to allow RX to process
//         if (df_rx_try_receive(&rx, &data)) {

//             if ((data != 0) && (data != value)) printf("Received: 0x%08x\n", data);
//         }

//         //if (value == 0xa0a0a0a0) gpio_put(25, 1);
//         //else gpio_put(25, 0);  
//         printf("Sent: 0x%08x\n", value);
//         sleep_ms(1000);
        


//     }

// }

