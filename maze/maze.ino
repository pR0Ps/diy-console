//int leds[12] = {6,7,8,9,10,11,12,13,14,15,18,19};
int LED_MAXX = 4;
int LED_MAXY = 3;
int LEDS[] = {6, 7, 13,12,
              8, 9, 15,14,
              10,19,18,11};

int BUTTONS[] = {2, 3, 4, 5}; // up, down, left, right
boolean pressed[4];

int BLINK_PERIOD = 3;
int P_LEDX = 1;
int P_LEDY = 1;

int px;
int py;

int framecnt;

int MAZE_MAXX = 9;
int MAZE_MAXY = 9;

boolean maze[] = {
  1,0,1,1,1,1,1,1,1,
  1,0,1,0,0,0,0,1,1,
  1,0,11,1,01,1,1,1,
  1,0,1,1,0,0,0,0,1,
  1,0,0,0,0,1,1,0,1,
  1,1,1,0,1,1,1,0,1,
  1,0,0,0,0,0,0,0,1,
  1,0,1,1,1,0,1,0,1,
  1,1,1,1,1,1,1,0,1};

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
  px = 1;
  py = 0;
  
  framecnt = 0;
  
}

int to1D(int x, int y, int xsize){
  return y * xsize + x;
}

int getMaze(int x, int y){
  
  // OOB is always a solid tile
  if (y < 0 || y >= MAZE_MAXY || x < 0 || x >= MAZE_MAXX){
    return true;
  }
  return maze[to1D(x, y, MAZE_MAXX)];
}

void draw(){
  // Player
  if (framecnt < BLINK_PERIOD){
    // Turn on player light
    digitalWrite(LEDS[to1D(P_LEDX, P_LEDY, LED_MAXX)], HIGH);
  }
  else{
    // Turn off player light
    digitalWrite(LEDS[to1D(P_LEDX, P_LEDY, LED_MAXX)], LOW);
    
    // Reset frame counter
    if (framecnt >= BLINK_PERIOD*2){
      framecnt = 0;
    }
  }
  
  //Maze
  for (int i = 0; i < LED_MAXX; i++){
    for(int j = 0; j < LED_MAXY; j++){
      // Don't overwrite player
      if (i != P_LEDX && j != P_LEDY){
        digitalWrite(LEDS[to1D(i, j, LED_MAXX)], getMaze(px + i - P_LEDX, py + j - P_LEDY) ? HIGH : LOW);
      }
    }
  }
  
}

void movePlayer(int i){
  if (i == 0){
     if (!getMaze(px, py - 1)){
       py--;
     }
  }
  else if (i == 1){
     if (!getMaze(px, py + 1)){
       py++;
     }
  }
  else if (i == 2){
     if (!getMaze(px - 1, py)){
       px--;
     }
  }
  else{
     if (!getMaze(px + 1, py)){
       px++;
     }
  }
}

void input(){
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

void loop() {
  delay(100);
  framecnt++;
  input();
  draw();
}
