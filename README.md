# PATHWAY
> 2WD Web-Controlled Robot

A simple 2-wheel-drive robot powered by an **ESP8266 (NodeMCU)** that can be controlled directly from a **web browser**.  
The project hosts a built-in web server with on-screen control buttons and sends movement commands to the motors using standard HTTP requests.

---

## Project Photo
![2WD Image](https://github.com/user-attachments/assets/d10a21ea-15fb-414a-815a-45fcec2fc3c4)

## Features
- Control robot from any browser (PC / phone)
- Press and hold buttons for real-time control  
- Simple HTML + JavaScript web UI  
- Uses basic HTTP requests (no external libraries needed)  
- Easy to modify and extend  

---

## Hardware Overview
- **MCU:** ESP8266 (NodeMCU)
- **Motor Driver:** L293D or TB6612FNG  
- **Motors:** 2× DC gear motors  
- **Power:** 2S Li-ion or 12V DC  
- **Connections:**  
  - IN1 → D5 (GPIO14)  
  - IN2 → D6 (GPIO12)  
  - IN3 → D7 (GPIO13)  
  - IN4 → D8 (GPIO15)  
  - ENA / ENB → Tied HIGH (always enabled)  

---

## Wiring Diagram


## How It Works
1. The ESP8266 connects to your Wi-Fi network using SSID and password.  
2. It hosts a simple webpage with direction buttons.  
3. When a button is pressed, the browser sends a request like `/move?dir=forward`.  
4. The ESP8266 sets motor pins accordingly (HIGH/LOW) to move the robot.  
5. Releasing the button sends `/move?dir=stop`, halting the motors.

---

## Getting Started
1. Update your Wi-Fi credentials in the code.  
2. Wire up the motor driver and power the board.
3.  Flash the sketch to your ESP8266.
4. Open the Serial Monitor to get your robot’s IP address.  
5. Visit that IP in a browser (e.g., `http://192.x.x.x`) and drive.

## Contribute
Want to improve this project? Contributions are welcome!

1. Fork this repository  
2. Edit the code or docs  
3. Submit a Pull Request  

## License
This project is open-source under the **MIT License**.  
Feel free to use, modify, and build upon it.
