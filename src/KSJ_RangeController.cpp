#include "KSJ_RangeController.h"

#include <math.h>

namespace KSJ
{

RangeController::RangeController(
    const RangeControllerConfig& config
)
    : _config(config),
      _outputStateKnown(false),
      _outputOn(false)
{
}

ControlDecision RangeController::update(
    float measuredValue,
    uint32_t nowMs
)
{
    ControlDecision decision;

    decision.measuredValue =
        measuredValue;

    decision.decidedAtMs =
        nowMs;

    decision.inputValid =
        !isnan(measuredValue);

    if (!decision.inputValid)
    {
        decision.action =
            ControlAction::TurnOff;

        _outputStateKnown = true;
        _outputOn = false;

        return decision;
    }

    if (measuredValue < _config.turnOnBelow)
    {
        if (!_outputStateKnown || !_outputOn)
        {
            decision.action =
                ControlAction::TurnOn;

            _outputStateKnown = true;
            _outputOn = true;
        }

        return decision;
    }

    if (measuredValue > _config.turnOffAbove)
    {
        if (!_outputStateKnown || _outputOn)
        {
            decision.action =
                ControlAction::TurnOff;

            _outputStateKnown = true;
            _outputOn = false;
        }

        return decision;
    }

    decision.action =
        ControlAction::Hold;

    return decision;
}

void RangeController::setConfig(
    const RangeControllerConfig& config
)
{
    _config = config;
}

const RangeControllerConfig&
RangeController::config() const
{
    return _config;
}

void RangeController::reset()
{
    _outputStateKnown = false;
    _outputOn = false;
}

}