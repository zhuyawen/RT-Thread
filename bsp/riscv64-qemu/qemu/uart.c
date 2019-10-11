#include "platform.h"

static volatile uint8_t *uart = (void *)0x10000000;

#define REG_QUEUE     0
#define REG_LINESTAT  5
#define REG_STATUS_RX 0x01
#define REG_STATUS_TX 0x20

void uart_putc(uint8_t ch) {
  while ((uart[REG_LINESTAT] & REG_STATUS_TX) == 0);
  uart[REG_QUEUE] = ch;
  if (ch == '\n') uart_putc('\r');
}

int uart_getc(void) {
  if (uart[REG_LINESTAT] & REG_STATUS_RX) {
    return uart[REG_QUEUE];
  }
  return -1;
}