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
#include "Adafruit_SSD1306.h"
#include <Button.h>
#include "Fonts\DSEG14_Modern_Regular_32.h"
#include "Fonts\Dialog_plain_25.h"
#include "OBD.h"

String displayName[]{
  // 0       1         2         3       4         5        6       7      8      9
  "Boost","Coolant","AirTemp","Igntn","EgTemp","Throttle","Speed","0-60","Batt","Afr"
};

COBD obd;
/* 
 *  declare OLED display
 */
#define OLED_RESET 4 
TwoWire WIRE1(1,I2C_FAST_MODE); // I2c1
TwoWire WIRE2(2,I2C_FAST_MODE); // I2c2
Adafruit_SSD1306 display_top(128, 32, &WIRE1, OLED_RESET);
Adafruit_SSD1306 display_bottom(128,32, &WIRE2, OLED_RESET);
/*
 * declare the function usage
 */
String ReadDataWithPid(String pid);
//void displayString(String disstring);

byte inData;
char inChar;
String BuildINString;
String DisplayString;
String WorkingString;

long DisplayValue;
long preview_time;
long startTime0_60;
long stopTime0_60;
int  time0_60_ms;

boolean obd_connected;
boolean button_pressed;
boolean refresh_display;

int menu_ID = 0;

Button ButtonUp(PB12); // Connect your button between pin 2 and GND
Button ButtonEnter(PB13); // Connect your button between pin 2 and GND
Button ButtonDown(PB14); // Connect your button between pin 2 and GND

/*
 *define engine variable 
 */
 
float engine_coolant;
float engine_rpm;
float engine_ita;
float engine_boost;
int RPM;

void setup(){         
  Serial.begin(38400);
  obd.begin();
 
  DisplayInit();
  //displayTopString("Initialize OBD");
  while (!obd.init()); 
  obd_connected = true;
   ("Ready");
  initButton();
  pinMode(PC13, OUTPUT);
  menu_ID = 1;
  displayTopString(displayName[menu_ID]);
}
void loop(){

  if (ButtonUp.pressed()){
    Serial.println(menu_ID);   
    menu_ID =menu_ID + 1;
    if ( menu_ID > 9 ){
      menu_ID = 0;
    }
    button_pressed = true;
    refresh_display = true;
    preview_time = millis();
  }
  if (ButtonDown.pressed()){ 
    menu_ID =menu_ID-1;
    if ( menu_ID < 0 ){
      menu_ID = 9;
    }
    button_pressed = true; 
    refresh_display = true;
    preview_time = millis();
  }
  if ( ( ( millis() - preview_time ) > 5000 )&&( button_pressed ) ){
       button_pressed = false;
       Serial.println("Button cycle done");
  }
  if( ( button_pressed )&& ( refresh_display )) {  
     Serial.println(menu_ID);  
     displayTopString(displayName[menu_ID]);
     refresh_display = false;
 }
 
 /*
  *  0       1         2         3       4         5        6       7      8      9
  *"Boost","Coolant","AirTemp","Igntn","EgTemp","Throttle","Speed","0-60","Batt","Afr"
  */
 int tempReading;
 if ( ( obd_connected )&&( !button_pressed ) ){
  if ( millis() - preview_time > 200 ){
     switch (menu_ID) {
           case 0:                                      //READ BOOST
                obd.read(PID_INTAKE_MAP,tempReading );
                displayBottomBigFloatNumber(float(tempReading/100));
                break;
           case 1:                                      //READ coolant
                obd.read(PID_COOLANT_TEMP,tempReading );
                displayBottomBigNumber(tempReading);
                break;
           case 2:                                      //READ AirTemp
                obd.read(PID_INTAKE_TEMP,tempReading );
                displayBottomBigNumber(tempReading);
                break;
           case 3:                                      //READ Igntn
                obd.read(PID_TIMING_ADVANCE,tempReading );
                displayBottomBigNumber(tempReading);
                break;
           case 4:                                      //READ EgTemp
                obd.read(PID_INTAKE_TEMP,tempReading );
                displayBottomBigNumber(tempReading);            
                break;
           case 5:                                      //READ Throttle
                obd.read(PID_THROTTLE,tempReading );
                displayBottomBigNumber(tempReading);   
                break;
           case 6:                                      //READ Speed
                obd.read(PID_SPEED,tempReading );
                displayBottomBigNumber(tempReading);  
                break;
           case 7:                                      //0-60
                obd.read(PID_SPEED,tempReading );
                displayBottomBigNumber(tempReading);  
                if( ( tempReading > 0 ) && (startTime0_60 == 0 ) ){
                  startTime0_60 = millis();
                }
                // display the time when speed started
                if( ( tempReading < 60 )&&(tempReading > 0 ) ) {
                  time0_60_ms = millis()- startTime0_60;
                }
                displayTopBigNumber(time0_60_ms);
                break;
           case 8:                                      //Batt
                obd.read(PID_CONTROL_MODULE_VOLTAGE,tempReading );
                displayBottomBigNumber(tempReading);  
                break;
           case 9:                                      //Afr
                obd.read(PID_ENGINE_LOAD,tempReading );
                displayBottomBigNumber(tempReading);           
                break;
     }
   }
  }
}

