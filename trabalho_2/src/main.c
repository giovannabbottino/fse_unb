#include <stdio.h>
#include "uart.h"

int main(int argc, const char * argv[]) {
    uart_init("/dev/serial0"); 

    unsigned char tx_buffer[20];
    unsigned char *p_tx_buffer;
    
    p_tx_buffer = &tx_buffer[0];
    *p_tx_buffer++ = 'H';
    *p_tx_buffer++ = 'e';
    *p_tx_buffer++ = 'l';
    *p_tx_buffer++ = 'l';
    *p_tx_buffer++ = 'o';

    printf("Buffers de memória criados!\n");

    int size_write = uart_write(tx_buffer,  (p_tx_buffer - &tx_buffer[0]));

    sleep(1);

    //----- CHECK FOR ANY RX BYTES -----
    int buffer_size = 256;
    unsigned char buffer[256];
    int size_read = uart_read(buffer, buffer_size);
    if (size_read != -1){
        //Bytes received
        buffer[size_read] = '\0';
        printf("%i Bytes lidos : %s\n", size_read, buffer);
    }

   uart_close();
   return 0;
}

