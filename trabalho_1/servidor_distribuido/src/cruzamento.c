#include "cruzamento.h"
#include "mensagem.h"

VariaveisCruzamento var = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
Cruzamento * cruzamento = {NULL};
int tipo;

static struct timeval ultimasMudancas;

float duracao;
bool mudar = false;

void *cruzamentoHandlerThread() {
    printf("\nComecei a thread de cruzamento...\n");

    limpaCruzamento(cruzamento);

    ligarLed(cruzamento->semaforos[0]->leds[0]); // liga semaforo principal led verde 
    cruzamento->semaforos[0]->led_ligado = 0;
    ligarLed(cruzamento->semaforos[1]->leds[2]); // liga semaforo auxiliar led vermelho
    cruzamento->semaforos[1]->led_ligado = 2;
    cruzamento->estado = 1;

    esvaziaMensagens();
    
    ultimaMudanca(); 
    printf("\nIniciando loop...\n");
    for(;;){
        handle();
    }
}

void handle(){
    struct timeval agora;
    gettimeofday(&agora, NULL); 
    duracao = time_diff(&ultimasMudancas, &agora);
    switch (cruzamento->estado) {
        /*
        estado 
        1 = principal verde
        0 = principal vermelho
        2 = emergencia
        3 = noturno
        */
        case 1: // ligado
            if((duracao >= DELAY_PRINCIPAL_VERDE_MINIMO && mudar == true) || duracao >= DELAY_PRINCIPAL_VERDE_MAXIMO){
                cruzamento->semaforos[0]->led_ligado = verdeParaVermelho(cruzamento->semaforos[0]->leds);
                cruzamento->semaforos[1]->led_ligado = vermelhoParaVerde(cruzamento->semaforos[1]->leds);
                cruzamento->estado = 0;
                mudar = false;
                ultimaMudanca();
            }
            break;
        case 0: // desligado
            if((duracao >= DELAY_AUXILIAR_VERDE_MINIMO && mudar == true) || duracao >= DELAY_AUXILIAR_VERDE_MAXIMO){
                cruzamento->semaforos[0]->led_ligado = verdeParaVermelho(cruzamento->semaforos[1]->leds);
                cruzamento->semaforos[0]->led_ligado = vermelhoParaVerde(cruzamento->semaforos[0]->leds);
                cruzamento->estado = 1; // ligado
                mudar = false;
                ultimaMudanca();
            }
            break;
        case 2: // emergencia    
            ligarLed(cruzamento->semaforos[0]->leds[0]); // liga semaforo principal verde
             cruzamento->semaforos[0]->led_ligado = 0;
            ligarLed(cruzamento->semaforos[1]->leds[2]); // liga semaforo auxiliar vermelho
            cruzamento->semaforos[1]->led_ligado = 2;
            cruzamento->estado = 2;
            ultimaMudanca();
            break;
        case 3: // noturno
            limpaCruzamento(cruzamento);
            if( duracao >= DELAY_AMARELO ){
            ligarLed(cruzamento->semaforos[0]->leds[1]);
            cruzamento->semaforos[0]->led_ligado = 1;
            ligarLed(cruzamento->semaforos[1]->leds[1]);
            cruzamento->semaforos[1]->led_ligado = 1;
            cruzamento->estado = 3;
            delay(DELAY_AMARELO);
            ultimaMudanca();
            }
            break;
    }
}

struct timeval ultimasMudancasBotao;

void botao_apertado() {
	struct timeval agora;
	unsigned long duracao;

	gettimeofday(&agora, NULL);
    duracao = time_diff(&ultimasMudancasBotao, &agora);

	if (duracao > IGNORE_CHANGE_BELOW_USEC) {
        printf("\nPedestre!\n");
        mudar = true;
	}
	ultimasMudancasBotao = agora;
}


bool estado = false;
void sensor_passagem(){
    if (estado) {
        if (cruzamento->estado == 1){
            printf("\nAvanço no vermelho!\n");
            soarAlarme();
            mensagens->avanco_vermelho++;
            estado = false;
        }
    }
    else {
        printf("\nCarro esperando passagem!\n");
        estado = true;
        mensagens->passagem_carro++;
        if (cruzamento->estado == 1){
            mudar = true;
        }
    }
}

