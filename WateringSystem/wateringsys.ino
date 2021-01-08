
#include<EEPROM.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <DS3231.h>

// Init the DS3231 using the hardware interface
DS3231  rtc(20, 21);

Adafruit_SSD1306 display(-1);


int soilspin=A7;
int moisture;
int menubt=A0;
int exitbt=A1;
int xpin=A3;
int ypin=A4;
int swpin=A5;
int pgvalue,pgvalue2,pgvalue3;
int xvalue;
int yvalue;
int en1=3;
float mspeed=255;

//dirrectiion
int IN1=2;
int IN2=7;



void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  pinMode(en1,OUTPUT);
   pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
  
 pinMode(menubt,INPUT);
 digitalWrite(menubt,HIGH);
 pinMode(xpin,INPUT);
 pinMode(ypin,INPUT);
 pinMode(swpin,INPUT);
 digitalWrite(swpin,HIGH);
 digitalWrite(exitbt,HIGH);
 
 
  Serial.begin(9600);
    rtc.begin();
  
  // The following lines can be uncommented to set the date and time
 //rtc.setDOW(TUESDAY);     // Set Day-of-Week to SUNDAY
 //rtc.setTime(20, 14, 0);     // Set the time to 12:00:00 (24hr format)
 // rtc.setDate(29, 12, 2020);   // Set the date to January 1st, 2014

   
}

