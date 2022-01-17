//hier werden die Variablen deklariert
int laserEmpfaenger = 21;
int laserSender = 22;
int motorgeschwindigkeit1 = 23;
int motorgeschwindigkeit2 = 24;
int untererKippschalter = 25;
int obererKippschalter = 26;
int motorObenRichtungUnten = 27;
int motorObenRichtungOben = 28;
int motorUntenRichtungVorne = 29;
int motorUntenRichtungHinten = 30;
boolean WertOben;
boolean WertUnten;
int Laser1 = 1;
int Detector1 = 2;
int Laser2 = 3;
int Detector2 = 4;
int Laser3 = 5;
int Detector3 = 6;
int g;
int m;
int k;
boolean kugelgros;
boolean kugelmittel;
boolean kugelklein;
char kugelgroese;
#include <Servo.h> 
Servo servoblau;
Servo servogelb;
unsigned long previousMillis = 0;
const long intervall = 2000;
int tasterG=9;
int tasterstatusG=0;
int tasterM=10;
int tasterstatusM=0;
int tasterK=11;
int tasterstatusK=0;

//Setup aktiviert Ports
void setup() {
  Serial.begin (9600);
  pinMode(laserSender, OUTPUT);
  pinMode(laserEmpfaenger, INPUT);
  pinMode(motorgeschwindigkeit1, OUTPUT);
  pinMode(motorgeschwindigkeit2, OUTPUT);
  pinMode(motorObenRichtungUnten, OUTPUT);
  pinMode(motorObenRichtungOben, OUTPUT);
  pinMode(motorUntenRichtungVorne, OUTPUT);
  pinMode(motorUntenRichtungHinten, OUTPUT);
  pinMode(untererKippschalter, OUTPUT);
  pinMode(obererKippschalter, OUTPUT);
  pinMode(Laser1, OUTPUT);
  pinMode(Detector1, INPUT);
  pinMode(Laser2, OUTPUT);
  pinMode(Detector2, INPUT);
  pinMode(Laser3, OUTPUT);
  pinMode(Detector3, INPUT);
  servoblau.attach(7);
  servogelb.attach(8);
  pinMode(tasterG, INPUT);
  pinMode(tasterM, INPUT);
  pinMode(tasterK, INPUT);
}


//einzele Programmteile und Unterprogramme laufen ab
void loop() {
     laserScanner;
     aufzugFahrt;
     groesenScanner;
  }
  



 //ab hier Unterprogramme

