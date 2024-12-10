//Follow us on other social media

//https://www.youtube.com/c/ZinTechIdeas
//https://www.facebook.com/zin.techideas.3
//https://www.instagram.com/zintechideas/
//https://twitter.com/Zintechideas
//https://zintechideas.ir/
#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>   

Servo sg90;          
int servo_pin = 2;
MPU6050 sensor ;


int16_t ax, ay, az ;
int16_t gx, gy, gz ;

int maxServo = 145;
int flatServo = 103;
int minServo = 65;
float value = flatServo;

void setup(){ 

  sg90.attach( servo_pin );

  Wire.begin( );
  Serial.begin(9600); 
  Serial.println( "Initializing the sensor" ); 
  sensor.initialize( ); 
  Serial.println(sensor.testConnection ( ) ? "Successfully Connected" : "Connection failed"); 
  delay(1000); 
  Serial.println( "Taking Values from the sensor" );
  delay(1000);

}

void loop ( ){ 

  float invertedAx, nextValue;

  sensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  ax = map(ax, -17000, 17000, 0, 180); // curren accelerometer value

  invertedAx=200-ax; // inverted accelerometer value

  value+=(invertedAx-value)/20.0f; // formula to calculate the smoothed value

  if (value >= maxServo) { // to prevent servo from burning out
    value = maxServo;
  } else if (value < minServo) { // to prevent servo from burning out
    value = minServo; 
  }

  sg90.write(value); 

  Serial.print("ax\t");
  Serial.println(ax);

  Serial.print("value\t");
  Serial.println(value);

  delay(100);
}
