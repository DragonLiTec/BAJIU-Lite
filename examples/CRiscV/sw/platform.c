#include "platform.h"
#include "stdio.h"

void trap_entry();

void platform_init() {
    csr_write(mtvec, trap_entry);
	csr_set(mie, MIE_MEIE);
	csr_write(mstatus, MSTATUS_MPP | MSTATUS_MIE);
}

int _write(int file, const char *data, int len)
{
	(void)file;
	for(int i = 0; i < len; i++) {
		uart_write(UART0_BASE, data[i]);
	}
	return len;
}
