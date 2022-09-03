#include "uart.h"
static int uart_file = -1;
static const char *FILE_DESCRIPTOR="/dev/serial0";

int uart_config(){

  uart_file = open(FILE_DESCRIPTOR, O_RDWR | O_NOCTTY | O_NDELAY); 
  if(uart_file == -1){
    printf("Erro - Não foi possível iniciar a UART.\n");
    return -1;
  }

  struct termios options;
  tcgetattr(uart_file, &options);
  options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(uart_file, TCIFLUSH);
  tcsetattr(uart_file, TCSANOW, &options);
  return 1;
}

int uart_write(unsigned char* message, unsigned int size){
  int count = write(uart_file, message, size);
  return count;
}

int uart_read(unsigned char* buffer, unsigned int index){
  int count = read(uart_file, (void*)buffer, index);
  return count;
}

void uart_close(){
  close(uart_file);
}
