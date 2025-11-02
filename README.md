# Self-Balancing-Bot using Arudino and MPU 6050 gyroscope



A two-wheeled robot that maintains balance autonomously using PID control and sensor feedback.
### Features
  - Real time angle measurement using MPU6050 IMU

  - PID control loop for stabilization

  - Continuous rotation servo motor control

  - Adjustable PID gains for performance tuning
 
### Hardware Use
  - Used an Arudino UNO for the mcrocontroller for the bot.
  - MPU6050 gyroscope sensor for measuring the angle tilt of the bot.
  - 2 continous Servo Motors.
  - 3d printed chasis.
  - Battery pack.
    
### How It Works

  - Sensor Data
    - The MPU 6050 gyroscope sensor continuously measures the bot's tilt angle.
    - This angle data gets filtered via the Kalman Filter, which combines gyroscope and accelerometer measurements to provide a more accurate and stable estimate of the actual angle.
    - Put pic here
      
  - Proportional Integral Derivative (PID) control algorithm
    - The PID algorithm calculates the error between the upright position (0 deg) and the current tilt angle.
    - PID controller computes corrective output.
    - Outputs motor speed required to achieve balance.
      
  - Actuation
    - The Arduino sends PWM signals to both servo motors to compensate for tilt in real-time.



### Robot Setup Images
<!--![](img/SelfBlancing%20Bot%20pic1.jpg) -->
### Results / Outcomes
### How to run for yourself






