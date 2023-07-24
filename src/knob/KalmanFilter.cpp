//
// Created by Igor Voronin on 24.07.23.
//

#include "KalmanFilter.h"

KalmanFilter::KalmanFilter(float initialGuess)
        : processNoiseCovariance(PROCESS_NOISE_COVARIANCE),
          measureMentNoiseCovariance(MEASUREMENT_NOISE_COVARIANCE),
          estimatedValue(initialGuess),
          estimationErrorCovariance(INITIAL_ESTIMATION_ERROR_COVARIANCE),
          kalmanGain(INITIAL_KALMAN_GAIN) {}

float KalmanFilter::update(float measurement) {
    // prediction update
    estimationErrorCovariance = estimationErrorCovariance + processNoiseCovariance;

    // measurement update
    kalmanGain = estimationErrorCovariance / (estimationErrorCovariance + measureMentNoiseCovariance);
    estimatedValue = estimatedValue + kalmanGain * (measurement - estimatedValue);
    estimationErrorCovariance = (1 - kalmanGain) * estimationErrorCovariance;

    return estimatedValue;
}
