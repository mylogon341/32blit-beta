
#include "32blit.hpp"

using namespace blit;

struct square
{
    Vec2 currentPosition;
    
    Rect rect (int* size) { return Rect(currentPosition.x,currentPosition.y,*size,*size); }
    square(Vec2 pos):currentPosition(pos){}

};
