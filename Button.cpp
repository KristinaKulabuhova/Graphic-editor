#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string.h>
#include "Button.hpp"

Button::Button(std::string name_font = "IndieFlower-Regular.ttf", std::string text = "Open photo", const sf::Vector2f& size = sf::Vector2f(120.f, 50.f), sf::Color color = sf::Color(0, 255, 0, 100), int code = 0) {
    shape_.setSize(size);
    shape_.setFillColor(color);

    font_.loadFromFile(name_font);
    text_.setFont(font_);
    text_.setString(text);
    text_.setPosition((shape_.getSize().x - text_.getLocalBounds().width) / 2, (shape_.getSize().y - 2* text_.getLocalBounds().height) / 2);
}

void Button::draw(sf::RenderWindow* window) {
    window->draw(shape_);
    window->draw(text_);
}

ButtonEvent Button::click(float mouse_x, float mouse_y, sf::RenderWindow* window) {

    ButtonEvent event_button(code_);

    EventQueue.push(event_button);

    if (shape_.getFillColor() == sf::Color(255, 0, 0, 100)) {
    shape_.setFillColor(sf::Color(0, 255, 0, 100));
    }
    else {
        shape_.setFillColor(sf::Color(255, 0, 0, 100));
    }
}

void Button::set_code(int code) {
    code_ = code;
}
