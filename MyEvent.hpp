#include <SFML/Graphics.hpp>
#include <queue>

enum {
    open_photo,
    close_photo
};

class Event {
    public:

};

class ButtonEvent: public Event {
    private:
        int code_;
    
    public:
        ButtonEvent(int code);
};

std::queue<ButtonEvent> EventQueue;