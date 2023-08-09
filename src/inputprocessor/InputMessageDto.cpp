#include "InputMessageDto.h"

InputMessageDto::InputMessageDto(char *rawInputData, unsigned long millisSinceBirth)
    : rawInputData(rawInputData), millisSinceBirth(millisSinceBirth) {}

InputMessageDto::~InputMessageDto() {
  delete rawInputData;
  rawInputData = nullptr;
}

char *InputMessageDto::getRawInputData() { return rawInputData; }

bool InputMessageDto::isValid() const { return itemValid && (millis() - millisSinceBirth < LIFE_SPAN); }

void InputMessageDto::setValid(bool validity) { itemValid = validity; }