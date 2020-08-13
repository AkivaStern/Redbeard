#include "CollisionHandling.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "Redbeard.h"
#include "Ground.h"
#include "Step.h"
#include "Ball.h"
#include "Water.h"
#include "DisappearingStep.h"
#include "Monster.h"
#include "Gold.h"
#include "Spikes.h"
#include "KeyTriangle.h"
#include <string>

const int COLL_EPS = 4;



namespace
{
    void redBeardGround(GameObject& red,
        GameObject& st)
    {
        RedBeard& redBeard = dynamic_cast<RedBeard&>(red);

        Ground& ground = dynamic_cast<Ground&>(st);

        sf::FloatRect ov; //overlap

        auto res = redBeard.getDrawable()->getGlobalBounds().intersects(ground.getDrawable()->getGlobalBounds(), ov);

        if (ov.width < COLL_EPS && ov.height < COLL_EPS)
            return;

        float myX = redBeard.getPosition().x;
        float myY = redBeard.getPosition().y;
        float groundX = ground.getPosition().x;
        float groundY = ground.getPosition().y;

        float myHeight = redBeard.getDrawable()->getGlobalBounds().height;
        float groundHeight = ground.getDrawable()->getGlobalBounds().height;
        float myWidth = redBeard.getDrawable()->getGlobalBounds().width;
        float groundWidth = ground.getDrawable()->getGlobalBounds().width;

        float x;

        bool blockedLeft = false;
        bool blockedRight = false;

        x = abs((groundX - myX) - (myWidth / 2 + groundWidth / 2));

        float y = abs((myY - groundY) - (myHeight / 2 + groundHeight / 2));

        if (x < COLL_EPS && y > COLL_EPS)
        {
            blockedRight = true;

            redBeard.setDisableRight(true);
        }

        x = abs((myX - groundX) - (myWidth / 2 + groundWidth / 2));

        if (x < COLL_EPS && y > COLL_EPS)
        {
            redBeard.setDisableLeft(true);
            blockedLeft = true;
        }

        x = abs((groundY - myY) - (myHeight / 2 + groundHeight / 2));

        if (x < COLL_EPS)
        {
            redBeard.setDisableFall(true);
            redBeard.setMidFall(false);
            redBeard.setOnGround(true);
        }

        x = abs((myY - groundY) - (myHeight / 2 + groundHeight / 2));

        if (x < COLL_EPS)
        {
            redBeard.setMidJump(false);
            redBeard.setOnGround(true);
        }
    }
         
    void redBeardStep(GameObject& red, GameObject& st)
    {
        RedBeard& redBeard = dynamic_cast<RedBeard&>(red);

        Step* step = dynamic_cast<Step*>(&st);

        redBeard.setStandingStep(step);

        float myX = redBeard.getPosition().x;

        float myY = redBeard.getPosition().y;

        float groundX = step->getPosition().x;

        float groundY = step->getPosition().y;

        float myHeight = redBeard.getDrawable()->getGlobalBounds().height;
        float groundHeight = step->getDrawable()->getGlobalBounds().height;
        float myWidth = redBeard.getDrawable()->getGlobalBounds().width;
        float groundWidth = step->getDrawable()->getGlobalBounds().width;

        float x;

        x = abs((groundY - myY) - (myHeight / 2 + groundHeight / 2));

        if (x < EPS && !redBeard.isDisableLeft() && !redBeard.isDisableRight())
        {
            redBeard.setDisableFall(true);
            redBeard.setMidFall(false);
            redBeard.setOnGround(true);
        }
    }


