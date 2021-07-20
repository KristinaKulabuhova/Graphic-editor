#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string.h>
#include "MyEvent.hpp"

class Button {
    private:
        sf::RectangleShape shape_; 
        sf::Font font_;
        sf::Text text_;
        sf::Event event_;

        int code_;

    public:
        Button(std::string name_font = "IndieFlower-Regular.ttf", std::string text = "Open photo", const sf::Vector2f& size = sf::Vector2f(120.f, 50.f), sf::Color color = sf::Color(0, 255, 0, 100), int code = 0);

        void draw(sf::RenderWindow* window);
        void set_code(int code);
        ButtonEvent click(float mouse_x, float mouse_y, sf::RenderWindow* window);

        ~Button() = default;
};

