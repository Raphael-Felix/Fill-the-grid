#include "RightLevelButton.h"

#include "MainScene.h"

void RightLevelButton::OnClicked()
{
	GetScene<MainScene>()->ShowRightLevel();
}