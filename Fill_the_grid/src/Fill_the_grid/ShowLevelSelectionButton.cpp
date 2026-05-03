#include "ShowLevelSelectionButton.h"

#include "MainScene.h"

void ShowLevelSelectionButton::OnClicked()
{
	GetScene<MainScene>()->ReturnToLevelSelection();
}
