
// Include the Servo library 
#include <Servo.h> 
// Create a servo object 
Servo Servo1; 
Servo Servo2; 

// partie LCD--------------------------------------------------------------------------
#include<LiquidCrystal.h>
const int rs = 12, e= 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

//Capteur de température---------------------------------------------------------------
/*const int sensor=A8; // Assigning analog pin A8 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius
float vout;  //temporary variable to hold sensor reading*/

//Clavier------------------------------------------------------------------------------
#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {37 , 36, 35 , 34};
byte colPins[COLS] =  {33 , 32, 31};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


// Declare the Servo pin 
int servoPin1 = 7; 
int servoPin2 = 8; 


/////////////////////////////////////////////////////////////////////////////////////
 
//Bouton de démarrage ---------------------------------------------------------------
const int Bouton = 30;
int EN = 0;

//password----------------------------------------------------------------------------
const String password = "777"; // change your password here
String input_password;
String input_password1;

char key;
int test=0;
int keytest = 0;

/////////////////////////////////////////////////////////////////////////////////////////

//Sortie tout ou rien --------------------------------------------------------------------
 
const int lampe1220v = 25;
//const int lampe2220v = 26;
const int servo1alim = 26;
const int lampe2220v = 27;
//const int lampe2220v = 26;
const int servo2alim = 28;

int etatlampe = 0;
const int vent12v = 24;



void setup()
{
Serial.begin(9600);

 // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin1); 
    Servo2.attach(servoPin2); 

//-capteur température------------------------------------------------------------------
//pinMode(sensor,INPUT); // Configuring pin A8 as input


//Bouton de démarrage--------------------------------------------------------------------
pinMode(Bouton,INPUT); // Configuring pin A1 as input
//pinMode(BoutonL,INPUT); // Configuring pin A1 as input

//LCD-messages-initial-et démarrage par mot de pass pui bouton --------------------------------------------------------------------------------
lcd.begin(16,2);  
  delay(500);
  //lcd.clear();
lcd.setCursor(0,0);
lcd.print("PFE Asma Hamdi");
Serial.println("PFE Asma Hamdi");
delay(1500); 


//password----------------------------------------------------------------------------

input_password.reserve(32); // maximum input characters is 33, change if needed
input_password1.reserve(32); 

lcd.clear();
lcd.setCursor(0,0);
lcd.print("entrez mot de passe:");
Serial.println("entrez mot de passe:");
do
{
  char key = keypad.getKey();

  if (key){
    //Serial.println(key);

    //if(key == '*') {
                    //input_password1 = ""; // clear input password
                  // } else
     if(key == '#') {
                            if(input_password  == password) 
                              {
                               lcd.clear();
                               lcd.setCursor(0,0);
                               lcd.print("Mot.de.passe correct merci"); 
                               Serial.println("Mot.de.passe correct merci");
                               delay(1500);
                               test=1;
                               //Serial.println("password is correct");
                
                              } 
                             else 
                             {
                               lcd.clear();
                               lcd.setCursor(0,0);
                               lcd.print("Motd.passe.incorrectressayez.de.nouveau");
                                Serial.println ("Motd.passe.incorrectressayez.de.nouveau"); 
                               // Serial.println("password is incorrect, try again");
                            //}

                             input_password = ""; // clear input password
                             input_password1 = "";
                             
                            } 
                        }
         else {
                  input_password += key; // append new character to input password string
                 input_password1 += '*';
                                       lcd.clear();
                                       lcd.setCursor(0,0);
                                       lcd.print("Mot.d.passe = ");
                                       Serial.println("Mot.d.passe = ");
                                       
                                       lcd.print(input_password1);
                                        Serial.println(input_password1);
                 
              }
           }
}
while(test==0);

//End password----------------------------------------------------------------------------

//bouton de démarrage---------------------------------------------------------------------
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Appuiez Bouton de   demarrage"); 
 Serial.println("Appuiez Bouton de   demarrage");
 do
{EN=digitalRead(Bouton);}
while (EN == LOW);

//afichage température avant demande de la consigne
/*vout=analogRead(sensor);
vout=(vout*500)/1023;
tempc=vout; // Storing value in Degree Celsius
lcd.clear();
lcd.setCursor(0,0);
lcd.print("la temperature      actuelle = ");
lcd.print(tempc);
delay(1500); */






// Fin Bouton de démarrage --> début du fonctionneent ------------------------------------------------------------------

// lampe et servo -----------------------------------------

pinMode(vent12v,OUTPUT); // Configuring pin A1 as OUTPUT
pinMode(lampe1220v,OUTPUT); // Configuring pin A1 as OUTPUT
pinMode(lampe2220v,OUTPUT); // Configuring pin A1 as OUTPUT


pinMode(servo1alim,OUTPUT); // Configuring pin A1 as OUTPUT
pinMode(servo2alim,OUTPUT); // Configuring pin A1 as OUTPUT
digitalWrite(servo1alim,HIGH);
digitalWrite(servo2alim,HIGH);

// ommencer le test -----------------------------------------
lcd.clear();
lcd.setCursor(0,0);
lcd.print("vouspouvez commencer le test"); 
 Serial.println("vouspouvez commencer le test");
delay(2000); 
/*
test=0;
input_password = ""; // clear input password
do
{
  char key = keypad.getKey();
  if (key){          
            if(key == '#') {
                              if (keytest == 1) {
                              input_password = ""; // clear input password
                              lcd.clear();
                              lcd.setCursor(0,0);
                              lcd.print("etat lamp incorrect   essayez de nouveau");    
                              //delay (1500); 
                              keytest = 0;
                              test = 0;         } 
                    

                              else
                                    {
                                       lcd.clear();
                                       lcd.setCursor(0,0);
                                       lcd.print("configuration acheve    Merci"); 
                                       delay(1500);
                                       test=1; 
                                    }
                             }
                               
                             
          
              else {
                 
                  /*if (!(key == '#'))*/  
                   /*                    input_password = key; // append new character to input password string
                                       
                                       etatlampe = input_password.toInt();
                                       if (!((key == '0')or(key == '1'))) { keytest = 1;}
                                       lcd.clear();
                                       lcd.setCursor(0,0);
                                       lcd.print("etat lampe = ");
                                       lcd.print(input_password);
                                       //delay(1500); //Delay of 1 second for ease of viewing in serial monitor
                 }
      }             
  }


while(test==0);

if (etatlampe==1)
{digitalWrite(lampe220v, HIGH);}
else {
digitalWrite(lampe220v, LOW);}*/
//End configuration etat lampe d'allumage---------------------------------------------------------------------------- 




 
}