void SETTIME()
{
   pgvalue3=0;
  while(true)
  { 
     
    int exitvalue=digitalRead(exitbt);
  
    if(exitvalue==0)
     {
      
      break;
      
     }

    switch(pgvalue3)
    {  
      
       
       case 0:   display.clearDisplay();
                 display.setTextSize(1);
                 display.setTextColor(WHITE);
                 display.setCursor(0,0);
                 display.println("    <  SET TIME  >");
                 display.setCursor(0,8);
                 display.setTextColor(BLACK,WHITE);
                 display.println("=>Timer(1)");
                 display.setTextColor(WHITE);
                 display.setCursor(0,16);
                 display.println("=>Timer(2)");
                 display.setTextColor(WHITE);
                 display.setCursor(0,24);
                 display.println("=>Timer(3)");
                 display.setCursor(80,8);
                 display.setTextColor(BLACK,WHITE);
                 
                 
                 yvalue= analogRead(ypin);
                 //delay(500);
                 
                 if(yvalue<100)
                  {
                    EEPROM.write(6,1);
                        
                  }
                  if(yvalue>900)
                      EEPROM.write(6,0);

                  if(EEPROM.read(6)==0)
                       display.println("deactive");

                  else if(EEPROM.read(6)==1)
                      display.println("active");      
                      
                  display.display();
                  
                if(digitalRead(swpin)==0)
                { 
                  int tswitch=0;
                  int h=7,s=0;
                  while(true)
                  {
                    int exitvalue=digitalRead(exitbt);

                     if(exitvalue==0)
                         {
      
                           break;
      
                             }

                   switch(tswitch)
                    {  
                      case 0:    display.clearDisplay();
                                 display.setTextSize(2);
                                 display.setTextColor(WHITE);
                                 display.setCursor(20,10);
                                 display.println("  h::  m");
                                 display.setTextColor(BLACK,WHITE);
                                 display.setCursor(15,10);
                                 display.println(h);
                                 display.setTextColor(WHITE);
                                 display.setCursor(80,10);
                                 display.println(s);
                                 display.display();
                                 
                                  xvalue= analogRead(xpin);
                                  yvalue= analogRead(ypin);

                                  if(yvalue<100 || yvalue>900)
                                    { 
                                         tswitch=1;
                      
                                        delay(500);
                                    }   

                                                 
                                   if(xvalue>900 && h>0)
                                      { 
                    
                                          h--;

                                          delay(500); 
                                       }   


                                    if(xvalue<100 && h<24)

                                      {
                                           h++;
                    
                      

                                      delay(500); 
                    
                                      }

                                      break;

                      case 1:    display.clearDisplay();
                                 display.setTextSize(2);
                                 display.setTextColor(WHITE);
                                 display.setCursor(20,10);
                                 display.println("  h::  m");
                                 display.setTextColor(WHITE);
                                 display.setCursor(15,10);
                                 display.println(h);
                                 display.setTextColor(BLACK,WHITE);
                                 display.setCursor(80,10);
                                 display.println(s);
                                 display.display();
                                 
                                  xvalue= analogRead(xpin);
                                  yvalue= analogRead(ypin);
                                  
                                  if(yvalue<100 || yvalue>900)
                                    { 
                                         tswitch=0;
                      
                                        delay(500);
                                    }   

                                                 
                                   if(xvalue>900 && s>0)
                                      { 
                    
                                          s--;

                                          //delay(500); 
                                       }   


                                    if(xvalue<100 && s<59)

                                      {
                                           s++;
                    
                      

                                    //  delay(500); 
                    
                                      }               
                            }
                             if(digitalRead(swpin)==0)
                               {
                                 EEPROM.write(0,h);
                                 EEPROM.write(1,s);
                                 display.clearDisplay();
                                 display.setTextSize(2);
                                 display.setTextColor(WHITE);
                                 display.setCursor(0,0);
                                 display.println("Changes saved!");
                                 display.display();
                                 delay(2000);
                                 break;
                               }
                         
                    
                  }
                }
       
               xvalue= analogRead(xpin);
               if(xvalue>900)
                   { pgvalue3++;
                    
                      

                   //  delay(500); 
                   }   


               if(xvalue<100)

                  {
                    pgvalue3=2;
                    
                      

                     // delay(500); 
                    
                  }

               break;

       case 1:    
                 display.clearDisplay();
                 display.setTextSize(1);
                 display.setTextColor(WHITE);
                 display.setCursor(0,0);
                 display.println("    <  SET TIME  >");
                 display.setCursor(0,8);
                 display.setTextColor(WHITE);
                 display.println("=>Timer(1)");
                 display.setTextColor(BLACK,WHITE);
                 display.setCursor(0,16);
                 display.println("=>Timer(2)");
                 display.setTextColor(WHITE);
                 display.setCursor(0,24);
                 display.println("=>Timer(3)");
                  display.setCursor(80,16);
                 display.setTextColor(BLACK,WHITE);
                 
                 
                 yvalue= analogRead(ypin);
                 //delay(500);
                 
                 if(yvalue<100)
                  {
                    EEPROM.write(7,1);
                        
                  }
                  if(yvalue>900)
                      EEPROM.write(7,0);

                  if(EEPROM.read(7)==0)
                       display.println("deactive");

                  else if(EEPROM.read(7)==1)
                      display.println("active");      
                      
                  display.display();
               xvalue= analogRead(xpin);
                 if(digitalRead(swpin)==0)
                { 
                  int tswitch=0;
                  int h=7,s=0;
                  while(true)
                  {
                    int exitvalue=digitalRead(exitbt);

                     if(exitvalue==0)
                         {
      
                           break;
      
                             }

                   switch(tswitch)
                    {  
                      case 0:    display.clearDisplay();
                                 display.setTextSize(2);
                                 display.setTextColor(WHITE);
                                 display.setCursor(20,10);
                                 display.println("  h::  m");
                                 display.setTextColor(BLACK,WHITE);
                                 display.setCursor(15,10);
                                 display.println(h);
                                 display.setTextColor(WHITE);
                                 display.setCursor(80,10);
                                 display.println(s);
                                 display.display();
                                 
                                  xvalue= analogRead(xpin);
                                  yvalue= analogRead(ypin);

                                  if(yvalue<100 || yvalue>900)
                                    { 
                                         tswitch=1;
                      
                                        delay(500);
                                    }   

                                                 
                                   if(xvalue>900 && h>0)
                                      { 
                    
                                          h--;

                                          delay(500); 
                                       }   


                                    if(xvalue<100 && h<24)

                                      {
                                           h++;
                    
                      

                                      delay(500); 
                    
                                      }

                                      break;

                      case 1:    display.clearDisplay();
                                 display.setTextSize(2);
                                 display.setTextColor(WHITE);
                                 display.setCursor(20,10);
                                 display.println("  h::  m");
                                 display.setTextColor(WHITE);
                                 display.setCursor(15,10);
                                 display.println(h);
                                 display.setTextColor(BLACK,WHITE);
                                 display.setCursor(80,10);
                                 display.println(s);
                                 display.display();
                                 
                                  xvalue= analogRead(xpin);
                                  yvalue= analogRead(ypin);
                                  
                                  if(yvalue<100 || yvalue>900)
                                    { 
                                         tswitch=0;
                      
                                        delay(500);
                                    }   

                                                 
                                   if(xvalue>900 && s>0)
                                      { 
                    
                                          s--;

                                          //delay(500); 
                                       }   


                                    if(xvalue<100 && s<59)

                                      {
                                           s++;
                    
                      

                                    //  delay(500); 
                    
                                      }               
                            }
                             if(digitalRead(swpin)==0)
                               {
                                 EEPROM.write(2,h);
                                 EEPROM.write(3,s);
                                 display.clearDisplay();
                                 display.setTextSize(2);
                                 display.setTextColor(WHITE);
                                 display.setCursor(0,0);
                                 display.println("Changes saved!");
                                 display.display();
                                 delay(2000);
                                 break;
                               }
                         
                    
                  }
                }
               if(xvalue>900)
                   { pgvalue3++;
                     
                     

                    // delay(500); 
                   }  

               else if(xvalue<100)
                   { 
                     pgvalue3--;
                     
 
                   //  delay(500);     
                   }

               

                 break;


        case 2:  
                 display.clearDisplay();
                 display.setTextSize(1);
                 display.setTextColor(WHITE);
                 display.setCursor(0,0);
                 display.println("    <  SET TIME  >");
                 display.setCursor(0,8);
                 display.setTextColor(WHITE);
                 display.println("=>Timer(1)");
                 display.setTextColor(WHITE);
                 display.setCursor(0,16);
                 display.println("=>Timer(2)");
                 display.setTextColor(BLACK,WHITE);
                 display.setCursor(0,24);
                 display.println("=>Timer(3)");
                 
                  display.setCursor(80,24);
                 display.setTextColor(BLACK,WHITE);
                 
                 
                 yvalue= analogRead(ypin);
                 //delay(500);
                 
                 if(yvalue<100)
                  {
                    EEPROM.write(8,1);
                        
                  }
                  if(yvalue>900)
                      EEPROM.write(8,0);

                  if(EEPROM.read(8)==0)
                       display.println("deactive");

                  else if(EEPROM.read(8)==1)
                      display.println("active");      
                      
                  display.display();

                  xvalue= analogRead(xpin);
                  if(digitalRead(swpin)==0)
                { 
                  int tswitch=0;
                  int h=7,s=0;
                  while(true)
                  {
                    int exitvalue=digitalRead(exitbt);

                     if(exitvalue==0)
                         {
      
                           break;
      
                             }

                   switch(tswitch)
                    {  
                      case 0:    display.clearDisplay();
                                 display.setTextSize(2);
                                 display.setTextColor(WHITE);
                                 display.setCursor(20,10);
                                 display.println("  h::  m");
                                 display.setTextColor(BLACK,WHITE);
                                 display.setCursor(15,10);
                                 display.println(h);
                                 display.setTextColor(WHITE);
                                 display.setCursor(80,10);
                                 display.println(s);
                                 display.display();
                                 
                                  xvalue= analogRead(xpin);
                                  yvalue= analogRead(ypin);

                                  if(yvalue<100 || yvalue>900)
                                    { 
                                         tswitch=1;
                      
                                        delay(500);
                                    }   

                                                 
                                   if(xvalue>900 && h>0)
                                      { 
                    
                                          h--;

                                          delay(500); 
                                       }   


                                    if(xvalue<100 && h<24)

                                      {
                                           h++;
                    
                      

                                      delay(500); 
                    
                                      }

                                      break;

                      case 1:    display.clearDisplay();
                                 display.setTextSize(2);
                                 display.setTextColor(WHITE);
                                 display.setCursor(20,10);
                                 display.println("  h::  m");
                                 display.setTextColor(WHITE);
                                 display.setCursor(15,10);
                                 display.println(h);
                                 display.setTextColor(BLACK,WHITE);
                                 display.setCursor(80,10);
                                 display.println(s);
                                 display.display();
                                 
                                  xvalue= analogRead(xpin);
                                  yvalue= analogRead(ypin);
                                  
                                  if(yvalue<100 || yvalue>900)
                                    { 
                                         tswitch=0;
                      
                                        delay(500);
                                    }   

                                                 
                                   if(xvalue>900 && s>0)
                                      { 
                    
                                          s--;

                                          //delay(500); 
                                       }   


                                    if(xvalue<100 && s<59)

                                      {
                                           s++;
                    
                      

                                    //  delay(500); 
                    
                                      }               
                            }
                             if(digitalRead(swpin)==0)
                               {
                                 EEPROM.write(4,h);
                                 EEPROM.write(5,s);
                                 display.clearDisplay();
                                 display.setTextSize(2);
                                 display.setTextColor(WHITE);
                                 display.setCursor(0,0);
                                 display.println("Changes saved!");
                                 display.display();
                                 delay(2000);
                                 break;
                               }
                         
                    
                  }
                }
       
               if(xvalue<100)
                   { pgvalue3--;
                     
                      
                   //  delay(500);
                   }   

               if(xvalue>900)
                   { 
                     pgvalue3=0;
                     
 
                     // delay(500);     
                   }                        
    
      }
  }
  
}

