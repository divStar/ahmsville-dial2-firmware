#include "HardwareCapacitiveSensorAdapter.h"

HardwareCapacitiveSensorAdapter::HardwareCapacitiveSensorAdapter(uint8_t sendingPin, uint8_t receivingPin)
        : sensor(CapacitiveSensor(sendingPin, receivingPin)) {
}

void HardwareCapacitiveSensorAdapter::set_CS_AutocaL_Millis(unsigned long millis) {
    return sensor.set_CS_AutocaL_Millis(millis);
}

long HardwareCapacitiveSensorAdapter::capacitiveSensor(uint8_t samples) {
    return sensor.capacitiveSensor(samples);
}
