# AhmsVille Dial 2 Firmware

## Concept
This firmware is driven by a cooperative task scheduler (https://github.com/arkhipenko/TaskScheduler).
`delay` statements are omitted as much as possible in favor of the scheduling of tasks.

Each task takes care of a particular workload either related to the device as a whole or a particular
sensor.

Furthermore, tasks are kept hardware-agnostic. Abstract classes / interfaces are used to encapsulate the
functionality of actual hardware. This is done in order to make the code testable.

In the end the value change of each sensor is written as often as defined to the Serial port for e.g.
an userspace driver to consume.

## Thanks
This piece of software was only possible due to incredible work from Ahmed Oyenuga as well as all the
respective developers of the open-source libraries.

## `setup()` function
In this function the device is configured and calibrated as needed.

Each `DialTask` has an `onSetup()` function, which is executed during the device set up and ensures, that
this task is ready to run its `onCallback()` function when `scheduler.execute()` is run (in the `loop()`
function of the `main` script).

## `loop()` function
In this function only `scheduler.execute()` is run, because the task scheduler keeps track of which task
gets assigned processing cycles next. Even though there can be "high priority" tasks, these are **not** used.

Whenever a particular task is scheduled to run, its `onCallback()` function is called.

## interrupting functions
A couple of sensors interrupt the program whenever a value change (rise, fall, change etc.) is determined.
For example each `MacroKey` interrupts the program and writes its value change to the Serial port.

This project is made using CLion and the PlatformIO plugin.

It currently is designed for the **AhmsVille Dial 2 Absolute Edition**.
It contains a program, that is supposed to be compiled and uploaded onto
the AhmsVille Dial 2 AE Arduino Zero via the Native USB Port.

## Serial port input
Some tasks handle user-input. `InputProcessorTask` parses messages from the Serial port and each individual
task handles its own messages.

Invalid messages are cleared by the `MessagesCleanerTask` after they become invalid (which is after some
milliseconds or if a task set the validity to false).

The currently valid input format is JSON. See individual tasks for the JSON structure.

## Serial port output
Some tasks output their sensor values to the Serial port. The output is in JSON.

Tasks output their values and the time (`millis()`) when they occurred.

Furthermore, tasks can also output error statements in JSON, usually describing any of the possibly anticipated
error messages. These can easily be processed by a userspace driver.

## Notes
 - This documentation is always subject to change as implementation progresses.
 - Ensure, that there is always a `delay(5000)` or more in the `setup()` function. 
If your implementation crashes, you will have 5 seconds to upload a new, e.g. empty application to recover.