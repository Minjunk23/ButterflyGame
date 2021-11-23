#include <SFML/Graphics.hpp>
#include "butterfly.cpp"

int main() {
    
    const int columns = 3;
    const int rows = 3;
    int gameScore = 0;
    bool pressed = false;
    bool correct = false;
    bool term = false;
    bool gameOver = false;
    bool startGame = true;
    double timeMultiplier = 1;
    int highScore = 0;
    
    sf::Font font;
    font.loadFromFile("/Users/minjunkim/Desktop/SFMLapp/SFMLapp/Fonts/parchment.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Current Score:");
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    
    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(30);
    score.setStyle(sf::Text::Bold);
    score.setFillColor(sf::Color::White);
    
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(30);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setFillColor(sf::Color::White);
    
    sf::Text restartText;
    restartText.setFont(font);
    restartText.setCharacterSize(30);
    restartText.setStyle(sf::Text::Bold);
    restartText.setFillColor(sf::Color::White);
    
    sf::Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(30);
    highScoreText.setStyle(sf::Text::Bold);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setString("Highscore:" + to_string(highScore));
    
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Game");
    sf::RectangleShape grid[columns][rows];
    
    Butterfly b1("/Users/minjunkim/Desktop/SFMLapp/SFMLapp/butterfly.png");
    
    int random_x = rand() %3;
    int random_y = rand() %3;
    
    sf::Clock clock;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        window.clear();
        
        if (startGame){
            
            restartText.setString("Press Anywhere to Start");
            restartText.setPosition(350,250);
            window.draw(restartText);
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                startGame = false;
                term = true;
                clock.restart();
            }
            
        }
        
        if (!gameOver){
            sf::Vector2f cellSize(200.0f, 200.0f);
            sf::Time elapsed = clock.getElapsedTime();
            
            if (elapsed.asSeconds() > 2/timeMultiplier && !term){
                if (!pressed){
                    gameOver = true;
                    pressed = true;
                    clock.restart();
                }
                random_x = rand() %3;
                random_y = rand() %3;
                pressed = false;
                correct = false;
                clock.restart();
                term = true;
            }
            
            for (int i = 0; i < columns; i++) {
                for (int j =0; j < rows; j++) {
                    grid[i][j].setSize(cellSize);
                    grid[i][j].setOutlineColor(sf::Color::Black);
                    grid[i][j].setOutlineThickness(2.0f);
                    
                    grid[i][j].setPosition(i * cellSize.x + 2.0f, j * cellSize.y + 2.0f);
                    
                    window.draw(grid[i][j]);
                }
                
            }
            
            
            float curX = random_x * cellSize.x + 2.0f;
            float curY = random_y * cellSize.y + 2.0f;
            
            sf::RectangleShape greenrec;
            greenrec.setSize(cellSize);
            greenrec.setOutlineThickness(2.0f);
            greenrec.setPosition(curX,curY);
            
            if (correct == true) {
                greenrec.setOutlineColor(sf::Color::Green);
                window.draw(greenrec);
            }
            
            if (!term) {
                window.draw(b1.draw(curX, curY));
            } else {
                sf::Time elapsed2 = clock.getElapsedTime();
                if (elapsed2.asSeconds() > 1) {
                    clock.restart();
                    term = false;
                    pressed = false;
                }
            }
            
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !term) {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                if (localPosition.x <600) {
                    if (localPosition.x >curX && localPosition.x < (curX +200) && localPosition.y > curY && localPosition.y < (curY + 200) && !pressed) {
                        gameScore += 1;
                        pressed = true;
                        correct = true;
                        timeMultiplier += 0.2;
                    } else if (!pressed){
                        gameOver = true;
                        pressed = true;
                        if (highScore < gameScore){
                            highScore = gameScore;
                        }
                        clock.restart();
                    }
                }
            }
            
            
            text.setPosition(650,200);
            window.draw(text);
            
            score.setString(to_string(gameScore));
            score.setPosition(800,200);
            window.draw(score);
        } else {
            gameOverText.setString("Game Over");
            gameOverText.setPosition(430, 200);
            window.draw(gameOverText);
            
            highScoreText.setString("Highscore:" + to_string(highScore));
            highScoreText.setPosition(410, 280);
            window.draw(highScoreText);
            
            text.setString("Current Score:");
            text.setPosition(380,330);
            window.draw(text);
            
            score.setString(to_string(gameScore));
            score.setPosition(550,330);
            window.draw(score);
            
            restartText.setString("Press Anywhere to Start Again");
            restartText.setPosition(330,400);
            window.draw(restartText);
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed){
                gameScore = 0;
                gameOver = false;
                pressed = true;
                term = true;
                correct = false;
                clock.restart();
                timeMultiplier = 1;
            }
            
            sf::Time elapsed3 = clock.getElapsedTime();
            if (elapsed3.asSeconds() > 0.5 && pressed){
                pressed = false;
            }
        }
        window.display();
    }
    
    return 0;
}

