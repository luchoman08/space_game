#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameManager.h"

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "Space Game");

    GameManager gameManager(app);

    if (!gameManager.Initialize())
    {
        std::cout << "Failure loading graphics." << std::endl;
        return EXIT_FAILURE;
    }
	app.setFramerateLimit (150); // Limit to 60 frames per second
    // Clock used to calculate the delta time
    sf::Clock deltaClock;

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event ;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        float elapsedTime = deltaClock.getElapsedTime().asMilliseconds();


         gameManager.UpdateGame(elapsedTime, event);
        // Clear screen
        app.clear();

        gameManager.DrawGame(elapsedTime);
        // Update the window
        app.display();
    }

    gameManager.FreeResources();

    return EXIT_SUCCESS;
}
