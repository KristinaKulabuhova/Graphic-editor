#include <SFML/Graphics.hpp>
#include <string>

class Photo {
    private:
        sf::Vector2f size_;
        sf::Image image_;
        sf::Texture texture_;
        sf::Sprite sprite_;
        sf::Vector2f position_;
    
    public:
        Photo(std::string path = "image.png", float pos_x = 50, float pos_y = 25) {
            image_.loadFromFile(path); //загружаем в него файл
            texture_.loadFromImage(image_); //передаем в него объект Image (изображения)
            sprite_.setTexture(texture_); //передаём в него объект Texture (текстуры)
            sprite_.setPosition(pos_x, pos_y); //задаем начальные координаты появления спрайта
        }

        void draw(sf::RenderWindow* window) {
            window->clear();
            this->draw(window);
            window->display();
        }

        // void wait(std::queue<ButtonEvent> EventQueue) {


        // }
};