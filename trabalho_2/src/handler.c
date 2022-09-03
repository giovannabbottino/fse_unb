#include "handler.h"

void uartHandler(){

}

void terminalHandler(float tr){
    int comando = 0;
    float temperatura_passada;
    while(comando == 0){
        usleep(500000);

        double te;
        int BME280_response = get_temp(&te);
        BME280_response += 0;

        pid_atualiza_referencia(tr);

        float ti = get_TI();
        if(ti < 0 || ti > 100){
            ti = temperatura_passada;
        }
        temperatura_passada = ti;

        float power = pid_controle(ti);
        float power_resistor, power_cooler;
        if(power < 0){
            power_cooler = power * -1;
            if(power_cooler < 40) power_cooler = 40;
            power_resistor = 0;
        } else {
            power_cooler = 0;
            power_resistor = power;
        }
 
        send_int(power);
        send_float(tr);
        
        lcd_clear();
        lcd_type_line("Terminal TR ");
        lcd_type_float(tr);
         lcd_set_line(LCD_LINE2);
        lcd_type_line("TE ");
        lcd_type_float(te);
        lcd_type_line("  TI");
        lcd_type_float(ti);
        
        printf("Terminal TR %.2f\tTE %.2f\tTI %.2f\n",tr, te, ti);
        
        muda_temperatura(power);
        // daqui para baixo mudar
        comando = get_comando();
    }
}
