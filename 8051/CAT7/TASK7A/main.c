#include <reg51.h>

sbit RS = P2^0;
sbit RW = P2^1;
sbit E  = P2^2;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) for (j = 0; j < 120; j++);
}

void lcd_pulse(void) {
    E = 1; delay_ms(2); E = 0; delay_ms(2);
}

void lcd_cmd(unsigned char cmd) {
    RS = 0; RW = 0;
    P2 = (P2 & 0x0F) | (cmd & 0xF0); lcd_pulse();
    P2 = (P2 & 0x0F) | ((cmd << 4) & 0xF0); lcd_pulse();
}

void lcd_data(unsigned char d) {
    RS = 1; RW = 0;
    P2 = (P2 & 0x0F) | (d & 0xF0); lcd_pulse();
    P2 = (P2 & 0x0F) | ((d << 4) & 0xF0); lcd_pulse();
}

void lcd_init(void) {
    delay_ms(20);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}

void main(void) {
    lcd_init();
    lcd_data('O'); lcd_data('K');
    while (1);
}
