//konstanter
const int Ledpin=3;
      int GreenB=8;
      int RedB=12;
      volatile int val = 0;
      


void setup() {
  pinMode (Ledpin, OUTPUT);
  pinMode (GreenB, INPUT_PULLUP);
  pinMode (RedB, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  analogWrite(Ledpin, val);
        //Dimmer opp
        if (digitalRead(GreenB) == LOW)
{
      
     if (val<255) //Sjekker om verdien på lyset er mindre enn 255 

      val++;  // Hvis det er mindre vil den øke med 1 om gangen så lenge man holder inne den grønne bryteren.
      delay(65);
     
}   
// Dimmer ned
if (digitalRead(RedB) == LOW)
{
     if (val>0) //Sjekker om verdien på lyset er større enn 0
     
      val--; //Så lenge verdien på lyset er over 0 så vil den dimme ned med 1 om gangen når rød bryter holdes nede
      delay(30);
     
  }
}      
