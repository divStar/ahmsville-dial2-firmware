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

    static bool isValidLedDataJson(JsonObject ledDataJson);
    StaticJsonDocument<128> filterDoc;
};


#endif //DIALER_READLEDTASK_H
