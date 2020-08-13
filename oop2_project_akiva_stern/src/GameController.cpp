#include "GameController.h"
#include "Ground.h"
#include "Step.h"
#include "Utilities.h"
#include "CollisionHandling.h"
#include "MovableObject.h"
#include <memory>
#include <vector>


using std::vector;
using std::shared_ptr;

const sf::Keyboard::Key PLAY = sf::Keyboard::Key::P;
const sf::Keyboard::Key HELP = sf::Keyboard::Key::H;
const sf::Keyboard::Key MAIN_MENU = sf::Keyboard::Key::M;
const float SCORE_OFFSET_X = 8; //for end of game only
const float SCORE_OFFSET_Y = 0.7;




void GameController::run()
{
    MediaResources::instance().playBackground();

    auto window = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_STR);

    m_defaultView = window.getView();

    while (window.isOpen())
    {
        mainMenu(window);

        sf::Clock motionClock;

        auto view = window.getView();
       
        m_world = WorldOfObjects();

        m_world.setupLevel();

        while (window.isOpen())
        {
            window.clear();

            auto deltaTime = motionClock.restart();

            view = window.getView();

            view = m_world.updateWorld(view, deltaTime);

            if (m_world.wonGame())
            {
                MediaResources::instance().win();

                finishedGame(window, MediaResources::instance().wonTexture());

                break;
            }
            if (m_world.gameOver())
            {
                MediaResources::instance().gameOver();

                finishedGame(window, MediaResources::instance().gameOverTexture());

                break;
            }

            window.setView(view);

            m_world.draw(window);

            m_dataDisplayer.updateAndDraw(view.getCenter(), m_world.getRedbeardPos(),  m_world.getRedbeardLives(), window, m_world.getTotalPoints(), m_world.getLevelPoints(), m_world.getLevel(), m_world.justStarted());
         
            window.display();

            if (auto event = sf::Event{}; window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                break;
                case sf::Event::KeyPressed:
                {
                    m_world.setRedbeardDirKey(event.key.code);
                    break;
                }
                break;
                case sf::Event::KeyReleased:
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                        continue;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
                        continue;
                    if (event.key.code != sf::Keyboard::Key::Space)
                        m_world.setRedbeardDirKey(sf::Keyboard::Key::BackSpace);
                }
                break;
                }
            }
        }
    }
}


void GameController::mainMenu(sf::RenderWindow& window)
{
    sf::Sprite background(*MediaResources::instance().openingBackgroundTexture());

    bool help = false;

    while (window.isOpen())
    {
        window.clear();
        
        window.draw(background);

        window.display();

        if (auto event = sf::Event{}; window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

                case sf::Event::KeyPressed:
                {
                    if (!help)
                    {
                        if (event.key.code == PLAY)
                            return;
                        if (event.key.code == HELP)
                        {
                            help = true;
                            background = sf::Sprite(*MediaResources::instance().helpTexture());
                        }
                    }
                    else
                    {
                        if (event.key.code == MAIN_MENU)
                        {
                            help = false;
                            background = sf::Sprite(*MediaResources::instance().openingBackgroundTexture());
                        }
                    }
                }
                break;
            }
        }
    }
}




void GameController::finishedGame(sf::RenderWindow& window, sf::Texture* texture)
{
    window.setView(m_defaultView);

    sf::Sprite background(*texture);

    sf::Text score("YOUR SCORE: " + std::to_string(m_world.getTotalPoints()), *MediaResources::instance().font(), 60);

    score.setColor(sf::Color::Green);

    score.setPosition(WINDOW_WIDTH / SCORE_OFFSET_X, WINDOW_HEIGHT * SCORE_OFFSET_Y);

    while (window.isOpen())
    {
        window.clear();

        window.draw(background);

        window.draw(score);

        window.display();

        if (auto event = sf::Event{}; window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == MAIN_MENU)
                {
                    MediaResources::instance().playBackground();
                    return;
                }
            break;
            }
        }
    }
}
