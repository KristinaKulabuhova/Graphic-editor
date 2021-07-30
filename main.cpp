#include <SFML/Graphics.hpp>
#include <iostream>
#include "MyEvent.hpp"
#include "Button.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!", sf::Style::Close);
    Button myButton;
    Photo photo;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Pressed" << std::endl;
                    myButton.set_code(open_photo);
                    myButton.click(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y), &window, &photo);
                }
            }
        }

        window.clear();
        myButton.draw(&window);
        window.display();
    }

    return 0;
}
