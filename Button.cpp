#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string.h>
#include <iostream>
#include "Button.hpp"

Button::Button(std::string name_font, std::string text, const sf::Vector2f& size, sf::Color color, int code) {
    //shape_.setSize(size);
    //shape_.setFillColor(color);

    //font_.loadFromFile(name_font);
    //text_.setFont(font_);
    //text_.setString(text);
    //text_.setPosition((shape_.getSize().x - text_.getLocalBounds().width) / 2, (shape_.getSize().y - 2 * text_.getLocalBounds().height) / 2);
}

void Button::draw(sf::RenderWindow* window) {
    window->draw(shape_);
    window->draw(text_);
}

void Button::click(float mouse_x, float mouse_y, sf::RenderWindow* window, Photo* photo) {
    if (mouse_x <= shape_.getPosition().x + shape_.getSize().x && mouse_y <= shape_.getPosition().y + shape_.getSize().y && mouse_y >= shape_.getPosition().y && mouse_x >= shape_.getPosition().x) {
        this->set_code(open_photo);
    }

    printf("button: %f %f\n", this->shape_.getPosition().x + this->shape_.getSize().x, this->shape_.getPosition().y - this->shape_.getSize().y);
    

    if (this->code_ == open_photo) {
        std::cout << "Pressed" << std::endl;
        shape_.setFillColor(sf::Color(255, 0, 0, 100));
        // window->clear();
        this->draw(window);
        //window->display();
        photo->open(window);
    }
    if (this->code_ == close_photo) {
        shape_.setFillColor(sf::Color(0, 255, 0, 100));
        photo->close(window);
    }
}

void Button::set_code(int code) {
    code_ = code;
}
