#include "MediaResources.h"



MediaResources& MediaResources::instance()
{
    static MediaResources instance;
    return instance;
}

MediaResources::MediaResources()
{
    
    if(!m_backgroundMusic.openFromFile("background.ogg"))
        throw std::runtime_error("can't open music");

    m_backgroundMusic.setVolume(MUSIC_VOL);
    m_backgroundMusic.setLoop(true);

    if(!m_jumpBfr.loadFromFile("jump.ogg"))
        throw std::runtime_error("can't open jump file");

    m_jump.setBuffer(m_jumpBfr);
    m_jump.setVolume(15);

    if (!m_ballCollectBfr.loadFromFile("ballCollect.wav"))
        throw std::runtime_error("can't open ball sound file");

    m_ballCollect.setBuffer(m_ballCollectBfr);

    if (!m_keyCollectBfr.loadFromFile("keyCollect.wav"))
        throw std::runtime_error("can't open key sound file");

    m_keyCollect.setBuffer(m_keyCollectBfr);

    if (!m_drownBfr.loadFromFile("drowning.wav"))
        throw std::runtime_error("cant open drown sound");

    m_drown.setBuffer(m_drownBfr);
    m_drown.setLoop(true);
    m_drown.setPitch(2);
    
    if (!m_deadBfr.loadFromFile("lifelost.wav"))
        throw std::runtime_error("cant open dead sound");

    m_dead.setBuffer(m_deadBfr);

    if (!m_levelUpBfr.loadFromFile("levelUp.wav"))
        throw std::runtime_error("cant open level up sound");

    m_levelUp.setBuffer(m_levelUpBfr);
   
    if (!m_gameOverBfr.loadFromFile("gameover.wav"))
        throw std::runtime_error("cant open game over sound");

    m_gameOver.setBuffer(m_gameOverBfr);

    if (!m_winBfr.loadFromFile("won.ogg"))
        throw std::runtime_error("cant open won sound");

    m_win.setBuffer(m_winBfr);

    if(!m_font.loadFromFile("C:/Windows/Fonts/Impact.ttf"))
        throw std::runtime_error("Can't load font");

    if (!m_groundTexture.loadFromFile("wall.png"))
    {
        throw std::runtime_error("Can't load file");
    }

    if (!m_monsterTexture.loadFromFile("monster.png"))
    {
        throw std::runtime_error("Can't load file");
    }
    if (!m_redbeardTexture.loadFromFile("redbeardSpritesheet.png"))
    {
        throw std::runtime_error("Can't load file");
    }
    if (!m_spikesTexture.loadFromFile("spikes.png"))
    {
        throw std::runtime_error("Can't load file");
    }
    if (!m_goldTexture.loadFromFile("gold.png"))
    {
        throw std::runtime_error("Can't load file");
    }
    if (!m_keyTexture.loadFromFile("key.png"))
    {
        throw std::runtime_error("Can't load file");
    }
    if (!m_waterTexture.loadFromFile("water.png"))
    {
        throw std::runtime_error("Can't load file");
    }
    if (!m_backgroundTexture.loadFromFile("background.png"))
    {
        throw std::runtime_error("Can't load file");
    }
    if (!m_bulletinTexture.loadFromFile("bulletin.png"))
    {
        throw std::runtime_error("Can't load file");
    }

    if (!m_livesTexture.loadFromFile("lives.png"))
    {
        throw std::runtime_error("Can't load file");
    }

    if (!m_openingBackgroundTexture.loadFromFile("openingBackground.png"))
    {
        throw std::runtime_error("Can't load file");
    }

    if (!m_helpTexture.loadFromFile("help.png"))
    {
        throw std::runtime_error("Can't load file");
    }

    if (!m_wonTexture.loadFromFile("won.jpg"))
    {
        throw std::runtime_error("Can't load file");
    }
    if (!m_gameOverTexture.loadFromFile("gameover.jpg"))
    {
        throw std::runtime_error("Can't load file");
    }
}


void MediaResources::dry()
{ 
    m_drown.stop(); 
    m_backgroundMusic.setVolume(MUSIC_VOL); 
}

void MediaResources::win() 
{ 
    m_backgroundMusic.stop(); 
    m_levelUp.stop(); 
    m_win.play(); 
}


void MediaResources::playBackground() 
{ 
    m_backgroundMusic.play(); 
    m_win.stop();
    m_gameOver.stop(); 
}


void MediaResources::gameOver() 
{
    m_backgroundMusic.stop();
    m_gameOver.play(); 
}
