#include "SpriteObject.h"

void SpriteObject::setTexture(sf::Texture* t, sf::Vector2f pos, sf::IntRect intRect) 
{
	if (t)
	{
		m_obj.setTexture(*t);

		if (intRect != sf::IntRect(0, 0, 0, 0))
			m_obj.setTextureRect(intRect);

		initializePos(pos);
	}
}