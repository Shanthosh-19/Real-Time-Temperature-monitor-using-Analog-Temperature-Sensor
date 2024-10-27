void initialize_port(char, char*);
int Analog_Read(void);
float calculate_temperature(int);

const float BETA = 3950; // varies based on the type of thermistor

void initialize_port(char port, char* direction){
  volatile char *dir = nullptr;
  if(port == 'A'){
    dir = (char*)0x21;
    if(direction == "INPUT") *dir = 0x00;
    else if(direction == "OUTPUT") *dir = 0xff;
  }
  else if(port == 'B'){
    dir = (char*)0x24;
    if(direction == "INPUT") *dir = 0x00;
    else if(direction == "OUTPUT") *dir = 0xff;
  }
  else if(port == 'C'){
    dir = (char*)0x27;
    if(direction == "INPUT") *dir = 0x00;
    else if(direction == "OUTPUT") *dir = 0xff;
  }
  else if(port == 'D'){
    dir = (char*)0x2a;
    if(direction == "INPUT") *dir = 0x00;
    else if(direction == "OUTPUT") *dir = 0xff;
  }
  else if(port == 'E'){
    dir = (char*)0x2d;
    if(direction == "INPUT") *dir = 0x00;
    else if(direction == "OUTPUT") *dir = 0xff;
  }
  else if(port == 'F'){
    dir = (char*)0x30;
    if(direction == "INPUT") *dir = 0x00;
    else if(direction == "OUTPUT") *dir = 0xff;
  }
  else if(port == 'G'){
    dir = (char*)0x33;
    if(direction == "INPUT") *dir = 0x00;
    else if(direction == "OUTPUT") *dir = 0xff;
  }
  else if(port == 'H'){
    dir = (char*)0x101;
    if(direction == "INPUT") *dir = 0x00;
    else if(direction == "OUTPUT") *dir = 0xff;
  }
  else if(port == 'J'){
    dir = (char*)0x104;
    if(direction == "INPUT") *dir = 0x00;
    else if(direction == "OUTPUT") *dir = 0xff;
  }
  else if(port == 'K'){
    dir = (char*)0x107;
    if(direction == "INPUT") *dir = 0x00;
    else if(direction == "OUTPUT") *dir = 0xff;
  }
  else if(port == 'L'){
    dir = (char*)0x10a;
    if(direction == "INPUT") *dir = 0x00;
    else if(direction == "OUTPUT") *dir = 0xff;
  }
}

int Analog_Read(void){
  volatile char *admux = nullptr, *adcsra = nullptr, *adcsrb = nullptr;
  volatile char *didr0 = nullptr;
  volatile unsigned char *adch = nullptr, *adcl = nullptr;
  volatile unsigned short data = 0;
  volatile unsigned char hb = 0, lb = 0;
  admux = 0x7c;
  didr0 = 0x7e;
  *didr0 = 0x10; // There is no need to read input, we are disabling the digital input 
                 // of that pin.
  adcsrb = 0x7b;
  adcsra = 0x7a;
  adch = 0x79;
  adcl = 0x78;

  // Here we have used ADC[4]
  *admux = 0x44; // adlar in admux register = 0 and
                 // AVcc is chosen for the AREF;

  *adcsrb = 0x00; // mux input is enables in adcsrb register
                  // and free running mode is selected;

  *adcsra = 0xc7; // adc conversion control, here the adie bit is set to "0" as we are
                  // manually checking for the interrupt flag, i.e., by polling; 

  while(*adcsra & 0x40){ // Polling
    hb = *adch;
    lb = *adcl;
    break;
  }
  data = hb;
  data = data << 8;
  data |= lb;
  volatile int value = (int)data;

  return value;
}

float calculate_temperature(int data){
  volatile float celsius = 1 / (log(1 / (1023. / data - 1)) / BETA + 1.0 / 298.15) - 273.15;
  return celsius;
}
