#include "temperatura.h"

void inicia_temperatura(){
    wiringPiSetup();

    pinMode(RESISTOR, OUTPUT);
    pinMode(COOLER, OUTPUT);

    softPwmCreate(RESISTOR,1,100);
    softPwmCreate(COOLER,1,100);
}

void muda_temperatura(double temperatura){
    if(temperatura < 0){
        temperatura *= -1;
        if(temperatura < 40) 
            temperatura = 40;
        softPwmWrite(COOLER,temperatura);
        softPwmWrite(RESISTOR,0);
    } else{
        softPwmWrite(RESISTOR,temperatura);
        softPwmWrite(COOLER,0);
    }
}

void desliga(){
    softPwmWrite(RESISTOR,0);
    softPwmWrite(COOLER,0);
}