void loop() 
{

/*vout=analogRead(sensor);
vout=(vout*500)/1023;
tempc=vout; // Storing value in Degree Celsius
lcd.clear();
lcd.setCursor(0,0);
lcd.print("la temperature      actuelle = ");
lcd.print(tempc);
delay(1500); */

// lecture et affichage température-------------------------------------------------------
/*vout=analogRead(sensor);
vout=(vout*500)/1023;
tempc=vout; // Storing value in Degree Celsius
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Temperature = ");
lcd.print(tempc);
lcd.setCursor(0,1);


delay(500); //Delay of 1 second for ease of viewing in serial monitor */
// Fin lecture et affichage température-------------------------------------------------------




//bouton Lampe---------------------------------------------------------------------
//EN1=digitalRead(BoutonL);
//if (EN1 == HIGH) {
etatlampe = (!etatlampe);
digitalWrite(lampe1220v, etatlampe);
digitalWrite(lampe2220v, etatlampe);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Testen cours");
Serial.println("Testen cours"); 
delay(1500);

// Fin Bouton Lampe ------------------------------------------------------------------*/

//SERVO

 // Make servo go to 0 degrees 
   Servo1.write(0); 
   Servo2.write(0); 
   delay(1000); 
   // Make servo go to 90 degrees 
   Servo1.write(90);
   Servo2.write(90); 
   delay(1000); 
   // Make servo go to 180 degrees 
   Servo1.write(180); 
   Servo2.write(180); 
   delay(1000); 
  //fin servo



/*delay(1000);
digitalWrite(lampe220v, HIGH);
delay(1500);
digitalWrite(triac, LOW);
delay(1500);
digitalWrite(vent12v, LOW);
delay(1500);
digitalWrite(lampe220v, LOW);
delay(1500);*/


/*lcd.clear();
lcd.setCursor(0,0);
lcd.print("Introduisez valeur  consigne"); 
do
{
char key = keypad.getKey();

if (key){
    lcd.print(key);
  }
}
  while (not key);*/
  
  //delay(1000);



 
}
