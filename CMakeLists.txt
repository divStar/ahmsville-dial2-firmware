# !!! WARNING !!! AUTO-GENERATED FILE, PLEASE DO NOT MODIFY IT AND USE
# https://docs.platformio.org/page/projectconf/section_env_build.html#build-flags
#
# If you need to override existing CMake configuration or add extra,
# please create `CMakeListsUser.txt` in the root of project.
# The `CMakeListsUser.txt` will not be overwritten by PlatformIO.

cmake_minimum_required(VERSION 3.13)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project("dialer" C CXX)

include(CMakeListsPrivate.txt)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeListsUser.txt)
include(CMakeListsUser.txt)
endif()

add_custom_target(
    Production ALL
    COMMAND platformio -c clion run "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    Debug ALL
    COMMAND platformio -c clion debug "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(Z_DUMMY_TARGET ${SRC_LIST} src/interfaces/ISerialPortUser.h src/interfaces/ISerialPort.h src/taskswitcher/TaskSwitcherTask.h src/interfaces/sensors/ICapacitiveSensorAdapter.h src/hardware-adapters/HardwareCapacitiveSensorAdapter.h src/interfaces/sensors/IHapticSensorAdapter.h src/hardware-adapters/HardwareHapticSensorAdapter.h src/interfaces/sensors/ISpaceNavigatorSensorAdapter.h src/hardware-adapters/HardwareSpaceNavigatorSensorAdapter.h src/interfaces/sensors/IRotaryEncoderAdapter.h src/hardware-adapters/HardwareMacroKeys.h src/interfaces/sensors/IMacroKeys.h)
