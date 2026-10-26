#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

/**
 * @file state_machine.h
 * @brief Tractive system startup sequence (rulebook EV7.8, Figure 41)
 */

#include <cstdint>

/**
 * @enum SystemState
 * @brief Represents the different states of the system.
 * 
 * The states include:
 * State = 0 - kTractiveSystemOff: The system is checking for faults and Ensuring responses from each board.
 * State = 1 - kPrecharge: The system is precharging and ensuring that the system is ready to drive. Timeout on precharge triggers state reset.
 * State = 2 - kReadyToDrive: The system closes main contactors and enables the inverter. The system is ready to drive and waits for driver input. 
 * State = 3 - kDrive: The system is in drive mode and the driver can control the vehicle.
 */
enum class SystemState : uint8_t {
    kTractiveSystemOff = 0,
    kPrecharge = 1,
    kReadyToDrive = 2,
    kDrive = 3
};

#endif // STATE_MACHINE_H
