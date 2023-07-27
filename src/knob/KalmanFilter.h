//
// Created by Igor Voronin on 24.07.23.
//

#ifndef DIALER_KALMANFILTER_H
#define DIALER_KALMANFILTER_H

class KalmanFilter {
public:
    explicit KalmanFilter(float initialGuess);

    float update(float measurement);

private:
    constexpr static const float PROCESS_NOISE_COVARIANCE = 0.02;
    constexpr static const float MEASUREMENT_NOISE_COVARIANCE = 9.0;
    constexpr static const float INITIAL_ESTIMATION_ERROR_COVARIANCE = 1.0;
    constexpr static const float INITIAL_KALMAN_GAIN = 0.0f;

    float processNoiseCovariance;
    float measureMentNoiseCovariance;
    float estimatedValue;
    float estimationErrorCovariance;
    float kalmanGain;
};


#endif //DIALER_KALMANFILTER_H
