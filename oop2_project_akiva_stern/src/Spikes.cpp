#include "Spikes.h"
#include "Factory.h"



bool Spikes::m_registerit = Factory::registeritStatic(SPIKES, [](std::string str, sf::Vector2f pos) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<Spikes>(MediaResources::instance().spikesTexture(), pos);
	});