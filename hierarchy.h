#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string.h>
#include <vector>
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

enum id_shape {
    CycleShape,
    RectangleShape
};

class PrimitiveShape {
    protected:
        Position pos_;
        sf::Vector2f size_;
        sf::Color color_;
        float radius_;
        id_shape id_;

    public:
        PrimitiveShape(Position pos = {0, 0}, sf::Vector2f size = {0, 0}, sf::Color color = sf::Color(0, 0, 0), float radius = 0, id_shape id = RectangleShape) : pos_(pos), size_(size), color_(color), radius_(radius), id_(id) {};
        virtual void render(sf::RenderWindow* window) = 0;
};

class CycleShape : public PrimitiveShape {
    private:
        sf::CircleShape shape_; 

    public:
        CycleShape() {
            shape_.setRadius(radius_);
            shape_.setFillColor(color_);
            shape_.setPosition(pos_.x, pos_.y);
        }

        void render(sf::RenderWindow* window) override {
            window->draw(shape_);
        }
};

class RectangleShape : public PrimitiveShape {
    private:
        sf::RectangleShape shape_;

    public:
        RectangleShape() {
            shape_.setSize(size_);
            shape_.setFillColor(color_);
            shape_.setPosition(pos_.x, pos_.y);
        }

        void render(sf::RenderWindow* window) override {
            window->draw(shape_);
        }
};

class Shape : public Element {
    private:
        std::vector<PrimitiveShape> shapes_;

    public:
        Shape(const std::vector<PrimitiveShape>& other) : shapes_(other) {}
        // перемещение
        void render(sf::RenderWindow* window) override {
            for (auto el : shapes_) {
                el.render(window);
            }
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