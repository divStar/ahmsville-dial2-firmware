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
    const float PROCESS_NOISE_COVARIANCE = 0.02;
    const float MEASUREMENT_NOISE_COVARIANCE = 9.0;
    const float INITIAL_ESTIMATION_ERROR_COVARIANCE = 1.0;
    const float INITIAL_KALMAN_GAIN = 0.0;

    float processNoiseCovariance;
    float measureMentNoiseCovariance;
    float estimatedValue;
    float estimationErrorCovariance;
    float kalmanGain;
};


#endif //DIALER_KALMANFILTER_H
