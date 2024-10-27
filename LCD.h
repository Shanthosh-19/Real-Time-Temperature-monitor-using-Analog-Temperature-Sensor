void initializeLED(void);
void outData(char);
void outControl(char);
void delaytime(int);
void lcd_out_control(void);
void writeString(char*);
void writeChar(char);

void outData(char out){
  volatile char *outk = (char*)0x108;
  *outk = out;
}

void delaytime(int num){
  while(num){
    for(volatile long i = 0; i < 10000; i++);
    num--;
  }
}

void outControl(char ctrl){
  volatile char *outa = (char*)0x22;
  *outa = ctrl;
}

void lcd_out_control(){ // Enable pin
  volatile char *outa = (char*)0x22;
  outControl(0x00);
  delay(1);
  outControl(0x01);
  delay(1);
  outControl(0x00);
  delay(1);
}

void initializeLED(){
  outData(0x38);// 8-bit data is sent and 1 line
  lcd_out_control();
  outData(0x0c); // set display and cursor
  lcd_out_control();
  outData(0x01); // clear display
  lcd_out_control();
  outData(0x06); // sets cursor direction and increments DisplayDataRAM(DDRAM); 
  lcd_out_control();
}

void writeChar(char data){
  outData(data);
  outControl(0x02); // A8 ---> E(Enable) || A9 ---> RS(Register Set);
  delay(1);
  outControl(0x03);
  delay(1);
  outControl(0x02);
  delay(1);
} 

void writeString(char *str){
  while(*str != '\0'){
    writeChar(*str);
    str++;
  }
}
