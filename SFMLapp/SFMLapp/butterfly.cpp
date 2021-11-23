#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class Butterfly
{
private:
    sf::Texture shapeTexture;
    sf::RectangleShape shape;
    
public:
    Butterfly(string url)
    {
        shape.setFillColor(sf::Color::White);
        shapeTexture.loadFromFile(url);
        shape.setTexture(&shapeTexture);
    }
    
    sf::RectangleShape draw(float x, float y)
    {
        sf::Vector2f cellSize(200.0f, 200.0f);
        shape.setSize(cellSize);
        shape.setPosition(x, y);
        
        return shape;
    }
    
};
