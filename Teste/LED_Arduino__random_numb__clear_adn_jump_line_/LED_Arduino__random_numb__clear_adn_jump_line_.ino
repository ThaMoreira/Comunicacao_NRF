#include <LiquidCrystal.h>

const int rs=12, en=11, d4=5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
int i;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
   lcd.begin(16,2);
   lcd.print("Random num @");
   lcd.setCursor(0,1);
   lcd.print("Clear% jumpLine>");
}

void loop() {
 
  if (Serial.available())
{
//faz a leitura atraves do monitor serial//
char cr = Serial.read();
//determina um caracter para limpar a tela//
  if (cr == '%')
  {
    lcd.clear();
  }
//determina um caracter para pular para a linha de baixo//
  else if (cr == '>')
  {
    lcd.setCursor(0,1);
  }
    else if (cr == '@')
    {
  
      for (i=0; i<10; i++){
      unsigned char data = random(0,200);
      lcd.clear();
      lcd.print("Mensagem:");
      Serial.println(data);
      lcd.setCursor(0,1);
      lcd.print(data);
      delay(1000);
 
      } 
    }
    
  else
      {
          lcd.write(cr);
          Serial.print(cr);
          delay(100);
    }
    }
}
