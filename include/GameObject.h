#include <iostream>

class GameObject{
    public:
        GameObject();
        ~GameObject();

        void draw();
        void update();
        void clean();

    protected:
        int m_x;
        int m_y;
};