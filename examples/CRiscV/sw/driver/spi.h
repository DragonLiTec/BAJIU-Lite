#pragma once

#include "common.h"


typedef struct {
	volatile u32 data;
	volatile u32 status;
	volatile u32 config;
	volatile u32 clockDivider;
	volatile u32 ssSetup;
	volatile u32 ssHold;
	volatile u32 ssDisable;
} Spi_Reg;

typedef struct {
	u32 cpol;
	u32 cpha;
	u32 config;
	u32 mode;
	u32 clockDivider;
	u32 ssSetup;
	u32 ssHold;
	u32 ssDisable;
} Spi_Config;

#define SPI_DATA 0
#define SPI_STATUS 4

#define SPI_CMD_WRITE
#define SPI_CMD_READ
#define SPI_SELECT_SS (0x11 << 24)
#define SPI_DISELECT_SS (0x10 << 24)

static u32 spi_canwrite(Spi_Reg *reg){
	return reg->data & 0xFFFF;
}
static u32 spi_canread(Spi_Reg *reg) {
	return reg->data >> 16;
}
static u8 spi_read(Spi_Reg *reg) {
	while(!spi_canread(reg));
	return reg->data & 0xff;
}

void spi_write(Spi_Reg *reg, u8 value) {
	while(!spi_canwrite(reg));
	reg->data = value;
}

void spi_select(Spi_Reg *reg, u8 id) {
	reg->data = SPI_SELECT_SS | id;
}
void spi_diselect(Spi_Reg *reg, u8 id) {
	reg->data = SPI_DISELECT_SS | id;
}

static void spi_applyConfig(Spi_Reg *reg, Spi_Config *config){
	reg->config = (config->cpol << 0) | (config->cpha << 1) | (config->mode << 4);
	reg->clockDivider = config->clockDivider;
	reg->ssSetup = config->ssSetup;
	reg->ssHold = config->ssHold;
	reg->ssDisable = config->ssDisable;
}
