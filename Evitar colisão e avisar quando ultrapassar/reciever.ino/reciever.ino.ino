#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(2, 3); // CE, CSN

const byte address[6] = "00001";

#define MAX_WORLD_COUNT 5
#define MIN_WORLD_COUNT 2
char *Words[MAX_WORLD_COUNT];
char *StringToParse;
String lat = "";
String lng = "";
String dir = "";
String spd = "";
String dis = "";
void setup() {
  pinMode (4,OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}
void loop() {
  byte word_count;
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    StringToParse = text;
  word_count = split_message(StringToParse);
  if (word_count >= MIN_WORLD_COUNT) {
    print_message(word_count);
  }
     delay(2000);
    
  }else {
      Serial.println("SAFE");
    }
}
////////// ////////// ////////// ////////// ////////// ////////// //////////
// Send array over serial
////////// ////////// ////////// ////////// ////////// ////////// //////////
void print_message(byte word_count) {
  int sms_block = 0;
  //if (word_count >= MIN_WORLD_COUNT) {
  //Serial.print("Word count : ");  Serial.println(word_count);
    
    Serial.print("LATITUDE");  Serial.print(" : "); Serial.println(Words[sms_block]);
    lat = Words[sms_block];
    sms_block++;
    Serial.print("LONGITUDE");  Serial.print(" : "); Serial.println(Words[sms_block]);
    lng = Words[sms_block];
    sms_block++;
    Serial.print("DIRECTION");  Serial.print(" : "); Serial.println(Words[sms_block]);
    dir = Words[sms_block];
    sms_block++;
    Serial.print("SPEED");  Serial.print(" : "); Serial.println(Words[sms_block]);
    spd = Words[sms_block];
    sms_block++;
    Serial.print("DISTANCE");  Serial.print(" : "); Serial.println(Words[sms_block]);
    dis = Words[sms_block];
    Serial.println("--------------------");
    
  //}
}
////////// ////////// ////////// ////////// ////////// ////////// //////////
// Split string into individual words and store each word into an array
// this function return word_count (number of words)
////////// ////////// ////////// ////////// ////////// ////////// //////////
byte split_message(char* str) {
  byte word_count = 0; //number of words
  char * item = strtok (str, "  "); //getting first word (uses space & comma as delimeter)

  while (item != NULL) {
    if (word_count >= MAX_WORLD_COUNT) {
      break;
    }
    Words[word_count] = item;
    item = strtok (NULL, " ,"); //getting subsequence word
    word_count++;
  }
  return  word_count;
}
