#include<Servo.h>
#include <DS3231.h>

//Download DS3231 library from - http://www.rinkydinkelectronics.com/library.php?id=73

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);




int servo1= 9;
int servo2=10;
int posx=0,posy=170,i;
int button=7,bv;
Servo first;
Servo Second;
 

void setup() {
  // put your setup code here, to run once:
//  pinMode(photo,INPUT);
  Serial.begin(9600);
  first.attach(servo1);
  Second.attach(servo2);
  pinMode(button,INPUT);
  digitalWrite(button,HIGH);
  
 
  rtc.begin();
  
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(SUNDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(14, 27, 55);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(21, 12, 2020);
  
}

//void(* resetFunc)(void)  =0;

void loop() {
  // put your main code here, to run repeatedly:
  i=1;
  
  
  
  String timer=rtc.getTimeStr(); 

  bv=digitalRead(button);

//Change time here 
  if(timer=="07:00:00"||bv==0)
  {
    if(bv==0)
    {

     i=2;
    }

  //Here 2 is the number of times the servo is in motion
    for(;i<=2;i++)
     {
   
      first.write(posy);

       delay(2000);

      first.write(posx);

       delay(2000);

   
      }
 first.write(posy);
 delay(3000);


 if(bv==0)
   {

    i=2;
   }

 else
    i=1;
 
 for(;i<=2;i++)
 {
   
   Second.write(posy);

   delay(2000);

   Second.write(posx);

   delay(2000);
}

Second.write(posy);
delay(500);
}



}
