#include "MusicsVolumeDownButton.h"

#include "MainScene.h"
#include "SoundManager.h"

#include <iostream>

void MusicsVolumeDownButton::OnClicked()
{
	GetScene<MainScene>()->PlayRandomClick();
	SoundManager::GetInstance()->ChangeMusicVolume(-5);
}
