# Trabalho 1
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)  ![C](https://img.shields.io/badge/Solutions-blue.svg?style=flat&logo=c) 

Este trabalho tem por objetivo a criação de um sistema distribuído para o controle e monitoramento de um grupo de sinais de trânsito. O sistema deve ser desenvolvido para funcionar em um conjunto de placas Raspberry Pi com um servidor central responsável pelo controle e interface com o usuário e servidores distribuídos para o controle local e monitoramento dos sinais do cruzamento junto aos respectivos sensores que monitoram as vias. Dentre os dispositivos envolvidos estão o controle de temporizaçãio e acionamento dos sinais de trânsito, o acionmento de botões de passagens de pedestres, o monitoramento de sensores de passagem de carros bem como a velocidade da via e o avanço de sinal vermelho.

## Executar

1. Clone esse [repositorio](https://github.com/giovannabbottino/fse_unb) 
```
git clone https://github.com/giovannabbottino/fse_unb
```
2. Entre na pasta `fse_unb/trabalho_1`
```
cd fse_unb/trabalho_1
```
3. O `servidor_central` deve estar ativo antes de rodar os `servidores_distribuidos`

3.1. Entre na pasta `servidor_central`
```
cd servidor_central
```
3.2. Se necessario, rode:
```
make clean
```
3.3. Dê build 
```
make all
```
4.4. Então, finalmente, lembre-se de colocar o valor da porta e do ip:
```
make run ip=127.0.0.1 porta_1=10161 porta_2=10165 porta_3=10167 porta_4=10169
```
4. Para cada uma das placas deve haver um `servidor_distribuido` rodando, por isso, em cada uma:

4.1. Entre na pasta `servidor_distribuido`
```
cd servidor_distribuido
```
4.2. Se necessario, rode:
```
make clean
```
4.3. Dê build 
```
make all
```
4.4. Então, finalmente, lembre-se de colocar o valor da porta, do ip e do cruzamento:
```
make run porta=10161 ip=127.0.0.1 cruzamento=1
```

```
make run porta=10165 ip=127.0.0.1 cruzamento=2
```

Obs: Na Rasp44 não foi possivel testar, apesar de conter o mesmo codigo sempre dava erros como `undefined reference to `wiringPiSetup'` 
```
make run porta=10167 ip=127.0.0.1 cruzamento=1
```

```
make run porta=10169 ip=127.0.0.1 cruzamento=2
```
Sendo a porta um inteiro entre 10161 e 10170, de acordo com o que foi disponibilizado pelo professor, já o ip o valor do servidor central, e o cruzamento entre 1 e 2.
