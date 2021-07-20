#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string.h>
#include "MyEvent.hpp"

class Button {
    protected:
        sf::RectangleShape shape_; 
        sf::Font font_;
        sf::Text text_;
        sf::Event event_;

        int code;

    public:
        Button(std::string name_font, std::string text, const sf::Vector2f& size, sf::Color color);

        virtual void draw(sf::RenderWindow* window) = 0;
        virtual void click(float mouse_x, float mouse_y, sf::RenderWindow* window) = 0;

        ~Button() = default;
};

class ButtonOpenPhoto: public Button {
    private:
        int code = 1;
    
    public:
        ButtonOpenPhoto(std::string name_font = "IndieFlower-Regular.ttf", std::string text = "Open photo", const sf::Vector2f& size = sf::Vector2f(120.f, 50.f), sf::Color color = sf::Color(0, 255, 0, 100));

        virtual ButtonEvent click(float mouse_x, float mouse_y, sf::RenderWindow* window) override;

        void draw(sf::RenderWindow* window) override;
};
