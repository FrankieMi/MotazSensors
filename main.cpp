/************************************************
  Multisensor array using ESP-32
  Miltiple BME sensors used on different pins with switching 
  I2C bus pins for serail access
  
  Developed by Motaz Salama Mabrouk and Frantisek Miksik
  Kyushu University, IGSES, TESC Labor
  February 2023

***********************************************/


#include <Arduino.h>


//--------------------------------------------------------------------------------
// BME280 Sensor
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// -----------------------------------------------------------------------------
#define I2C_SDA_1 18
#define I2C_SCL_1 19

#define I2C_SDA_2 21
#define I2C_SCL_2 22

#define I2C_SDA_3 27
#define I2C_SCL_3 15

//We will initialize only one data bus for data handling
//we will be calling then each BME sensor in series, hence no need to compete between them
TwoWire I2CLine = TwoWire(0);
Adafruit_BME280 bme; // I2C

void BME_Begin(int sda, int scl){
  I2CLine.begin(sda, scl, 100000);
  bme.begin(0x76,&I2CLine);
  I2CLine.end(); //we need to release the line's lock
}

void setup () {

  Serial.begin(115200);
  delay(500);
  BME_Begin(I2C_SDA_1, I2C_SCL_1);
  delay(500);
  BME_Begin(I2C_SDA_2, I2C_SCL_2);
  delay(500);
  BME_Begin(I2C_SDA_3, I2C_SCL_3);
  delay(500);
}

// ------------------------------------------------------------------
// BME280
// this function will output the reading of the individual BME sensors.
// As the sensors have already been initialized, we should be able to read them just by swithing the I2C lines in the ESP-32
// Because the line itself stays the same, we should be able to achieve the same effect using the only one BUS reference
// When we swith the lines, different BME will be accessible even thou we are using the same global variable as reference
String BME_Data(String sensorNo, int sda, int scl){
    
    I2CLine.begin(sda, scl, 100000);
    delay(10); //the delay is just to make sure that the line is stable after initializing, it might be not necessary, you can try to remove it later
    String bme_str_data;
    float temp = bme.readTemperature();
    float hum = bme.readHumidity();
    float press = (bme.readPressure() / 100.0F);
    delay(10); //same as above
    bme_str_data = ",S" + sensorNo + "," + String( temp ) + "," + String( hum ) + "," + String( press );
    I2CLine.end(); //we need to release the line's lock
    return bme_str_data;
}


void loop () {
  delay(3000);
  Serial.print(BME_Data("1", I2C_SDA_1, I2C_SCL_1));
  Serial.print(BME_Data("2", I2C_SDA_2, I2C_SCL_2));
  Serial.println(BME_Data("3", I2C_SDA_3, I2C_SCL_3));
}
