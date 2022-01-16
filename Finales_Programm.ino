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

void loop() {
     laserScanner;
     tasterstatusG=digitalRead(tasterG);
     tasterstatusM=digitalRead(tasterM);
     tasterstatusK=digitalRead(tasterK);

   if (tasterstatusG == HIGH){

      if (kugelgroese == g){
        servogelbweiter;
        servoblauauf;
        servoblauzu;
      }else{
        servogelbraus;
        servoblauauf;
        servoblauzu;
      }
    
   }

   if (tasterstatusM == HIGH){

      if (kugelgroese == m){
        servogelbweiter;
        servoblauauf;
        servoblauzu;
      }else{
        servogelbraus;
        servoblauauf;
        servoblauzu;
      }
    
   }

   if (tasterstatusK == HIGH){
      
      if (kugelgroese == k){
        servogelbweiter;
        servoblauauf;
        servoblauzu;
      }else{
        servogelbraus;
        servoblauauf;
        servoblauzu;
      }
    
   }
  }
  
 //ab hier Unterprogramme

void laserScanner(){
  digitalWrite(laserSender, HIGH);
  boolean val = digitalRead(laserEmpfaenger);
  Serial.println(val);


 while(val == 1){
  digitalWrite(motorUntenRichtungVorne, HIGH);
  digitalWrite(motorUntenRichtungHinten,LOW);
  analogWrite(motorgeschwindigkeit1, 200);
 }
  digitalWrite(motorUntenRichtungVorne,LOW);
  digitalWrite(motorUntenRichtungHinten,LOW);
  
  aufzugFahrt;

}

void aufzugFahrt(){

  digitalWrite(obererKippschalter, HIGH);
  WertOben = digitalRead(obererKippschalter);
  Serial.println(WertOben);
  
  while(WertOben == 1){
    digitalWrite(motorObenRichtungOben, HIGH);
    digitalWrite(motorObenRichtungUnten, LOW);
    analogWrite(motorgeschwindigkeit2, 200);
  }
  digitalWrite(motorObenRichtungOben, LOW);
  digitalWrite(motorObenRichtungUnten, LOW);
  
  digitalWrite(untererKippschalter, HIGH);
  WertOben = digitalRead(untererKippschalter);
  Serial.println(WertUnten);
  
   while(WertUnten == 1){
    digitalWrite(motorObenRichtungOben, LOW);
    digitalWrite(motorObenRichtungUnten, HIGH);
    analogWrite(motorgeschwindigkeit2, 200);
   }
  digitalWrite(motorObenRichtungOben, LOW);
  digitalWrite(motorObenRichtungUnten, LOW);
  
   laserScanner; 
}
int IstKugelgros (){

  digitalWrite(Laser1, HIGH);
  boolean val1 = digitalRead(Detector1);
    if (val1 == 0){
      kugelgros = true;
    }else{
      kugelgros = false;
    }
  return kugelgros;

}


int IstKugelmittel (){
  digitalWrite(Laser2, HIGH);
  boolean val2 = digitalRead(Detector2);
    if (val2 == 0){
      kugelmittel = true;
    }else{
      kugelmittel = false;
    }
  return kugelmittel;

}


int IstKugelklein (){
  digitalWrite(Laser3, HIGH);
  boolean val3 = digitalRead(Detector3);
    if (val3 == 0){
      kugelklein = true;
    }else{
      kugelklein = false;
    }
  return kugelklein;

}


int sogrosistdieKugel () {
    if (kugelgros == true && kugelmittel == true && kugelklein == true) {
        kugelgroese = g;
    }
    
    if (kugelgros == false && kugelmittel == true && kugelklein == true) {
        kugelgroese = m;
    }

    if (kugelgros == false && kugelmittel == false && kugelklein == true) {
        kugelgroese = k;
    }
  return kugelgroese;
  
}


int servoblauauf(){
  
   servoblau.write(180);
 
}


int servoblauzu(){
  
  servoblau.write(0); 
   
}


int servogelbweiter(){

  servogelb.write(20);
  
}


int servogelbraus(){

  servogelb.write(45);
  
}
