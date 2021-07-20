#include <SFML/Graphics.hpp>
#include <queue>

enum ButtonType {
    open_photo,
    close_photo
};

enum EventType {
    button
};

class Event {
    private: 
        EventType type_;

    public:
        Event();
        virtual ~Event() = 0;

};

class ButtonEvent: public Event {
    private:
        int code_;
    
    public:
        ButtonEvent(int code);
};

std::queue<ButtonEvent> EventQueue;