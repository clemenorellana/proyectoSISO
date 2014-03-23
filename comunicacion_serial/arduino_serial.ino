int led2 = 2;
int led3 = 3;
int led13 = 13;
int led;
int state;

void setup()
{
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led13,OUTPUT);

  /*digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led13, LOW);  */
  
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available() > 0)
  {
    if(Serial.peek() == 'e')
    {
      Serial.read();
      led = Serial.parseInt();
      Serial.print("Encendiendo led ");
      Serial.println(led);
      state = 1;
      if(led == 2)
        digitalWrite(led2,state);
      else if(led == 3)
        digitalWrite(led3,state);
      else if(led == 13)
        digitalWrite(led13,state);
    }
    else if(Serial.peek() == 'a')
    {
      Serial.read();
      led = Serial.parseInt();
      Serial.print("Apagando led ");
      Serial.println(led);
      state = 0;
      if(led == 2)
        digitalWrite(led2,state);
      else if(led == 3)
        digitalWrite(led3,state);
      else if(led == 13)
        digitalWrite(led13,state);
    }
    else if(Serial.peek() == 'r')
    {
      Serial.print("P2 = ");
      Serial.print(digitalRead(led2));
      Serial.print(" | P3 = ");
      Serial.print(digitalRead(led3));
      Serial.print(" | P13 = ");
      Serial.println(digitalRead(led13));
    }
    while(Serial.available() > 0)
    {
      Serial.read();
    }
  }
}
