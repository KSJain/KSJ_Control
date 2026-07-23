#include <Arduino.h>

#include <ControlAction.h>
#include <ControlDecision.h>
#include <KSJ_RangeController.h>
#include <RangeControllerConfig.h>

namespace Timing
{
    constexpr uint32_t STEP_INTERVAL_MS =
        1500;
}

const KSJ::RangeControllerConfig humidityConfig
{
    75.0F,
    82.0F
};

KSJ::RangeController humidityController(
    humidityConfig
);

const float simulatedHumidityValues[] =
{
    84.0F,
    81.0F,
    78.0F,
    74.0F,
    73.0F,
    76.0F,
    80.0F,
    83.0F,
    NAN,
    79.0F
};

constexpr size_t VALUE_COUNT =
    sizeof(simulatedHumidityValues) /
    sizeof(simulatedHumidityValues[0]);

size_t currentValueIndex = 0;

uint32_t previousStepMs = 0;

const char* actionName(
    KSJ::ControlAction action
)
{
    switch (action)
    {
        case KSJ::ControlAction::TurnOn:
            return "TURN ON";

        case KSJ::ControlAction::TurnOff:
            return "TURN OFF";

        case KSJ::ControlAction::Hold:
        default:
            return "HOLD";
    }
}

void printDecision(
    const KSJ::ControlDecision& decision
)
{
    Serial.println();
    Serial.println("------------------------");

    Serial.print("Measured value: ");

    if (decision.inputValid)
    {
        Serial.print(
            decision.measuredValue,
            1
        );

        Serial.println(" %");
    }
    else
    {
        Serial.println("INVALID");
    }

    Serial.print("Decision: ");
    Serial.println(
        actionName(decision.action)
    );

    Serial.print("Decided at: ");
    Serial.print(
        decision.decidedAtMs
    );

    Serial.println(" ms");

    Serial.println("------------------------");
}

void setup()
{
    Serial.begin(115200);
    delay(300);

    Serial.println();
    Serial.println(
        "KSJ_Control Basic_Range_Control"
    );

    Serial.println(
        "Turn on below: 75%"
    );

    Serial.println(
        "Turn off above: 82%"
    );

    previousStepMs =
        millis() - Timing::STEP_INTERVAL_MS;
}

void loop()
{
    const uint32_t nowMs =
        millis();

    if (
        nowMs - previousStepMs <
        Timing::STEP_INTERVAL_MS
    )
    {
        return;
    }

    previousStepMs = nowMs;

    const float simulatedHumidity =
        simulatedHumidityValues[
            currentValueIndex
        ];

    const KSJ::ControlDecision decision =
        humidityController.update(
            simulatedHumidity,
            nowMs
        );

    printDecision(decision);

    currentValueIndex =
        (currentValueIndex + 1) %
        VALUE_COUNT;
}