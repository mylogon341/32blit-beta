#include <cstdlib>
#include "32blit.hpp"
#include "direction.hpp"

using namespace blit;

class Snake
{
private:
    /* data */
    const int* _size = 0;
    Vec2 _position;

    Direction _currentDirection;

public:
    Snake(const int* size = 0, Vec2 startPosition = Vec2(0,0)) { 
        _size = size;
        _position = startPosition;
        _currentDirection = Direction(Dir::RIGHT, _size);
    }
    
    ~Snake();

    Rect head() { 
        return Rect(_position.x,_position.y,*_size,*_size); 
    }

    void updateLocation () { _position += _currentDirection.vector(); }

    void setDirection(Dir dir) 
    {
        if (_currentDirection.isConflicting(dir) == false) {
            _currentDirection = Direction(dir, _size);
        }
    }

};

Snake::~Snake()
{
}


