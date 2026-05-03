#include "SoundsVolumeDownButton.h"

#include "MainScene.h"
#include "SoundManager.h"

#include <iostream>

void SoundsVolumeDownButton::OnClicked()
{
	GetScene<MainScene>()->PlayRandomClick();
	SoundManager::GetInstance()->ChangeSoundVolume(-10);
}
