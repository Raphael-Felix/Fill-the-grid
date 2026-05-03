#include "MenuButton.h"

#include "MainScene.h"

#include <iostream>

void MenuButton::OnClicked()
{
	GetScene<MainScene>()->ShowMenu();
}
