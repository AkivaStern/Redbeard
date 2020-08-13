/*
class DisappearingStep
*/

#pragma once
#include "Step.h"

class DisappearingStep : public Step {
public:

	DisappearingStep(sf::Color color, float width, sf::Vector2f pos);

	void activate() override;

	void disActivate() override;

private:

	static bool m_registerit;
};