struct timeval ultimasMudancasVelocidadeA, ultimasMudancasVelocidadeB;
bool estado_velocidade_a = false;
bool estado_velocidade_b = false;
void velocidade_a(){
    if (estado_velocidade_a) {
        if (cruzamento->estado == 0){
            printf("\nAvanço no vermelho!\n");
            soarAlarme();
            mensagens->avanco_vermelho++;
        } else {
            gettimeofday(&ultimasMudancasVelocidadeA, NULL);
        }
    }
    else {
        printf("\nCarro esperando passagem!\n");
        estado_velocidade_a = true;
        mensagens->passagem_carro++;
        if (cruzamento->estado == 0){
            mudar = true;
        }
    }
    if (estado_velocidade_b){
        estado_velocidade_b = false;
        
        struct timeval agora;
        unsigned long duracao;
        gettimeofday(&agora, NULL);
        duracao = time_diff(&ultimasMudancasVelocidadeB, &agora);
        float velocidade = 3.6 * 1 / duracao;
        if (velocidade >= 66){
            printf("\nMuito Veloz!\n");
            soarAlarme();
            mensagens->acima_velocidade++;
        } 
        if (cruzamento->estado == 0){
            printf("\nAvanço no vermelho!\n");
            soarAlarme();
            mensagens->avanco_vermelho++;
        }
        mensagens->velocidade_media = (velocidade + mensagens->velocidade_media) / 2;
    } 
}

void velocidade_b(){
    if (estado_velocidade_a){
        estado_velocidade_a = false;
        
        struct timeval agora;
        unsigned long duracao;
        gettimeofday(&agora, NULL);
        duracao = time_diff(&ultimasMudancasVelocidadeA, &agora);
        float velocidade = 3.6 * 1 / duracao;
        if (velocidade >= 66){
            printf("\nMuito Veloz!\n");
            soarAlarme();
            mensagens->acima_velocidade++;
        } 
        if (cruzamento->estado == 0){
            printf("\nAvanço no vermelho!\n");
            soarAlarme();
            mensagens->avanco_vermelho++;
        }
        mensagens->velocidade_media = (velocidade + mensagens->velocidade_media) / 2;
    } 
    if (estado_velocidade_b){
        if (cruzamento->estado == 0){
            printf("\nAvanço no vermelho!\n");
            soarAlarme();
            mensagens->avanco_vermelho++;
        } else {
            gettimeofday(&ultimasMudancasVelocidadeB, NULL);
        }
    } else {
        printf("\nCarro esperando passagem!\n");
        estado_velocidade_b = true;
        mensagens->passagem_carro++;
        if (cruzamento->estado == 0){
            mudar = true;
        }
    }
}

void configuraCruzamento(){ 
    printf("\nConfigurando cruzamento...\n");
    cruzamento = (Cruzamento*)realloc(cruzamento, sizeof(Cruzamento));
    
    int semaforos1[3] = {var.semaforo_1_verde, var.semaforo_1_amarelo, var.semaforo_1_vermelho};
    int velocidade1[2] = {var.sensor_velocidade_1_A, var.sensor_velocidade_1_B};

    Semaforo * s1 = configuraSemaforo(
            semaforos1,
            var.botao_pedestre_1,
            var.sensor_passagem_1,
            velocidade1
        );

    int semaforos2[3] = {var.semaforo_2_verde, var.semaforo_2_amarelo, var.semaforo_2_vermelho};
    int velocidade2[2] = {var.sensor_velocidade_2_A, var.sensor_velocidade_2_B};
    Semaforo * s2 = configuraSemaforo(
            semaforos2,
            var.botao_pedestre_2,
            var.sensor_passagem_2,
            velocidade2
        );

    wiringPiISR(s1->botao, INT_EDGE_BOTH, botao_apertado);
    wiringPiISR(s2->botao, INT_EDGE_BOTH, botao_apertado);

    wiringPiISR(s1->sensor_passagem, INT_EDGE_BOTH , sensor_passagem);
    wiringPiISR(s2->sensor_passagem, INT_EDGE_BOTH , sensor_passagem);

    wiringPiISR(s1->sensores_velocidade[0], INT_EDGE_BOTH , velocidade_a);
    wiringPiISR(s1->sensores_velocidade[1], INT_EDGE_BOTH, velocidade_b);

    cruzamento->semaforos[0] = s2;
    cruzamento->semaforos[1] = s1;
    cruzamento->estado = 1; // ligado o cruzamento 0
}

