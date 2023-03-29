#include <bits/stdc++.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
    int rectangle_velocity_x = 100;
    int rectangle_velocity_y = 300;
    int rectangle_angular_velocity = 10;

    int dot_vel_x = 500;
    int dot_vel_y = 600;

    bool dot_flag_y = false, dot_flag_x = false;

    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "My window");

    // create some shapes
    sf::CircleShape circle(100.0);
    circle.setPosition(100.0, 300.0);
    circle.setFillColor(sf::Color(100, 250, 50));

    sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color(100, 50, 250));

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0.0, 0.0));
    triangle.setPoint(1, sf::Vector2f(0.0, 100.0));
    triangle.setPoint(2, sf::Vector2f(140.0, 40.0));
    triangle.setOutlineColor(sf::Color::Red);
    triangle.setOutlineThickness(5);
    triangle.setPosition(600.0, 100.0);

    sf::CircleShape dot(10.0);
    dot.setPosition(10.0, 10.0);
    dot.setFillColor(sf::Color::Cyan);

    // run the program as long as the window is open
    while (window.isOpen()) {
        sf::Clock clock;
        sf::Time elapsed = clock.restart();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);
        window.draw(dot);

        // end the current frame
        window.display();

        elapsed = clock.getElapsedTime();
        std::cout << 1/elapsed.asSeconds() << std::endl;
        float dt = elapsed.asSeconds();

        rectangle.move(rectangle_velocity_x*dt,rectangle_velocity_y*dt);
        rectangle.rotate(rectangle_angular_velocity*dt);

        sf::FloatRect rectangle_bounds = rectangle.getGlobalBounds();

        dot.move(dot_vel_x * dt, dot_vel_y * dt);

        sf::FloatRect dot_bounds = dot.getGlobalBounds();

        if(dot_bounds.top <= 0 || dot_bounds.top + dot_bounds.height>=window.getSize().y){
            if(dot_flag_y != true)
                dot_vel_y *= -1;
            dot_flag_y = true;
        }
        else
            dot_flag_y = false;

        if(dot_bounds.left<=0 || dot_bounds.left+dot_bounds.width>=window.getSize().x){
            if(dot_flag_x!=true)
                dot_vel_x *= -1;
            dot_flag_x = true;
        }
        else
            dot_flag_x = false;

        if(rectangle_bounds.top <= 0){
            rectangle_velocity_y = abs(rectangle_velocity_y);
            rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.top + rectangle_bounds.height >= window.getSize().y){
            rectangle_velocity_y = abs(rectangle_velocity_y) * -1;
            rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.left <= 0 ){
            rectangle_velocity_x = abs(rectangle_velocity_x);
            rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.left + rectangle_bounds.width >= window.getSize().x){
            rectangle_velocity_x = abs(rectangle_velocity_x) * -1;
            rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }
    }

    return 0;
}
