int LEDS[12] = {6,7,8,9,10,11,12,13,14,15,18,19};
int BUTTONS[4] = {2,3,4,5}; // up, down, left, right

void setup(){

  // Run through the LEDs (in pin order)
  for(int i = 0; i < 12; i++){

    pinMode(LEDS[i], OUTPUT);

    digitalWrite(LEDS[i], HIGH);
    delay(200);
    digitalWrite(LEDS[i], LOW);
   
  }

  // Set up the button pins for input
  for(int i = 0; i<4; i++){
   pinMode(BUTTONS[i], INPUT); 
  }
}

void loop(){

  // Light up LEDs in response to buttons
  for(int i = 0; i < 4; i++){
  
    if(digitalRead(BUTTONS[i]) == HIGH){
      digitalWrite(LEDS[i], HIGH);
    }
    else{
      digitalWrite(LEDS[i], LOW);
    }
  }
}
