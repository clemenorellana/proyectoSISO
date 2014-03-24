int BUTTON_ON = 2;
int BUTTON_OFF = 4;
int ledPin = 13;

/* keyboard report buffer */
uint8_t buf[8] = { 0 }; 	

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(BUTTON_ON, INPUT);
  pinMode(BUTTON_OFF, INPUT);
  
  digitalWrite(13,LOW); 
       
  //delay(200); 
}

void send_key ( char * ch ) {

  buf[2] = *ch - 'a' + 4;

  // for debugging purposes 
  // Serial.println(buf[2]); 

  Serial.write(buf, 8);	// Send keypress
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);	// Release key  
} 


void loop() 
{
  if ( digitalRead(BUTTON_ON) == HIGH ) {
     digitalWrite(13,HIGH); 
     //Serial.print("1");
  } 
  else if (digitalRead(BUTTON_OFF) == HIGH)
  {
      int state = digitalRead(13);
      if(state == 1){
        Serial.println("1");
        send_key("1");
      }
      else{  
        Serial.println("0");
        send_key("0"); 
      }
  }
  
}


