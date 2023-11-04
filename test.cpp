#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <random>


int main(){
    sf::RenderWindow window(sf::VideoMode(500,500), "Test", sf::Style::Default);

    window.setFramerateLimit(120);

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<> dist (0,255);


    sf::RectangleShape toolbar(sf::Vector2f(500.0f, 100.0f));
    toolbar.setFillColor(sf::Color::Blue);
    toolbar.setPosition(0,0);

    sf::Clock clock;
    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }

        if(clock.getElapsedTime().asSeconds() >= 1){
            window.clear(sf::Color(dist(mt), dist(mt), dist(mt)));
            clock.restart();
        }
        

        window.draw(toolbar);

        window.display();

    }


    return 0;
}