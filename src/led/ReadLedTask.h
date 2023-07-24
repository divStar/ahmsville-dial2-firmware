//
// Created by Igor Voronin on 18.06.23.
//

#ifndef DIALER_READLEDTASK_H
#define DIALER_READLEDTASK_H

#include "Vector.h"
#include "ArduinoJson.h"
#include "DialTask.h"
#include "LedDataDto.h"

class ReadLedTask : public DialTask {
public:
    explicit ReadLedTask(Vector<LedDataDto*>* dataToProcess);

    void onCallback() override;

    Vector<LedDataDto*>* dataToProcess;
private:
    static const int BUFFER_SIZE = 2048;

    StaticJsonDocument<128> filterDoc; // this JSON describes what to filter for
    static bool isValidLedDataJson(JsonObject ledDataJson);
};


#endif //DIALER_READLEDTASK_H
