#pragma once

#include <Arduino.h>

#include "ControlAction.h"

namespace KSJ
{

struct ControlDecision
{
    ControlAction action =
        ControlAction::Hold;

    bool inputValid = false;

    float measuredValue = NAN;

    uint32_t decidedAtMs = 0;
};

}