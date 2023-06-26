//
// Created by Igor Voronin on 18.06.23.
//

#ifndef DIALER_DIALTASK_H
#define DIALER_DIALTASK_H
class DialTask {
public:
    virtual void onSetup() {};
    virtual void onCallback() = 0;
};

#endif //DIALER_DIALTASK_H
