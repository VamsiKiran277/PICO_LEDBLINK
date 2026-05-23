# PICO_LEDBLINK

A bare-metal C and ARM Assembly implementation to blink the onboard LED (GPIO 25) on the Raspberry Pi Pico (RP2040 microcontroller). This project bypasses the standard Raspberry Pi Pico SDK, interacting directly with the hardware registers for educational, low-level system understanding.

---

##  Project Structure

Based on the project configuration, the environment utilizes a modular structure typical of ARM Keil/embedded toolchains:

* **`main.c`**: Contains the core logic, memory-mapped register definitions, peripheral initialization, and the main blinking loop.
* **`startup.s`**: The assembly startup file containing the vector table (`__Vectors`), stack allocation, and the `Reset_Handler` that branches directly to our C entry point.
* **`Blink_led.uf2`**: The final compiled binary ready to be flashed onto the Raspberry Pi Pico.
* **`Listings/` & `Objects/`**: Toolchain build artifacts (compiler outputs, maps, object files).

---

##  Technical Overview & Memory Mapping

The code targets specific peripheral registers within the RP2040 address space to take control of GPIO 25:

### 1. Subsystem Reset Controller (`RESETS_BASE`: `0x4000C000`)
Before using `IO_BANK0`, it must be taken out of reset state.
* De-asserts bit 5 of `RESET_RESET` to bring `IO_BANK0` alive.
* Polls bit 5 of `RESET_DONE` to verify the peripheral clock and hardware stabilizes.

### 2. GPIO Function Selection (`IO_BANK0_BASE`: `0x40014000`)
* Configures `GPIO25_CTRL` with the function value `5`, routing control of the physical pin to the **Single-cycle IO (SIO)** block.

### 3. SIO Direction and Toggling (`SIO_BASE`: `0xd0000000`)
* **`SIO_GPIO_OE_SET`**: Configures GPIO 25 as an Output pin using `LED_MASK` ($1 \text{U} \ll 25$).
* **`SIO_GPIO_XOR`**: Atomically toggles the state of the pin inside an infinite loop, avoiding standard read-modify-write performance penalties.

---

##  How to Run It on Your Pico

### 1. Build the Project
Open the project file (`Blink_led.uvprojx`) in your IDE/Toolchain and compile the source files (`main.c` and `startup.s`) to generate the target binary.

### 2. Boot the Pico in Storage Mode
1. Connect your Raspberry Pi Pico to your computer using a Micro-USB cable while holding down the white **BOOTSEL** button.
2. Release the button once the Pico mounts on your operating system as a mass storage device named `RPI-RP2`.

### 3. Flash the Binary
Locate the compiled **`Blink_led.uf2`** file in your local workspace and drag-and-drop (or copy) it directly onto the `RPI-RP2` drive. 

The Pico will automatically unmount itself, reboot, and execute the firmware. The green onboard LED will begin flashing.

---

##  License
This project is open-source and intended for bare-metal ARM Cortex-M0+ educational exploration. Feel free to modify and build upon it!
