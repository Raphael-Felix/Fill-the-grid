#pragma once

#include "Button.h"

class EndGameButton :
    public Button
{
public:
    void OnClicked() override;
};
