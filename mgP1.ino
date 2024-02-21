// Define pins for the LED matrix
const int row[8] = {9, 2, 3, 4, 5, 6, 7, 8};
const int col[8] = {10, 11, 12, 21, 20, 19, 18, 17};

// Define pins for the HAL sensors
const int halPin1 = A0; // Upper HAL sensor
const int halPin2 = A2; // Left HAL sensor

// Define pin for button
const int button = 15;

// Text array creation adapted from https://howtomechatronics.com/tutorials/arduino/8x8-led-matrix-max7219-tutorial-scrolling-text-android-control-via-bluetooth/
int snakeText[][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,1},
  {1,0,0,1,0,0,0,1},
  {1,0,0,1,0,0,0,1},
  {1,0,0,1,0,0,0,1},
  {1,0,0,0,1,1,1,0},
  {0,0,0,0,0,0,0,0},
  {1,1,1,1,1,1,1,1},
  {0,1,1,0,0,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,0,0,1,1,0},
  {1,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,0},
  {0,1,1,1,1,1,1,1},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,0},
  {1,1,1,1,1,1,1,1},
  {0,0,0,1,0,0,0,0},
  {0,0,1,0,1,0,0,0},
  {0,1,0,0,0,1,0,0},
  {1,0,0,0,0,0,1,1},
  {0,0,0,0,0,0,0,0},
  {1,1,1,1,1,1,1,1},
  {1,0,0,1,0,0,0,1},
  {1,0,0,1,0,0,0,1},
  {1,0,0,1,0,0,0,1},
  {1,0,0,1,0,0,0,1}
};

int gameOverText[][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,1,1,1,1,1,1,0},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,1},
  {1,0,0,0,1,0,0,1},
  {0,1,0,0,0,1,1,0},
  {0,0,0,0,0,0,0,0},
  {0,1,1,1,1,1,1,1},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,0},
  {1,1,1,1,1,1,1,1},
  {0,1,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {1,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,0}, 
  {1,1,1,1,1,1,1,1},
  {1,0,0,1,0,0,0,1},
  {1,0,0,1,0,0,0,1},
  {1,0,0,1,0,0,0,1},
  {1,0,0,1,0,0,0,1},
  {0,0,0,0,0,0,0,0}, 
  {0,0,0,0,0,0,0,0}, 
  {0,0,0,0,0,0,0,0}, 
  {0,0,0,0,0,0,0,0}, 
  {0,0,0,0,0,0,0,0}, 
  {0,1,1,1,1,1,1,0},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {0,1,1,1,1,1,1,0},
  {0,0,0,0,0,0,0,0}, 
  {1,1,1,1,1,1,0,0},
  {0,0,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,1,0}, 
  {1,1,1,1,1,1,0,0},
  {0,0,0,0,0,0,0,0}, 
  {1,1,1,1,1,1,1,1},
  {1,0,0,1,0,0,0,1},
  {1,0,0,1,0,0,0,1},
  {1,0,0,1,0,0,0,1},
  {1,0,0,1,0,0,0,1},
  {0,0,0,0,0,0,0,0},
  {1,1,1,1,1,1,1,1},
  {1,0,0,1,1,0,0,0},
  {1,0,0,1,0,1,0,0},
  {1,0,0,1,0,0,1,0},
  {1,1,1,1,0,0,0,1}
};

// Enum to hold the direction variables
enum direction {
  UP, RIGHT, DOWN, LEFT
};

// States of the game
enum states {
  START, GAME, END
};

// 2-dimensional array representing the LED matrix:
int pixels[8][8];

// Snake parameters
int snakeX[64];
int snakeY[64];
int snakeLength = 1;
int foodX, foodY;
int prevDir = 1; // 0: up, 1: right, 2: down, 3: left

// Game Parameters
int textSpeed = 200;
int speed = 1000;
int curState = START;

void setup() {
  Serial.begin(9600);

  // Set up hal sensors as input pins
  pinMode(halPin1, INPUT);
  pinMode(halPin2, INPUT);

  // Set up button as input and attach an interrupt
  pinMode(button, INPUT);
  attachInterrupt(button, isr, FALLING);

  // Initialize LED matrix
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    digitalWrite(col[thisPin], HIGH);
  }

  // Initialize pixel matrix all off
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = LOW;
    }
  }

  // Initial snake position
  snakeX[0] = 3;
  snakeY[0] = 3;

  // Initial food position
  spawnFood();
}

