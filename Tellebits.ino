int LedPins[] = {5, 4, 3, 2}; //Definerer hvilke pins som skal brukes
void setup() {
  // put your setup code here, to run once:

  for (int i =0;i<4;i++) //for loop for å telle fra 0 til 3
  {
    pinMode(LedPins[i], OUTPUT); //Setter LedPins i array til output
  }
  Serial.begin(9600);

}

void loop() {
  //Array for tall som skal skrives ut som binary på ledlysene
    byte bitvalues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; //Endre tallene for å få en annen rekkefølge
    
    for(byte x = 0; x <15; x++)//Teller fra venstre til høyre i tabellen
    {  
      displaybinary(bitvalues[x]);//Tallet fra bitvalues arrayen blir satt inn her representert som x, tallet blir satt inn i metoden displaybinary
      delay(500); //Delay er satt inn slik at den ikke skal telle så fort
    }

}

//Metode for å skrive ut tallet ved å bruke de fire leddiodene
void displaybinary(byte number){
  for (int i =0;i<4;i++){

   if (bitRead(number, i)==0){
    digitalWrite(LedPins[i], LOW);
   }
   else{
    digitalWrite(LedPins[i], HIGH);
   }
  }
  
}
