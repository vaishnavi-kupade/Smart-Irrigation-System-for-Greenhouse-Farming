#include<SoftwareSerial.h>
SoftwareSerial gsm(6,7);

int count=0;
String line="";
float hum;  //Stores humidity value
float temp; //Stores temperature value
int soil_pin=A0;
int ldr_pin=A1;
int output_value,ldr;
int motor = 8;
int LED=9;
int fan=10;
String msg;


void setup()
{
// put your setup code here, to run once:
  pinMode(soil_pin, INPUT);
    pinMode(ldr_pin, INPUT);
    pinMode(motor, OUTPUT);
    pinMode(LED,OUTPUT);
    pinMode(fan,OUTPUT);
    
    digitalWrite(motor,HIGH);
    digitalWrite(LED,LOW);
    digitalWrite(fan,LOW);

Serial.begin(9600);
gsm.begin(9600);
          msg="Status is - ";

          

}


void loop() {
   if(gsm.available())
  {
      char c=(char)gsm.read();
      Serial.write(c);

       if(c=='\r' || c=='\n')
      {        
        Serial.print("LINE:"+line);
       
        if(line.indexOf("MOTORON")>0)
        {
          digitalWrite(motor, LOW);
        }


         if(line.indexOf("MOTOROFF")>0)
        {
          digitalWrite(motor, HIGH);
        }


        if(line.indexOf("LEDON")>0)
        {
          digitalWrite(LED, HIGH);
        }


         if(line.indexOf("LEDOFF")>0)
        {
          digitalWrite(LED, LOW);
        }

        if(line.indexOf("FANON")>0)
        {
          digitalWrite(fan, HIGH);
        }


         if(line.indexOf("FANOFF")>0)
        {
          digitalWrite(fan, LOW);
        }


        if(line.indexOf("ALLON")>0)
        {
          digitalWrite(fan, HIGH);
          digitalWrite(LED, HIGH);
          digitalWrite(motor, LOW);
          
        }


         if(line.indexOf("ALLOFF")>0)
        {
          digitalWrite(fan, LOW);
          digitalWrite(LED, LOW);
          digitalWrite(motor, HIGH);
        }

        if(line.indexOf("status")>0)
        {

          if(digitalRead(LED))
          {
            Serial.println("LED is On");
            msg=msg+" LED is On.";  
          }
          if(!digitalRead(LED))
          {
            Serial.println("LED is Off");
            msg=msg+" LED is Off. ";  
          }

          if(digitalRead(motor))
          {
            Serial.println("Motor is Off");
            msg=msg+" Motor is Off. ";  
          }
          if(!digitalRead(motor))
          {
            Serial.println("Motor is on");
            msg=msg+" Motor is On. ";  
          }
          if(digitalRead(fan))
          {
            Serial.println("FAN is On");
            msg=msg+" Fan is On. ";  
          }
          if(!digitalRead(fan))
          {
            Serial.println("Fan is Off");
            msg=msg+" Fan is Off. ";  
          }

        gsm.print("AT+CMGS=\"7385029262\"\r\n");
        delay(400);
        gsm.print(msg);
        gsm.write(26);        
        
        delay(400);
        msg="";        
        }
        line="";
      }
      line=line+c;        
      }


        switch(count)
        {
          case 0:
          Serial.println(count);
          gsm.print("ATZ\r\n");
          
          delay(400);          
          count++;
          break;
          case 1:
          gsm.print("AT+CMGF=1\r\n");
        delay(400);
        gsm.print("AT+CNMI=1,2,0,0,0\r\n");        
        delay(400);
        count++;
        break;

     }
}
