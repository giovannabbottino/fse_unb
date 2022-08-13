# Trabalho 2
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)  ![C](https://img.shields.io/badge/Solutions-blue.svg?style=flat&logo=c) 


Este trabalho tem por objetivo a implementação de um sistema (que simula) o controle de um Air Fryer com controle digital.
O trablho envolve o desenovlimento do software que efetua o controle completo da AirFyer incluindo ligar/desligar o equipamento, controlar a temperatura, temporização e diferentes modos de alimentos. Especificamente a temperatura do forno é controlada à partir de dois elementos atuadores: um resistor de potência de 15 Watts utilizado para aumentar temperatura e; uma ventoinha que puxa o ar externo (temperatura ambiente) para reduzir a temperatura do sistema.
Os comandos do usuário do sistema para definir a temperatura desejada serão controlados de três maneiras:

Através de botões no painel de controle (Via UART);
Através de entrada de teclado no terminal;
Seguindo os tempo e temperaturas pré-definidas para cada tipo de alimento.

## Info para o desenvolvimento
```
git config user.name "giovannabbottino"
git config user.email giovannabbottino@gmail.com
https://youtu.be/87kvtAH7zsM

Execício 1 - UART - Rasp44 

ssh <user>@164.41.98.17 -p 13508

Exercício 2 - UART MODBUS - Rasp43

ssh <user>@164.41.98.26 -p 13508
```