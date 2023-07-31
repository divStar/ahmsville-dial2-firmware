This library is derived from https://github.com/ElectronicCats/mpu6050/.

In addition I merged the abomination that is `MPU6050_6Axis_MotionApps20.h` into `MPU6050.cpp` and added the corresponding flag wherever necessary (`#define MPU6050_INCLUDE_DMP_MOTIONAPPS20`).

The downside of using this library is, that it doesn't get proper updates - you have to do them manually. Updates for it are rare though.