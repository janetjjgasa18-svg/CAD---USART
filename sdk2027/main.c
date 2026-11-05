#include "leds.h"
#include "exti.h"
#include "usart.h"
#include "delay.h"
#include "adc.h"      
#include <stdio.h>    

int main() {
    // Inicialización de periféricos
    init_led_pin();
    led_on_off();
    init_exti_pin();
    init_exti();
    init_usart1_pin();
    init_usart1();
    
    // Inicialización del CAD
    init_adc1_pin();
    init_adc1();

    usart1_sendbyte('\n');
    usart1_sendstring("Iniciando lectura de voltaje CAD...\r\n");
    delay_ms(1000);

    uint16_t valor_cad;
    uint32_t voltaje_mv;
    uint16_t parte_entera;
    uint16_t parte_decimal;
    char buffer[40];

    while(1) {
        // 1. Leer el valor del CAD (0 a 4095)
        valor_cad = adc1_read(); 

        // 2. Convertir el valor a milivolts (0 a 3300 mV)
        // Se multiplica primero para no perder precisión en la división entera
        voltaje_mv = (valor_cad * 3300) / 4095; 

        // 3. Separar los Volts de los milivolts para poder imprimirlos
        parte_entera = voltaje_mv / 1000;       // Ejemplo: 2500 / 1000 = 2
        parte_decimal = voltaje_mv % 1000;      // Ejemplo: 2500 % 1000 = 500

        // 4. Formatear la cadena construyendo el punto decimal artificialmente (%03d rellena con ceros)
        sprintf(buffer, "Voltaje: %d.%03d V\r\n", parte_entera, parte_decimal);

        // 5. Enviar por el puerto serial
        usart1_sendstring(buffer);

        // 6. Retardo para estabilizar la lectura en terminal
        delay_ms(300); 
    }
}