void MANUAL()
{
  int dura=40;
  while(true)
  { 
    
    int exitvalue=digitalRead(exitbt);
  
    if(exitvalue==0)
     {
      
      break;
      
     }
          xvalue= analogRead(xpin);
       
               if(xvalue>900 && dura>15)
                   { dura--;
                     
                     

                      
                   }  

               else if(xvalue<100)
                   { 
                     dura++;
                     
 
                          
                   }
     

                 display.clearDisplay();
                 display.setTextSize(1);
                 display.setTextColor(WHITE);
                 display.setCursor(0,0);
                 display.println(" <  MANUAL CONTROL  >");
                 display.setCursor(0,11);
                 display.setTextColor(BLACK,WHITE);
                 display.println("Press Joyst to start");
                 display.setTextSize(1);
                 display.setTextColor(WHITE);
                 display.setCursor(0,21);
                 display.println("=>Duration(sec):");
                 display.setCursor(100,21);
                 display.print(dura);
                 display.display(); 
                 
                 if(digitalRead(swpin)==0)
                  {
                     int counter=0;
                     int duration=dura*1000;
                     digitalWrite(IN1,3.3);
                     digitalWrite(IN2,LOW);

                     analogWrite(en1,255);

                   while(counter<=dura)
                   {
                     display.clearDisplay();
                     display.setTextSize(2);
                     display.setTextColor(WHITE);
                     display.setCursor(8,8);
                     display.println(counter);
                     display.setCursor(30,8);
                     display.println(" s /");
                     display.setCursor(90,8);
                     display.println(dura);
                     display.display();
                     delay(1000);
                     counter++;
                   }
                     
                    }

                 else
                   {
                       analogWrite(en1,0);
  
                   }   
  }
}

