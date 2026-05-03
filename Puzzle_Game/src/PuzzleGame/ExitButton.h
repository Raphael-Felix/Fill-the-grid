#pragma once

#include "Button.h"

class ExitButton :
    public Button
{
public:
    void OnClicked() override;
};
