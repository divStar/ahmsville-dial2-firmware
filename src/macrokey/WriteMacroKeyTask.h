//
// Created by Igor Voronin on 26.06.23.
//

#ifndef DIALER_WRITEMACROKEYTASK_H
#define DIALER_WRITEMACROKEYTASK_H

#include "MacroKey.h"
#include "interfaces/ISchedulableDialTask.h"

class WriteMacroKeyTask : public ISchedulableDialTask {
public:
    WriteMacroKeyTask();

    void onSetup() override;

    void onCallback() override;

private:
    static MacroKey keys[];

    static void initializeKeys();
};


#endif //DIALER_WRITEMACROKEYTASK_H
