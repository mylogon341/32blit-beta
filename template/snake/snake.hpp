#include <cstdlib>
#include "32blit.hpp"
#include "../direction.hpp"
#include "square.hpp"
#include <vector>

using namespace blit;

class Snake
{
private:
    /* data */
    int* _size = 0;

    Direction _currentDirection;
public:

    std::vector<square> body;
    
    void createBodyPiece (Vec2 pos) {
        square sq = square(pos);
        body.push_back(sq);
    }
    
    Snake(int* size = 0, Vec2 startPosition = Vec2(0,0)) { 
        _size = size;
        createBodyPiece(startPosition);
        _currentDirection = Direction(Dir::RIGHT, _size);
    }

    ~Snake();

    square head() {
        return body.at(0);
    }

    Rect headRect() {
        return head().rect(_size);
    }

    void updateLocation () { 
        square h = head();
        h.currentPosition += _currentDirection.vector();
        // body.insert.at(0);
    }

    void setDirection(Dir dir) 
    {
        if (_currentDirection.isConflicting(dir) == false) {
            _currentDirection = Direction(dir, _size);
        }
    }

    void draw() {
        screen.pen = Pen(50,200,0,255);
        for(int i = 0; int(body.size()); i++) {
            screen.rectangle(body[i].rect(_size));
        }
    }

};

Snake::~Snake()
{
}


