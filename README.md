# Bare-Metal Programming on STM32 (Nucleo-64 STM32C031C6)

This repository contains a collection of **bare-metal embedded C projects** for the **STM32C031C6** microcontroller on a **Nucleo-64** development board. Each project is simulated and visualized using the **Wokwi** online simulator.

---

## 🔧 Repository Structure

Each project is organized into its own folder with the following contents:

- `sketch.ino` – Contains bare-metal C code (not Arduino functions) compiled via Wokwi.
- `diagram.json` – Defines the virtual hardware circuit used in Wokwi.
- `wokwi-project.txt` – URL to open the project simulation on [Wokwi](https://wokwi.com).

## 📁 Projects

| Project | Description |
|--------|-------------|------------------|
| `LED Blinky` | Basic GPIO output toggle using delay loop |
| `LED Blinky with button` | External interrupt on button press |
| `LED Blinky with EXTI` | UART transmission using bare-metal code |


## 📘 Documentation

Reference documents used for register-level programming and debugging:

- [✅ STM32C031C6 Reference Manual (RM0490)](https://www.st.com/resource/en/reference_manual/rm0490-stm32c0x1-advanced-armbased-64bit-mcus-stmicroelectronics.pdf)
- [✅ STM32C031C6 Datasheet](https://www.st.com/resource/en/datasheet/stm32c031c6.pdf)
- [✅ Nucleo-64 User Manual (UM)](https://www.st.com/resource/en/user_manual/um2953-stm32-nucleo64-board-mb1717-stmicroelectronics.pdf)
- [✅ STM32 Programming Manual (PM0215)](https://www.st.com/resource/en/programming_manual/pm0223-stm32-cortexm0-mcus-programming-manual-stmicroelectronics.pdf)
- [✅ Nucleo-64 Board Schematic](https://www.st.com/resource/en/schematic_pack/mb1717-c031c6-b02_schematic.pdf)


## 🚀 Tools Used

- **Wokwi** – Online simulator for microcontrollers: [https://wokwi.com](https://wokwi.com)
- **STM32C031C6** – Cortex-M0+ MCU used for bare-metal experiments
- **Register-level C** – No HAL/LL/Arduino libraries

## ⚙️ Getting Started

To simulate a project:

1. Open the `wokwi-project.txt` file in any project folder.
2. Paste the link into your browser.
3. Modify `sketch.ino` and `diagram.json` to experiment with code and circuit.
4. Click **Start Simulation**.

## 🧠 Goals of This Repository

- Master low-level peripheral control (GPIO, EXTI, UART, TIM, etc.)
- Understand ARM Cortex-M0+ architecture
- Practice debugging using register references
- Avoid abstraction layers (no HAL, no Arduino)