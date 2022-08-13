# Fundamentos de Sistemas Embarcados
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)  ![C](https://img.shields.io/badge/Solutions-blue.svg?style=flat&logo=c) 

Repositório para a matéria de Fundamentos de Sistemas Embarcados 1.2022 da faculdade do Gama Universidade de Brasília.

## Trabalho 1

Este trabalho tem por objetivo a criação de um sistema distribuído para o controle e monitoramento de um grupo de sinais de trânsito. O sistema deve ser desenvolvido para funcionar em um conjunto de placas Raspberry Pi com um servidor central responsável pelo controle e interface com o usuário e servidores distribuídos para o controle local e monitoramento dos sinais do cruzamento junto aos respectivos sensores que monitoram as vias. Dentre os dispositivos envolvidos estão o controle de temporizaçãio e acionamento dos sinais de trânsito, o acionmento de botões de passagens de pedestres, o monitoramento de sensores de passagem de carros bem como a velocidade da via e o avanço de sinal vermelho.

## Trabalho 2

Este trabalho tem por objetivo a implementação de um sistema (que simula) o controle de um Air Fryer com controle digital.
O trablho envolve o desenovlimento do software que efetua o controle completo da AirFyer incluindo ligar/desligar o equipamento, controlar a temperatura, temporização e diferentes modos de alimentos. Especificamente a temperatura do forno é controlada à partir de dois elementos atuadores: um resistor de potência de 15 Watts utilizado para aumentar temperatura e; uma ventoinha que puxa o ar externo (temperatura ambiente) para reduzir a temperatura do sistema.
Os comandos do usuário do sistema para definir a temperatura desejada serão controlados de três maneiras:

Através de botões no painel de controle (Via UART);
Através de entrada de teclado no terminal;
Seguindo os tempo e temperaturas pré-definidas para cada tipo de alimento.