/*Self balancing robot code
Arnav Kute
*/
#include <Wire.h>
#include <Servo.h>
#include <MPU6050_light.h>

// Create MPU6050 and Servo objects
MPU6050 mpu(Wire);
Servo leftMotor;
Servo rightMotor;

// PID constants for balance control
float setPoint = 0;  // Desired angle (upright position)
float Kp = 21;       // Proportional gain
float Ki = 0.75;     // Integral gain
float Kd = 0.45;     // Derivative gain

// Variables for PID calculation
float error, previousError = 0;
float pid, p, i, d;
unsigned long previousTime;
float angle;
float filteredAngle = 0;
unsigned long currentTime;
float elapsedTime;

// Motor speed variables
int baseSpeed;
int leftSpeed;
int rightSpeed;

void setup() {
  Serial.begin(9600);  // Start serial communication
  Wire.begin();        // Initialize I2C communication

  // Initialize MPU6050 sensor
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) {}  // Stop program if sensor initialization fails

  // Calibrate MPU6050 sensor
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets();  // Gyro and accel calibration
  Serial.println("Done!\n");

  // Attach continuous rotation servos to pins
  leftMotor.attach(3);
  rightMotor.attach(11);

  previousTime = millis();  // Record initial time
}

void loop() {
  mpu.update();  // Update MPU6050 sensor data

  // Get raw Y-axis angle (forward/backward tilt)
  float rawAngle = mpu.getAngleY();

  // Apply low-pass filter to reduce noise
  float alpha = 0.95;
  filteredAngle = alpha * filteredAngle + (1 - alpha) * rawAngle;
  angle = filteredAngle;

  // Calculate time since last loop
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000.0;
  if (elapsedTime == 0) elapsedTime = 0.001;

  // PID calculations
  error = angle - setPoint;  // Calculate difference from upright
  p = error;                 // Proportional term
  i += error * elapsedTime;  // Integral term

  // Limit integral to avoid windup
  float iLimit = 100;
  i = constrain(i, -iLimit, iLimit);

  d = (error - previousError) / elapsedTime;  // Derivative term

  // Calculate PID output
  pid = Kp * p + Ki * i + Kd * d;

  previousError = error;
  previousTime = currentTime;

  // Set motor speeds using PID
  baseSpeed = 90;                // 90 is "stop" for continuous rotation servos
  leftSpeed = baseSpeed + pid;   // Adjust left motor
  rightSpeed = baseSpeed - pid;  // Adjust right motor

  // Limit motor speeds to servo range
  leftSpeed = constrain(leftSpeed, 0, 180);
  rightSpeed = constrain(rightSpeed, 0, 180);

  // Drive the motors
  leftMotor.write(leftSpeed);
  rightMotor.write(rightSpeed);

  // Print debug info
  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print(" | PID: ");
  Serial.println(pid);

  delay(5);  // Short delay to allow smooth control
}
