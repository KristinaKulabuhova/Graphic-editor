#include <SFML/Graphics.hpp>
#include "Photo.hpp"
#include <iostream>
#include <string>

Photo::Photo(std::string path, float pos_x, float pos_y) {
    image_.loadFromFile(path); //загружаем в него файл
    texture_.loadFromImage(image_, sf::IntRect(250, 250, 150, 150)); //передаем в него объект Image (изображения)
    sprite_.setTexture(texture_); //передаём в него объект Texture (текстуры)
    sprite_.setPosition(pos_x, pos_y); //задаем начальные координаты появления спрайта
}

void Photo::open(sf::RenderWindow* window) {
    std::cout << "Draw image" << std::endl;
    //window->clear();
    window->draw(sprite_);
    window->display();
    //scanf("%s");
}

void Photo::close(sf::RenderWindow* window) {
    window->clear();
}    