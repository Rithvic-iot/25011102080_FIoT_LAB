#include <reg51.h>

void uart_init(void) {
    TMOD = 0x20;
    TH1 = 0xFD;
    SCON = 0x50;
    TR1 = 1;
    ES = 1;
    EA = 1;
}

void uart_isr(void) interrupt 4 {
    if (RI) {
        char c = SBUF;
        RI = 0;
        SBUF = c;
        while (!TI);
        TI = 0;
    }
}

void main(void) {
    uart_init();
    while (1);
}
