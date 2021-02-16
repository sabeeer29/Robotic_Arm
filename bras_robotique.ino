#include <Servo.h>

double O1init=0,O2init=0, O3init=20;
double L1=0.1, L2=0.142, L3=0.242;
double Xcible, Ycible, Zcible;
double Xinit,Yinit,Zinit;
double O1cible, O2cible, O3cible;
Servo myServo1, myServo2, myServo3, myServo4,myServo5;
double pos;

void setup() {
 myServo1.attach(10);
 myServo2.attach(9);
 myServo3.attach(6);
 myServo4.attach(5);
 myServo5.attach(3);
 Serial.begin(9600);
}


void goto_angle (double Odep, double Ofin, Servo myServo)
{ if (Ofin> Odep) 
    { for (pos=Odep ; pos <= Ofin; pos++) 
          {myServo.write(pos);           
          delay(15);}
      for (pos=Ofin; pos >= Odep; pos--)
          {myServo.write(pos);             
          delay(15); }
     }
                    
else if (Ofin < Odep) 
    { for (pos=Ofin; pos >= Odep; pos--) 
          {myServo.write(pos);             
           delay(15); }
      for (pos=Odep ; pos <= Ofin; pos++) 
           {myServo.write(pos);           
           delay(15);}
     }

else return;                 
}

void tube ( Servo myServo) // pour verser le contenu du tube
{   myServo.write(0);
    for (pos=0 ; pos <= 90; pos++)// verser le contenu du tube 
                    {myServo.write(pos);           
                    delay(15);}
    for (pos=90; pos >= 0; pos--) // retour a la position initiale
                      {    myServo.write(pos);             
                      delay(15); }
}


void pince (Servo myServo)// pour ouvrir et fermer le pince
{ myServo.write (150);
  for (pos=150 ; pos <= 180; pos++)// fermer le pince
                    {myServo.write(pos);           
                    delay(15);}
    for (pos=180; pos >= 150; pos--) // ouvrir le pince
                      {    myServo.write(pos);             
                      delay(15); }
}


void loop() {
  
int i=0;

while(1){
if (Serial.available()>0)
  {if(i==0)
    { Serial.println("entrer Xcible");
      Xcible= Serial.parseInt()/100;
      Serial.println(Xcible);
    }
      i++;
  }
 else if(i==1)
   {
    Serial.println("entrer Ycible");
    Ycible= Serial.parseInt()/100;
    Serial.println(Ycible);
    i++;
   }
 else if(i==2)
   {
    Serial.println("entrer Zcible");
    Zcible= Serial.parseInt()/100;
    Serial.println(Zcible);
    i++;
   }
else if(i==3){
 O1init=map(O1init,0,180,0,3.14);
 O2init=map(O2init,0,180,0,3.14);
 O3init=map(O3init,0,180,0,3.14);

 Xinit=(L2*cos(O21init)+L3*cos(O3init))*cos(O1init);
 Yinit=(L2*cos(O2init)+L3*cos(O3init))*sin(O1init);
 Zinit= L1+L2*sin(O2init)+L3*sin(O3init);
 
 O1cible= O1init + (-sin(O1init)/(L2*cos(O1init)*cos(O1init)*sin(O2init) + L3*cos(O1init)*cos(O1init)*sin(O3init) + L2*sin(O1init)*sin(O1init)*sin(O2init) + L3*sin(O1init)*sin(O1init)*sin(O3init)))*(Xcible-Xinit)+ (cos(O1init)/(L2*cos(O1init)*cos(O1init)*sin(O2init) + L3*cos(O1init)*cos(O1init)*sin(O3init) + L2*sin(O1init)*sin(O1init)*sin(O2init) + L3*sin(O1init)*sin(O1init)*sin(O3init)))*(Ycible - Yinit);
 O2cible= O2init +(cos(O1init)/(2*(L2*cos(O2init)*cos(O1init)*cos(O1init) + L2*cos(O2init)*sin(O1init)*sin(O1init))))*(Xcible -Xinit)+(sin(O1init)/(2*(L2*cos(O2init)*cos(O1init)*cos(O1init) + L2*cos(O2init)*sin(O1init)*sin(O1init))))*(Ycible-Yinit)+(1/(2*L2*cos(O2init)))*(Zcible-Zinit);
 O3cible= O3init +(cos(O1init)/(2*(L3*cos(O3init)*cos(O1init)*cos(O1init) + L3*cos(O3init)*sin(O1init)*sin(O1init))))*(Xcible-Xinit)+(sin(O1init)/(2*(L3*cos(O3init)*cos(O1init)*cos(O1init) + L3*cos(O3init)*sin(O1init)*sin(O1init))))*(Ycible-Yinit)+(-1/(2*L3*cos(O3init)))*(Zcible-Zinit);

 O1cible=map(O1cible,0,3.14,0,180);
 O2cible=map(O2cible,0,3.14,0,180);
 O3cible=map(O3cible,0,3.14,0,180);
   
 if ((O1cible> 180)||(O1cible<0)) Serial.print(" erreur O1cible depasse la limite");
 else if ((O2cible<0)||(O2cible>40)) Serial.print (" erreur O2cible depasse la limite");
 else if ((O3cible>70)||(O3cible<20)) Serial.print(" erreur O3cible depasse la limite ");
 else {   
goto_angle (O1init,O1cible,myServo1);
goto_angle (O2init,O2cible,myServo2);
goto_angle (O3init,O3cible,myServo3);
tube (myServo4);
pince (myServo5); 
 }}
 i=0;
// while(1);
    }}