void SETDUR()
{
  
  pgvalue2=0;
  while(true)
  { 
     
    int exitvalue=digitalRead(exitbt);
  
    if(exitvalue==0)
     {
      
      break;
      
     }

    switch(pgvalue2)
    {  
      
       
       case 0:   display.clearDisplay();
                 display.setTextSize(1);
                 display.setTextColor(WHITE);
                 display.setCursor(0,0);
                 display.println(" <  SET DURATION  >");
                 display.setCursor(0,8);
                 display.setTextColor(BLACK,WHITE);
                 display.println("=>Seeds        (30s)");
                 display.setTextColor(WHITE);
                 display.setCursor(0,16);
                 display.println("=>Plant        (1min)");
                 display.setTextColor(WHITE);
                 display.setCursor(0,24);
                 display.println("=>Custom");
                 
                 display.display();

                if(digitalRead(swpin)==0)
                  { 
                    EEPROM.write(9,0);
                    EEPROM.write(10,30);
                    display.clearDisplay();
                    display.setTextSize(2);
                    display.setTextColor(WHITE);
                    display.setCursor(0,0);
                    display.println("DURATION  SET!");
                    
                    display.display();
                    delay(2000);
                    
                    
                  }
               xvalue= analogRead(xpin);
               if(xvalue>900)
                   { pgvalue2++;
                    
                      

                     delay(500); 
                   }   


               if(xvalue<100)

                  {
                    pgvalue2=2;
                    
                      

                      delay(500); 
                    
                  }

               break;

       case 1:    
                 display.clearDisplay();
                 display.setTextSize(1);
                 display.setTextColor(WHITE);
                 display.setCursor(0,0);
                 display.println(" <  SET DURATION  >");
                 display.setCursor(0,8);
                 display.setTextColor(WHITE);
                 display.println("=>Seeds        (30s)");
                 display.setTextColor(BLACK,WHITE);
                 display.setCursor(0,16);
                 display.println("=>Plant        (1min)");
                 display.setTextColor(WHITE);
                 display.setCursor(0,24);
                 display.println("=>Custom");
                 
                 display.display();

                 if(digitalRead(swpin)==0)
                  { 
                    EEPROM.write(9,1);
                    EEPROM.write(10,0);
                    display.clearDisplay();
                    display.setTextSize(2);
                    display.setTextColor(WHITE);
                    display.setCursor(0,0);
                    display.println("DURATION  SET!");
                    
                    display.display();
                    delay(2000);
                    
                    
                  }
               xvalue= analogRead(xpin);
       
               if(xvalue>900)
                   { pgvalue2++;
                     
                     

                     delay(500); 
                   }  

               else if(xvalue<100)
                   { 
                     pgvalue2--;
                     
 
                     delay(500);     
                   }

               

                 break;


        case 2:  
                 display.clearDisplay();
                 display.setTextSize(1);
                 display.setTextColor(WHITE);
                 display.setCursor(0,0);
                 display.println(" <  SET DURATION  >");
                 display.setCursor(0,8);
                 display.setTextColor(WHITE);
                 display.println("=>Seeds        (30s)");
                 display.setTextColor(WHITE);
                 display.setCursor(0,16);
                 display.println("=>Plant        (1min)");
                 display.setTextColor(BLACK,WHITE);
                 display.setCursor(0,24);
                 display.println("=>Custom");
                 
                 display.display();
                          if(digitalRead(swpin)==0)
                { 
                  int tswitch=0;
                  int h=7,s=0;
                  while(true)
                  {
                    int exitvalue=digitalRead(exitbt);

                     if(exitvalue==0)
                         {
      
                           break;
      
                             }

                   switch(tswitch)
                    {  
                      case 0:    display.clearDisplay();
                                 display.setTextSize(2);
                                 display.setTextColor(WHITE);
                                 display.setCursor(20,10);
                                 display.println("  m::  s");
                                 display.setTextColor(BLACK,WHITE);
                                 display.setCursor(15,10);
                                 display.println(h);
                                 display.setTextColor(WHITE);
                                 display.setCursor(80,10);
                                 display.println(s);
                                 display.display();
                                 
                                  xvalue= analogRead(xpin);
                                  yvalue= analogRead(ypin);

                                  if(yvalue<100 || yvalue>900)
                                    { 
                                         tswitch=1;
                      
                                        delay(500);
                                    }   

                                                 
                                   if(xvalue>900 && h>0)
                                      { 
                    
                                          h--;

                                          //delay(500); 
                                       }   


                                    if(xvalue<100 && h<60)

                                      {
                                           h++;
                    
                      

                                    //  delay(500); 
                    
                                      }

                                      break;

                      case 1:    display.clearDisplay();
                                 display.setTextSize(2);
                                 display.setTextColor(WHITE);
                                 display.setCursor(20,10);
                                 display.println("  m::  s");
                                 display.setTextColor(WHITE);
                                 display.setCursor(15,10);
                                 display.println(h);
                                 display.setTextColor(BLACK,WHITE);
                                 display.setCursor(80,10);
                                 display.println(s);
                                 display.display();
                                 
                                  xvalue= analogRead(xpin);
                                  yvalue= analogRead(ypin);
                                  
                                  if(yvalue<100 || yvalue>900)
                                    { 
                                         tswitch=0;
                      
                                        delay(500);
                                    }   

                                                 
                                   if(xvalue>900 && s>0)
                                      { 
                    
                                          s--;

                                          //delay(500); 
                                       }   


                                    if(xvalue<100 && s<59)

                                      {
                                           s++;
                    
                      

                                    //  delay(500); 
                    
                                      }               
                            }
                             if(digitalRead(swpin)==0)
                               {
                                 EEPROM.write(9,h);
                                 EEPROM.write(10,s);
                                 display.clearDisplay();
                                 display.setTextSize(2);
                                 display.setTextColor(WHITE);
                                 display.setCursor(0,0);
                                 display.println("Changes saved!");
                                 display.display();
                                 delay(2000);
                                 break;
                               }
                         
                    
                  }
                }

                  xvalue= analogRead(xpin);
       
               if(xvalue<100)
                   { pgvalue2--;
                     
                      
                     delay(500);
                   }   

               if(xvalue>900)
                   { 
                     pgvalue2=0;
                     
 
                      delay(500);     
                   }                        
    
      }
  }
}

