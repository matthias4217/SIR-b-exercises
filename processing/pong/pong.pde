int CIRCLE_RADIUS = 10;

int screen_type = 0; // 0 : 800x600 ; 1: 1366x768


int ballPosX = 20;
int ballPosY = 40;
int ballSpdX = 3;
int ballSpdY = 2;

int PADDLE_WIDTH = 200;
int PADDLE_HEIGHT = 30;
int paddlePosX = 100;
int paddlePosY = 500;
int curMouseX;

// TODO : do something with Internet
// TODO : control the paddle with the sensor


void collisionPaddleBall() {
  // doesn't treat all cases
  if (ballPosX + CIRCLE_RADIUS > paddlePosX &&ballPosX - CIRCLE_RADIUS < paddlePosX + PADDLE_WIDTH) {
    if (ballPosY + CIRCLE_RADIUS > paddlePosY) {
      ballSpdY = -ballSpdY;
    }
  }
}

void setup() {
  size(800, 600);
  curMouseX = mouseX;
}

void draw() {
  // we compute the new coords
  ballPosX += ballSpdX;
  ballPosY += ballSpdY;
  if (ballPosX < 0 || ballPosX > width) {
    ballSpdX = -ballSpdX;
  }
  
  if (ballPosY < 0 || ballPosY > height) {
    ballSpdY = -ballSpdY;
  }
  collisionPaddleBall();
  
  // we should add the bouncing ball with the paddle
  
  // we draw stuff
  clear();
  rect(paddlePosX, paddlePosY, PADDLE_WIDTH, PADDLE_HEIGHT); 
  circle(ballPosX, ballPosY, CIRCLE_RADIUS);
}

void mouseMoved() {
  //int deltaX = mouseX - curMouseX;
  curMouseX = mouseX;
  
  //paddlePosX += deltaX;
  paddlePosX = curMouseX;
}
  
