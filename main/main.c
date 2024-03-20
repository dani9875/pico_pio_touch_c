#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "hello.pio.h"

int main() 
{
    stdio_init_all();

    gpio_init(2);
    gpio_pull_up(2);

    gpio_init(3);
    gpio_pull_up(3);

    gpio_init(4);
    gpio_pull_up(4);

    gpio_init(5);
    gpio_pull_up(5);

    gpio_init(6);
    gpio_pull_up(6);

    PIO pio = pio0;
    PIO pio_1 = pio1;
    uint offset = pio_add_program(pio, &hello_program);
    uint offset1 = pio_add_program(pio_1, &hello_program);

    hello_program_init(pio, 0, offset, 6);
    hello_program_init(pio, 1, offset, 5);
    hello_program_init(pio, 2, offset, 4);
    hello_program_init(pio, 3, offset, 3);
    hello_program_init(pio_1, 0, offset1, 2);

    while(true) 
    {
        tight_loop_contents();

        /* The cap_values obtained from the state machines represent some form of data that we have captured.
        These values can be utilized in a variety of ways depending on the requirements of your project.
        One possible use case could be to transfer these values over a communication bus, such as I2C, to another microcontroller unit (MCU).
        This would allow you to process or react to these values on a separate MCU, perhaps one with more computational power or specific peripherals.
        Alternatively, you could use these values to control the state of an LED. For example, you could set a threshold value,
        and light up an LED when a cap_value exceeds this threshold. This could serve as a visual indicator of some condition being met.
        The possibilities are endless and are left up to your creativity and the specific needs of your project.*/  

        uint32_t cap_value_pin_6 = pio_sm_get_blocking(pio, 0);
        cap_value_pin_6 = 4294967295 - cap_value_pin_6;

        uint32_t cap_value_pin_5 = pio_sm_get_blocking(pio, 1);
        cap_value_pin_5 = 4294967295 - cap_value_pin_5;

        uint32_t cap_value_pin_4 = pio_sm_get_blocking(pio, 2);
        cap_value_pin_4 = 4294967295 - cap_value_pin_4;

        uint32_t cap_value_pin_3 = pio_sm_get_blocking(pio, 3);
        cap_value_pin_3 = 4294967295 - cap_value_pin_3;

        uint32_t cap_value_pin_2 = pio_sm_get_blocking(pio_1, 0);
        cap_value_pin_2 = 4294967295 - cap_value_pin_2;

        /*By disabling the state machines for a certain period of time, you prevent them from actively pulling the GPIO pins, which reduces noise and interference generated during operation.
        This can be particularly important for complying for EMC standards.*/
        pio_sm_set_enabled(pio, 0, false);
        pio_sm_set_enabled(pio, 1, false);
        pio_sm_set_enabled(pio, 2, false);
        pio_sm_set_enabled(pio, 3, false);
        pio_sm_set_enabled(pio_1, 0, false);
       
        sleep_ms(3000);
        
        pio_sm_set_enabled(pio, 0, true);
        pio_sm_set_enabled(pio, 1, true);
        pio_sm_set_enabled(pio, 2, true);
        pio_sm_set_enabled(pio, 3, true);
        pio_sm_set_enabled(pio_1, 0, true); 

    }

    return 0;
}