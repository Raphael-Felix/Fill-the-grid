#include "EndGameButton.h"

#include "MainScene.h"

void EndGameButton::OnClicked()
{
	GetScene<MainScene>()->EndGame();
}
