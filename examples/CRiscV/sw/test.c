#include <stdio.h>
#include <stdlib.h>

#include "platform.h"
#include "timer.h"


void interrupt_handler() {
	puts(__func__);
	while(1) {};
}

int main() {

	platform_init();

	//can't use printf, because this newlib impl not Low memory friendly
    puts("Hello CriscV!");

	int a = 0;
	int b = 1;
	int c = 2;
	for(int i = 0; i <= 'z' - 'A'; i++) {
		a += i;
        b += a;
		c += a + b;
		uart_write(UART0_BASE, 'A'+i);
		timer_usleep(50*1000);
	}
	uart_write(UART0_BASE, '\n');
	uart_write(UART0_BASE, '\r');

	return c;
}
