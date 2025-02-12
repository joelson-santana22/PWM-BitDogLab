---------------------------------------------------------EMBARCATECH----------------------------------------------------------------

UNIDADE 4 | CAPÍTULO 7 | PWM
____________________________________________________________________________________________________________________________________

## Aluno (matrícula) => Joelson Santana Alves (tic370101150)

A tarefa proposta consiste em utilizar o módulo PWM do microcontrolador RP2040 para controlar o ângulo de um servomotor. O projeto foi desenvolvido utilizando a ferramenta Pico SDK e simulado no ambiente Wokwi. O objetivo é controlar o servomotor em diferentes ângulos (0°, 90° e 180°) e criar uma rotina para movimentação suave do braço do servomotor entre 0° e 180°.

## Funcionalidades Implementadas ao Projeto

1. Configuração do PWM - A GPIO 22 foi configurada para operar com uma frequência de 50Hz (período de 20ms), que é a frequência típica para controle de servomotores.

2. Controle do Ângulo do Servomotor -
   - 180° -> O ciclo ativo do PWM foi definido para 2.400µs (Duty Cycle de 0,12%), ajustando o servomotor para aproximadamente 180°. O sistema aguarda 5 segundos nesta posição.
   - 90° -> O ciclo ativo do PWM foi definido para 1.470µs (Duty Cycle de 0,0735%), ajustando o servomotor para aproximadamente 90°. O sistema aguarda 5 segundos nesta posição.
   - 0° -> O ciclo ativo do PWM foi definido para 500µs (Duty Cycle de 0,025%), ajustando o servomotor para aproximadamente 0°. O sistema aguarda 5 segundos nesta posição.

3. Movimentação Periódica do Servomotor - Foi criada uma rotina para movimentar o braço do servomotor suavemente entre 0° e 180°. A movimentação é realizada incrementando o ciclo ativo em ±5µs a cada 10ms, garantindo uma transição suave entre os ângulos.

4. Integração com o LED RGB - Utilizando a ferramenta BitDogLab, foi realizado um experimento com o LED RGB (GPIO 12) para observar o comportamento da iluminação do LED durante a execução do código. O LED RGB foi utilizado para indicar o estado do servomotor durante a simulação.

## Instruções

1 - Faça o download dos arquivos do projeto clonando o repositório com o comando
| git clone <link do repositório>
ou baixe o arquivo .zip seguindo as opções "CODE > Download ZIP";

2 - No VSCode, utilizando a extensão do Raspberry Pi Pico, selecione "Import Project" e clique em "Change" para selecionar a pasta do projeto extraída caso seja o .zip. 

3 - Após aberto no VSCode, compile o código-fonte;

4 - Para execução na prática do funciomento do LED com PWM, conecte a placa BitDogLab à porta USB do seu computador/notebook. No VSCode, selecione a opção Run no menu/barra inferior do editor. ATENÇÃO - NÃO FAÇA USO DE UM SERVO MOTOR NESSA PRÁTICA, POIS O PRESENTE PROJETO RELACIONADO AO USO DESSE COMPONENTE É SOMENTE A NÍVEL DE SIMULAÇÃO VIA WOKWI.

5- Se atente que a placa deverá está em modo BOOTSEL antes de selecionar o Run. A ativação do modo BOOTSEL pode ser feita de suas maneiras, sendo-as 
- No momento da coneção do cabo USB da placa ao notebook, simultaneamente o botão presente no Raspberry na parte de baixo pode ser pressionado para ativar o modo BOOTSEL;
- Pressionar esse botão citado anteriormente e simultaneamente clicar em um outro botão que fica na parte de cima da placa que tem o nome de Reset. Após o clique, ambos podem ser "soltados". 

## Requisitos

Hardware

- Microcontrolador Raspberry Pi Pico W.
- LED AZUL DO RGB (conectado na GPIO 12).
- PWM presente na Plca BitDogLab.

Software

- SDK do Raspberry Pi Pico configurado.
- Compilador C compatível (como GCC);
- Ferramentas para upload do código para o Pico (VSCode e extensões do Raspberry Pi Pico).
- Acesso à platarforma Wokwi web e integrada ao VSCode.

## LINK DO REPOSITÓRIO GITHUB: 

## Link do vídeo desmonstrativo: https://drive.google.com/drive/folders/1_l-GPlkp8PZr6ayEdxw6Rp2WD52hdrvl?usp=sharing
____________________________________________________________________________________________________________________________________