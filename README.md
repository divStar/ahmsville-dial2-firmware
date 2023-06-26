# Dial2 firmware

This project is made using CLion and the PlatformIO plugin.

It currently is designed for the **AhmsVille Dial 2 Absolute Edition**.
It contains a program, that is supposed to be compiled and uploaded onto
the AhmsVille Dial 2 AE Arduino Zero via the Native USB Port.

## Notes
 - Ensure, that there is always a `delay(5000)` or more in the `setup()` method. If your implementation crashes, you will have 5 seconds to upload a new, e.g. empty application to recover.