//
// Created by Igor Voronin on 03.07.23.
//

#ifndef MACROKEYDEVICE_H
#define MACROKEYDEVICE_H

#include "MacroKey.h"

class MacroKeyDevice {
public:
    static void init();
private:
    static MacroKey keys[];
};


#endif //MACROKEYDEVICE_H
