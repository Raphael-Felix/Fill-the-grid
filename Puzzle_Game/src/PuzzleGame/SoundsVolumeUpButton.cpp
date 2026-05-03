#include "SoundsVolumeUpButton.h"

#include "MainScene.h"
#include "SoundManager.h"

#include <iostream>

void SoundsVolumeUpButton::OnClicked()
{
	GetScene<MainScene>()->PlayRandomClick();
	SoundManager::GetInstance()->ChangeSoundVolume(10);
}
