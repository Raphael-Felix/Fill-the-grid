#include "Button.h"
#include "Debug.h"

#include "SFML/Graphics/Shape.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

void Button::OnUpdate()
{
	if (mActive)
	{
		m_waitDelay += GetDeltaTime();

		sf::Vector2f position = GetPosition(1.f, 0.5f);

		position.x -= m_text.size() * m_charSize / 1.25;
		position.y -= m_charSize / 2;

		Debug::DrawText(position.x, position.y, m_text, m_textColor, m_charSize);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*dynamic_cast<sf::Window*>(GameManager::Get()->mpWindow));

			if (IsInside(mousePos.x, mousePos.y) && m_waitDelay >= 0.25f)
			{
				OnClicked();
				m_waitDelay = 0.f;
			}
		}
	}
}

void Button::Initialize(std::string text, int charSize, int outlineThickness, sf::Color color)
{
	SetText(text);
	SetCharSize(charSize);
	SetTextColor(color);
	GetShape()->setOutlineThickness(outlineThickness);
}