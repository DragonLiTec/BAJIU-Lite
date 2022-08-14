#include "uart.h"
#include "clint.h"
#include "io.h"
#include "gpio.h"
#include "criscv.h"
#include "i2c.h"


static void i2c_init() {
	I2c_Config i2c;
	i2c.samplingClockDivider = 3;				//Number of cycle - 1 between each SDA/SCL sample
	i2c.timeout = CORE_HZ / 1000;    //1 ms;		//care about time out value for stopbit //Number of cycle - 1 between each SDA/SCL sample
	i2c.tsuDat  = CORE_HZ / 2000000; //500 ns //Number of cycle - 1 between each SDA/SCL sample

	i2c.tLow  = CORE_HZ / 2000000;	//100khz	//Number of cycle - 1 between each SDA/SCL sample
	i2c.tHigh = CORE_HZ / 2000000;	//100khz	//Number of cycle - 1 between each SDA/SCL sample
	i2c.tBuf  = CORE_HZ / 1000000;	//Number of cycle - 1 between each SDA/SCL sample
	i2c_applyConfig(I2C0_BASE, &i2c);
	i2c_setFilterConfig(I2C0_BASE, 0, I2C_FILTER_7_BITS | I2C_FILTER_ENABLE); //0x30 => Address byte = 0x60 | 0x61
	i2c_disableInterrupt(I2C0_BASE, I2C_INTERRUPT_FILTER);
}

static void i2c_oled_init() {
	static u8 msg[] = {
		0xae, 0xa8, 0x3f, 0xd3,
		0x00, 0x40, 0xa1, 0xc8,
		0xda, 0x32, 0xa4, 0xa6,
		0xd5, 0x80, 0x8d, 0x14,
		0x20, 0x20, //0x21 v, 0x20, h
		0xaf, 0x21,
		0x00, 0x7f, 0x22, 0x00,
		0x07
	};
	i2c_masterStartBlocking(I2C0_BASE);
	i2c_txByte(I2C0_BASE, 0x3c << 1);
	i2c_txNackBlocking(I2C0_BASE);
	i2c_txByte(I2C0_BASE, 0x00);
	i2c_txNackBlocking(I2C0_BASE);
	for(u8 i = 0; i < sizeof(msg); i++) {
		i2c_txByte(I2C0_BASE, msg[i]);
		i2c_txAckBlocking(I2C0_BASE);
	}
	i2c_masterStopBlocking(I2C0_BASE);
}

static void i2c_proc(int v) {
	i2c_masterStartBlocking(I2C0_BASE);
	i2c_txByte(I2C0_BASE, 0x3c<<1);
	i2c_txNackBlocking(I2C0_BASE);
	i2c_txByte(I2C0_BASE, 0x40);
	i2c_txNackBlocking(I2C0_BASE);
	char sw = 0;
	for(int i = 0; i < 1024; i++) {
		if(i % v == 0)
			sw = !sw;
		char sv = sw ? 0 : 0xff;
		i2c_txByte(I2C0_BASE, sv);
		i2c_txAckBlocking(I2C0_BASE);
	}
	i2c_masterStopBlocking(I2C0_BASE);
}
int font_pos(char c) {
	return (c - 0x20) * 8 + 4;
}
void i2c_clear() {
	i2c_masterStartBlocking(I2C0_BASE);
	i2c_txByte(I2C0_BASE, 0x3c<<1);
	i2c_txNackBlocking(I2C0_BASE);
	i2c_txByte(I2C0_BASE, 0x40);
	i2c_txNackBlocking(I2C0_BASE);
	for(short i = 0; i < 1024; i++) {
		i2c_txByte(I2C0_BASE, 0);
		i2c_txAckBlocking(I2C0_BASE);
	}
	i2c_masterStopBlocking(I2C0_BASE);

	i2c_masterStartBlocking(I2C0_BASE);
	i2c_txByte(I2C0_BASE, 0x3c<<1);
	i2c_txNackBlocking(I2C0_BASE);
	i2c_txByte(I2C0_BASE, 0x40);
	i2c_txNackBlocking(I2C0_BASE);
	for(short i = 0; i < 129; i++) {
		i2c_txByte(I2C0_BASE, i & 1 ? 0 : 127);
		i2c_txAckBlocking(I2C0_BASE);
	}
	i2c_masterStopBlocking(I2C0_BASE);
}

void i2c_main() {
	i2c_init();
	i2c_oled_init();
	i2c_clear();
	u8 c = 0;
	while(1) {
		i2c_proc(c++);
		clint_uDelay(100*1000);
	}

}
