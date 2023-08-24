/*
 * Projeto de Controle de LEDs com Controle Infravermelho
 * Desenvolvido por: Elismar Silva
 * Data: 24/08/2023
 
 * Este projeto permite controlar LEDs utilizando um controle infravermelho.
 * Os LEDs podem ser ligados ou desligados usando os botões do controle.
 * Os códigos infravermelhos correspondentes a cada ação são mapeados e usados para
 * ativar ou desativar os LEDs correspondentes.
 */

#include <IRremote.h>

// Definição dos pinos dos LEDs e do receptor infravermelho
#define  LED_AZUL     6
#define  LED_VERDE    5
#define  LED_VERMELHO 4
#define  PIN_IR       3

// Array com os pinos dos LEDs
int pin_leds[] = {LED_AZUL, LED_VERDE, LED_VERMELHO};

// Variável para armazenar o valor do código infravermelho recebido
unsigned long valor_recebido;

// Variáveis para controlar o estado dos LEDs
bool azulOn = false;
bool verdeOn = false;
bool vermelhoOn = false;

void setup() {
  // Inicialização do receptor infravermelho e comunicação serial
  IrReceiver.begin(PIN_IR);
  Serial.begin(9600);

  // Configuração dos pinos dos LEDs como saídas
  for (int i = 0; i <= 2; i++) {
    pinMode(pin_leds[i], OUTPUT);
  }
}

void loop() {
  // Loop para processar códigos infravermelhos enquanto estão disponíveis
  while (IrReceiver.decode()) {
    valor_recebido = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(valor_recebido);
    IrReceiver.resume();

    // Mapeamento dos códigos infravermelhos para ações nos LEDs
    switch (valor_recebido) {
      case 4010852096:
        azulOn = !azulOn;
        digitalWrite(LED_AZUL, azulOn);
        break;
      case 3994140416:
        verdeOn = !verdeOn;
        digitalWrite(LED_VERDE, verdeOn);
        break;
      case 3977428736:
        vermelhoOn = !vermelhoOn;
        digitalWrite(LED_VERMELHO, vermelhoOn);
        break;
      default:
        valor_recebido = 0;
    }
  }
}
