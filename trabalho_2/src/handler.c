#include "handler.h"

int comando = 0;
float tr = 0;
float temperatura_passada = 25;

void desligarHandler(){
    if(lcd_init() == -1) exit(1);
    lcd_clear();
    lcd_type_line("Finalizado");
    desliga();
    send_int(0);
}

void userHandler(int comando){
    switch (comando){
    case 0: 
        terminalHandler();
        break;
    case 2:
        desligarHandler();
        exit(0);
        break;
    case 3:
        uartHandler();
        break;
    case 4:
        desligarHandler();
        userHandler(get_comando());
        break;
    case 5:
        add_tempo(60000); // adciona 60 segundos
        send_time(duracao);
        userHandler(get_comando());
        break;
    case 6:
        rm_tempo(60000); // remove 60 segundos
        send_time(duracao);
        userHandler(get_comando());
        break;
    case 7:
        menu_programados();
        break;
    default:
        userHandler(get_comando());
    }
    usleep(500000);
}

void uartHandler(){
    int comando = 0;
    ultimaMudanca();
    while(comando == 0 || comando == 3){
        if (get_tempo_restante() > 0){

            float potenciometro = get_potenciometro_temp();
            double te;

            int BME280_response = get_temp(&te);
            BME280_response += 0;

            pid_atualiza_referencia(potenciometro);

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

            lcd_clear();
            lcd_type_line("UART TT ");
            lcd_type_float(get_tempo_restante()  / 10000);
            lcd_set_line(LCD_LINE_2);
            lcd_type_line("TR ");
            lcd_type_float(tr);
            lcd_type_line("  TI");
            lcd_type_float(ti);
            
            printf("Potenciometro TT %.2f TR %.2f\tTI %.2f\n",get_tempo_restante(), tr, ti);
            
            muda_temperatura(power);
            Data data = {ti, te, potenciometro, power_cooler, power_resistor};
            csv_append_data(data);
        } else {
            desligarHandler();
        }
        usleep(500000);
        comando = get_comando();
    }
    userHandler(comando);
}

void terminalHandler(){
    int comando = 0;
    ultimaMudanca();
    while(comando == 0){
        if (get_tempo_restante() >= 0){ 
            float temperatura_passada;

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
            lcd_type_line("Terminal TT ");
            lcd_type_float(get_tempo_restante() / 10000);
            lcd_set_line(LCD_LINE_2);
            lcd_type_line("TR ");
            lcd_type_float(tr);
            lcd_type_line("  TI");
            lcd_type_float(ti);

            printf("Terminal TT %.2f TR %.2f\tTI %.2f\n",get_tempo_restante(), tr, ti);
            
            Data data = {ti, te, tr, power_cooler, power_resistor};
            csv_append_data(data);

            muda_temperatura(power);
        } else{
            desligarHandler();
        }
        usleep(500000);
        comando = get_comando();
    }
    userHandler(comando);
}