    void redBeardBall(GameObject& redBeard,
        GameObject& b)
    {
        RedBeard& red = dynamic_cast<RedBeard&>(redBeard);

        Ball& ball = dynamic_cast<Ball&>(b);

        if (ball.getDrawable()->getColor() != red.getCurrentCollectionColor() && !ball.isCollected())
        {   
            auto s = ball.getDrawable()->getColor();

            red.dropAllBalls();

            red.setCurrentCollectionColor(ball.getDrawable()->getColor());
        }

        if (!ball.isCollected())
        {
            MediaResources::instance().ballCollect();

            red.addToBag(&ball);

            ball.getDrawable()->setColor(sf::Color::Transparent, 0);

            ball.collect();
        }
    }

    
    void redBeardDisappearingStep(GameObject& redBeard,
        GameObject& disStep)
    {
        RedBeard& red = dynamic_cast<RedBeard&>(redBeard);

        Step* step = dynamic_cast<Step*>(&disStep);

        if (step->isActive())
            redBeardStep(red, *step);
    }
 
    void redBeardMonster(GameObject& redBeard,
        GameObject& monster)
    {
        RedBeard& red = dynamic_cast<RedBeard&>(redBeard);

        auto rect = monster.getDrawable()->getGlobalBounds();

        if(red.getDrawable()->getGlobalBounds().intersects(rect));
            red.kill();
    }

    void redBeardSpikes(GameObject& redBeard,
        GameObject& spikes)
    {
        RedBeard& red = dynamic_cast<RedBeard&>(redBeard);
        red.kill();
    }

    void redBeardKeyTriangle(GameObject& redBeard,
        GameObject& keyTriangle)
    {
        RedBeard& red = dynamic_cast<RedBeard&>(redBeard);

        KeyTriangle& keyTri = dynamic_cast<KeyTriangle&>(keyTriangle);

        if (keyTri.m_isCollected)
            return;

        if (redBeard.getDrawable()->getGlobalBounds().intersects(keyTri.getKeyGlobalBounds()))
        {
            red.setBallsNeededForColor(keyTri.getDrawable()->getColor(), 0);

            keyTri.collectKey();

            MediaResources::instance().keyCollect();

            red.addKey(&keyTri);
        }
    }

    void redBeardGold(GameObject& redBeard,
        GameObject& gold)
    {
        RedBeard& red = dynamic_cast<RedBeard&>(redBeard);

        red.collectGold();

        MediaResources::instance().levelUp();
    }



    using HitFunctionPtr = void (*)(GameObject&, GameObject&);
    using Key = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<Key, HitFunctionPtr>;


    HitMap initializeCollisionMap()
    {
        HitMap phm;
        phm[Key(typeid(RedBeard), typeid(Ground))] = &redBeardGround;
        phm[Key(typeid(RedBeard), typeid(Step))] = &redBeardStep;
        phm[Key(typeid(RedBeard), typeid(Ball))] = &redBeardBall;
        phm[Key(typeid(RedBeard), typeid(DisappearingStep))] = &redBeardDisappearingStep;
        phm[Key(typeid(RedBeard), typeid(Monster))] = &redBeardMonster;
        phm[Key(typeid(RedBeard), typeid(Spikes))] = &redBeardSpikes;
        phm[Key(typeid(RedBeard), typeid(Gold))] = &redBeardGold;
        phm[Key(typeid(RedBeard), typeid(KeyTriangle))] = &redBeardKeyTriangle;

        return phm;
    }

    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            return nullptr;
        }
        return mapEntry->second;
    }

} // end namespace


void processCollision(GameObject& object1, GameObject& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (!phf)
    {
        throw UnknownCollision(object1, object2);
    }
    phf(object1, object2);
}



bool collided(GameObject& object1, GameObject& object2)
{
    return object1.getDrawable()->getGlobalBounds().intersects(object2.getDrawable()->getGlobalBounds());
}



void checkIfSubmerged(Water& water, RedBeard& redbeard)
{
    if (water.getDrawable()->getGlobalBounds().contains(redbeard.getPosition()))
    {
        redbeard.submerge();
        
        if (MediaResources::instance().isDrowning() != sf::SoundSource::Status::Playing)
        {
            MediaResources::instance().drowning();
            MediaResources::instance().setBackgroundVolume(UNDERWATER_MUS_VOL);
        }
    }

    else
    {
        redbeard.dryOff();
        MediaResources::instance().dry();
    }
}
