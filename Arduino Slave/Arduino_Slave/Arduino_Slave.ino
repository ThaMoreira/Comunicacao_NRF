const int Enable =  2; 
const int SlaveNumber = 1;

void setup() 
{ 
  Serial.begin(9600);  
  Serial.setTimeout(250);
  pinMode(Enable, OUTPUT);
  digitalWrite(Enable, LOW);
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);
} 

void loop() 
{ 
  if(Serial.available())
  {
    if(Serial.read()=='I')
    {   
        int Slave = Serial.parseInt();
        if(Slave == SlaveNumber)
        {   
            char command = Serial.read();       
             
             if(command == 'L')
             {
                if(Serial.read()=='F')
                 {
                   int AnalogValue = analogRead(0);
                        
                   digitalWrite(Enable, HIGH);
                   
                   Serial.print("i");
                   Serial.print(SlaveNumber);   
                   Serial.print(AnalogValue);
                   Serial.print("f");
                   Serial.flush();
                   
                   digitalWrite(Enable, LOW);           
                 }
             }
             
        }
    }
  }
  delay(10);
}
