#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>         
#include <fcntl.h>          
#include <termios.h>        

void uart_close();
int uart_config();
int uart_read(unsigned char* message, unsigned int size);
int uart_write(unsigned char* buffer, unsigned int index);
#endif