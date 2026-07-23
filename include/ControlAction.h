#pragma once

#include <Arduino.h>

namespace KSJ
{

enum class ControlAction : uint8_t
{
    Hold,
    TurnOn,
    TurnOff
};

}