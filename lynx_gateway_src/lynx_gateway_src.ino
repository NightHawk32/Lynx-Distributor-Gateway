#include <Wire.h>

//0x08 A: DIP 1:OFF, 2:OFF 
//0x09 B: DIP 1:ON, 2:OFF
//0x0A C: DIP 1:OFF, 2:ON
//0x0B D: DIP 1:ON, 2:OFF

void setup()
{
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nLynx Gateway");
  Serial.println("Detecting Lynx:");

  static uint8_t error = 0xFF;

  for(uint8_t a = 0x08; a <= 0x0B; a++){
    Wire.beginTransmission(a);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("Lynx found at address 0x");
      if (a<16){ 
        Serial.print("0");
      }
      Serial.println(a,HEX);
    }else{
      Serial.print("Lynx 0x");
      if (a<16){ 
        Serial.print("0");
      }
      Serial.print(a,HEX);
      Serial.println(" not responding");
    }
  }
}

void loop()
{
  uint8_t val = 0x00;
  uint8_t address = 0x08;

  Serial.print("\nFuse states of Lynx A: 0x");
  
  Wire.beginTransmission(address);
  Wire.write(0xFF);
  Wire.endTransmission();
  Wire.requestFrom(address, 1); // We want one byte
  val = Wire.read();
  Wire.endTransmission();
  if (val<16){ 
      Serial.print("0");
  }
  Serial.println(val,HEX);

  Wire.beginTransmission(address);
  Wire.write(0xFF);
  Wire.endTransmission();

  for(uint8_t f = 4; f <= 7; f++){
    Serial.print("Fuse ");
    Serial.print(f-3);
    Serial.print(": ");
    if(!((val >> f) & 0x01)){
      Serial.print("Good");
    }else{
      Serial.print("Bad");
    }
    Serial.println("");  
  }
  delay(3000);
}
