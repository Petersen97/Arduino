/*
* Author: Erik Petersen
* Date Created 14/11/2018
* Date Modified 21/11/2018
*/

/* Forklaring av programmet
* Ved hjelp av to brytere skal man kunne dimme en LED-pære opp eller ned
* ved å holde inne på-bryteren eller av-bryteren
* Lyststyrken vil være fra og med 0 til og med 255
*/

//konstanter
const int Ledpin=3; //Setter Ledpin til pin 3
      int GreenB=8; //Setter GreenB/dimme opp-knapp til pin 8
      int RedB=12;  //Setter RedB/dimme ned-knapp til pin 12
//Variabler
volatile int val = 0;
      


void setup() {
  pinMode (Ledpin, OUTPUT);         //Setter Ledpin til output
  pinMode (GreenB, INPUT_PULLUP);   //Setter på-knapp til INPUT_PULLUP
  pinMode (RedB, INPUT_PULLUP);     //Setter på-knapp til INPUT_PULLUP
  Serial.begin(9600);               //Starter seriell tilkobling med hastighet 9600

}

void loop() {
      //Setter veriden "val" har til ledlyset 0-255
      analogWrite(Ledpin, val);
        //Dimmer opp
        if (digitalRead(GreenB) == LOW) //Sjekker om dimme opp-knappen er holdt nede
{
      
     if (val<255) //Sjekker om verdien på lyset er mindre enn 255 

      val++;  // Hvis det er mindre vil den øke med 1 om gangen så lenge man holder inne den grønne bryteren.
      delay(65); //Delay på 65 millisekunder slik at man ser lyset dimmer opp
     
}   
// Dimmer ned
if (digitalRead(RedB) == LOW) //Sjekker om dimme ned-knappen er holdt nede
{
     if (val>0) //Sjekker om verdien på lyset er større enn 0
     
      val--; //Så lenge verdien på lyset er over 0 så vil den dimme ned med 1 om gangen når rød bryter holdes nede
      delay(30); //Delay på 65 millisekunder slik at man ser lyset dimmer ned
     
  }
}      
