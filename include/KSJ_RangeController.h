#pragma once

#include <Arduino.h>

#include "ControlDecision.h"
#include "RangeControllerConfig.h"

namespace KSJ
{

class RangeController
{
public:
    explicit RangeController(
        const RangeControllerConfig& config
    );

    ControlDecision update(
        float measuredValue,
        uint32_t nowMs
    );

    void setConfig(
        const RangeControllerConfig& config
    );

    const RangeControllerConfig&
        config() const;

    void reset();

private:
    RangeControllerConfig _config;

    bool _outputStateKnown;
    bool _outputOn;
};

}