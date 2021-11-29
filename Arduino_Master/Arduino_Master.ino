#include <LiquidCrystal_I2C.h> //Biblioteca I2C do LCD 16x2
LiquidCrystal_I2C lcd(0x27,16,2);  // Configurando o endereco do LCD 16x2 para 0x27

int value1 = 0, value2 = 0;

const int LED =  13;   
const int Enable =  2;

void setup() 
{ 
  Serial.begin(9600);
  Serial.setTimeout(250);

  pinMode(LED, OUTPUT);
  pinMode(Enable, OUTPUT);
  
  digitalWrite(LED, LOW); 
  
  digitalWrite(Enable, HIGH);

  lcd.init();      
  lcd.backlight();
}
 
void loop() 
{ 
  
  Serial.print("I");
  Serial.print("1");
  Serial.print("L");
  Serial.print("F");
  Serial.flush();
  
  digitalWrite(Enable, LOW);
  
  if(Serial.find("i"))
  {   
      int slave1 = Serial.parseInt();
      value1 = Serial.parseInt();
      
      if(Serial.read() == 'f' && slave1 == 1)
      {
        lcd.setCursor(0,0);
        lcd.print("Escravo 1:      ");
        lcd.setCursor(11,0);
        lcd.print(value1);
      }
 }
      digitalWrite(Enable, HIGH);

  Serial.print("I");
  Serial.print("2");
  Serial.print("L");
  Serial.print("F");
  Serial.flush();
  
  digitalWrite(Enable, LOW);
  
  if(Serial.find("i"))
  {   
      int slave2 = Serial.parseInt();
      value2 = Serial.parseInt();
      
      if(Serial.read() == 'f' && slave2 == 2)
      {
        lcd.setCursor(0,1);
        lcd.print("Escravo 2:      ");
        lcd.setCursor(11,1);
        lcd.print(value2);
      }
  }
      digitalWrite(Enable, HIGH);
}
