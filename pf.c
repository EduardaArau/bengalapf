#include <stdio.h>
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define BTN_A 5
#define BTN_B 6
#define LED_RED 13
#define LED_BLUE 12
#define BUZZER 21

//Funcao para ativar o Buzzer
void ativar_buzzer() {
    gpio_set_function(BUZZER, GPIO_FUNC_PWM); // Configura pino como saída PWM
    uint slice_num = pwm_gpio_to_slice_num(BUZZER); // Obter o slice do PWM

    pwm_set_clkdiv(slice_num, 125.0);                  
    pwm_set_wrap(slice_num, 255);                      
    pwm_set_gpio_level(BUZZER, 50);               
    pwm_set_enabled(slice_num, true);          // Ativar o PWM        

    sleep_ms(1000);  // Som por 1 segundo
    pwm_set_enabled(slice_num, false);  // Desativar o PWM  
}

// Função principal
int main() {
    stdio_init_all();
//Inicialização do led vermelho
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, 0);  

//Inicialização do led azul

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, 0);  

//Inicialização dos botões
    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);  

    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);  

     // Configurar o pino do Buzzer como saída
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
    gpio_put(BUZZER, 0);

    // controle de leds e buzzer
    while (true) {
        if (!gpio_get(BTN_A)) {  
            sleep_ms(200);  // Debounce
            while (!gpio_get(BTN_A));  // Espera soltar o botão
            gpio_put(LED_BLUE, 1);
            gpio_put(LED_RED, 0);
        }

        if (!gpio_get(BTN_B)) {  
            sleep_ms(200);  
            while (!gpio_get(BTN_B));  
            gpio_put(LED_BLUE, 0);
            gpio_put(LED_RED, 1);  
            ativar_buzzer();  
            gpio_put(LED_RED, 0);  // Apaga o led vermelho quando o buzzer parar
            gpio_put(LED_BLUE, 1);// Acende o botão azul
        }

    }
}
