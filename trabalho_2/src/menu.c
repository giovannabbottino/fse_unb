#include "menu.h"
#include "pid.h"

void menuInicial(){
    int escolha;
    printf("\n<<<<< MENU >>>>>\n");
    printf("Defina as constantes, para:\n");
    printf("1. RASP 42\n");
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
            menuInicial();
    }
}

void *menuHandlerThread(){
   menuInicial();
   while(1){

   }
};
