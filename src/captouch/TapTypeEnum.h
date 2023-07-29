//
// Created by Igor Voronin on 29.07.23.
//

#ifndef DIALER_TAPTYPEENUM_H
#define DIALER_TAPTYPEENUM_H

class TapTypeEnum {
public:
    TapTypeEnum() : threshold(INVALID) {}

    explicit TapTypeEnum(int threshold);

    void setThreshold(int newThreshold);

    [[nodiscard]] int getThreshold() const;

    [[nodiscard]] bool isValid() const;

private:
    static constexpr const auto INVALID = -1;

    int threshold;
};

#endif //DIALER_TAPTYPEENUM_H
