/*
font Generator http://oleddisplay.squix.ch/#/home
STM32 adaption by Matthias Diro, tested with maple mini and heltec OLED 12864 I2c; adress: 0x3C (SPI should work, but I didn't own one)
Things to know:
 This adaption uses hardware I2C (now Wire.h), Port: I2c2. SDA=0, SCL=1 on maple mini
 further details: STM32_README.txt
*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SSD1306_STM32.h"
#include "Fonts\DSEG14_Modern_Regular_32.h"
#include "Fonts\FreeSans9pt7b.h"
#include "ELM327_PID.h"
#include <Button.h>


#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);
/*
 * declare the function usage
 */
String ReadDataWithPid(String pid);
void displayString(String disstring);
void displayBigNumber(long dispaly_temp_number,String Unit);

byte inData;
char inChar;
String BuildINString;
String DisplayString;
String WorkingString;
long DisplayValue;
long PreviewTime;
long A;
boolean obd_connected;

int menu_ID = 1;
Button button1(PB11); // Connect your button between pin 2 and GND
/*
 *define engine variable 
 */
float engine_coolant;
float engine_rpm;
float engine_ita;
float engine_boost;

void setup(){                
  Serial.begin(9600);
  Serial2.begin(38400);
 // while(!Serial.isConnected() );
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display();
  delay(5000);
  display.clearDisplay();
  obd_connected = false;
  displayString("Reseting");
  delay(1000);
  init_obd2();
  displayString("OBD2 Ready");
  obd_connected = true;
  button1.begin();
  pinMode(PB11,INPUT_PULLDOWN);
  
}
void loop() {
  if (button1.pressed()){
    Serial.println(menu_ID);   
    menu_ID =menu_ID+1;
    if ( menu_ID > 4 ){
      menu_ID = 1;
    }
  }
 if(obd_connected){
  if (millis() - PreviewTime > 20 ){
   switch ( menu_ID ){
       case 1 :
          Serial.println(menu_ID);
          dispalyCoolant();
          break;
       case 2 :
          Serial.println(menu_ID);
          displayRPM();
          break;       
       case 3 :
          Serial.println(menu_ID);
          display_boost();
          break;
       case 4 :
          Serial.println(menu_ID);
          display_airintake_temp();
          break;;                            
     }
     PreviewTime = millis();
   }
  }
  else {
    displayString("No Connection");
    }
}
void displayBigNumber(long dispaly_temp_number,String Unit){
  display.clearDisplay();
  display.setFont(&DSEG14_Modern_Regular_32);
  display.setTextColor(WHITE);
  display.setCursor(0,32);
  display.println(dispaly_temp_number + Unit);
  display.display();
}
void displayString(String disstring){
  display.clearDisplay();
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(WHITE);
  display.setCursor(0,22);
  display.println(disstring);
  display.display();
}
//Read Data Function ***********************************************************
String ReadDataWithPid(String pid)
{
  Serial2.println(pid);                   // Send Coolant PID request 0105
  Serial2.flush();                        //Not sure if it's needed*********************************************
  String TempBuildINString="";  
  while(Serial2.available() > 0)
  {
    inData=0;
    inChar=0;
    inData = Serial2.read();
    inChar=char(inData);
    TempBuildINString = TempBuildINString + inChar;
  }
  return TempBuildINString;
}

void init_obd2(){
  Serial.println("Sending ATZ");
  WorkingString = ReadDataWithPid("ATZ");                    // sending the ATZ for resetting the obd2 port
  Serial.println(WorkingString);
  while ( WorkingString != "ATZ"){
    Serial.println("Sending ATZ");
    WorkingString = ReadDataWithPid("ATZ").substring(16);   // sending the ATZ for resetting the obd2 port
    Serial.print("WorkingString :");
    Serial.println( WorkingString = "ATZ" );
    delay(1000);
  }
  WorkingString = ReadDataWithPid("ATE0");              // sending the ATE0 for setting no echo
  Serial.println(WorkingString);
  while ( WorkingString!= "OK"){
    Serial.println("Sending ATE0");
    WorkingString = ReadDataWithPid("ATE0");          
    Serial.print("WorkingString :");
    Serial.println(WorkingString = "OK");
    delay(1000);
  }
  WorkingString = ReadDataWithPid("ATS0");              // sending the ATS0 setting no space
  Serial.println(WorkingString);
  while ( WorkingString!= "OK"){
    Serial.println("Sending ATS0");
    WorkingString = ReadDataWithPid("ATS0");            
    Serial.print("WorkingString :");
    Serial.println(WorkingString = "OK");
    delay(1000);
  }
}
void dispalyCoolant(){
       BuildINString = ReadDataWithPid(EngineCoolant);
      Serial.print("len: ");
      Serial.println(BuildINString.length());
      Serial.print("BuildINString :");
      Serial.println(BuildINString);
      WorkingString = BuildINString.substring(4,6);                    //read coolant410534410534>0105 ---lenth 27;
      Serial.print("WorkingString :");
      Serial.println(WorkingString);
      engine_coolant = strtol(WorkingString.c_str(),NULL,16) - 40;                              //convert hex to decimnal
      displayBigNumber(engine_coolant,"C");      
 }
 void displayRPM(){
  
      BuildINString = ReadDataWithPid(EngineRPM);                  //RPM
      Serial.print("len: ");
      Serial.println(BuildINString.length());
      Serial.print("BuildINString : ");
      Serial.println(BuildINString);
      WorkingString = BuildINString.substring(4,8);                    //BuildINString : 41 0C 0B 64 41 0C 0B 64 >010C
      Serial.print("WorkingString : ");
      Serial.println(WorkingString);
      engine_rpm = (strtol(WorkingString.c_str(),NULL,16))/4;                              //convert hex to decimnal
      displayBigNumber(engine_rpm," ");      
 }
void display_boost(){
      BuildINString = ReadDataWithPid(BoostPressureControl);    //bOOST 00C0:4170120000041:5A0000045300AA>00C0:4170120000041:660000046100AA
>
*/
      Serial.print("len: ");
      Serial.println(BuildINString.length());
      Serial.print("BuildINString : ");
      Serial.println(BuildINString);
      WorkingString = BuildINString.substring(6,8);                    //BuildINString : 00C 0: 41 70 12 00 00 04 1: A5 00 00 04 A1 00 AA >0170
      Serial.print("WorkingString : ");
      Serial.println(WorkingString);
      engine_boost = strtol(WorkingString.c_str(),NULL,16) - 40;                              //convert hex to decimnal
      displayBigNumber(engine_boost,"PSI");      
}
void display_airintake_temp(){
      BuildINString = ReadDataWithPid(ChargeAirCoolerTemperature);                  //intake temp
      Serial.print("len: ");
      Serial.println(BuildINString.length());
      Serial.print("BuildINString : ");
      Serial.println(BuildINString);
      WorkingString = BuildINString.substring(6,8);                    //BuildINString : 00C 0: 41 70 12 00 00 04 1: A5 00 00 04 A1 00 AA >0170
      Serial.print("WorkingString : ");
      Serial.println(WorkingString);
      engine_ita = strtol(WorkingString.c_str(),NULL,16) - 40;                              //convert hex to decimnal
      displayBigNumber(engine_ita,"C"); 
}
