#include <Wire.h>
int INS = 0x68; // MPU6050 I2C address
int16_t Gyro_X, Gyro_Y, Gyro_Z;
float P, Q, R;

void setup() {
  Serial.begin(9600);
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(INS);       // Start communication with MPU6050 // INS=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0);                     // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        // End the transmission

}
void loop() {  
  
  // Write to INS Requesting Gyroscope Data
  Wire.beginTransmission(INS);
  Wire.write(0x43); // 
  Wire.endTransmission();
  Wire.requestFrom(INS, 6, true); 

  // Read Gyroscope Data and Convert to Physical Units (DPS)
  Gyro_X= (Wire.read() << 8 | Wire.read());
  Gyro_Y = (Wire.read() << 8 | Wire.read());
  Gyro_Z = (Wire.read() << 8 | Wire.read());

  Q=Gyro_X/131.0;
  P=Gyro_Y/131.0;
  R=Gyro_X/131.0;

  // Print the values on the serial monitor
  //Serial.print(P);
  //Serial.print("  ");
  Serial.println(Q);
  //Serial.println(R);

  delay(100);
}