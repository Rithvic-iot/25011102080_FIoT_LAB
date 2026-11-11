/*
 * ============================================================================
 * Experiment: CAT 6 (Week 6)
 * Title: 8051 UART Driver and Serial Debugging
 * Hardware: AT89S52 MCU, CP2102 USB-to-TTL Serial Converter, PC with PuTTY
 * Description: 9600-8-N-1 UART driver using Timer 1 in Mode 2 (8-bit auto-reload).
 *              Task A: String transmission to PC terminal ("Hello from 8051").
 *              Task B: Interactive terminal echo.
 *              Task C: Interrupt-driven RX circular buffer.
 * ============================================================================
 */

#include <reg51.h>

#define RX_BUFFER_SIZE 32
volatile char rx_buffer[RX_BUFFER_SIZE];
volatile unsigned char rx_head = 0;
volatile unsigned char rx_tail = 0;

void uart_init(void) {
    /*
     * Configure Timer 1 for Baud Rate Generation:
     * Mode 2: 8-bit Auto-Reload
     * SMOD = 0, f_crystal = 11.0592 MHz
     * Reload value for 9600 baud = 256 - ((11059200 / (12 * 32)) / 9600)
     *                            = 256 - 3 = 253 = 0xFD
     */
    TMOD = (TMOD & 0x0F) | 0x20; /* Timer 1 Mode 2 */
    TH1 = 0xFD;
    TL1 = 0xFD;
    TR1 = 1;                     /* Start Timer 1 */

    /* Configure Serial Port Control (SCON):
     * Mode 1: 8-bit UART, variable baud
     * REN = 1: Enable reception
     * SCON = 0x50 (0101 0000b)
     */
    SCON = 0x50;

    /* Enable Serial Interrupt */
    ES = 1;
    EA = 1;
}

void uart_send_char(char ch) {
    SBUF = ch;
    while (TI == 0); /* Wait for transmission to complete */
    TI = 0;          /* Clear transmission flag */
}

void uart_send_string(char *str) {
    while (*str) {
        uart_send_char(*str++);
    }
}

/* UART Interrupt Service Routine */
void serial_ISR(void) interrupt 4 {
    if (RI) {
        char ch = SBUF;
        RI = 0; /* Clear receive interrupt flag */

        /* Store in ring buffer */
        rx_buffer[rx_head] = ch;
        rx_head = (rx_head + 1) % RX_BUFFER_SIZE;
    }
    if (TI) {
        /* Handled synchronously in uart_send_char */
    }
}

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++);
    }
}

void main(void) {
    char received_char;

    uart_init();

    /* Task A: Initial banner transmission */
    uart_send_string("\r\n========================================\r\n");
    uart_send_string("  Foundations of IoT - 8051 UART Ready  \r\n");
    uart_send_string("  Baud: 9600 bps | Config: 8-N-1       \r\n");
    uart_send_string("  Message: Hello from 8051!             \r\n");
    uart_send_string("========================================\r\n\r\n");

    while (1) {
        /* Task B: Interactive Echo from RX ring buffer */
        if (rx_head != rx_tail) {
            received_char = rx_buffer[rx_tail];
            rx_tail = (rx_tail + 1) % RX_BUFFER_SIZE;

            /* Echo character back to PC */
            uart_send_char(received_char);

            /* Auto-insert linefeed on carriage return */
            if (received_char == '\r') {
                uart_send_char('\n');
            }
        }
    }
}
