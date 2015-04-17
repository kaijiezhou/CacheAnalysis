#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>
#include "degree_analysis_kernal.c"

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	(void) r0;
	(void) r1;
	(void) atags;
	char c;
    int x = 0;
 
	uart_init();
	uart_puts("Hello, kernel World!\r\n");
    init_ccr();

    //counter_start();
    //x = x + 1;
    //counter_stop();
    //counter_print();
    //uart_puts("rwh");
    degreeCalculateTime();
	while ( true ) {
		c = uart_getc();
		if (c == '\r') {
			uart_puts("\r\n");
		} else {
			uart_putc(c);
		}
	}

}

