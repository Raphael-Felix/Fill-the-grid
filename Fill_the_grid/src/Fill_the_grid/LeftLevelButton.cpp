#include "LeftLevelButton.h"

#include "MainScene.h"

void LeftLevelButton::OnClicked()
{
	GetScene<MainScene>()->ShowLeftLevel();
}