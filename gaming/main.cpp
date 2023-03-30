#include <bits/stdc++.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {

    int dot_vel_x = 500;
    int dot_vel_y = 600;

    bool dot_flag_y = false, dot_flag_x = false;

    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "My window");
    window.setFramerateLimit(144);

    const float grid_size = 50.f;

    // create some shapes

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(grid_size, grid_size));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color::Blue);

    sf::CircleShape dot(10.f);
    dot.setPosition(10.0, 10.0);
    dot.setFillColor(sf::Color::Red);

    const float movement_speed = 250.f;
    sf::Vector2f velocity;
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
        window.draw(rectangle);
        window.draw(dot);

        window.display();

        //sf::FloatRect rectangle_bounds = rectangle.getGlobalBounds();

        sf::FloatRect dot_bounds = dot.getGlobalBounds();

        elapsed = clock.getElapsedTime();
        float dt = elapsed.asSeconds();

        //movement control
        velocity.x = 0;
        velocity.y = 0;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            velocity.y += -movement_speed * dt;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            velocity.x += -movement_speed * dt;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            velocity.y += movement_speed * dt;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            velocity.x += movement_speed * dt;

        rectangle.move(velocity);

        dot.move(dot_vel_x * dt, dot_vel_y * dt);

        std::cout << rectangle.getPosition().y << std::endl;

        //collisions
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

        if(rectangle.getPosition().x <= 0) //left
            rectangle.setPosition(0, rectangle.getPosition().y);
        if(rectangle.getPosition().x + rectangle.getSize().x >= 1000) //right
            rectangle.setPosition(1000 - rectangle.getSize().x, rectangle.getPosition().y);
        if(rectangle.getPosition().y <= 0) //top
            rectangle.setPosition(rectangle.getPosition().x, 0);
        if(rectangle.getPosition().y + rectangle.getSize().y >= 800) //bottom
            rectangle.setPosition(rectangle.getPosition().x, 800 - rectangle.getSize().y);


        // end the current frame



    }

    return 0;
}
