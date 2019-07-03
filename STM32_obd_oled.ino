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

#define ButtonUpdateRate_timer2  50000    //in mills
#define Led_pin  PC13           
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
int Previewmilles;

boolean obd_connected;
boolean button_pressed;
boolean refresh_display;
boolean readPid;
int LED_flash = 0;

int menu_ID = 0;

void Timer3_handler(void);
void Timer4_handler(void);

Button ButtonUp(PB12); // Connect your button between pin 2 and GND
Button ButtonEnter(PB13); // Connect your button between pin 2 and GND
Button ButtonDown(PB14); // Connect your button between pin 2 and GND

void setup(){         
  Serial.begin(38400);
  //while(!Serial);
  initButton();
  obd.begin();
  DisplayInit();
  while (!obd.init());
  obd_connected = true;
  pinMode(Led_pin, OUTPUT);
  digitalWrite(Led_pin, HIGH);
  SetupTimer2();
  SetupTimer3();
  menu_ID = 1;
  displayTopString(displayName[menu_ID]);
}
int testPsi = -30;
void loop(){
  if ( readPid ){
    processPid();
    readPid = false;
    Timer3.resume();
  }
}
/*
 * Process button press and menu
 */
void processButton_timer2(void){
    if (ButtonUp.pressed()){  
      menu_ID =menu_ID + 1;
      if ( menu_ID > 9 ){
        menu_ID = 0;
      }
      button_pressed = true;
      refresh_display = true;
  }
  if (ButtonDown.pressed()){ 
    menu_ID =menu_ID-1;
    if ( menu_ID < 0 ){
      menu_ID = 9;
    }
    button_pressed = true; 
    refresh_display = true;
  }
  if( ( button_pressed )&& ( refresh_display )) {  
     displayTopString(displayName[menu_ID]);
     refresh_display = false;
     button_pressed = false;
 }
}
 /*
  *  0       1         2         3       4         5        6       7      8      9
  *"Boost","Coolant","AirTemp","Igntn","EgTemp","Throttle","Speed","0-60","Batt","Afr"
  *read PID every 200ms
  */
void processPid(){
 int tempReading;
 int psi;
 if ( obd_connected ){   
     switch (menu_ID) {
      case 0:                                      //READ BOOST
        obd.read(PID_INTAKE_MAP,tempReading );
        if ( tempReading >= 0 ){
            psi = float(tempReading/100.0);
            //displayBottomBigFloatNumber(psi);            // display PSI
        }else{
            psi = float( ( tempReading*2.036 )/100.0);
        }
        displayBottomBigFloatNumber( psi ); // converted to Hg
        drawBoostBarOnTopDisplay( psi );
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
        tempReading = ( float(tempReading) *62.1371 )/ 100.0 ;
        displayBottomBigNumber(tempReading);  
        break;
      case 7:                                      //0-60
        obd.read(PID_SPEED,tempReading );
        tempReading = ( float(tempReading) *62.1371 )/ 100.0 ;
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
 // Serial.println(psi);
  Serial.println( millis());
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
/*
 * Set up every 200ms for process the PID
 */
void Timer3_handler(void){
  Timer3.pause();
  readPid = true;
}
/*
 * Set up Timer 2 as Button update timer
 * every 20ms
 */
void SetupTimer2(){
    // Pause the timer while we're configuring it
    Timer2.pause();
    Timer2.setMode(TIMER_CH1, TIMER_OUTPUTCOMPARE);
    Timer2.setPeriod(ButtonUpdateRate_timer2); // in microseconds
    Timer2.setCompare(TIMER_CH1, 1);      // overflow might be small
    Timer2.refresh();
    Timer2.attachInterrupt(TIMER_CH1, processButton_timer2);
    Timer2.resume();
}
void SetupTimer3(){
  Timer3.pause();
  Timer3.setMode(TIMER_CH1,TIMER_OUTPUT_COMPARE);
  Timer3.setPeriod(200000);                       // in microSecond
  Timer3.refresh();
  Timer3.setCompare(TIMER_CH1, 1);      // overflow might be small
  Timer3.attachInterrupt(TIMER_CH1,Timer3_handler);
  Timer3.resume();

}
