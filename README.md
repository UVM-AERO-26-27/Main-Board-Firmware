## Dev Environments

- Multiple environments ultized through PlatformIO. This allows for Testing Firmware Locally on your computer.
- This increases the number and speed of tests and allows for hardware-agnostic logic testing.

### Available Profiles
1. **`esp32s3` (Default)**: Compiles the production firmware for the physical vehicle control unit. Configured for the ESP32-S3-DevKitC-1U-N8R8 PSRAM enabled.
2. **`native`**: Compiles the state machine logic natively for a laptop's processor. Used to run the test suite.

### How to switch between the environments
1. Ensure PlatformIO is installed
2. View the status bar at the bottom of VSCode window
3. Click on the text label that says `env:esp32s3` or `Default (esp32s3)`. If unavailable, restart VSCode.
4. Select your target profile from the dropdown menu at the top of the screen.