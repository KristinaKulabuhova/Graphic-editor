#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string.h>
#include <unordered_set>
#include "Photo.hpp"
#include "MyEvent.hpp"

//------classes--------//

class Element;
class Image;
class Text;
class Sprite;
class Button;
class CycleShape;
class RectangleShape;

//---------------------//

struct Position {
    float x;
    float y; // нет конструкторов - больно

    Position(float pos_x, float pos_y) {
        x = pos_x;
        y = pos_y;
    }
};

class Element {
    protected:
        bool rendering = 0;
        std::unordered_set<Element*> heirs; 

    public:
        virtual void render(sf::RenderWindow* window) {
            for (auto it = heirs.begin(); it != heirs.end(); ++it) {
                if ((*it)->rendering == 1) {
                    (*it)->render(window);
                }
            }
            //window->display(); // так не должно быть, мы хотим рисовать на экране что-то после рендера всего дерева
        }

        void clear() {
            rendering = 0;
        }

        void add_heir (Element* other) {
            heirs.insert(other);
        }

        void pop_heir (Element* other) {
            heirs.erase(other);
        }
};

class Image : public Element {
    private:
        sf::Image image_;

        std::unordered_set<Element*> heirs; 
    
    public:
        Image(std::string path) {
            image_.loadFromFile(path); 
        }

        sf::Image get_image() const {
            return image_;
        }
};

class Button : public Element { // только обработка нажатий
    private:        
        sf::Event event_;
        int code_;

        std::unordered_set<Element*> heirs; 

    public:
        Button() {
            //...
        }

        void click(float mouse_x, float mouse_y, sf::RenderWindow* window, Photo* photo);
        void set_code(int code);
};

class Text : public Element {
    private:
        sf::Text text_;
        sf::Font font_;

        std::unordered_set<Element*> heirs;
    
    public:
        Text(std::string name_font, std::string text, Position pos = {100.f, 100.f}) {
            font_.loadFromFile(name_font);
            text_.setFont(font_);
            text_.setString(text);
            text_.setPosition(pos.x, pos.y);
        }

        void render(sf::RenderWindow* window) override {
            window->draw(text_);
            Element::render(window);
        }
};

class CycleShape : public Element {
    private:
        sf::CircleShape shape_; // надо избавиться от shape внутри и сделать как-то без него

        std::unordered_set<Element*> heirs;

    public:
        void render(sf::RenderWindow* window) override {
            window->draw(shape_);
            Element::render(window);
        }
};

class RectangleShape : public Element {
    private:
        sf::RectangleShape shape_;

        std::unordered_set<Element*> heirs;

    public:
        RectangleShape(sf::Color color, const sf::Vector2f& size) {
            shape_.setSize(size);
            shape_.setFillColor(color);
        }

        void render(sf::RenderWindow* window) override {
            window->draw(shape_);
            Element::render(window);
        }
};

class Sprite : public Element {
    private:
        sf::Sprite sprite_;
        sf::Texture texture_;

        std::unordered_set<Element*> heirs; 
    
    public:
        Sprite(Image* photo, Position pos) {
            texture_.loadFromImage(photo->get_image(), sf::IntRect(250, 250, 150, 150)); 
            sprite_.setTexture(texture_); 
            sprite_.setPosition(pos.x, pos.y); 
        }

        void render(sf::RenderWindow* window) override {
            window->draw(sprite_);
            Element::render(window);
        }
};