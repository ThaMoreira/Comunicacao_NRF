#include "Arduino.h"
#include <SPI.h>
#include <RF24.h>

// Configuração de Hardware: Configura o nRF24L01 em SPI bus (pins 10, 11, 12, 13) e pins 7 & 8
RF24 radio(8, 10);
byte addresses[][6] = {"1Node", "2Node"}; //nomeia os arduinos

void setup() {
  Serial.begin(9600); //velocidade de transmissão monitor serial
  Serial.println("ESTE É O TRANSMITTER - É NECESSÁRIO OUTRO ARDIUNO PARA ENVIAR A RESPOSTA DE VOLTA");

  radio.begin(); //inicia o rádio
  radio.setPALevel(RF24_PA_MIN); //energia de transmissão mínimo (evita sobrecarga)
  radio.setDataRate(RF24_2MBPS); //fornece a velocidade de transmissão entre NRF's
  radio.setChannel(124); //Canal de transmissão (evita interferência) 

  // Abre um canal de escrita e leitura em cada rádio, com endereço oposto
  radio.openWritingPipe(addresses[1]); //abre caminho de escrita
  radio.openReadingPipe(1, addresses[0]); //abre caminho de leitura
  randomSeed(analogRead(A0)); //Inicializa o número aleatório a ser enviado
}

void loop() {

  //unsigned char data = random(0, 100); //gera um número aleatório entre 0 e 100 para transmitir
  int data = 50;
      
  radio.stopListening(); //Para de ouvir senão não conseguiremos transmitir

  // Conseguimos mesmo transmitir isso? (Conseguindo um conhecimento do outro arduino)
  // Mesmo que não for possível continuamos o código, as fadas do rádio vão nos ajudar
 // if (!radio.write( &data, sizeof(unsigned char) )) {
   // Serial.println("Sem transmissão - está realmente conectado?");    
  //}

  if (!radio.write( &data, sizeof(int) )) {
    Serial.println("Sem transmissão - está realmente conectado?");    
  }

  radio.startListening(); //começa a ouvir por resposta
  
  unsigned long started_waiting_at = millis(); //escuta por 200 milisegundos é suficiente para aguardar por resposta

  // Aqui entra o Loop até termos algum dado para ler (ou time out)
  while ( ! radio.available() ) {

    // ah não! Sem resposta dentro do tempo estipulado (200 milisegundos)
    if (millis() - started_waiting_at > 200 ) {
      Serial.println("Ahh não! Sem resposta - timeout! Tente novamente mais tarde");
      return;
    }
  }

  // Agora lemos os dados que está esperando no buffer do nRF24L01
  //unsigned char dataRx;
  //radio.read( &dataRx, sizeof(unsigned char) );

  int dataRx;
  radio.read( &dataRx, sizeof(int) );

  // Mostrar o dado que enviamos e que recebemos
  Serial.print("Enviado: ");
  Serial.print(data);
  Serial.print(", Recebido: ");
  Serial.println(dataRx);

  // Roda novamente após 1 segundo
  delay(1000);
}
