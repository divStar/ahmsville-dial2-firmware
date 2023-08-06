#include "HardwareHapticSensorAdapter.h"

HardwareHapticSensorAdapter::HardwareHapticSensorAdapter(byte hapticPin) : hapticPin(hapticPin) {}

void HardwareHapticSensorAdapter::writeStrength(byte strength) {
    analogWrite(hapticPin, strength);
}
