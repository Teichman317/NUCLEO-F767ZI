
#include "kbd_input.h"
#include "stm32f7xx_hal.h"  // Adjust to your STM32 family
#include <stdio.h>
#include <stdlib.h>


extern UART_HandleTypeDef huart3;
#define MAX_DIGITS 3
char *endptr;


int get_position_input(uint32_t timeout_ms, uint8_t echo_enabled) {
    #define MAX_DIGITS 3
    uint8_t buffer[MAX_DIGITS + 1] = {0};  // 3 digits + null terminator
    uint8_t char_received = 0;
    int digit_count = 0;

    flush_uart_line(&huart3);  // Optional line clear

    while (digit_count < MAX_DIGITS) {
        if (HAL_UART_Receive(&huart3, &char_received, 1, timeout_ms) != HAL_OK)
            return -1;

        if (char_received == '\r' || char_received == '\n') break;

        if (char_received >= '0' && char_received <= '9') {
            buffer[digit_count++] = char_received;
            if (echo_enabled)
                HAL_UART_Transmit(&huart3, &char_received, 1, timeout_ms);
        }
    }

    buffer[digit_count] = '\0';

    printf("🧵 Buffer = '%s' (length = %d)\n\r", buffer, digit_count);
    for (int i = 0; i < digit_count; ++i) {
        printf("byte[%d] = 0x%02X\n\r", i, buffer[i]);
    }

    char *endptr;
    int parsed = strtol((char *)buffer, &endptr, 10);
    printf("📤 Parsed value = %d\n\r", parsed);

    if (*endptr != '\0') {
        printf("🧨 Non-digit trailing data detected\n\r");
        return -1;
    }

    if (parsed < 0 || parsed > 255) {
        printf("🚫 Parsed number out of range\n\r");
        return -1;
    }
    printf("🚚 Returning parsed value = %d\n\r", parsed);

    return parsed;
}




void flush_uart_line(UART_HandleTypeDef *huart) {
    uint8_t ch;

    while (HAL_UART_Receive(huart, &ch, 1, 1) == HAL_OK) {
        if (ch != '\r' && ch != '\n') {
            break;  // Stop flushing — legit input arrived
        }
    }
}

int get_angle_input(uint32_t timeout_ms, uint8_t echo_enabled) {
    uint8_t buffer[4] = {0};  // Up to 3 digits + null terminator
    uint8_t char_received;
    int digit_count = 0;

    flush_uart_line(&huart3);  // 🧹 Clean line endings

    while (digit_count < 3) {
        if (HAL_UART_Receive(&huart3, &char_received, 1, timeout_ms) != HAL_OK)
            return -1;

        if (char_received == '\r' || char_received == '\n') break;

        if (char_received >= '0' && char_received <= '9') {
            buffer[digit_count++] = char_received;
            if (echo_enabled) HAL_UART_Transmit(&huart3, &char_received, 1, timeout_ms);
        }
    }

    // Wait for Enter if needed
    if (char_received != '\r' && char_received != '\n') {
        do {
            if (HAL_UART_Receive(&huart3, &char_received, 1, timeout_ms) != HAL_OK)
                return -1;
        } while (char_received != '\r' && char_received != '\n');
    }

    buffer[digit_count] = '\0';
    int angleIndex = atoi((char *)buffer);

    if (angleIndex < 0 || angleIndex >= 256) return -1;

    return angleIndex;
}



