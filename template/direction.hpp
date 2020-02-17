enum Dir {
    UP, DOWN, LEFT, RIGHT 
};

struct Direction { 

    private:
        Dir _direction;
        const int* _size;
    public:

        Direction(Dir d = Dir::RIGHT, const int *size = 0): _direction(d), _size(size) { }

        bool isConflicting(const Dir &d) {
            switch (d) {
                case UP:
                    return _direction == DOWN;
                case DOWN:
                    return _direction == UP;
                case LEFT:
                    return _direction == RIGHT;
                case RIGHT:
                    return _direction == LEFT;
            }
        }

        Vec2 vector () {
            switch (_direction) {
                case UP:
                    return Vec2(0,-*_size);
                case DOWN:
                    return Vec2(0,*_size);
                case LEFT:
                    return Vec2(-*_size,0);
                case RIGHT:
                    return Vec2(*_size,0);
            }
        }
};
