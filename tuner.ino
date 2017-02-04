/* Program do obslugi stroika gitarowego Arduino */

// Deklaracja zmiennych
unsigned int knock;
float t;
const int n = 500; // Liczba probek
int cmd = 0;

void setup() 
{
   // Konfiguracja portu szeregowego
   Serial.begin(115200); 
   // Ustawienie pinow kontrolujacych diody
   pinMode(3, OUTPUT);
   pinMode(5, OUTPUT);
   pinMode(6, OUTPUT);
   pinMode(9, OUTPUT);
   pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);
   // Arduino czeka na sygnal rozpoczecia pomiarow
   Serial.println("Gotowy?");
   while(Serial.available() == 0);  
   while(Serial.available() > 0) {  
   Serial.read();}
}

void loop() 
{
   Serial.print(cmd);
   t = millis();  // Czas start
   for(int i=0; i<n; i++){
     knock = analogRead(0); // Odczyt z mikrofonu
     Serial.println(knock); // Wyslanie danych do komputera
   }
   t = millis() - t; // Obliczenie czasu pomiaru

   Serial.println("Czas:");
   Serial.println(t);  // Czas pomiaru trafia do komputera


   // Blok kontrolujacy diody
   while (Serial.available() > 0)
   {
     cmd = Serial.read();
     if (cmd == 51){
        digitalWrite(3, HIGH);
        delay(2000);
        digitalWrite(3, LOW);
      }
     else if (cmd == 53){
        digitalWrite(5, HIGH);
        delay(2000);
        digitalWrite(5, LOW);
      }
     else if (cmd == 54){
        digitalWrite(6, HIGH);
        delay(2000);
        digitalWrite(6, LOW);
      }
      else if (cmd == 57){
        digitalWrite(9, HIGH);
        delay(2000);
        digitalWrite(9, LOW);
      }
      else if (cmd == 48){
        digitalWrite(10, HIGH);
        delay(2000);
        digitalWrite(10, LOW);
      }
      else if (cmd == 49){
        digitalWrite(11, HIGH);
        delay(2000);
        digitalWrite(11, LOW);
      }
      break;
   }
}

