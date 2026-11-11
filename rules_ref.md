# Applicable Rules (FHE 2027)

- **EV2.10 Precharge:** the tractive system must precharge to at least 90% of pack voltage, confirmed by measured voltage. Time-based precharge is not allowed.
    - Satisfied by: [REQ_SS1_001 - REQ_SS1_004](requirements.md#system-state-1)

- **EV3.5 Accelerator signal:** an analog pedal signal must detect an open circuit, a short to ground, and a short to sensor power. A digital or CAN signal must detect loss of communication. The motors must spin freely when the tractive system is shut down.
- **EV7.1 Shutdown circuit:**
  - No programmable logic or microcontrollers in the shutdown loop (EV7.1.3).
  - Battery management system and insulation monitoring device faults latch and need a manual reset.
  - If CAN carries a safety function, an independent CAN watchdog must open the shutdown loop when the relevant messages stop.
- **EV7.5, EV7.6 Shutdown buttons:** three big red buttons (one on each side, one in the cockpit) open the shutdown loop.
- **EV7.7 Start action:** reaching ready to drive takes a driver action, and that action can't be left "on" after a shutdown.
- **EV7.8 State machine:** the car must follow Figure 41, or an alternative approved by the Electrical System Form (ESF) deadline.
- **EV9.3 Lamp check:** the indicators turn on together within 1 second of the low-voltage master switch turning on, stay on for 2–3 seconds, then return to normal. Software may only add to this, never block it.
- **EV9.4 Ready-to-drive sound:** 1–3 seconds, 1000–3500 Hz, at least 80 dBA, with no similar sound at any other time.
- **IC1.6.4 Accelerator failures:** any single failure in the pedal system must result in zero torque.