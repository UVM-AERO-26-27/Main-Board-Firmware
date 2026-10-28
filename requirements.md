# Firmware Requirements Specification

## Boot Sequence
This section defines the behaviors which must happen at boot

* `REQ_BOOT_001`: Upon recieving power, the TSCMU shall drive dangerous outputs (VICOR_EN, RTD_BUZZER, PRECHARGE, MAIN_CONTACT) low as first action of startup
* `REQ_BOOT_002`: the TSCMU shall configure all other pins (except CAN TX/RX) to be used
* `REQ_BOOT_003`: The MCU shall initialize the TWAI "Two wire automotive interface" (CAN) driver.
* `REQ_BOOT_004`: The CAN/TWAI driver shall be initialized with fixed baud rate of TBD
* `REQ_BOOT_005`: If the TWAI controller driver fails to allocate or start, the system shall keep outputs safe, the car shall remain in State 0, and the fault is shown TBD
* `REQ_BOOT_006`: The system state shall be initialized to kTractiveSystemOff (state 0)
* `REQ_BOOT_007`: The tasks shall be created from their functions for the program to run


## Task Definitions
This sections outlines the tasks to be created which will be used by the MCU in the main loop

* `REQ_TASK_001`: Task 1 shall send a check and recieve a response from all other boards on CAN shall check any fault signals recieved from Vicor and BMS/IMD fault pins
* `REQ_TASK_002`: Task 2 shall be control (highest priority, fixed rate, every 10 ms TBD): runs the state machine, works out torque, and sends the command to the DTI.
* `REQ_TASK_003`: Task 3 shall be CAN receive (high priority): waits for incoming messages and stores the latest values from the BMS, DTI and Pac-Man and when they were last heard from.
* `REQ_TASK_004`: Task 4 shall be I/O (lower priority): reads the buttons and brake pressure, and drives the buzzer, fans, pumps and lights.
* `REQ_TASK_005`: Task 5 shall be supervisor (lowest priority): resets the external watchdog, but only after every other task has checked in.

## System state 0
This section outlines the state 0 behaviors of the system state machine.

* `REQ_SS0_001`: State 0 shall consider startup conditions met when every required board heard from within X ms (TBD), fault lines inactive, and the shutdown loop closed (TBD)
* `REQ_SS0_002`: The system state shall not leave state 0 unless Task 1 and 2 and fulfilled entirely

TODO: Seperate out CAN TX AND RXX into their own tasks