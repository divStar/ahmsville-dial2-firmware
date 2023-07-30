//
// Created by Igor Voronin on 26.06.23.
//

#ifndef DIALER_MACROKEYTASK_H
#define DIALER_MACROKEYTASK_H

#include "MacroKey.h"
#include "interfaces/ISchedulableDialTask.h"

class MacroKeyTask : public ISchedulableDialTask {
public:
    MacroKeyTask();

    void onSetup() override;

    void onCallback() override;

private:
    static MacroKey keys[];

    static void initializeKeys();
};


#endif //DIALER_MACROKEYTASK_H
