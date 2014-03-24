int led2 = 2;
int led3 = 3;
int led4 = 4;
int led13 = 13;
int led;
int state;

void setup()
{
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led13,OUTPUT);  
  
  Serial.begin(9600);
}

void imprimir()
{
      Serial.print(" P2 = ");
      Serial.print(digitalRead(led2));
      Serial.print(" | P3 = ");
      Serial.print(digitalRead(led3));
      Serial.print(" | P4 = ");
      Serial.print(digitalRead(led4));
      Serial.print(" | P13 = ");
      Serial.println(digitalRead(led13));
      
}

void loop()
{
  if(Serial.available() > 0)
  {
    if(Serial.peek() == 'e')
    {

      Serial.read();
      led = Serial.parseInt();
      //Serial.print("Encendiendo led ");
      //Serial.print(led);
      //Serial.print(" ..... " );
      state = 1;
      digitalWrite(led,state);
    }
    else if(Serial.peek() == 'a')
    {
      Serial.read();
      led = Serial.parseInt();
      //Serial.print("Apagando led ");
      //Serial.print(led);
      //Serial.print(" ..... " );
      state = 0;
      digitalWrite(led,state);
    }
    if(Serial.peek() == 'r')
    {
      Serial.read();
      imprimir();
    }
    imprimir();  
    while(Serial.available() > 0)
    {
      Serial.read();
    }
  }
}
