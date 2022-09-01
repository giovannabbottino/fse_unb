#include "menu.h"

double kp;
double ki;
double kd;

void menuInicial(){
    int escolha;
    printf("\n<<<<< MENU >>>>>\n");
    printf("Defina as constantes, para:\n");
    printf("1. RASP 42\n");
    printf("2. RASP 43\n");
    printf("3. Escolher\n");

    scanf("%d", &escolha);

    switch(){
        case 1:
            kp = 30.0;
            ki = 0.2;
            kd = 400.0;
            break;
        case 2:
            kp = 20.0;
            ki = 0.1;
            kd = 100.0;
            break;
        case 3:
            printf("\nkp: ");
            scanf("%f", &kp);

            printf("\nki: ");
            scanf("%f", &ki);

            printf("\nkd: ");
            scanf("%f", &kd);
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
