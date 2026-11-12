#include <reg51.h>

void uart_init(void) {
    TMOD = 0x20;
    TH1 = 0xFD;
    SCON = 0x50;
    TR1 = 1;
}

void uart_tx(char c) {
    SBUF = c;
    while (!TI);
    TI = 0;
}

void uart_send_str(char *s) {
    while (*s) uart_tx(*s++);
}

void main(void) {
    uart_init();
    uart_send_str("Hello from 8051 UART!
");
    while (1);
}
