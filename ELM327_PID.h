String PID_NAME[]{
  "CheckSupportedPID0 TO 32",
  "Status since clearing codes",
  "Fault code  freeze frame",
  "Fuel system status",
  "Engine load calculated in %",
  "Engine coolant in °C",
  "Short-term fuel trim bank 1",
  "Long-term fuel  bank 1",
  "Short-term fuel  bank 2",
  "Long-term fuel  bank 2",
  "Fuel pressure in kPa",
  "Intake  pressure kPa",
  "Engine speed in rpm",
  "Vehicle speed in kph",
  "Timing  cylinder 1",
  "Intake air temperature °C",
  "Air flow  in g/s",
  "Throttle position in %",
  "Status secondary intake",
  "O2 sensor positions sensor",
  "O2 volts bank 1 sensor 1",
  "O2 volts bank 1 sensor 2",
  "O2 volts bank 1 sensor 3",
  "O2 volts bank 1 sensor 4",
  "O2 volts bank 2 sensor 1",
  "O2 volts bank 2 sensor 2",
  "O2 volts bank 2 sensor 3",
  "O2 volts bank 2 sensor 4",
  "OBD  specification",
  "O2 sensor positions sensor",
  "Auxiliary input status",
  "Run time  engine start",
  "PIDs supported 33 to 64",
  "Distance  MIL on in kms",
  "Relative fuel rail pressure",
  "Fuel rail pressure in kPa",
  "O2 sensor  bank 1, sensor 1",
  "O2 sensor bank 1, sensor 2",
  "O2 sensor bank 1, sensor 3",
  "O2 sensor bank 1, sensor 4",
  "O2 sensor bank 2, sensor 1",
  "O2 sensor bank 2, sensor 2",
  "O2 sensor bank 2, sensor 3",
  "O2 sensor bank 2, sensor 4",
  "EGR in %",
  "EGR error in %",
  "Evaporation purge in %",
  "Fuel level in %",
  "Warnings since faults cleared",
  "Distance since faults cleared",
  "Evaporation pressure in Pa",
  "Barometic pressure in kPa",
  "O2 sensor bank 1, sensor 1",
  "O2 sensor bank 1, sensor 2",
  "O2 sensor bank 1 , sensor 3",
  "O2 sensor bank 1, sensor 4",
  "O2 sensor bank 2, sensor 1",
  "O2 sensor bank 2, sensor 2",
  "O2 sensor bank 2, sensor 3",
  "O2 sensor bank 2, sensor 4",
  "Catalyst temp bank 1, sensor 1",
  "Catalyst temp bank 2, sensor 1",
  "Catalyst temp bank 1, sensor 2",
  "Catalyst temp bank 2, sensor 1",
  "PIDs supported 65 to 96",
  "Monitor status this drive cycle",
  "Control module voltage in V",
  "Absolute engine load",
  "Equivalent fuel/air mixture",
  "Relative throttle position in %",
  "Ambient air temperature in °C",
  "Absolute throttle position B in %",
  "Absolute throttle position C in %",
  "Accelerator pedal position D in %",
  "Accelerator pedal position E in %",
  "Accelerator pedal position F in %",
  "Commanded throttle actuator in %",
  "run time MIL on in min",
  "run time faults cleared in min",
  "Exteral test equipment no. 1 configuration information",
  "Exteral test equipment no. 2 configuration information",
  "Fuel type used by the vehicle",
  "Ethanol fuel %",
  "Evaporation system  pressure in kPa",
  "Evaporation system  pressure in Pa",
  "O2 sensor trim bank 1 and 3",
  "O2 sensor trim bank 1 and 3",
  "O2 sensor trim bank 2 and 4",
  "O2 sensor trim bank 2 and 4",
  "fuel rail pressure in kPa",
  "accelerator pedal position in %",
  "Battery unit life (hybrid) in %",
  "Engine oil temperature in °C",
  "Fuel injection timing in °",
  "Fuel consumption in litre/hr",
  "Fuel consumption in litre/hr",
  "PIDs supported 97 to 128",
  "Torque percentage (%)",
  "Engine torque percentage (%)",
  "Engine torque reference in Nm",
  "Engine torque data in %",
  "Auxiliary inputs / outputs",
  "Flowmeter sensor",
  "Engine water temperature in °C",
  "Air temperature sensor in °C",
  "Commanded EGR and EGR error",
  "intake air flow control position",
  "Recirculation gas temp in °C",
  "throttle actuator control",
  "Fuel pressure control system",
  "Injection pressure control system",
  "Turbocharger inlet pressure in kPa",
  "Boost pressure control in kPa",
  "Geometry turbo(VGT)control",
  "Wastegate control",
  "Exhaust pressure in kPa",
  "Turbocharger RPM",
  "Turbo A temperature in °C",
  "Turbo B temperature in °C",
  "Charge air cooler temp in °C",
  "Exhaust Gas temp(EGT) Bank 1",
  "Exhaust Gas temp(EGT) Bank 2"
  "Diesel (DPF) bank 1",
  "Diesel (DPF) bank 2",
  "Diesel (DPF) temperature",
  "NOx NTE control area status",
  "PM NTE control area status",
  "Engine run time",
  "PIDs supported 129 to 160"      //128
};
String PID_NUM[]{ 
 "0100","0101","0102","0103","0104","0105","0106","0107","0108","0109","010A","010B","010C","010D","010E","010F", //00
 "0110","0111","0112","0113","0114","0115","0116","0117","0118","0119","011A","011B","011C","011D","011E","011F", //10
 "0120","0121","0122","0123","0124","0125","0126","0127","0128","0129","012A","012B","012C","012D","012E","012F", //20
 "0130","0131","0132","0133","0134","0135","0136","0137","0138","0139","013A","013B","013C","013D","013E","013F", //30
 "0140","0141","0142","0143","0144","0145","0146","0147","0148","0149","014A","014B","014C","014D","014E","014F", //40
 "0150","0151","0152","0153","0154","0155","0156","0157","0158","0159","015A","015B","015C","015D","015E","015F", //50
 "0160","0161","0162","0163","0164","0165","0166","0167","0168","0169","016A","016B","016C","016D","016E","016F", //60
 "0170","0171","0172","0173","0174","0175","0176","0177","0178","0179","017A","017B","017C","017D","017E","017F", //70
 "0180",                                                                                                          //80
};
String PID_DATA[]{
  "ABCD"   ,"ABCD"  ,"AB"   ,"AB"   ,"A"    ,"A"      ,"AB"     ,"AB"  ,"AB"       ,"AB"       ,"A"      ,"A"      ,"AB"       ,"A"          ,"A"        ,"A",              //00
  "AB"     ,"A"     ,"A"    ,"A"    ,"AB"   ,"AB"     ,"AB"     ,"AB"  ,"AB"       ,"AB"       ,"AB"     ,"AB"     ,"A"        ,"A"          ,"A"        ,"AB",             //10
  "AB"     ,"AB"    ,"AB"   ,"AB"   ,"ABCD" ,"ABCD"   ,"ABCD"   ,"ABCD","ABCD"     ,"ABCD"     ,"ABCD"   ,"ABCD"   ,"A"        ,"A"          ,"A"        ,"A",              //21
  "A"      ,"AB"    ,"AB"   ,"A"    ,"ABCD" ,"ABCD"   ,"ABCD"   ,"ABCD","ABCD"     ,"ABCD"     ,"ABCD"   ,"ABCD"   ,"AB"       ,"AB"         ,"AB"       ,"AB",             //31
  "ABCD"   ,"ABCD"  ,"AB"   ,"AB"   ,"AB"   ,"A"      ,"A"      ,"A"   ,"A"        ,"A"        ,"A"      ,"A"      ,"A"        ,"AB"         ,"AB"       ,"ABCD",           //41
  "ABCD"   ,"ABCD"  ,"A"    ,"AB"   ,"AB"   ,"AB"     ,"AB"     ,"AB"  ,"AB"       ,"AB"       ,"A"      ,"A"      ,"A"        ,"AB"         ,"AB"       ,"A",              //51
  "ABCD"   ,"A"     ,"A"    ,"AB"   ,"ABCDE","AB"     ,"ABCDE"  ,"ABC" ,"ABCDEFG"  ,"ABCDEFG"  ,"ABCD"   ,"ABCDE"  ,"ABCD"     ,"ABCDEFGHIJK","ABCDEFGHI","ABC",            //61
  "ABCDHIJ","ABCDEF","ABCDE","ABCDE","ABCDE","ABCDEFG","ABCDEFG","ACDE","ABCDEFGHI","ABCDEFGHI","ABCDEFG","ABCDEFG","ABCDEFGHI","A"          ,"A"        ,"ABCDEFGHIJKLM",  //71
};
float formula_multi[]{
//0        1        2       3      4       5
  0,       0,       0,      0,  100/255,   1
};
long formula_ADD[]{
  
};
String PID_NAME_SHORT[]{
  // 0       1         2         3       4         5        6       7      8      9
  "Boost","Coolant","AirTemp","Igntn","EgTemp","Throttle","Speed","0-60","Batt","Afr"
};
String PID_NUM_SHORT[]{
 };
