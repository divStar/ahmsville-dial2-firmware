//
// Created by Igor Voronin on 26.06.23.
//

#ifndef DIALER_WRITEMACROKEYTASK_H
#define DIALER_WRITEMACROKEYTASK_H
#include "macrokey/MacroKeyDevice.h"
#include "DialTask.h"

class WriteMacroKeyTask: public DialTask {
public:
    void onSetup() override;
    void onCallback() override;
};


#endif //DIALER_WRITEMACROKEYTASK_H
