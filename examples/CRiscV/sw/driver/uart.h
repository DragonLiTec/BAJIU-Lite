#ifndef UART_H_
#define UART_H_
#include "io.h"

typedef struct
{
  volatile u32 DATA;
  volatile u32 STATUS;
  volatile u32 CLOCK_DIVIDER;
  volatile u32 FRAME_CONFIG;
} Uart_Reg;

enum UartParity {NONE = 0,EVEN = 1,ODD = 2};
enum UartStop {ONE = 0,TWO = 1};

typedef struct {
	u32 dataLength;
	enum UartParity parity;
	enum UartStop stop;
	u32 clockDivider;
} Uart_Config;

static u32 uart_writeAvailability(u32 base){
	Uart_Reg *reg = (Uart_Reg *)base;
	return (reg->STATUS >> 16) & 0xFF;
}
static u32 uart_readOccupancy(u32 base){
	Uart_Reg *reg = (Uart_Reg *)base;
	return reg->STATUS >> 24;
}

static void uart_write(u32 base, u32 data){
	Uart_Reg *reg = (Uart_Reg *)base;
	while(uart_writeAvailability((u32)reg) == 0);
	reg->DATA = data;
}

static void uart_applyConfig(u32 base, Uart_Config *config){
	Uart_Reg *reg = (Uart_Reg *)base;
	reg->CLOCK_DIVIDER = config->clockDivider;
	reg->FRAME_CONFIG = ((config->dataLength-1) << 0) | (config->parity << 8) | (config->stop << 16);
}

#endif /* UART_H_ */


