#include "menu.h"

void menu_programados(){
    int escolha;
    printf("\n<<<<< MENU >>>>>\n");
    printf("Qual alimento?:\n");
    printf("1. Galinha\n");
    printf("2. Nugget\n");
    printf("3. Batata frita\n");

    scanf("%d", &escolha);

    switch(escolha){
        case 1:
            tr = 20.0;
            duracao = 10000; // adciona 10 segundos
            terminalHandler();
            break;
        case 2:
            tr = 30.0;
            duracao = 30000; // adciona 30 segundos
            terminalHandler();
            break;
        case 3:
            tr = 25.0;
            duracao = 20000; // adciona 30 segundos
            terminalHandler();
            break;
        default:
            printf("\nSelecione uma opção válida\n");
            menu_programados();
    }
}

void menu_modo(){
    if(lcd_init() == -1) exit(1);
    lcd_clear();

    int escolha;
    printf("\n<<<<< MENU >>>>>\n");
    printf("Defina o modo\n");
    printf("1. Terminal\n");
    printf("2. UART\n");

    scanf("%d", &escolha);

    switch(escolha){
        case 1:
            printf("Iniciando modo terminal...\n");
            printf("Defina a temperatura:\n");
            scanf("%f",&tr);
            printf("Defina a duracao:\n");
            scanf("%f",&duracao);
            terminalHandler();
            break;
        case 2:
            printf("Iniciando modo UART...\n");
            printf("Aguardando...\n");
            userHandler(3);
            break;
        default:
            printf("\nSelecione uma opção válida\n");
            menu_modo();
    }
}


void menu_inicial(){
    int escolha;
    printf("\n<<<<< MENU >>>>>\n");
    printf("Defina as constantes, para:\n");
    printf("1. RASP 44\n");
    printf("2. RASP 43\n");
    printf("3. Escolher\n");

    scanf("%d", &escolha);

    switch(escolha){
        case 1:
            pid_configura_constantes(30.0, 0.2, 400.0);
            break;
        case 2:
            pid_configura_constantes(20.0, 0.1, 100.0);
            break;
        case 3:
            printf("\nKp: ");
            double Kp;
            scanf("%f", &Kp);
            double Ki;
            printf("\nKi: ");
            scanf("%f", &Ki);
            double Kd;
            printf("\nKd: ");
            scanf("%f", &Kd);
            pid_configura_constantes(Kp, Ki, Kd);
            break;
        default:
            printf("\nSelecione uma opção válida\n");
            menu_inicial();
    }
    menu_modo();
}