float time_diff(struct timeval *start, struct timeval *end){
    return ((end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec) )* 1000.0;
}

void ultimaMudanca(){
    gettimeofday(&ultimasMudancas, NULL);
}

void limpaCruzamento(){
    cruzamento->semaforos[0]->led_ligado = apagaLeds(cruzamento->semaforos[0]);
    cruzamento->semaforos[1]->led_ligado = apagaLeds(cruzamento->semaforos[1]);
}

void tipoCruzamento(int t){
    tipo = t;
    printf("\nCruzamento %d...\n", tipo);
    if (tipo == 1){
        var.semaforo_1_verde = CRUZAMENTO_1_SEMAFORO_1_VERDE;
        var.semaforo_1_amarelo = CRUZAMENTO_1_SEMAFORO_1_AMARELO;
        var.semaforo_1_vermelho = CRUZAMENTO_1_SEMAFORO_1_VERMELHO;
        var.semaforo_2_verde = CRUZAMENTO_1_SEMAFORO_2_VERDE;
        var.semaforo_2_amarelo = CRUZAMENTO_1_SEMAFORO_2_AMARELO;
        var.semaforo_2_vermelho = CRUZAMENTO_1_SEMAFORO_2_VERMELHO;
        var.botao_pedestre_1 = CRUZAMENTO_1_BOTAO_PEDESTRE_1;
        var.botao_pedestre_2 = CRUZAMENTO_1_BOTAO_PEDESTRE_2;
        var.sensor_passagem_1 = CRUZAMENTO_1_SENSOR_PASSAGEM_1;
        var.sensor_passagem_2 = CRUZAMENTO_1_SENSOR_PASSAGEM_2;
        var.sensor_velocidade_1_A = CRUZAMENTO_1_SENSOR_VELOCIDADE_1_A;
        var.sensor_velocidade_1_B = CRUZAMENTO_1_SENSOR_VELOCIDADE_1_B;
        var.sensor_velocidade_2_A = CRUZAMENTO_1_SENSOR_VELOCIDADE_2_A;
        var.sensor_velocidade_2_B = CRUZAMENTO_1_SENSOR_VELOCIDADE_2_B;
    } else {
        var.semaforo_1_verde = CRUZAMENTO_2_SEMAFORO_1_VERDE;
        var.semaforo_1_amarelo = CRUZAMENTO_2_SEMAFORO_1_AMARELO;
        var.semaforo_1_vermelho = CRUZAMENTO_2_SEMAFORO_1_VERMELHO;
        var.semaforo_2_verde = CRUZAMENTO_2_SEMAFORO_2_VERDE;
        var.semaforo_2_amarelo = CRUZAMENTO_2_SEMAFORO_2_AMARELO;
        var.semaforo_2_vermelho = CRUZAMENTO_2_SEMAFORO_2_VERMELHO;
        var.botao_pedestre_1 = CRUZAMENTO_2_BOTAO_PEDESTRE_1;
        var.botao_pedestre_2 = CRUZAMENTO_2_BOTAO_PEDESTRE_2;
        var.sensor_passagem_1 = CRUZAMENTO_2_SENSOR_PASSAGEM_1;
        var.sensor_passagem_2 = CRUZAMENTO_2_SENSOR_PASSAGEM_2;
        var.sensor_velocidade_1_A = CRUZAMENTO_2_SENSOR_VELOCIDADE_1_A;
        var.sensor_velocidade_1_B = CRUZAMENTO_2_SENSOR_VELOCIDADE_1_B;
        var.sensor_velocidade_2_A = CRUZAMENTO_2_SENSOR_VELOCIDADE_2_A;
        var.sensor_velocidade_2_B = CRUZAMENTO_2_SENSOR_VELOCIDADE_2_B;
    }
}
