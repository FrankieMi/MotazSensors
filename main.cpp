#include <Arduino.h>


//--------------------------------------------------------------------------------
// BME280 Sensor
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// -----------------------------------------------------------------------------
#define I2C_SDA 18
#define I2C_SCL 19

#define I2C_SDA_2 21
#define I2C_SCL_2 22

#define I2C_SDA_3 27
#define I2C_SCL_3 15

TwoWire I2CLine_1= TwoWire(0);
Adafruit_BME280 bme; // I2C

TwoWire I2CLine_2= TwoWire(1);
Adafruit_BME280 bme_2; // I2C

TwoWire I2CLine_3= TwoWire(2);
Adafruit_BME280 bme_3; // I2C

void setup () {

  Serial.begin(115200);
  I2CLine_1.begin(I2C_SDA, I2C_SCL, 100000);
  I2CLine_2.begin(I2C_SDA_2, I2C_SCL_2, 100000);
  I2CLine_3.begin(I2C_SDA_3, I2C_SCL_3, 100000);
  bme.begin(0x76,&I2CLine_1);
  bme_2.begin(0x76,&I2CLine_2);
  bme_3.begin(0x76,&I2CLine_3);
}

// ------------------------------------------------------------------
// BME280
String BME_Data(){
    
    String bme_str_data;
    float temp=bme.readTemperature();
    float hum=bme.readHumidity();
    float press=(bme.readPressure() / 100.0F);
    bme_str_data=",Sensor NO.1 Temperature,"   + String( temp )   + " ,"   + String( hum )   + " ," +   String( press );
    return bme_str_data;
}

// NO.2 BME280
String BME_Data_2(){
    
    String bme_str_data;
    float temp=bme_2.readTemperature();
    float hum=bme_2.readHumidity();
    float press=(bme_2.readPressure() / 100.0F);
    bme_str_data="   ,Sensor NO.2 Temperature," +  String( temp )   + " ,"  +  String( hum )  + " ," +  String( press );
    return bme_str_data;
}

// NO.3 BME280
String BME_Data_3(){
    
    String bme_str_data;
    float temp=bme_3.readTemperature();
    float hum=bme_3.readHumidity();
    float press=(bme_3.readPressure() / 100.0F);
    bme_str_data="   ,Sensor NO.3 Temperature," +  String( temp )   + " ,"  +  String( hum )  + " ," +  String( press );
    return bme_str_data;
}
void loop () {
  delay(3000);
  Serial.print(BME_Data());
  Serial.println(BME_Data_2());
  Serial.println(BME_Data_3());
}
