// NOTE: Learn about Timers and Auto trigerring modes in ADC
// NEXT TASK: Make the Analog_Read() function compatile for all ADCs
#include "Functions.h"
#include "LCD.h"

void setup() {
  // put your setup code here, to run once:
  initialize_port('F', "INPUT");
  initialize_port('K', "OUTPUT");
  initialize_port('A', "OUTPUT"); 
  initializeLED();
  
  char string_Temp[20] = {};
  volatile int temp = 0;
  volatile float Temperature = 0.00;
  writeString("Temperature:");
  while(1){
    temp = Analog_Read();
    Temperature = calculate_temperature(temp);
    dtostrf(Temperature, 3, 2, string_Temp); // snprintf(), can be used. But for mega, they can't format floating point numbers.
    outData(0xc8); // for printing value of temperature
    lcd_out_control();
    writeString(string_Temp);
    delay(500);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