void groesenScanner(){
  
     tasterstatusG=digitalRead(tasterG);
     tasterstatusM=digitalRead(tasterM);  //Die Tasterzustände werden abgefragt 
     tasterstatusK=digitalRead(tasterK);

   if (tasterstatusG == HIGH){  // Wenn der Taster für die großen Kugeln gedrückt ist und die Größe der gemessenen Kugel auch groß ist, wird die Schranke geöffnet und der Trenner leitet die Kugel zur nächsten Maschine

      if (kugelgroese == g){
        servogelbweiter;
        servoblauauf;
        servoblauzu;
      }else{
        servogelbraus;    //Wenn nicht, wird die Kugel ins Auffangbecken geleitet
        servoblauauf;
        servoblauzu;
      }
    
   }

   if (tasterstatusM == HIGH){  // Wenn der Taster für die mittleren Kugeln gedrückt ist und die Größe der gemessenen Kugel auch mittel ist, wird die Schranke geöffnet und der Trenner leitet die Kugel zur nächsten Maschine

      if (kugelgroese == m){
        servogelbweiter;
        servoblauauf;
        servoblauzu;
      }else{
        servogelbraus;  //Wenn nicht, wird die Kugel ins Auffangbecken geleitet
        servoblauauf;
        servoblauzu;
      }
}

void laserScanner(){
  digitalWrite(laserSender, HIGH); //Scanner wird aktiveiert
  boolean val = digitalRead(laserEmpfaenger); //Wert des Scanners wird ausgelesen
  Serial.println(val); //Wert wird in "val" abgespeichert


 while(val == 1){ //solange val den Wert 1  annimmt(Laser wird nicht blockiert), fährt der Schieber weiter
  digitalWrite(motorUntenRichtungVorne, HIGH); //-->Richtung
  digitalWrite(motorUntenRichtungHinten,LOW); //-->Richtung
  analogWrite(motorgeschwindigkeit1, 200); //--> Geschwindigkeit
 }
  digitalWrite(motorUntenRichtungVorne,LOW); //Motor stoppt
  digitalWrite(motorUntenRichtungHinten,LOW); //Motor stoppt
  
  //aufzugFahrt; //Aufzug fährt mit Kugel nach oben, läd sie aus und kehrt wieder an seine Anfangsposition

}

void aufzugFahrt(){

  digitalWrite(obererKippschalter, HIGH); //oberer Kippschalter wird aktiveiert
  WertOben = digitalRead(obererKippschalter); //Wert des Schalters wird ausgelesen
  Serial.println(WertOben); //Wert wird in "WertOben" abgespeichert
  
  while(WertOben == 1){ //solange WertOben den Wert 1  annimmt(Schalter offen ist), fährt der Aufzug weiter nach oben
    digitalWrite(motorObenRichtungOben, HIGH); //-->Richtung
    digitalWrite(motorObenRichtungUnten, LOW); //-->Richtung
    analogWrite(motorgeschwindigkeit2, 200); //--> Geschwindigkeit
  }
  digitalWrite(motorObenRichtungOben, LOW); //Motor stoppt
  digitalWrite(motorObenRichtungUnten, LOW); //Motor stoppt
  
  digitalWrite(untererKippschalter, HIGH); //unterer Kippschalter wird aktiveiert
  WertOben = digitalRead(untererKippschalter); //Wert des Schalters wird ausgelesen
  Serial.println(WertUnten); //Wert wird in "WertUnten" abgespeichert
  
   while(WertUnten == 1){ //solange WertUnten den Wert 1  annimmt(Schalter offen ist), fährt der Aufzug weiter nach unten
    digitalWrite(motorObenRichtungOben, LOW); //-->Richtung
    digitalWrite(motorObenRichtungUnten, HIGH); //-->Richtung
    analogWrite(motorgeschwindigkeit2, 200); //--> Geschwindigkeit
   }
  digitalWrite(motorObenRichtungOben, LOW); //Motor stoppt
  digitalWrite(motorObenRichtungUnten, LOW); //Motor stoppt
  
   //laserScanner; //nächste Kugel wird in den Aufzug gegeben
}
int IstKugelgros (){ //hier wird gemessen, ob die Kugel groß ist

  digitalWrite(Laser1, HIGH); //Laser1 misst, ob sich dort eib Objekt befindet
  boolean val1 = digitalRead(Detector1);
    if (val1 == 0){ //befindet sich dort ein Objekt, wird der Wert val1 = 0 gesetzt, ist dieser Null wird kugelgros = true gesetzt, weil die Kugel groß ist
      kugelgros = true;
    }else{
      kugelgros = false; // Wenn die Lichtschranke nicht durchbrochen wird, wird kugelgros = false gesetzt
    }
  return kugelgros; //kugelgros wird zurückgegeben 

}


int IstKugelmittel (){
  digitalWrite(Laser2, HIGH); //Laser2 misst, ob sich dort eib Objekt befindet
  boolean val2 = digitalRead(Detector2);
    if (val2 == 0){ //befindet sich dort ein Objekt, wird der Wert val2 = 0 gesetzt, ist dieser Null wird kugelklein = true gesetzt, weil die Kugel mittel ist
      kugelmittel = true;
    }else{
      kugelmittel = false;  // Wenn die Lichtschranke nicht durchbrochen wird, wird kugelmittel = false gesetzt
    }
  return kugelmittel; //kugelmittel wird zurückgegeben 

}


int IstKugelklein (){
  digitalWrite(Laser3, HIGH); //Laser3 misst, ob sich dort eib Objekt befindet
  boolean val3 = digitalRead(Detector3);
    if (val3 == 0){ //befindet sich dort ein Objekt, wird der Wert val3 = 0 gesetzt, ist dieser Null wird kugelklein = true gesetzt, weil die Kugel klein ist
      kugelklein = true;
    }else{
      kugelklein = false; // Wenn die Lichtschranke nicht durchbrochen wird, wird kugelklein = false gesetzt
    }
  return kugelklein;  //kugelklein wird zurückgegeben 

}


int sogrosistdieKugel () {  //Hier wird nun die Variabel kugelgroese deklariert
    if (kugelgros == true && kugelmittel == true && kugelklein == true) {
        kugelgroese = g;  //mit g (für Groß), falls alle Lichtschranken unterbrochen werden
    }
    
    if (kugelgros == false && kugelmittel == true && kugelklein == true) {
        kugelgroese = m;  //mit m (für Mittel), falls nur die zwei unteren Lichtschranken unterbrochen werden
    }

    if (kugelgros == false && kugelmittel == false && kugelklein == true) {
        kugelgroese = k;  //mit k (für Klein), falls nur die unterste Lichtschranke unterbrochen wird
    }
  return kugelgroese; //die Variable kugelgroese wird zurückgegeben
  
}


int servoblauauf(){ //Ein Servomotor dreht sich auf 180°
  
   servoblau.write(180);
 
}


int servoblauzu(){  //Ein Servomotor dreht sich auf 0°
  
  servoblau.write(0); 
   
}


int servogelbweiter(){  //Ein Servomotor dreht sich auf 20°

  servogelb.write(20);
  
}


int servogelbraus(){  //Ein Servomotor dreht sich auf 45°

  servogelb.write(45);
  
}
