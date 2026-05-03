#include "MusicsVolumeUpButton.h"

#include "MainScene.h"
#include "SoundManager.h"

#include <iostream>

void MusicsVolumeUpButton::OnClicked()
{
	GetScene<MainScene>()->PlayRandomClick();
	SoundManager::GetInstance()->ChangeMusicVolume(5);
}
