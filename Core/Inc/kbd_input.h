#ifndef __KBD_INPUT_H
#define __KBD_INPUT_H

#include "stm32f7xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void flush_uart_line(UART_HandleTypeDef *huart);
int get_position_input(uint32_t timeout_ms, uint8_t echo_enabled);
int get_angle_input(uint32_t, uint8_t );

#ifdef __cplusplus
}
#endif

#endif /* __KBD_INPUT_H */

