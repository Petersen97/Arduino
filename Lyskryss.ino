/*
Author: Erik Petersen
Created: 05.02.2019
Rødt 5sek
Rød og gul 2sek
Grønn 10sek
Gul 4sek
*/

int PedLEDgreen = 6;
int PedLEDred = 7;
int LEDred = 8;
int LEDyellow = 9;
int LEDgreen = 10;
int Button = 11;

unsigned long previousMillis; //For å lagre millis
const long Redinterval = 5000;
const long RedYellinterval = 2000;
const long Greeninterval = 10000;
const long Yellowinterval = 2000;
int ledstate = LOW;
int lightstate = 0;


void setup()
{
pinMode(LEDred, OUTPUT);
pinMode(LEDyellow, OUTPUT);
pinMode(LEDgreen, OUTPUT);
pinMode(PedLEDgreen, OUTPUT);
pinMode(PedLEDred, OUTPUT);


}
void loop(){
unsigned long currentMillis = millis();

if((currentMillis - previousMillis >=Yellowinterval) && (lightstate == 0)){ //Sjekker om lightstate er 0 og at det gule lyset har hatt sitt intervall

    
    lightstate = 1;

digitalWrite(LEDred, HIGH);
digitalWrite(LEDyellow, LOW);
previousMillis = currentMillis;
}
if((currentMillis - previousMillis >=Redinterval) && (lightstate == 1)){ //Sjekker om lightstate er 1 og at det røde lyset har hatt sitt intervall

    
    lightstate = 2;
    
digitalWrite(LEDred, HIGH);
digitalWrite(LEDyellow, HIGH);
previousMillis = currentMillis;
}
if((currentMillis - previousMillis >=RedYellinterval) && (lightstate == 2)){ //Sjekker om lightstate er 2 og at det røde og gule lyset har hatt sitt intervall

    
    lightstate = 3;

digitalWrite(LEDgreen, HIGH);
digitalWrite(LEDred, LOW);
digitalWrite(LEDyellow, LOW);
previousMillis = currentMillis;
}
if((currentMillis - previousMillis >=Greeninterval) && (lightstate == 3)){ //Sjekker om lightstate er 3 og at det grønne lyset har hatt sitt intervall

    
    lightstate = 0;
    
digitalWrite(LEDyellow, HIGH);
digitalWrite(LEDgreen, LOW);
previousMillis = currentMillis;
}
}

