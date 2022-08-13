#include "uart.h"

static int uart_filestream = -1;

void uart_init(char * uart_filestream_path){

	uart_filestream = open(uart_filestream_path, O_RDWR | O_NOCTTY | O_NDELAY);
    /* Open in non blocking read/write mode
    O_RDWR access mode read/write
    O_NOCTTY file status flags - it will not become the process's controlling terminal
     even if the process does not have one
    O_NDELAY the file is opened in nonblocking mode.*/

	if (uart_filestream < 0){
        perror("Erro - Não foi possível iniciar a UART.\n");
        exit(0);
    }
    printf("UART inicializada!\n"); 

	struct termios options;
	tcgetattr(uart_filestream, &options);
    /* 
    Set baud rate
    termios_p to speed B9600
    Character size mask CS8
    CLOCAL - Ignore modem control lines.
    CREAD - Enable receiver.
    IGNPAR - Ignore framing errors and parity errors.
    TCIFLUSH - flushes data received but not read.
    TCSANOW - the change occurs immediately.
    */
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart_filestream, TCIFLUSH);
	tcsetattr(uart_filestream, TCSANOW, &options);
}

int uart_read(Byte *buffer, unsigned int buffer_size){
	if(uart_filestream != -1){
		int size = read(uart_filestream, (void*)buffer, buffer_size);
        if (size < 0){
            perror("Erro na leitura.\n"); //An error occured (will occur if there are no bytes)
        }
        else if (size == 0){
            printf("Nenhum dado disponível.\n"); //No data waiting
        }
        else{
            return size;
        }
	}
	return -1;
}

int uart_write(Byte *buffer, unsigned int buffer_size){

	if(uart_filestream != -1){
		int size = write(uart_filestream, buffer, buffer_size);
        if (size < 0){
            perror("UART TX error\n");
        }
        else{
            printf("escrito.\n");
            return size;
        }
	}
	return -1;
}

void uart_close(){
	close(uart_filestream);
}
