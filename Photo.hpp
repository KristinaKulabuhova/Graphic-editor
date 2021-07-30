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
        Photo(std::string path = "image.png", float pos_x = 200.f, float pos_y = 200.f);

        void open(sf::RenderWindow* window);
        void close(sf::RenderWindow* window);  
};