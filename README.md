# Login_system_to_control_temperature_and_lights
A system based on Atmega32 microcontroller used to control temperature and lights using analog sensors (LM35 and LDR sensors)
## System Description
This system provides two main applications
- **First:**Controlling the PWM of a FAN based on the reading we get from the LM35 sensor.
- **Second:** Controlling room lights based on the reading we get from thr LDR sensor.
## System Components
1. Atmega32 AVR microcontroller with the usage of these SWC
   - DIO
   - ADC to get the reading from LDR and LM35 Sensors.
   - EXTI0 to control getting back to the main menu.
   - TIMER0 to control PWM of the DC motor.
2. LCD LMB161A 
3. Keypad consists of 16 tactile switches
4. 2 tactile switches to control EXTI0, EXTI2 interrupts
5. USBASP burner
## Project Pictures
![20230219_194124](https://user-images.githubusercontent.com/94296738/224461447-9a10adc5-7ed5-4c52-ba81-1e959e2ff7e3.jpg)
![20230219_194545](https://user-images.githubusercontent.com/94296738/224461465-595bbc3e-6e89-4ad8-8327-0864f417350e.jpg)

## Operation Video
