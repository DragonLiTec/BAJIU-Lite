#pragma once

#include "riscv.h"
#define MAIN_CLOCK_HZ (100 * 1000 * 1000)

#define GPIO_BASE  (0xF0000000U)
#define UART0_BASE (0xF0010000U)
#define I2C0_BASE  (0xF0011000U)
#define TIMER_BASE (0xF0020000U)
