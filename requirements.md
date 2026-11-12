# Firmware Requirements Specification

## System Requirements
This represents the system wide functions that need to happen at any given state

* `REQ_SYS_001`: In any given state, the TSMCU shall send a CAN heartbeat message out on the bus.


## Boot Sequence
This section defines the behaviors which must happen at boot

* `REQ_BOOT_001`: Upon receiving power, the TSMCU shall drive dangerous outputs (VICOR_EN, RTD_BUZZER, PRECHARGE, MAIN_CONTACT) low as first action of startup
* `REQ_BOOT_002`: the TSMCU shall configure all other pins (except CAN TX/RX) to be used
* `REQ_BOOT_003`: The MCU shall initialize the TWAI "Two wire automotive interface" (CAN) driver.
* `REQ_BOOT_004`: The CAN/TWAI driver shall be initialized with fixed baud rate of 500kbit/s
* `REQ_BOOT_005`: If the TWAI controller driver fails to allocate or start, the system shall keep outputs safe, the car shall remain in State 0, and the fault is shown TBD
* `REQ_BOOT_006`: The system state shall be initialized to kTractiveSystemOff (state 0)
* `REQ_BOOT_007`: The tasks shall be created from their functions for the program to run
* `REQ_BOOT_008` : All listed warning lights shall all turn on together within 1 second of power-up, stay on for 2–3 seconds, then turns off. Mark who drives it as TBD. Shall not be blocking


## Task Definitions
This sections outlines the tasks to be created which will be used by the MCU in the main loop

* `REQ_TASK_001`: Control Task (highest priority, fixed rate, every 10 ms TBD): runs the state machine, works out torque, and sends the command to the DTI.
* `REQ_TASK_002`: CAN Receive Task (high priority): waits for incoming messages and stores the latest values from the BMS, DTI and Pac-Man and when they were last heard from.
* `REQ_TASK_003`: I/O Task (lower priority): reads the buttons and brake pressure, and drives the buzzer, fans, pumps and lights.
* `REQ_TASK_004`: Supervisor Task (lowest priority): resets the external watchdog, but only after every other task has checked in.


## System state 0
This section outlines the state 0 behaviors of the system state machine. **MCU checking and fault checking**

* `REQ_SS0_001`: State 0 shall consider startup conditions met when every required board heard from within X ms (TBD), fault lines inactive, and the shutdown loop closed (TBD)
* `REQ_SS0_002`: The system state shall not leave state 0 until there are no faults and each board has been heard from.

## System state 1
This section outlines the state 1 behaviors of the system state machine. **Precharge sequence control**

* `REQ_SS1_001`: State 1 shall not send a CAN to Pac-Man unless no faults are active, and all boards have been heard from.
* `REQ_SS1_002`: State 1 shall send a CAN command to the Pac-Man to initiate the precharge sequence and start a running timer.
* `REQ_SS1_003`: State 1 shall immediately terminate action if the timer exceeds limit of TBD
* `REQ_SS1_004`: Should the timer exceed the limit, state 1 shall return to state 0 immediately
* `REQ_SS1_005`: The state machine shall return to state 0 if any fault arises send zero torque and disable inverter 


## System state 2
This section outlines the state 2 behaviors of the system state machine. **Process enabling inverter**
* `REQ_SS2_001`: The TSMCU shall not send a CAN command to enable inverter until Pac-Man reports that precharge is done.
* `REQ_SS2_002`: The Vicor Enable wire shall be set to VICOR_EN (HIGH)
* `REQ_SS2_003`: Start button shall be ready to send a enable command to the inverter once the precharge is successful
* `REQ_SS2_004`: Within less than 1 second of pressing start, a lamp check shall be preformed for less than 2 seconds
* `REQ_SS2_005`: The state machine shall return to state 0 if any fault arises send zero torque and disable inverter

## System state 3
This section outlines the state 3 behaviors of the system state machine. **Ready to drive**

* `REQ_SS3_001`: Upon the start button being pressed, it shall act only on the moment the button is pressed (edge detection) and a CAN command will send to enable the inverter.
* `REQ_SS3_002`: When the inverter is enabled there must be a HIGH sent to the Ready-to-Drive buzzer for 1 to 3 seconds, at 1000 to 3500 Hz and at least 80 dBA, and no similar sound at any other time
* `REQ_SS3_003`: While the inverter is enabled, to send a torque command, pedal 0/1 shall agree within TBD to send a torque command on CAN
* `REQ_SS3_004`: While in state 3, if the start button is pressed, the system shall return to state 2.
* `REQ_SS3_005`: If the two pedal sensors disagree, the TSMCU shall command zero torque to the inverter
* `REQ_SS3_006`: The state machine shall return to state 0 if any fault arises send zero torque and disable inverter









