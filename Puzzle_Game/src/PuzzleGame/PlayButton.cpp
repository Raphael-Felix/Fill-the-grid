#include "PlayButton.h"

#include "MainScene.h"

void PlayButton::OnClicked()
{
	GetScene<MainScene>()->LoadLevel();
}