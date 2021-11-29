//#include <nRF24L01.h>
//#include <printf.h>
#include <RF24.h>
//#include <RF24_config.h>

#define radioID 1 //alterar para nomear os transmissores e receptores

RF24 radio(7,8);  //ce e csn

uint8_t enderecos[][6] = {"1Node","2Node"};
bool radioNumber = 1;
char dadosRecebidos;

void setup() {

    Serial.begin (9600);
    radio.begin();
    
     #if radioID == 0
      radio.openWritingPipe(enderecos[0]);
      radio.openReadingPipe(1, enderecos[1]);
  #else
      radio.openWritingPipe(enderecos[1]);
      radio.openReadingPipe(1, enderecos[0]);
  #endif
     
    radio.startListening();

}

void loop() {

char dadosRF; 

  if(radio.available()){ //recebeu informação 
    //Serial.println("Você recebeu uma mensagem: ");
    radio.read( &dadosRecebidos,sizeof(dadosRecebidos) );
    Serial.print(dadosRecebidos);
    //delay(4000);
    
  }else{}
    
    if(Serial.available() > 0){
      
      dadosRF =  Serial.read();
       Serial.println(dadosRF);
      radio.stopListening(); //parar de ler
      radio.write( &dadosRF,  sizeof(dadosRF));
      radio.startListening();
       Serial.println("");
      Serial.println("Mensagem enviada ");
      Serial.println("");
      //delay(4000);
    }else{}

    //Serial.println("");
     // Serial.println("Nenhum dado enviado ou recebido ");
      //Serial.println(""); 
     // delay(4000);
  
}
