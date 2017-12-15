Documento de Instruções
Componentes utilizados:
- 2 sensores MPU6050: Esses dispositivos possuem cada um 1 acelerômetro e 1
giroscópio.
- Uma placa “BluePill” STM32F103C8T6
- Jumpers
- Uma placa Protoboard
- Um debugger e programador ST Link V2
Softwares utilizados:
- STM32Cube MX
- Atollic TrueStudio for Arm 8.1
1. Conecte a bluepill ao ST Link V2 conforme as instruções a seguir:
Tabela 1: Conexões entre Bluepill e Stlink v2
STLINKV2 BLUEPILL
Pino 1 (VCC) 3V3
Pino 4 (GND) GND
Pino 7 (SWDIO) SWDIO
Pino 9 (SWCLK) SWCLK
Conector de debugger da Bluepill
 Conector do Stlinkv2 (para família STM32). Para referência, perceba o pequeno espaço entre 9 e 11.
2. Após conectar a bluepill ao STlink, conecte os dois a portas usb do computador.
3. Abra o Atollic TrueStudio e carregue as pastas do projeto.
4. Carregue o código para a placa, apertando F11 para entrar no modo debugger e
apertando F8 para executar o código inteiro.
5. Após compilar, o código já estará na BluePill, e não mais precisaremos do ST Link,
podendo retirar os fios que conectam o ST Link à BluePill e retirar o usb do ST Link do
computador.
6. Como último passo, retire e coloque de volta o cabo usb que conecta a BluePill ao
computador.
7. Quando reconectar, o mouse já estará funcionando, podendo ser utilizado com os
movimentos de sua mão.
Manual de utilização da luva:
Para movimentar o cursor, supondo a utilização na mão direita e partindo da posição
onde a mão está reta com a palma virada para baixo:
- Para a direita​: Gire sua mão lentamente para a direita. Levando seu polegar a apontar
para cima.
- Para a esquerda​: Gire sua mão lentamente para esquerda. Levando seu polegar a
apontar para baixo.
- Para cima​: Gire sua mão lentamente para cima. Levando a ponta do seus quatro outros
dedos a apontar para cima.
- Para baixo​: Gire sua mão lentamente para baixo. Levando a ponta dos seus quatro
outros dedos a apontar para baixo.
- Para clicar: ​Faça rapidamente o gesto de click com seu dedo indicador.
