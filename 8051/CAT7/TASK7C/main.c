#include <reg51.h>

sbit RS = P2^0;
sbit RW = P2^1;
sbit E  = P2^2;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) for (j = 0; j < 120; j++);
}

void lcd_pulse(void) { E = 1; delay_ms(2); E = 0; delay_ms(2); }

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
    lcd_cmd(0x28); lcd_cmd(0x0C); lcd_cmd(0x06); lcd_cmd(0x01);
}

unsigned char row = 0, col = 0;

void update_pos(void) {
    lcd_cmd((row == 0 ? 0x80 : 0xC0) + col);
    lcd_data('A');
}

void main(void) {
    lcd_init();
    update_pos();
    while (1) {
        /* Poll keypad on Port 1 */
        if ((P1 & 0x01) == 0) { row = 0; lcd_cmd(0x01); update_pos(); delay_ms(200); }
        if ((P1 & 0x02) == 0) { row = 1; lcd_cmd(0x01); update_pos(); delay_ms(200); }
    }
}
