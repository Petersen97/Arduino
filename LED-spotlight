//konstanter
const int Ledpin =  3;
const int GreenB =  8;
const int RedB   = 12;
//Variabler
volatile int  dim_val = 0;
unsigned long ON_BUTTON_PRESSED;
unsigned long ON_BUTTON_LAST_PRESSED;
unsigned long ON_Button_millis_held;
const long    Delay_time = 500;
int ON_Button_current;
byte ON_Button_previous = HIGH;

void setup() {
  pinMode (Ledpin, OUTPUT);
  pinMode (GreenB, INPUT_PULLUP);
  pinMode (RedB,   INPUT_PULLUP);
  Serial.begin(9600);


}

void loop() {
  ON_Button_current = digitalRead(GreenB);
  ON_BUTTON_PRESSED = millis();
  if (ON_Button_current == LOW && ON_Button_previous == HIGH && ON_BUTTON_PRESSED - ON_BUTTON_LAST_PRESSED >=Delay_time){
      ON_BUTTON_PRESSED = ON_BUTTON_LAST_PRESSED;
  }
  ON_Button_millis_held = (millis() - ON_BUTTON_PRESSED);
  if (ON_Button_current == LOW && ON_Button_millis_held >= Delay_time) {
      
  do
  {
    dim_val++;
    analogWrite(Ledpin, dim_val);
    delay(30);
  }while (digitalRead(GreenB) == LOW);
  ON_Button_previous = ON_Button_current;
  }
  
}
