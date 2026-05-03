#pragma once
#include "Entity.h"

class Button :
    public Entity
{
protected:
    std::string m_text = "";
    sf::Color m_textColor = sf::Color::White;

    float m_waitDelay = 0.f;

    int m_charSize = 20;

public:
    virtual void OnUpdate() override;
    virtual void OnClicked() = 0;

    void Initialize(std::string text, int charSize = 20, int outlineThickness = 1, sf::Color color = sf::Color::White);

    void SetText(std::string text) { m_text = text; }
    std::string GetText() { return m_text; }

    void SetCharSize(int size) { m_charSize = size; }

    void SetTextColor(sf::Color color) { m_textColor = color; }
};

