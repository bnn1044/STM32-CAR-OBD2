void DisplayInit(){
  display_top.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3C  first LED
  display_bottom.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display_top.display();
  display_bottom.display();
  delay(1000);
  display_top.clearDisplay();
  display_bottom.clearDisplay();
  displayTopString("Rsting");
}
void displayBottomBigNumber(long dispaly_temp_number){
  display_bottom.clearDisplay();
  display_bottom.setFont(&DSEG14_Modern_Regular_32);
  display_bottom.setTextColor(WHITE);
  
  display_bottom.setTextSize(1);
  display_bottom.setCursor(0,32);
  display_bottom.println(dispaly_temp_number);
  display_bottom.display();
}
void displayBottomBigFloatNumber(float dispaly_temp_number){
  display_bottom.clearDisplay();
  display_bottom.setFont(&DSEG14_Modern_Regular_32);
  display_bottom.setTextColor(WHITE);
  
  display_bottom.setTextSize(1);
  if(dispaly_temp_number > 0){
    display_bottom.setCursor(8,32);   
  }else{
    display_bottom.setCursor(0,32);
  }
  display_bottom.println(dispaly_temp_number,1);
  display_bottom.display();
}
void displayTopBigNumber(long dispaly_temp_number){
  display_top.clearDisplay();
  display_top.setFont(&DSEG14_Modern_Regular_32);
  display_top.setTextColor(WHITE);
  display_top.setTextSize(1);
  display_top.setCursor(0,32);
  display_top.println(dispaly_temp_number);
  display_top.display();
}

void displayTopString(String disstring){
  //int len = disstring.length();
  display_top.clearDisplay();
  display_top.setFont(&Dialog_plain_25);
  display_top.setTextColor( WHITE );
  display_top.setCursor(0,25);
  display_top.println( disstring );
  display_top.display();
}
void drawBoxTopScreen(){
  
}
