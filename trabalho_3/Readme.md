# Trabalho Final 

## Alunos
|Matrícula | Aluno |
| -- | -- |
| 18/0119818  |  Felipe Boccardi Silva Agustini |
| 17/0011267  |  Giovanna Borges Bottino |


## Objetivos

O objetivo deste trabalho é criar sensores e atuadores distribuídos baseados nos microcontroladores ESP32 interconectados via Wifi através do protocolo MQTT, podendo ser aplicada em diversos contextos de automação a exemplo das áreas de Automação Residencial, Predial ou Industrial.

Os microcontroladores ESP32 irão controlar a aquisição de dados de sensores, botões e chaves e acionar saídas como leds, dentre outras. Haverão dois modos de operação dos dispositivos: modo energia que representa o dispositivo ligado à tomada e modo bateria que representa o dispositivo que deverá operar em modo de baixo consumo.

Toda a comunicação será feita via rede Wifi com o protocolo MQTT e será provido um servidor central para cadastro e controle dos dispositivos através da plataforma Thingsboard.


## Recursos utilizados

- **PlatformIO V. 6.1.5a3**
- **Espressif 32 V. 5.1.1**


## Utilização

Baixe o repositorio e entre na pasta do trabalho 3

```
$ git clone https://github.com/giovannabbottino/fse_unb.git
$ cd trabalho_3/
```
Em seguida, utilizando a extensão do **platformIO** para o vscode abra o projeto
e um novo terminal.
no terminal insira o comando 

```
/trabalho_3 $ pio run -t menuconfig
```
para acessar a tela de configurações
na tela de configuração
procure pela opção ```Project Configuration``` e em seguida ```Wifi Configuration``` 

Lá dentro é necessario inserir o SSID e a senha da rede wifi
Após a configuração da Wifi, faça o upload do codigo para a placa utilizando o platformIO

Finalizado o upload, o projeto pode ser executado através do botão Serial Monitor.


## Vídeo
