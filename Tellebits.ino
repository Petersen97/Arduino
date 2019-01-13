//Dette programmet teller bits opp til verdi 15. Den benytter seg av 4 led-pærer for å vise tallene.
//Avslått led-pære representerer verdien 0 og led-pære som lyser representerer verdien 1

int LedPins[] = {5, 4, 3, 2}; //Definerer hvilke pins som skal brukes
void setup() {
  // put your setup code here, to run once:

  for (int i =0;i<4;i++) //for-loop for å telle fra 0 til 3
  {
    pinMode(LedPins[i], OUTPUT); //Setter LedPins i array til output
  }

}

void loop() {
  //Array for tall som skal skrives ut som binary på ledlysene
    byte bitvalues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; //Endre tallene for å få en annen rekkefølge
    
    for(byte x = 0; x <15; x++)//Teller fra venstre til høyre i tabellen
    {  
      telleBits(bitvalues[x]);//Tallet fra bitvalues arrayen blir satt inn her representert som x, tallet blir satt inn i metoden displaybinary
      delay(500); //Delay er satt inn slik at den ikke skal telle så fort
    }

}

//Metode for å skrive ut tallet ved å bruke de fire leddiodene
void telleBits(byte number){
  //Teller seg gjennom tallet i binary for å sjekke hva som er 0 og hva som er 1
  for (int i =0;i<4;i++){

   //if statement som bruker bitread for å sjekke om verdien er lik 0
    if (bitRead(number, i)==0){ //Hvis tallet representert som i ==0 vil LEDen være slått av
    digitalWrite(LedPins[i], LOW);
   }
   //Hvis den ikke er ==0 vil den slå seg på
    else{
    digitalWrite(LedPins[i], HIGH);
   }
  }
  
}
