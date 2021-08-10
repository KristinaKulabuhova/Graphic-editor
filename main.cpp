#include <SFML/Graphics.hpp>
#include <iostream>
#include "MyEvent.hpp"
#include "hierarchy.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!", sf::Style::Close);

    Element top_tree;
    // RectangleShape rect_shape; 
    // CycleShape cycle_shape;
    RoundedRectElement rounded;

    // top_tree.add_heir(&rect_shape);
    // top_tree.add_heir(&cycle_shape);
    //top_tree.add_heir(&rounded);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // if (event.type == sf::Event::MouseButtonPressed) {
            //     if (event.mouseButton.button == sf::Mouse::Left) {
            //         printf("Mouse: %d %d\n", event.mouseButton.x, event.mouseButton.y);
            //         myButton.click(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y), &window, &photo);
            //     }
            // }
        }

        window.clear();
        top_tree.render(&window);
        rounded.render(&window);
        window.display();
    }

    return 0;
}
