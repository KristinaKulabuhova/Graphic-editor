#pragma once
#include <SFML/Graphics.hpp>

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