/*
MediaResources:
Singleton for audio/images
*/

#pragma once

#include <SFML/graphics.hpp>
#include <SFML/Audio.hpp>
#include "Utilities.h"
#include <vector>



class MediaResources
{
public:

    static MediaResources& instance();

    MediaResources(const MediaResources&) = delete;

    MediaResources& operator=(const MediaResources&) = delete;

    sf::Font* font() { return &m_font; }

    sf::Texture* waterTexture() { return &m_waterTexture; }

    sf::Texture* backgroundTexture() { return &m_backgroundTexture; }

    sf::Texture* groundTexture()  { return &m_groundTexture; }

    sf::Texture* monsterTexture() { return &m_monsterTexture; }

    sf::Texture* redbeardTexture() { return &m_redbeardTexture; }

    sf::Texture* spikesTexture() { return &m_spikesTexture; }

    sf::Texture* goldTexture() { return &m_goldTexture; }

    sf::Texture* keyTexture() { return &m_keyTexture; }

    sf::Texture* bulletinTexture() { return &m_bulletinTexture; }

    sf::Texture* livesTexture() { return &m_livesTexture; }

    sf::Texture* openingBackgroundTexture() { return &m_openingBackgroundTexture; }

    sf::Texture* helpTexture() { return &m_helpTexture; }

    sf::Texture* gameOverTexture() { return &m_gameOverTexture; }

    sf::Texture* wonTexture() { return &m_wonTexture; }

    void playBackground();

    void setBackgroundVolume(int vol) { m_backgroundMusic.setVolume(vol); }

    void jumpSound() { m_jump.play();  }

    void ballCollect() { m_ballCollect.play(); }

    void keyCollect() { m_keyCollect.play(); }

    void drowning() { m_drown.play(); }

    sf::SoundSource::Status isDrowning() { return m_drown.getStatus(); }

    void dry();

    void kill() { m_dead.play(); }

    void levelUp() { m_levelUp.play(); }

    void gameOver();

    void win();

private:

    MediaResources();
    sf::Font m_font;
    sf::Texture m_backgroundTexture;
    sf::Texture m_waterTexture;
    sf::Texture m_groundTexture;
    sf::Texture m_monsterTexture;
    sf::Texture m_redbeardTexture;
    sf::Texture m_spikesTexture;
    sf::Texture m_goldTexture;
    sf::Texture m_keyTexture;
    sf::Texture m_bulletinTexture;
    sf::Texture m_livesTexture;
    sf::Texture m_openingBackgroundTexture;
    sf::Texture m_helpTexture;
    sf::Texture m_wonTexture;
    sf::Texture m_gameOverTexture;
    sf::Music m_backgroundMusic;
    sf::SoundBuffer m_jumpBfr;
    sf::Sound m_jump;
    sf::SoundBuffer m_ballCollectBfr;
    sf::Sound m_ballCollect;
    sf::SoundBuffer m_keyCollectBfr;
    sf::Sound m_keyCollect;
    sf::SoundBuffer m_drownBfr;
    sf::Sound m_drown;
    sf::SoundBuffer m_deadBfr;
    sf::Sound m_dead;
    sf::SoundBuffer m_levelUpBfr;
    sf::Sound m_levelUp;
    sf::SoundBuffer m_gameOverBfr;
    sf::Sound m_gameOver;
    sf::SoundBuffer m_winBfr;
    sf::Sound m_win;
};

