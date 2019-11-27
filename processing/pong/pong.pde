import http.requests.*;

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

String message;
PFont f;

PImage img;

// TODO : do something with Internet
// TODO : control the paddle with the sensor


void collisionPaddleBall() {
  // doesn't treat all cases
  if (ballPosX + CIRCLE_RADIUS > paddlePosX &&ballPosX - CIRCLE_RADIUS < paddlePosX + PADDLE_WIDTH) {
    if (ballPosY + CIRCLE_RADIUS > paddlePosY) {
      ballSpdY = -ballSpdY;
      thread("reloadMessage");
    }
  }
}

void reloadMessage()
{
  
  //GetRequest get = new GetRequest("http://quotes.rest/quote/random");//qod");
  GetRequest get = new GetRequest("http://evilinsult.com/generate_insult.php?lang=en&type=json"); // get random insult
  get.send();
  println(get.getContent());
  JSONObject quoteJSON = parseJSONObject(get.getContent());
  //message = quoteJSON.getJSONObject("contents").getJSONArray("quotes").getJSONObject(0).getString("quote");
  message = quoteJSON.getString("insult");
}

void setup() {
  size(800, 600);
  curMouseX = mouseX;
  
  f = createFont("FiraCode",16,true); // Arial, 16 point, anti-aliasing on
  textFont(f,10);
  fill(255);

  reloadMessage();
  
}

void draw() {
  // we compute the new coords
  ballPosX += ballSpdX;
  ballPosY += ballSpdY;
  if (ballPosX < 0 || ballPosX > width) {
    ballSpdX = -ballSpdX;
    //reloadMessage();
  }
  
  if (ballPosY < 0 || ballPosY > height) {
    ballSpdY = -ballSpdY;
  }
  collisionPaddleBall();
  
  // we should add the bouncing ball with the paddle
  
  // we draw stuff
  clear();
  
  text(message, 10, 100);
  
  rect(paddlePosX, paddlePosY, PADDLE_WIDTH, PADDLE_HEIGHT); 
  circle(ballPosX, ballPosY, CIRCLE_RADIUS);
}

void mouseMoved() {
  //int deltaX = mouseX - curMouseX;
  curMouseX = mouseX;
  
  //paddlePosX += deltaX;
  paddlePosX = curMouseX;
}
  
