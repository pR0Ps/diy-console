//int leds[12] = {6,7,8,9,10,11,12,13,14,15,18,19};
int MAXX = 4;
int MAXY = 3;
int LEDS[] = {6, 7, 13,12,
              8, 9, 15,14,
              10,19,18,11};

int BUTTONS[] = {2, 3, 4, 5}; // up, down, left, right
boolean pressed[4];

int BLINK_PERIOD = 30;

int px;
int py;
int tx;
int ty;

int framecnt;

void setup() {

  // Setup outputs
  for(int i = 0; i < 12; i++){
    pinMode(LEDS[i], OUTPUT);
    digitalWrite(LEDS[i], LOW);
  }

  // Setup inputs
  for(int i = 0; i < 4; i++){
   pinMode(BUTTONS[i], INPUT);
   pressed[i] = false;
  }

  // Set player
  px = 0;
  py = 0;

  // Initilize RNG
  randomSeed(0);

  tx = 2;
  ty = 2;
  framecnt = 0;

}

int to1D(int x, int y, int xsize){
  return y * xsize + x;
}

int canWalk(int x, int y){
  if (y < 0 || y >= MAXY || x < 0 || x >= MAXX){
    return false;
  }
  return true;
}

void draw(){
  // Target
  boolean target_state;
  if (framecnt < BLINK_PERIOD){
    // Turn on target light
    target_state = HIGH;
  }
  else{
    // Turn off target light
    target_state = LOW;

    // Reset frame counter
    if (framecnt >= BLINK_PERIOD*2){
      framecnt = 0;
    }
  }

  for (int i = 0; i < MAXX; i++){
    for(int j = 0; j < MAXY; j++){
      if (i == px && j == py){
        // Player
        digitalWrite(LEDS[to1D(i, j, MAXX)], HIGH);
      }
      else if (i == tx && j == ty){
        // Target
        digitalWrite(LEDS[to1D(i, j, MAXX)], target_state);
      }
      else{
        // Clear the rest
        digitalWrite(LEDS[to1D(i, j, MAXX)], LOW);
      }
    }
  }
}

void movePlayer(int i){
  if (i == 0){
     if (canWalk(px, py - 1)){
       py--;
     }
  }
  else if (i == 1){
     if (canWalk(px, py + 1)){
       py++;
     }
  }
  else if (i == 2){
     if (canWalk(px - 1, py)){
       px--;
     }
  }
  else{
     if (canWalk(px + 1, py)){
       px++;
     }
  }
}

void input(){
  // Movement
  for (int i = 0; i < 4; i++){
    if (!pressed[i] && digitalRead(BUTTONS[i]) == HIGH){
      movePlayer(i);
      pressed[i] = true;
    }
    else if (digitalRead(BUTTONS[i]) == LOW){
      pressed[i] = false;
    }
  }
}

void checkWin(){
 if (px == tx && py == ty){
   tx = random(MAXX);
   ty = random(MAXY);
 }
}

void loop() {
  delay(10);
  framecnt++;
  input();
  draw();
  checkWin();
}
