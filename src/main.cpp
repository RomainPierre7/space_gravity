#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "planet.hpp"

int main(){
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktop.width, desktop.height), "Solar System");
    window.setFramerateLimit(60);

    sf::CircleShape sun;
    sun.setRadius(30);
    sun.setFillColor(sf::Color::Yellow);
    sun.setPosition(sf::Vector2f(desktop.width / 2 - sun.getRadius(), desktop.height / 2 - sun.getRadius()));

    Planet planets[PLANET_COUNT] = {
        Planet(57.91 * SCALE, 100, 10, sf::Vector2f(desktop.width / 2 + 100 - 10, desktop.height / 2 - 10)), //Mercury
        Planet(108.2 * SCALE, 150, 10, sf::Vector2f(desktop.width / 2 + 150 - 10, desktop.height / 2 - 10)), //Venus
        Planet(149.6 * SCALE, 200, 10, sf::Vector2f(desktop.width / 2 + 200 - 10, desktop.height / 2 - 10)), //Earth
        Planet(227.9 * SCALE, 250, 10, sf::Vector2f(desktop.width / 2 + 250 - 10, desktop.height / 2 - 10)), //Mars
        Planet(778.5 * SCALE, 300, 10, sf::Vector2f(desktop.width / 2 + 300 - 10, desktop.height / 2 - 10)), //Jupiter
        Planet(1400 * SCALE, 350, 10, sf::Vector2f(desktop.width / 2 + 350 - 10, desktop.height / 2 - 10)), //Saturn
        Planet(2900 * SCALE, 400, 10, sf::Vector2f(desktop.width / 2 + 400 - 10, desktop.height / 2 - 10)), //Uranus
        Planet(4500 * SCALE, 450, 10, sf::Vector2f(desktop.width / 2 + 450 - 10, desktop.height / 2 - 10)) //Neptune
    };

    planets[0].setFillColor(sf::Color(128, 128, 128, 255));
    planets[1].setFillColor(sf::Color(255, 165, 0, 255));
    planets[2].setFillColor(sf::Color(0, 0, 255, 255));
    planets[3].setFillColor(sf::Color(255, 0, 0, 255));
    planets[4].setFillColor(sf::Color(255, 255, 150, 255));
    planets[5].setFillColor(sf::Color(218, 165, 32, 255));
    planets[6].setFillColor(sf::Color(0, 191, 255, 255));
    planets[7].setFillColor(sf::Color(0, 0, 139, 255));

    for (int i = 0; i < PLANET_COUNT; i++){
        planets[i].setAngularVelocity(sqrt((G * SUN_MASS) / (pow(planets[i].getDistance(), 3))));
    }

    sf::CircleShape circles[PLANET_COUNT] = {
        sf::CircleShape(planets[0].getDistanceShape()),
        sf::CircleShape(planets[1].getDistanceShape()),
        sf::CircleShape(planets[2].getDistanceShape()),
        sf::CircleShape(planets[3].getDistanceShape()),
        sf::CircleShape(planets[4].getDistanceShape()),
        sf::CircleShape(planets[5].getDistanceShape()),
        sf::CircleShape(planets[6].getDistanceShape()),
        sf::CircleShape(planets[7].getDistanceShape())
    };

    for (int i = 0; i < PLANET_COUNT; i++){
        circles[i].setFillColor(sf::Color::Transparent);
        circles[i].setOutlineColor(sf::Color::White);
        circles[i].setOutlineThickness(1);
        circles[i].setPosition(desktop.width / 2 - planets[i].getDistanceShape(), desktop.height / 2 - planets[i].getDistanceShape());
    }

    double time = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        time += 0.1;
        window.draw(sun);
        for (int i = 0; i < PLANET_COUNT; i++){
            planets[i].update(time, desktop.width, desktop.height);
            planets[i].draw(window);
            window.draw(circles[i]);
        }
        window.display();
    }
    return 0;
}