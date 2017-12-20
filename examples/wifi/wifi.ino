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

#define BAUDRATE 74800

SoftwareSerial DT06(10,12);

String messageReceived= "";

//Initialize program.
void setup()
{
  devduino.begin();  
  devduino.attachToIntButton(buttonPressed);
  display.drawSprite(devduinoLogo, 37, 0);
  display.flush();    
  delay(2000);
  display.clear(); 

  DT06.begin(BAUDRATE); 
  DT06.setTimeout(1000);
  
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

  checkStatus();  
}

void loop() 
{
 while(DT06.available()) 
 {
  messageReceived = DT06.readString();  
 } 
 if (messageReceived.length() > 0) 
 //if (messageReceived.length() >0 && messageReceived.length() < 128) 
 {  
  //console.println(messageReceived);
  /*****************************************************/
  /*                  DIGITAL 0                        */
  /*****************************************************/
  if ((messageReceived.indexOf("D00") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {
    digitalWrite(0,HIGH);
    console.println("*     D00 = ON      *");
   }
   else if((messageReceived.indexOf("OFF") != -1)) 
   {
    digitalWrite(0,LOW);
    console.println("*     D00 = OFF     *");
   }
  }
  /*****************************************************/
  /*                  DIGITAL 1                        */
  /*****************************************************/
  else if ((messageReceived.indexOf("D01") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {
    digitalWrite(1,HIGH);  
    console.println("*     D01 = ON      *");
    }
   else if((messageReceived.indexOf("OFF") != -1)) 
   {
    digitalWrite(1,LOW);   
    console.println("*     D01 = OFF     *");
   }   
  }
  /*****************************************************/
  /*                  DIGITAL 1                        */
  /*****************************************************/
  else if ((messageReceived.indexOf("D04") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {
    digitalWrite(4,HIGH);  
    console.println("*     D04 = ON      *");
    }
   else if((messageReceived.indexOf("OFF") != -1)) 
   {
    digitalWrite(4,LOW);   
    console.println("*     D04 = OFF     *");
   }   
  }
  /*****************************************************/
  /*                  DIGITAL 5                        */
  /*****************************************************/
  else if ((messageReceived.indexOf("D05") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {
    digitalWrite(5,HIGH);  
    console.println("*     D05 = ON      *");
    }
   else if((messageReceived.indexOf("OFF") != -1)) 
   {
    digitalWrite(5,LOW);   
    console.println("*     D05 = OFF     *");
   }   
  }
  /*****************************************************/
  /*                  DIGITAL 6                        */
  /*****************************************************/
  else if ((messageReceived.indexOf("D06") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {
    digitalWrite(6,HIGH);  
    console.println("*     D06 = ON      *");
    }
   else if((messageReceived.indexOf("OFF") != -1)) 
   {
    digitalWrite(6,LOW);   
    console.println("*     D06 = OFF     *");
   }   
  }
  /*****************************************************/
  /*                  DIGITAL 8                        */
  /*****************************************************/
  else if ((messageReceived.indexOf("D08") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {
    digitalWrite(8,HIGH);  
    console.println("*     D08 = ON      *");
    }
   else if((messageReceived.indexOf("OFF") != -1)) 
   {
    digitalWrite(8,LOW);   
    console.println("*     D08 = OFF     *");
   }   
  }
  /*****************************************************/
  /*                  DIGITAL 9                        */
  /*****************************************************/
  else if ((messageReceived.indexOf("D09") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {
    digitalWrite(9,HIGH);  
    console.println("*     D09 = ON      *");
    }
   else if((messageReceived.indexOf("OFF") != -1)) 
   {
    digitalWrite(9,LOW);   
    console.println("*     D09 = OFF     *");
   }   
  }
  /*****************************************************/
  /*                  DIGITAL 11                       */
  /*****************************************************/
  else if ((messageReceived.indexOf("D11") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {
    digitalWrite(11,HIGH);  
    console.println("*     D11 = ON      *");
    }
   else if((messageReceived.indexOf("OFF") != -1)) 
   {
    digitalWrite(11,LOW);   
    console.println("*     D11 = OFF     *");
   }   
  }
  /*****************************************************/
  /*                  DIGITAL 13                       */
  /*****************************************************/
  else if ((messageReceived.indexOf("D13") != -1)) 
  {
   if ((messageReceived.indexOf("ON") != -1)) 
   {
    digitalWrite(13,HIGH);  
    console.println("*     D13 = ON      *");
    }
   else if((messageReceived.indexOf("OFF") != -1)) 
   {
    digitalWrite(13,LOW);   
    console.println("*     D13 = OFF     *");
   }   
  }  
  messageReceived=""; // Flush buffer
  }
  delay(1);
}

void checkStatus()
{
  boolean STA_OK = false;
  boolean TCP_OK = false;
  console.println("INIT...");
  console.println("---------------------"); 
  DT06.print("AT+TCPCLIENT");
  delay(100);
  while(DT06.available()) 
   {
    messageReceived = DT06.readString();  
   } 
  console.println(messageReceived); 

  if ((messageReceived.indexOf("OK") != -1)) 
   {
    TCP_OK = true;      
   }
  messageReceived=""; 
  console.println("---------------------"); 
  delay(300);
  
  DT06.print("AT+STASTATUS");  
  delay(100);
  while(DT06.available()) 
   {
    messageReceived = DT06.readString();  
   }
  console.println(messageReceived);
  
  if ((messageReceived.indexOf("OK") != -1)) 
   {
    STA_OK = true;      
   }
  console.println("---------------------"); 
  messageReceived=""; 
  delay(100);
     
  if (STA_OK && TCP_OK)
  {
    console.println("READY!");     
    console.println("---------------------"); 
    DT06.print("AT+STAINFO");  
    delay(100);
    while(DT06.available()) 
     {
      messageReceived = DT06.readString();  
     }
    //console.println(messageReceived); 
    console.println("MAC|" + messageReceived.substring(0,2) +"-" +messageReceived.substring(2,4)+"-" +messageReceived.substring(4,6)+"-" +messageReceived.substring(6,8)+"-" +messageReceived.substring(8,10)+"-" +messageReceived.substring(10,12)    );
    console.println("---------------------"); 
    delay(100);
    console.println(" IP | 115.29.109.104"); 
    console.println("PORT| 6524"); 
  }  
  else
  {
    console.println("FAILED!");  
    console.println("Go to www.devduino.cc");      
  }
  messageReceived="";  
  DT06.flush();
  console.println("---------------------");  
}
void buttonPressed()
{
  DT06.print("AT+RESET"); 
}


