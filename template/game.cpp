// #include <string>
// #include <string.h>
// #include <memory>
// #include <cstdlib>
#include <time.h>

#include "snake.hpp"

#include "game.hpp"

using namespace blit;

void calculateMaxBorder ();
bool hasCrashedIntoWalls ();

const uint16_t screen_width = 160;
const uint16_t screen_height = 120;
// const uint16_t screen_width = 320;
// const uint16_t screen_height = 240;

const int squareSize = 12;
Rect maxSize;
Snake s;

clock_t lastTime = clock();
double secondsToWait = 0.2;

Map map(Rect(0, 0, 128, 128));

Vec2 pos(0, 0);
static Vec2 sz(10,10);

void init () {

  set_screen_mode(ScreenMode::lores);
  calculateMaxBorder();
  s = Snake(&squareSize, Vec2(maxSize.x,maxSize.y));
}

double lastTime_d () { return lastTime/(double)CLOCKS_PER_SEC; }
double now_d () { return clock()/(double)CLOCKS_PER_SEC; }

void calculateMaxBorder () { 
  int maxWidth = floor(screen_width/squareSize) * squareSize;
  int maxHeight = floor(screen_height/squareSize) * squareSize;
  double widthDelta = screen_width - maxWidth;
  double heightDelta = screen_height - maxHeight;
  maxSize = Rect(widthDelta/2.0,heightDelta/2.0,maxWidth,maxHeight);
}

void drawBoundingBox () {

  screen.pen = Pen(200,200,200);
  screen.rectangle(maxSize);
}

int framesSkipped = 0;
int framesToSkip = 25;
bool directionUpdated = false;
bool hasCrashed = false;

void render(uint32_t time) {

  if (++framesSkipped < framesToSkip) {
    return;
  }

  framesSkipped = 0;
  directionUpdated = false;

  screen.pen = Pen(180,180,180,255);
  screen.clear();

  s.updateLocation();
  
  drawBoundingBox();

  if (hasCrashedIntoWalls ()){

    debug("crashed!");
    hasCrashed = true;
  } else {
    screen.pen = Pen(50,200,0,255);
    screen.rectangle(s.head());
  }
}

bool hasCrashedIntoWalls () {
  return !maxSize.contains(s.head());
}

void setDirection (Dir direction) {
  if (directionUpdated) { return; }

  s.setDirection(direction);
  directionUpdated = true;
}

void update(uint32_t time_ms) 
{
  if (pressed(Button::DPAD_LEFT))  { setDirection(Dir::LEFT);  }
  if (pressed(Button::DPAD_RIGHT)) { setDirection(Dir::RIGHT); }
  if (pressed(Button::DPAD_UP))    { setDirection(Dir::UP);    }
  if (pressed(Button::DPAD_DOWN))  { setDirection(Dir::DOWN);  }

  if (hasCrashed && pressed(Button::A)) {
    // reset
  } 
}
