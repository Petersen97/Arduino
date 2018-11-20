//konstanter
const int Ledpin =  3;
const int GreenB =  8;
const int RedB   = 12;
//Variabler
int  dim_val;

int Delay_time = 1000;

//Lagre tiden når knappene ble trykket sist ved å bruke millis()
int  ON_LASTPRESS = millis();
int  OFF_LASTPRESS = millis();

bool volatile OFF_LASTSTATE = false;
bool volatile ON_LASTSTATE  = false;

void setup() {
  pinMode (Ledpin, OUTPUT);
  pinMode (GreenB, INPUT_PULLUP);
  pinMode (RedB,   INPUT_PULLUP);
  Serial.begin(9600);


}

void loop() {
    unsigned long currentTime = millis();
    
    int ON_INC = digitalRead(GreenB);
    int OFF_DEC = digitalRead(RedB);
   //Dimme opp
  //Sjekk om ON-button er trykket  
  if (ON_INC == LOW){

      if (!ON_LASTSTATE){
          ON_LASTPRESS = currentTime;
          ON_LASTSTATE = true;
       }
      //Sjekker om ON-button har vært holdt nede lenge nok
      if ((currentTime - ON_LASTPRESS) >= Delay_time) {
        //Dimmer lyset opp så lenge ON-button er holdt nede etter forrige if-statement
        while (digitalRead(GreenB) == LOW && dim_val == min(dim_val, 254))
        {
        dim_val++;
        Serial.println(dim_val);
        analogWrite(Ledpin, dim_val);
        delay(20);
        }      
      
      }
  
  }
  else
  {
  //Sjekker om ON-button har vært holdt nede i mindre enn 500 millisekunder
  if ((currentTime - ON_LASTPRESS) < Delay_time && ON_LASTSTATE == true && dim_val <=255)
  {
    Serial.print("PÅ");
    Serial.println(" ");
    Serial.print(currentTime - ON_LASTPRESS);
    //Setter verdi til 255, lys på
    analogWrite(Ledpin, 255);
  }
  ON_LASTSTATE = false;
  }

  //Dimme ned
    //Sjekk om OFF-button er trykket
    if (OFF_DEC == LOW){

      if (!OFF_LASTSTATE){
          OFF_LASTPRESS = currentTime;
          OFF_LASTSTATE = true;
       }
      //Sjekker om OFF-button har vært holdt nede lenge nok
      if ((currentTime - OFF_LASTPRESS) > Delay_time && OFF_LASTSTATE == true) {
        //Dimmer lyset ned så lenge OFF-button er holdt nede etter forrige if-statement
        while (digitalRead(RedB) == LOW && dim_val == max(dim_val, 1))
        {
        dim_val--;
        Serial.println(dim_val);
        analogWrite(Ledpin, dim_val);
        delay(20);
        }
             
      }
  }
  else
  {
  //Sjekker om OFF-button har vært holdt nede i mindre enn 500 millisekunder
  if ((currentTime - OFF_LASTPRESS) < Delay_time && OFF_LASTSTATE == true && dim_val >= 0)
  {
    Serial.print("AV");
    Serial.println(" ");
    //Setter verdi til 0, lys av
    analogWrite(Ledpin, 0);
  }
  OFF_LASTSTATE = false;
  }
 delay(100);
}
