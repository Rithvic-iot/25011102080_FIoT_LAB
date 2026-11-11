/*
 * ============================================================================
 * Experiment: CAT 7 (Week 7)
 * Title: 16x2 LCD Driver Development and Dynamic Display Control
 * Hardware: AT89S52 MCU, 16x2 HD44780 LCD (4-bit mode on Port 2), 4x4 Keypad (Port 1)
 * Description: Implements 4-bit parallel LCD driver, cursor positioning,
 *              dynamic integer printing, and interactive keypad character mover.
 *              Key 2: Up | Key 8: Down | Key 4: Left | Key 6: Right
 * ============================================================================
 */

#include <reg51.h>
#include <stdio.h>

/* LCD Control Pins on Port 2 */
sbit LCD_RS = P2^0;
sbit LCD_RW = P2^1;
sbit LCD_EN = P2^2;

/* Keypad Port */
#define KEYPAD_PORT P1

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++);
    }
}

void delay_us(unsigned int us) {
    while (us--);
}

void lcd_pulse_enable(void) {
    LCD_EN = 1;
    delay_us(5);
    LCD_EN = 0;
    delay_us(50);
}

void lcd_write_nibble(unsigned char nibble) {
    /* Place upper 4 bits on P2.4 - P2.7 */
    P2 = (P2 & 0x0F) | (nibble & 0xF0);
    lcd_pulse_enable();
}

void lcd_cmd(unsigned char cmd) {
    LCD_RS = 0; /* Command mode */
    LCD_RW = 0; /* Write mode */
    lcd_write_nibble(cmd & 0xF0);        /* Send high nibble */
    lcd_write_nibble((cmd << 4) & 0xF0); /* Send low nibble */
    delay_ms(2);
}

void lcd_data(unsigned char ch) {
    LCD_RS = 1; /* Data mode */
    LCD_RW = 0; /* Write mode */
    lcd_write_nibble(ch & 0xF0);        /* Send high nibble */
    lcd_write_nibble((ch << 4) & 0xF0); /* Send low nibble */
    delay_ms(1);
}

void lcd_init(void) {
    delay_ms(50); /* Power-on initialization delay (>40ms) */
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;

    /* Initialization sequence for 4-bit mode as per HD44780 datasheet */
    lcd_write_nibble(0x30); delay_ms(5);
    lcd_write_nibble(0x30); delay_us(150);
    lcd_write_nibble(0x30); delay_ms(1);
    lcd_write_nibble(0x20); delay_ms(1); /* Set to 4-bit mode */

    lcd_cmd(0x28); /* 4-bit, 2-line, 5x8 font */
    lcd_cmd(0x0C); /* Display ON, Cursor OFF */
    lcd_cmd(0x06); /* Entry mode: Increment cursor */
    lcd_cmd(0x01); /* Clear display */
    delay_ms(3);
}

void lcd_goto(unsigned char row, unsigned char col) {
    unsigned char addr;
    if (row == 0) {
        addr = 0x80 + col; /* Line 1 start address: 0x00 */
    } else {
        addr = 0xC0 + col; /* Line 2 start address: 0x40 */
    }
    lcd_cmd(addr);
}

void lcd_puts(char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}

void lcd_print_number(int val) {
    char buf[8];
    sprintf(buf, "%d", val);
    lcd_puts(buf);
}

unsigned char keypad_get_key(void) {
    unsigned char row, col;
    unsigned char row_mask[4] = {0xFE, 0xFD, 0xFB, 0xF7};

    for (row = 0; row < 4; row++) {
        KEYPAD_PORT = row_mask[row] | 0xF0;
        col = (KEYPAD_PORT >> 4) & 0x0F;
        if (col != 0x0F) {
            delay_ms(20);
            col = (KEYPAD_PORT >> 4) & 0x0F;
            if (col != 0x0F) {
                if (row == 0 && col == 0x0D) return 2; /* Up key */
                if (row == 1 && col == 0x0E) return 4; /* Left key */
                if (row == 1 && col == 0x0B) return 6; /* Right key */
                if (row == 2 && col == 0x0D) return 8; /* Down key */
            }
        }
    }
    return 0;
}

void main(void) {
    unsigned char cur_row = 0;
    unsigned char cur_col = 0;
    unsigned char key;

    lcd_init();

    /* Task 7A: Static String Display */
    lcd_goto(0, 0);
    lcd_puts("IOT LAB CAT-7");
    lcd_goto(1, 0);
    lcd_puts("16x2 LCD DRIVER");
    delay_ms(2000);
    lcd_cmd(0x01); /* Clear display */

    /* Initial draw */
    lcd_goto(cur_row, cur_col);
    lcd_data('A');

    while (1) {
        key = keypad_get_key();
        if (key != 0) {
            /* Erase old character */
            lcd_goto(cur_row, cur_col);
            lcd_data(' ');

            /* Move cursor based on key */
            if (key == 2 && cur_row > 0) cur_row--;         /* Up */
            else if (key == 8 && cur_row < 1) cur_row++;    /* Down */
            else if (key == 4 && cur_col > 0) cur_col--;    /* Left */
            else if (key == 6 && cur_col < 15) cur_col++;   /* Right */

            /* Render character at new position */
            lcd_goto(cur_row, cur_col);
            lcd_data('A');

            /* Wait for button release */
            while (keypad_get_key() != 0);
            delay_ms(50);
        }
    }
}
