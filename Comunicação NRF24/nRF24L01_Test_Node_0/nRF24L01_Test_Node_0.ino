#include "Arduino.h"
#include <SPI.h>
#include <RF24.h>

// Configuração de Hardware: Configura o nRF24L01 em SPI bus (pins 10, 11, 12, 13) e pins 7 & 8
RF24 radio(7, 8); //CE e CSN
int motorPin = 5; //pino do motor
int speed = 200; //testando motor

byte addresses[][6] = {"1Node","2Node"}; //nomeia os arduinos

void setup() {
  Serial.begin(9600); //velocidade de transmissão monitor serial
  Serial.println("ESTE É O RECEIVER - É NECESSÁRIO OUTRO ARDUINO PARA TRANSMITIR");

  //pinMode(motorPin, OUTPUT); //ligando motor

  radio.begin(); //inicia o rádio
  radio.setPALevel(RF24_PA_MIN); //energia de transmissão mínima (evita sobrecarga)
  radio.setDataRate(RF24_2MBPS); //fornece a velocidade de transmissão entre NRF's
  radio.setChannel(124); //Canal de transmissão (evita interferência) 

  // Abre um canal de escrita e leitura em cada rádio, com endereço oposto
  radio.openWritingPipe(addresses[0]); //abre caminho de escrita 
  radio.openReadingPipe(1, addresses[1]); //abre caminho de leitura
  radio.startListening(); //o rádio começa a ouvir por dados
}

// -----------------------------------------------------------------------------
// Estamos OUVINDO apenas (Mesmo que estamos envando uma resposta)
// -----------------------------------------------------------------------------
void loop() {

  //unsigned char data; //esse dado recebemos do transmissor (outro arduino)
  int data; //esse dado recebemos do transmissor (outro arduino)

  // Tem algum dado para receber?
  //if ( radio.available()) {
  
    // Leia e arameza na variável
    //while (radio.available()) {
      //radio.read( &data, sizeof(char));
    //}

  if ( radio.available()) {
      radio.read( &data, sizeof(int));
    // Leia e arameza na variável
    while (radio.available() && data == 50) {
      radio.read( &data, sizeof(int));
      analogWrite(motorPin, speed);
    }

    // Sem dados a receber então envie adicionado a 1 unidade
    // Mas primeiro, pare de ler para conserguirmos conversar
    radio.stopListening();
   // data++;
    //radio.write( &data, sizeof(char) );
    radio.write( &data, sizeof(int) );

    // Agora, comece a ouvir para o próximo dado.
    radio.startListening();

    // Informa o que enviamos de dados (número aleatório +1)
    Serial.print("Resposta enviada: ");
    Serial.println(data);
  }
}
