#include "ExitButton.h"

#include "GameManager.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

void ExitButton::OnClicked()
{
	GameManager::Get()->mpWindow->close();
}
