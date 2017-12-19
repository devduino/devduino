/** MIT License
*
* Copyright(c) 2017 DevDuino
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restri  ction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include <devduino.h>
#include <SoftwareSerial.h>
#include "devduinoLogo.h"

SoftwareSerial HC06(10,12);

String messageReceived= "";
float analogValue = 0;

float analogRef = 4.9;

//Initialize program.
void setup()
{
  devduino.begin();  
  devduino.attachToIntButton(buttonPressed);
  display.drawSprite(devduinoLogo, 37, 0);
  display.flush();  
  delay(1000);
  display.clear();

  //Serial.begin(9600);
  HC06.begin(9600); 
  
  for(int i=0;i<=1;i++)
  {
	pinMode(i, OUTPUT);
    digitalWrite(i, LOW); 
  }  
  for(int i=4;i<=6;i++)
  {
  pinMode(i, OUTPUT);
    digitalWrite(i, LOW); 
  }
  for(int i=8;i<=9;i++)
  {
  pinMode(i, OUTPUT);
  digitalWrite(i, LOW); 
  }
  
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() 
{
 while(HC06.available()) 
 {
  delay(3);
  char c = HC06.read();
  messageReceived+= c;
 }
 if (messageReceived.length() >0) 
 {  
  console.println(messageReceived);
  /*****************************************************/
  /*                  DIGITAL 0                        */
  /*****************************************************/
  if ((messageReceived.indexOf("D00") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {digitalWrite(0,HIGH);}
   else if((messageReceived.indexOf("OFF") != -1)) 
   {digitalWrite(0,LOW);}     
  }
  /*****************************************************/
  /*                  DIGITAL 1                        */
  /*****************************************************/
  else if ((messageReceived.indexOf("D01") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {digitalWrite(1,HIGH);}
   else if((messageReceived.indexOf("OFF") != -1)) 
   {digitalWrite(1,LOW);}     
  }  
  /*****************************************************/
  /*                  DIGITAL 4                        */
  /*****************************************************/
  else if ((messageReceived.indexOf("D04") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {digitalWrite(4,HIGH);}
   else if((messageReceived.indexOf("OFF") != -1)) 
   {digitalWrite(4,LOW);}     
  }
  /*****************************************************/
  /*                  DIGITAL 5                        */
  /*****************************************************/
  else if ((messageReceived.indexOf("D05") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {digitalWrite(5,HIGH);}
   else if((messageReceived.indexOf("OFF") != -1)) 
   {digitalWrite(5,LOW);}   
   else
   {   
     messageReceived=  messageReceived.substring(4,7);
     analogWrite(5,messageReceived.toInt());
   }  
  }
  /*****************************************************/
  /*                  DIGITAL 6                        */
  /*****************************************************/
  else if ((messageReceived.indexOf("D06") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {digitalWrite(6,HIGH);}
   else if((messageReceived.indexOf("OFF") != -1)) 
   {digitalWrite(6,LOW);}   
   else
   {   
     messageReceived=  messageReceived.substring(4,7);
     analogWrite(6,messageReceived.toInt());
   }  
  }
  /*****************************************************/
  /*                  DIGITAL 8                        */
  /*****************************************************/
  else if ((messageReceived.indexOf("D08") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {digitalWrite(8,HIGH);}
   else if((messageReceived.indexOf("OFF") != -1)) 
   {digitalWrite(8,LOW);}     
  }
  /*****************************************************/
  /*                  DIGITAL 9                        */
  /*****************************************************/
  else if ((messageReceived.indexOf("D09") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {digitalWrite(9,HIGH);}
   else if((messageReceived.indexOf("OFF") != -1)) 
   {digitalWrite(9,LOW);}   
   else
   {   
     messageReceived=  messageReceived.substring(4,7);
     analogWrite(9,messageReceived.toInt());
   }  
  }
  /*****************************************************/
  /*                  DIGITAL 11                        */
  /*****************************************************/
  else if ((messageReceived.indexOf("D11") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {digitalWrite(11,HIGH);}
   else if((messageReceived.indexOf("OFF") != -1)) 
   {digitalWrite(11,LOW);}   
   else
   {   
     messageReceived=  messageReceived.substring(4,7);
     analogWrite(11,messageReceived.toInt());
   }  
  }
  /*****************************************************/
  /*                  DIGITAL 13                       */
  /*****************************************************/
  else if ((messageReceived.indexOf("D13") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {digitalWrite(13,HIGH);}
   else if((messageReceived.indexOf("OFF") != -1)) 
   {digitalWrite(13,LOW);}   
   else
   {   
     messageReceived=  messageReceived.substring(4,7);
     analogWrite(13,messageReceived.toInt());
   }  
  }
  /*****************************************************/
  /*                    ANALOG 0                       */
  /*****************************************************/
  else if ((messageReceived.indexOf("A0") != -1)) 
  {
   analogValue = analogRead(0);   
   analogValue = analogValue*analogRef/1000;
   console.println("A0=" + String(analogValue));
   HC06.print(String(analogValue));
  }
  /*****************************************************/
  /*                    ANALOG 1                       */
  /*****************************************************/
  else if ((messageReceived.indexOf("A1") != -1)) 
  {
   analogValue = analogRead(1);   
   analogValue = analogValue*analogRef/1000; 
   console.println("A1=" + String(analogValue));
   HC06.print(String(analogValue));
  }
  /*****************************************************/
  /*                    ANALOG 2                       */
  /*****************************************************/
  else if ((messageReceived.indexOf("A2") != -1)) 
  {
   analogValue = analogRead(2);   
   analogValue = analogValue*analogRef/1000; 
   console.println("A2=" + String(analogValue));
   HC06.print(String(analogValue));
  }
  /*****************************************************/
  /*                    ANALOG 3                       */
  /*****************************************************/
  else if ((messageReceived.indexOf("A3") != -1)) 
  {
   analogValue = analogRead(3);   
   analogValue = analogValue*analogRef/1000;
   console.println("A3=" + String(analogValue));
   HC06.print(String(analogValue));
  }
  /*****************************************************/
  /*                    ANALOG 4                       */
  /*****************************************************/
  else if ((messageReceived.indexOf("A4") != -1)) 
  {
   analogValue = analogRead(4);   
   analogValue = analogValue*analogRef/1000;
   console.println("A4=" + String(analogValue));
   HC06.print(String(analogValue));
  }
  /*****************************************************/
  /*                    ANALOG 5                       */
  /*****************************************************/
  else if ((messageReceived.indexOf("A5") != -1)) 
  {
   analogValue = analogRead(5);   
   analogValue = analogValue*analogRef/1000;
   console.println("A5=" + String(analogValue));
   HC06.print(String(analogValue));
  }
  /*****************************************************/
 }
 messageReceived="";
}

void buttonPressed()
{
  
}