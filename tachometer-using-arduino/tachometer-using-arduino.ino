#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,6,5,4,3);
float value=0;
float rev=0;
int rpm;
int oldtime=0;
int time;
int count;

void isr() //interrupt service routine
{
  count++;
  if(count==20)
{rev++;
count=0;
}
}

void setup()
{
lcd.begin(16,2);                //initialize LCD
attachInterrupt(0,isr,RISING);  //attaching the interrupt
pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
}

void loop()
{
  
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  analogWrite(10,50);
delay(150);
detachInterrupt(0);           //detaches the interrupt
time=millis()-oldtime;        //finds the time
rpm=(rev/time)*3600;         //calculates rpm
oldtime=millis();             //saves the current time
rev=0;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("___RPM METER___");
lcd.setCursor(0,1);
lcd.print(     rpm);
lcd.print(" RPM");
lcd.print("   ");
attachInterrupt(0,isr,RISING);

}
