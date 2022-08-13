#ifndef CRUZAMENTO_H
#define CRUZAMENTO_H

#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART

void uart_init(char * uart_filestream_path);
int uart_read(Byte *buffer, unsigned int buffer_size);
int uart_write(Byte *buffer, unsigned int buffer_size);
void uart_close();

#endif