// State Machine
void loop() {
  // Start state should just repeat SNAKE Text
  if (curState == START) {
    displayText(snakeText, 37, curState);
  }

  // Game state includes all of the game play 
  else if (curState == GAME) {
    readHals();  // Read hal values
    moveSnake(); // Update snake position
    checkCollision();
    
    // Display updates to the led matrix
    if (curState == GAME){
      unsigned long starttime = millis();
      unsigned long endtime = starttime;
      while ((endtime - starttime) <= speed) // do this loop for up to 1000mS
      {
        displaySnake();
        endtime = millis();
      }
    }

    // Check if there are game updates
    checkFood();
  }

  // End state should just repeat GAME OVER text
  else if (curState == END) {
    displayText(gameOverText, 59, curState);
  }
}

// Displays the text matrix given
void displayText(int array[][8], int length, int initState) {

  for (int k = 0; k < length; k++) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        pixels[i][j] = array[(j + k)%length][i];
      }
    }

    unsigned long starttime = millis();
    unsigned long endtime = starttime;
    while ((endtime - starttime) <= textSpeed) // do this loop for up to 1000mS
    {
      if (curState != initState){
        return;
      }
      refreshScreen();
      endtime = millis();
    }
  }
}

// Interrupt code adapted from https://www.tutorialspoint.com/arduino/arduino_interrupts.htm
void isr() {
  // Move to the next state
  if (curState == START) {
    curState = GAME;
  }
  else if (curState == END) {
    delay(500);
    curState = START;

    // Reset the game
    snakeLength = 1;
    snakeX[0] = 3;
    snakeY[0] = 3;
    prevDir = RIGHT;
    spawnFood();
  }
}

// Read hal sensor values to update direction
void readHals() {
  int halVal1 = analogRead(halPin1);
  int halVal2 = analogRead(halPin2);

  if ((halVal1 > 900) && (halVal2 > 900)) {
    prevDir = UP;
  }
  else if ((halVal1 < 200) && (halVal2 > 900)) {
    prevDir = RIGHT;
  }
  else if ((halVal1 < 200) && (halVal2 < 200)) {
    prevDir = DOWN;
  }
  else if ((halVal1 > 900) && (halVal2 < 200)) {
    prevDir = LEFT;
  }
}

void moveSnake() {
  // Move the snake body
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // Move the snake head
  switch (prevDir) {
  case UP:
    snakeX[0]--;
    break;
  case RIGHT:
    snakeY[0]++;
    break;
  case DOWN:
    snakeX[0]++;
    break;
  case LEFT:
    snakeY[0]--;
    break;
  }
}

// Check if the snake hit the side or itself
void checkCollision() {
  if (snakeX[0] < 0 || snakeX[0] >= 8 || snakeY[0] < 0 || snakeY[0] >= 8) {
    curState = END;
  }

  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      curState = END;
    }
  }
}

// Check if the snake ate the food
void checkFood() {
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    // Increase snake length
    snakeLength++;

    // Spawn new food
    spawnFood();
  }
}

// Update the pixels matrix to display the snake and food
void displaySnake() {
  // Clear the display
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = LOW;
    }
  }

  // Display snake body
  for (int i = 0; i < snakeLength; i++) {
    pixels[snakeX[i]][snakeY[i]] = HIGH;
  }

  // Display food
  pixels[foodX][foodY] = HIGH;

  // Refresh the screen
  refreshScreen();
}


// Adapted from https://bitbucket.org/nerdfirst/arduino-8x8-basics/src/master/Smiley/
// Updates the LED matrix
void refreshScreen() {
  for (int i=0; i<8; i++) {
    digitalWrite(row[i], LOW);

    for (int j=0; j<8; j++) {
      if (pixels[i][j] == 1) {
        digitalWrite(col[j], LOW);
      }
      else {
        digitalWrite(col[j], HIGH);
      }
    }
    digitalWrite(row[(i+1)%8], HIGH);

    delay(1);
  }
}

// Creates food
void spawnFood() {
  // Generate random food position
  foodX = random(8);
  foodY = random(8);

  // Ensure the food does not spawn on the snake
  for (int i = 0; i < snakeLength; i++) {
    if (foodX == snakeX[i] && foodY == snakeY[i]) {
      spawnFood();
      return;
    }
  }
}
