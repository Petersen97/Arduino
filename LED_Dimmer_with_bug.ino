/*
* Author: Erik Petersen
* Date Created 20/11/2018
* Date Modified 21/11/2018
*/

/* Forklaring av programmet
* Programmet emulerer lysbryteren i klasserommet
* Ved kort puls av på-bryter skal lyset slå seg på.
* Hvis på-knappen holdes inne i ett sekund eller mer dimmer lyset opp når knappen holdes inne.
* Av-knappen fungerer på samme måte, men på den vil lyset slukkes eller dimmes ned.
*/
/*Feil i programmet
* Programmet vil fungere helt fint i starten. Etter en stund vil programmet slutte å fungere
* og du vil ikke få dimmet eller slått lyset av eller på. Vet ikke helt hva som gjør det.
*/

//konstanter
const int Ledpin =  3;  // Pin 3 for lys
const int GreenB =  8;  // Pin 8 for på-knapp
const int RedB   = 12;  // Pin 12 for av-knapp
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
  pinMode (GreenB, INPUT_PULLUP); //Setter som pullup fordi da vil inputen være stabil
  pinMode (RedB,   INPUT_PULLUP);
  //Starter seriell kobling med hastighet 9600
  //Brukes for feilsøking
  Serial.begin(9600);


}

void loop() {
    //Setter currentTime til nåværende tid til den interne klokken.
    unsigned long currentTime = millis();
    //Caller void loop hvert 30 sekund for å unngå at programmet fungerer i lengre tid.
    //Programmet vil uansett bugge seg etter en hvis tid.
    if (currentTime >= 30000) { 
      loop();   
    }
    
    
    //Gir lesing av input-knappene et navn.
    int ON_INC = digitalRead(GreenB);
    int OFF_DEC = digitalRead(RedB);
   //Dimme opp
  //Sjekk om ON-button er trykket  
  if (ON_INC == LOW){

    //Sjekker om ON_LASTSTATE har endret seg til true  
    if (!ON_LASTSTATE){
          //Setter ON_LASTPRESS til currentTime og ON_LASTSTE til true
          ON_LASTPRESS = currentTime;
          ON_LASTSTATE = true;
       }
      //Sjekker om ON-button har vært holdt nede lenge nok
      if ((currentTime - ON_LASTPRESS) >= Delay_time) {
        //Dimmer lyset opp så lenge ON-button er holdt nede etter forrige if-statement
        while (digitalRead(GreenB) == LOW && dim_val == min(dim_val, 254) && dim_val < 255)
        {
        //Dimmer opp lyset med 1 om gangen hvert 10ende millisekund så lenge while-statement er sann 
        dim_val++;
        Serial.println(dim_val);
        analogWrite(Ledpin, dim_val);
        //Delay for while loop slik at lyset gradvis dimmer seg opp.
        delay(20);
        }      
      
      }
  
  }
  else //Hvis ikke det over stemmer vil det under bli utført
  {
  //Sjekker om ON-button har vært holdt nede i mindre enn 500 millisekunder
  if ((currentTime - ON_LASTPRESS) < Delay_time && ON_LASTSTATE == true && dim_val <=255)
  {
    //Serial.print er blitt brukt til å feilsøke
    Serial.print("PÅ");
    Serial.println(" ");
    Serial.print(currentTime - ON_LASTPRESS);
    //Setter verdi til 255, lys på
    analogWrite(Ledpin, 255);
    //Setter dim_val til verdi 255 for at dim-ned funksjonen skal fungere når lyset er slått på
    dim_val = 255;
  }
  //Resetter ON_LASTSTATE til false
  ON_LASTSTATE = false;
  }

  //Dimme ned
    //Sjekk om OFF-button er trykket
    if (OFF_DEC == LOW){

      //Sjekker om OFF_LASTSTATE har endret seg til true
      if (!OFF_LASTSTATE){
          //Lagrer tiden for når av-knappen ble sist trykt.
          OFF_LASTPRESS = currentTime;
          OFF_LASTSTATE = true;
       }
      //Sjekker om OFF-button har vært holdt nede lenge nok
      if ((currentTime - OFF_LASTPRESS) > Delay_time && OFF_LASTSTATE == true && dim_val <=255) {
        //Dimmer lyset ned så lenge OFF-button er holdt nede etter forrige if-statement
        //While-statement looper så lenge den er sann
        while (digitalRead(RedB) == LOW && dim_val == max(dim_val, 1))
        {
        //Dimmer ned lyset med 1 om gangen hvert 10ende millisekund så lenge while-statement er sann  
        dim_val--;
        Serial.println(dim_val);
        analogWrite(Ledpin, dim_val);
        //Delay for while loop slik at lyset gradvis dimmer seg opp.
        delay(10);
        }
             
      }
  }
  else //Hvis ikke det over stemmer vil det under bli utført
  {
  //Sjekker om OFF-button har vært holdt nede i mindre enn 500 millisekunder
  if ((currentTime - OFF_LASTPRESS) < Delay_time && OFF_LASTSTATE == true && dim_val >= 0)
  {
    //Serial.print har blitt brukt for feilsøking
    Serial.print("AV");
    Serial.println(" ");
    //Setter verdi til 0, lys av
    analogWrite(Ledpin, 0);
    dim_val = 0;
  }
  //Setter OFF_LASTSTATE til false
  OFF_LASTSTATE = false;
  }
 delay(100);
}
