#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string.h>
#include <variant>
#include <vector>
#include <unordered_set>
#include "Photo.hpp"
#include "MyEvent.hpp"

//------classes--------//

// class Element;
// class Image;
// class Text;
// class Button;
// class CycleShape;
// class RectangleShape;

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
        bool rendering = 1;
        std::unordered_set<Element*> heirs; 

    public:
        virtual void render(sf::RenderWindow* window) {
            for (auto it = heirs.begin(); it != heirs.end(); ++it) {
                if ((*it)->rendering == 1) {
                    (*it)->render(window);
                }
            }
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

class Image {
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

class Button { // только обработка нажатий
    private:        
        sf::Event event_;
        int code_;

        std::unordered_set<Element*> heirs; 

    public:
        Button() {
            //...
        }

        //void click(float mouse_x, float mouse_y, sf::RenderWindow* window, Photo* photo);
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
class RectangleShape : public Element {
    private:
        sf::Vector2f size_;
        Position pos_;
        sf::Color color_;

    public:
        RectangleShape(sf::Vector2f size = {100, 100}, Position pos = {200, 200}, sf::Color color = sf::Color(255,0,0)) : size_(size), pos_(pos), color_(color) {}

        void render(sf::RenderWindow* window) {
            auto shape = sf::RectangleShape(size_);
            shape.setPosition(pos_.x, pos_.y);
            shape.setFillColor(color_);

            window->draw(shape);
        }
};

class CycleShape : public Element {
    private:
        float radius_;
        Position pos_;
        sf::Color color_;

    public:
        CycleShape(float radius = 50, Position pos = {300, 300}, sf::Color color = sf::Color(0,255,0)) : radius_(radius), pos_(pos), color_(color) {}

        void render(sf::RenderWindow* window) {
            auto shape = sf::CircleShape(radius_);
            shape.setPosition(pos_.x, pos_.y);
            shape.setFillColor(color_);

            window->draw(shape);
        }
};

class RoundedRectElement : public RectangleShape {
    private:

    public:
        void render(sf::RenderWindow* window) override {
            auto rect_one = RectangleShape({300, 325}, {200, 175}, sf::Color(255, 0, 0));
            auto rect_two = RectangleShape({325, 300}, {175, 200}, sf::Color(255, 0, 0));

            auto cycle_lu = CycleShape(25, {200, 200}, sf::Color(255, 0, 0));
            auto cycle_ru = CycleShape(25, {300, 200}, sf::Color(255, 0, 0));
            auto cycle_ld = CycleShape(25, {200, 300}, sf::Color(255, 0, 0));
            auto cycle_rd = CycleShape(25, {300, 300}, sf::Color(255, 0, 0));

            //window->draw(rect_one);
        }
};

// class Sprite : public Element {
//     private:
//         sf::Sprite sprite_;
//         sf::Texture texture_;

//         std::unordered_set<Element*> heirs; 
    
//     public:
//         Sprite(Image* photo, Position pos) {
//             texture_.loadFromImage(photo->get_image(), sf::IntRect(250, 250, 150, 150)); 
//             sprite_.setTexture(texture_); 
//             sprite_.setPosition(pos.x, pos.y); 
//         }

//         void render(sf::RenderWindow* window) override {
//             window->draw(sprite_);
//             Element::render(window);
//         }
// };