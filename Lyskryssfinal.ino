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

unsigned long previousMillis = 0; //For å lagre millis
unsigned long lastbuttonpress; //For lagre millis når knappen er trykt inn
const long Redinterval = 5000;
const long RedYellinterval = 2000;
const long Greeninterval = 10000;
const long Yellowinterval = 2000;
const long Pedinterval = 5000;
const long blinkinterval = 200;
const long debounce = 200;
int buttonState = 0;
int lightstate = 0;
int start = 0;
int trafficstate = 0;
int pedLEDstate = HIGH;
int Redstate = 0;
int previousButton = HIGH;
int blink = 0;
int blinkCount = 0;


void setup()
{
pinMode(LEDred, OUTPUT);
pinMode(LEDyellow, OUTPUT);
pinMode(LEDgreen, OUTPUT);
pinMode(PedLEDgreen, OUTPUT);
pinMode(PedLEDred, OUTPUT);
pinMode(Button, INPUT_PULLUP);
Serial.begin(9600);


}
void loop(){
unsigned long currentMillis = millis();
/*
Trafikklys
*/

if((lightstate == 5) && (currentMillis - previousMillis >=500)){ //Tidsforsinkelse fra da fotgjenger blir rødt til trafikklyset skal starte igjen
    
    lightstate = 0;
    previousMillis = currentMillis;
}

if((currentMillis - previousMillis >=Yellowinterval) && (lightstate == 0) || (start == 0)){ //Sjekker om lightstate er 0 og at det gule lyset har hatt sitt intervall

    
    lightstate = 1;
    start = 1;

        digitalWrite(LEDred, HIGH);
        digitalWrite(LEDyellow, LOW);
        Redstate = 1;
        previousMillis = currentMillis;
}
    if((currentMillis - previousMillis >=Redinterval) && (lightstate == 1)){ //Sjekker om lightstate er 1 og at det røde lyset har hatt sitt intervall

    
            lightstate = 2;
    
                digitalWrite(LEDred, HIGH);
                digitalWrite(LEDyellow, HIGH);
                Redstate = 0;
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

/*
Fotgjenger
*/
if((digitalRead(Button) == LOW) && (previousButton == HIGH) && (currentMillis - previousMillis  > debounce)){
    if(buttonState == 0){
        buttonState = 1;
        previousButton = digitalRead(Button);
        lastbuttonpress = currentMillis;
        Serial.println("Button works");
        Serial.println(lastbuttonpress);
        Serial.println(buttonState);
        }
        else
        {
            buttonState = 0;
        }
}
        
   
        if (buttonState == 1){
            if(currentMillis - lastbuttonpress >= Pedinterval){
            trafficstate = 1;
            buttonState = 0;
            Serial.println("Millis fungerer");
            }
        
        }
    

    
if((trafficstate == 1) && (Redstate == 1)){
    digitalWrite(PedLEDgreen, HIGH);
    digitalWrite(PedLEDred, LOW);
    if(currentMillis - lastbuttonpress >=Pedinterval){

               lightstate = 4;
               trafficstate = 0;
               previousMillis = currentMillis;
             } 
        
     }

    if (lightstate == 4 && (currentMillis - previousMillis >= Pedinterval)) {
    blink = 1;
    }

    if(blink == 1){
        if((blinkCount < 24) && (currentMillis - previousMillis >=blinkinterval)) {
        previousMillis = currentMillis;
    
        if (pedLEDstate == LOW) {
            pedLEDstate = HIGH;
        }else
        {
            pedLEDstate = LOW;
        }
        digitalWrite(PedLEDgreen, pedLEDstate);    
        Serial.println(blinkCount);
        blinkCount++;
        
    } 
        
}
        

        if (blinkCount == 19) {
            previousButton = HIGH;
            lightstate = 5;
            blink = 0;
            blinkCount = 0;
            digitalWrite(PedLEDred, HIGH);
            previousMillis = currentMillis;
        }
        
        
    }