//Read Data Function ***********************************************************
String ReadDataWithPid(String pid)
{
  Serial2.println(pid);                   // Send Coolant PID request 0105
  Serial2.flush();                        // Not sure if it's needed*********************************************
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
  obd_connected = true;
}
void initButton(){
  pinMode(PB12,INPUT_PULLUP);  
  pinMode(PB13,INPUT_PULLUP);  
  pinMode(PB14,INPUT_PULLUP);  
  ButtonUp.begin();
  ButtonEnter.begin();
  ButtonDown.begin();
}
/*void dispalyCoolant(){
      BuildINString = ReadDataWithPid(EngineCoolant);
      Serial.print("len: ");
      Serial.println(BuildINString.length());
      Serial.print("BuildINString :");
      Serial.println(BuildINString);
      WorkingString = BuildINString.substring(4,6);                    //410534410534;
      Serial.print("WorkingString :");
      Serial.println(WorkingString);
      engine_coolant = strtol(WorkingString.c_str(),NULL,16) - 40;     //convert hex to decimnal
      displayBigNumber(engine_coolant,"C");      
}
void displayRPM(){
      BuildINString = ReadDataWithPid(EngineRPM);                      //RPM
      Serial.print("len: ");
      Serial.println(BuildINString.length());
      Serial.print("BuildINString : ");
      Serial.println(BuildINString);
      WorkingString = BuildINString.substring(4,8);                    //BuildINString :410C0B64 410C0B64 >010C
      Serial.print("WorkingString : ");
      Serial.println(WorkingString);
      engine_rpm = (strtol(WorkingString.c_str(),NULL,16))/4;          //convert hex to decimnal
      displayBigNumber(engine_rpm," ");      
}
void display_boost(){
      BuildINString = ReadDataWithPid(BoostPressureControl);           //BOOST  00C
                                                                                0:41 70 12 00 00 04
                                                                                         A  B  C  D
                                                                                1:5A 00 00 04 53 00 AA>
                                                                                   E   F  G  H  I  J
                                                                                00C
                                                                                0:417012000004
                                                                                1:660000046100 AA>
      Serial.print("len: ");
      Serial.println(BuildINString.length());
      Serial.print("BuildINString : ");
      Serial.println(BuildINString);
      WorkingString = BuildINString.substring(6,8);                    //BuildINString : 00C 0: 41 70 12 00 00 04 1: A5 00 00 04 A1 00 AA >0170
      Serial.print("WorkingString : ");
      Serial.println(WorkingString);
      engine_boost = strtol(WorkingString.c_str(),NULL,16) - 40;       //convert hex to decimnal
      displayBigNumber(engine_boost,"PSI");      
}
void display_airintake_temp(){
      BuildINString = ReadDataWithPid(ChargeAirCoolerTemperature);     //intake temp
      Serial.print("len: ");
      Serial.println(BuildINString.length());
      Serial.print("BuildINString : ");
      Serial.println(BuildINString);
      WorkingString = BuildINString.substring(6,8);                    
      Serial.print("WorkingString : ");
      Serial.println(WorkingString);
      engine_ita = strtol(WorkingString.c_str(),NULL,16) - 40;         //convert hex to decimnal
      displayBigNumber(engine_ita,"C"); 
}*/
