# Applicable Rules (FHE 2027)

- **EV2.10 Precharge:** the tractive system must precharge to at least 90% of pack voltage, confirmed by measured voltage. Time-based precharge is not allowed.
    - Satisfied by: [REQ_SS1_001 - REQ_SS1_004](requirements.md#system-state-1), [REQ_SS2_001](requirements.md#system-state-2)
    - Note: Pac-Man measures the voltage and decides when 90% is reached. The TSMCU only requests precharge, times out, and waits for Pac-Man's "precharge done" report.

- **EV3.5 Accelerator signal:** an analog pedal signal must detect an open circuit, a short to ground, and a short to sensor power. A digital or CAN signal must detect loss of communication. The motors must spin freely when the tractive system is shut down.
    - Satisfied by: [REQ_SS3_003](requirements.md#system-state-3), [REQ_SS3_005](requirements.md#system-state-3) (pedal disagreement); [REQ_SS1_005](requirements.md#system-state-1), [REQ_SS2_005](requirements.md#system-state-2), [REQ_SS3_006](requirements.md#system-state-3) (zero torque and inverter disabled on shutdown, so the motors spin freely)
    - Gap: no requirement for an out-of-range pedal signal (open circuit, short to ground, short to sensor power).
    - Gap: no requirement for what happens when a board's CAN messages stop. [REQ_TASK_002](requirements.md#task-definitions) records when each board was last heard from, but nothing acts on it.

- **EV7.1 Shutdown circuit:**
  - No programmable logic or microcontrollers in the shutdown loop (EV7.1.3).
  - Battery management system and insulation monitoring device faults latch and need a manual reset.
  - If CAN carries a safety function, an independent CAN watchdog must open the shutdown loop when the relevant messages stop.
    - Satisfied by: hardware (the shutdown loop, the fault latches and the reset button). The TSMCU is not in the loop.
    - Supports: [REQ_SYS_001](requirements.md#system-requirements) (heartbeat), if the team adds a CAN watchdog.
    - Gap: no requirement that the firmware never clears or resets battery management system or insulation monitoring faults.

- **EV7.5, EV7.6 Shutdown buttons:** three big red buttons (one on each side, one in the cockpit) open the shutdown loop.
    - Satisfied by: hardware. The side buttons cut the TSMCU's power, so it restarts in state 0 ([REQ_BOOT_006](requirements.md#boot-sequence)).
    - Gap: the cockpit button opens the main contactors without cutting the TSMCU's power. No requirement yet says "Pac-Man reports the main contactors open → return to state 0".

- **EV7.7 Start action:** reaching ready to drive takes a driver action, and that action can't be left "on" after a shutdown.
    - Satisfied by: [REQ_SS2_003](requirements.md#system-state-2), [REQ_SS3_001](requirements.md#system-state-3) (acts only on the press itself), [REQ_BOOT_006](requirements.md#boot-sequence) (always starts in state 0)

- **EV7.8 State machine:** the car must follow Figure 41, or an alternative approved by the Electrical System Form (ESF) deadline.
    - Satisfied by: [REQ_BOOT_006](requirements.md#boot-sequence), [System state 0](requirements.md#system-state-0) through [System state 3](requirements.md#system-state-3), including [REQ_SS3_004](requirements.md#system-state-3) (state 3 back to state 2)

- **EV9.3 Lamp check:** the indicators turn on together within 1 second of the low-voltage master switch turning on, stay on for 2–3 seconds, then return to normal. Software may only add to this, never block it.
    - Satisfied by: [REQ_BOOT_008](requirements.md#boot-sequence)
    - Conflict: [REQ_SS2_004](requirements.md#system-state-2) runs a lamp check after the start press, for under 2 seconds. The rule only asks for one at power-up, for 2–3 seconds, so REQ_SS2_004 should be deleted.

- **EV9.4 Ready-to-drive sound:** 1–3 seconds, 1000–3500 Hz, at least 80 dBA, with no similar sound at any other time.
    - Satisfied by: [REQ_SS3_002](requirements.md#system-state-3), with [REQ_BOOT_001](requirements.md#boot-sequence) holding the buzzer low at power-up

- **IC1.6.4 Accelerator failures:** any single failure in the pedal system must result in zero torque.
    - Satisfied by: [REQ_SS3_003](requirements.md#system-state-3), [REQ_SS3_005](requirements.md#system-state-3), [REQ_SS1_005](requirements.md#system-state-1), [REQ_SS2_005](requirements.md#system-state-2), [REQ_SS3_006](requirements.md#system-state-3)
    - Gap: same as EV3.5. A single broken or shorted pedal wire needs the out-of-range check.