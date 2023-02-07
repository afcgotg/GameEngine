#include "GameObject.h"

class Player : public GameObject{
    public:
        Player();
        ~Player();

        void draw();
        void update();
        void clean();
};