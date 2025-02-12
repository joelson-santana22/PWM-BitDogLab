#include <stdio.h> 
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definição dos pinos para o servo e LED
const uint SERVO_PIN = 22;       // Pino onde o servo motor está conectado
const uint LED_PIN = 12;         // Pino onde o LED RGB está conectado

// Configuração do PWM para o servo motor (50Hz = período de 20ms)
const uint16_t PERIOD = 20000;   // Período do PWM do servo em contagens (~20ms)
const float DIVIDER_PWM = 125.0; // Divisor de clock para obter frequência de 50Hz

// Configuração do PWM para o LED RGB
const uint16_t LED_WRAP = 2000;  // Período do PWM do LED (~controle de brilho)
const float LED_DIVIDER = 16.0;  // Divisor do clock do PWM do LED

// Definição dos pulsos do servo motor (em microssegundos)
const uint16_t STEP = 5;         // Passo de ajuste do duty cycle para movimento suave
const uint16_t PULSE_0 = 500;    // Posição de 0° -> 500 µs
const uint16_t PULSE_90 = 1470;  // Posição de 90° -> 1470 µs
const uint16_t PULSE_180 = 2400; // Posição de 180° -> 2400 µs

uint16_t pulse_width = PULSE_0;  // Começa na posição de 0° do servo

// Função para configurar um pino como saída PWM
void setup_pwm(uint gpio, uint wrap, float clk_div) {
    uint slice = pwm_gpio_to_slice_num(gpio);  // Obtém o slice PWM associado ao pino
    gpio_set_function(gpio, GPIO_FUNC_PWM);    // Define a função PWM no pino
    pwm_set_clkdiv(slice, clk_div);            // Define o divisor do clock para a frequência desejada
    pwm_set_wrap(slice, wrap);                 // Define o valor máximo do contador PWM
    pwm_set_gpio_level(gpio, 0);               // Inicializa o duty cycle como 0%
    pwm_set_enabled(slice, true);              // Habilita o PWM no pino
}

// Função para definir a posição do servo motor e ajustar o brilho do LED
void set_servo_position(uint16_t pulse_width) {
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
    pwm_set_gpio_level(SERVO_PIN, pulse_width); // Atualiza o PWM do servo para a nova posição

    // Ajusta o brilho do LED proporcionalmente à posição do servo
    uint16_t led_level = (pulse_width - PULSE_0) * LED_WRAP / (PULSE_180 - PULSE_0);
    pwm_set_gpio_level(LED_PIN, led_level); // Atualiza o PWM do LED

    // Exibe no terminal a posição atual do servo e o nível do LED
    printf("Servo: %d µs | LED: %d\n", pulse_width, led_level);

    sleep_ms(5000); // Aguarda 5 segundos para manter a posição antes de mudar
}

int main() {
    stdio_init_all();
    sleep_ms(2000); // Pequeno atraso para estabilizar a comunicação serial

    // Configura os pinos de PWM para o Servo e para o LED
    setup_pwm(SERVO_PIN, PERIOD, DIVIDER_PWM);
    setup_pwm(LED_PIN, LED_WRAP, LED_DIVIDER);

    // Movimentos iniciais fixos do servo com pausa de 5 segundos entre cada posição
    set_servo_position(PULSE_180);  // Posição de 180° (brilho máximo do LED)
    set_servo_position(PULSE_90);   // Posição de 90° (brilho intermediário do LED)
    set_servo_position(PULSE_0);    // Posição de 0° (brilho mínimo do LED)

    uint8_t direction = 1; // Variável para controlar a direção do movimento do servo

    // Loop principal para movimento contínuo do servo e ajuste do LED
    while (true) {
        uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
        pwm_set_gpio_level(SERVO_PIN, pulse_width); // Atualiza a posição do servo

        // Atualiza o brilho do LED proporcionalmente à posição do servo
        uint16_t led_level = (pulse_width - PULSE_0) * LED_WRAP / (PULSE_180 - PULSE_0);
        pwm_set_gpio_level(LED_PIN, led_level);

        // Exibe no terminal a posição atual do servo e o brilho do LED
        printf("Servo: %d µs | LED: %d\n", pulse_width, led_level);
        sleep_ms(10); // Delay recomendado para suavidade do movimento

        // Controla o movimento do servo motor
        if (direction) {
            pulse_width += STEP; // Aumenta o pulso (gira o servo para 180°)
            if (pulse_width >= PULSE_180) direction = 0; // Inverte sentido ao chegar no limite
        } else {
            pulse_width -= STEP; // Diminui o pulso (gira o servo para 0°)
            if (pulse_width <= PULSE_0) direction = 1; // Inverte sentido ao chegar no limite
        }
    }
}