void pump()
{
  Time t= rtc.getTime();
  long int ho=t.hour,durat;
  int mi=t.min;
  
  durat= EEPROM.read(9)* 60000 + EEPROM.read(10)*1000;
  Serial.println(t.sec);
  if(((EEPROM.read(0)==ho&& EEPROM.read(1)==mi && EEPROM.read(6)==1)||(EEPROM.read(2)==ho&& EEPROM.read(3)==mi && EEPROM.read(7)==1)||(EEPROM.read(4)==ho&& EEPROM.read(5)==mi&& EEPROM.read(8)==1))&&t.sec==1)
   {
     digitalWrite(IN1,3.3);
     digitalWrite(IN2,LOW);
     analogWrite(en1,255);
     delay(durat);
     
   }

   else
     analogWrite(en1,0);
}
void loop() {
  // put your main code here, to run repeatedly:
  pump();
  moisture = analogRead(soilspin);
  moisture = map(moisture,550,10,0,100);
  
  String mtime= rtc.getTimeStr();

 //Serial.println(mtime);
 display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK,WHITE);
  display.setCursor(0,2);
  display.println("SYSTEM ACTIVE");
  display.setTextColor(WHITE);
  display.setCursor(0,12);
   String ttime="TIME: "+ mtime;
  display.println(ttime);
  display.setCursor(0,21);
  display.println("Soil Moisture:    %");  
   display.setCursor(90,21);
  display.println(moisture); 
  display.display();


  int menuvalue= digitalRead(menubt);
  pgvalue=0;

  
     
  while(menuvalue==0)
  {
   
    int exitvalue=digitalRead(exitbt);
    if(exitvalue==0)
     {
      
      break;
     }

    switch(pgvalue)
    {  
      
       
       case 0:   display.clearDisplay();
                 display.setTextSize(1);
                 display.setTextColor(WHITE);
                 display.setCursor(0,0);
                 display.println("    <  SETTINGS  >");
                 display.setCursor(0,8);
                 display.setTextColor(BLACK,WHITE);
                 display.println("=>Set Time");
                 display.setTextColor(WHITE);
                 display.setCursor(0,16);
                 display.println("=>Set Duration");
                 display.setTextColor(WHITE);
                 display.setCursor(0,24);
                 display.println("=>Manual Control");
                 
                 display.display();

                  if(digitalRead(swpin)==0)
                  { 
                    SETTIME();
                    delay(500);
                  }
       
               xvalue= analogRead(xpin);
               if(xvalue>900)
                   { pgvalue++;
                    
                      

                     delay(500); 
                   }   


               if(xvalue<100)

                  {
                    pgvalue=2;
                    
                      

                      delay(500); 
                    
                  }

               break;

       case 1:    
                 display.clearDisplay();
                 display.setTextSize(1);
                 display.setTextColor(WHITE);
                 display.setCursor(0,0);
                 display.println("    <  SETTINGS  >");
                 display.setCursor(0,8);
                 display.setTextColor(WHITE);
                 display.println("=>Set Time");
                 display.setTextColor(BLACK,WHITE);
                 display.setCursor(0,16);
                 display.println("=>Set Duration");
                 display.setTextColor(WHITE);
                 display.setCursor(0,24);
                 display.println("=>Manual Control");
                 
                 display.display();

                 if(digitalRead(swpin)==0)
                  { 
                    SETDUR();
                    delay(500);
                  }
                   
               xvalue= analogRead(xpin);
       
               if(xvalue>900)
                   { pgvalue++;
                     
                     

                     delay(500); 
                   }  

               else if(xvalue<100)
                   { 
                     pgvalue--;
                     
 
                     delay(500);     
                   }

               

                 break;

       case 2:    
                 display.clearDisplay();
                 display.setTextSize(1);
                 display.setTextColor(WHITE);
                 display.setCursor(0,0);
                 display.println("    <  SETTINGS  >");
                 display.setCursor(0,8);
                 display.setTextColor(WHITE);
                 display.println("=>Set Time");
                 display.setTextColor(WHITE);
                 display.setCursor(0,16);
                 display.println("=>Set Duration");
                 display.setTextColor(BLACK,WHITE);
                 display.setCursor(0,24);
                 display.println("=>Manual Control");
                 
                 display.display();

                  if(digitalRead(swpin)==0)
                  { 
                    MANUAL();
                    delay(500);
                  }

                  xvalue= analogRead(xpin);
       
               if(xvalue<100)
                   { pgvalue--;
                     
                      
                     delay(500);
                   }   

               if(xvalue>900)
                   { 
                     pgvalue=0;
                     
 
                      delay(500);     
                   }           
               
    }
  }
   
  
  
    





    
  


}
