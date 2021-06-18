#include<SoftwareSerial.h>
#include <dht.h>
SoftwareSerial gsm(6,7);
dht DHT;

#define DHT11_PIN A2  //what pin we're connected to


//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value
int soil_pin=A0;
int ldr_pin=A1;
int output_value,ldr;
int motor = 8;
int LED=9;
int fan=10; 
String msg;
float humi;
    float tmp;
    int mois;
    int LDR;
int count;

void setup()
{
  // put your setup code here, to run once:

    humi=42;
    tmp=45;
    mois=35;
    LDR=80;
    count=0;
    
    msg="";
    pinMode(soil_pin, INPUT);
    pinMode(ldr_pin, INPUT);
    pinMode(motor, OUTPUT);
    pinMode(LED,OUTPUT);
    pinMode(fan,OUTPUT);
    


Serial.begin(9600);
gsm.begin(9600);
Serial.println("Reading from sensor");
delay(2000);


}

void loop() 
{

  // put your main code here, to run repeatedly:
output_value=analogRead(soil_pin);
output_value=map(output_value,1023,10,0,100);
Serial.print("Moisture=");
Serial.print(output_value);
Serial.print("%");
delay(1000);
  if (output_value<=40)
   {
      digitalWrite(motor,LOW);
      Serial.println(" MOTOR ON");
   }
  else
  {
      digitalWrite(motor,HIGH);
      Serial.println(" MOTOR OFF");
  }


   ldr=analogRead(ldr_pin);
   ldr=map(ldr,511,10,0,100);
   Serial.print("Intensity=");
   Serial.print(ldr);
   Serial.print("%");
   delay(1000);

   if (ldr>=80)
  {
  digitalWrite(LED,HIGH);
  Serial.println(" LIGHT ON");
  }
  else
  {
    digitalWrite(LED,LOW);
    Serial.println(" LIGHT OFF");
  }

    int chk = DHT.read11(DHT11_PIN);
    //Read data and store it to variables hum and temp
    hum = DHT.humidity;
    temp= DHT.temperature;
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println("%");
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print("C");
    delay(1000); //Delay 1 seconds.

    if (temp>=45)
    {
      digitalWrite(fan,HIGH);
      Serial.println(" FAN ON");
    }
    else
    {
      digitalWrite(fan,LOW);
      Serial.println(" FAN OFF");
    }  
  
  
if((LDR != ldr) || (temp != tmp) || (mois != output_value) || (hum != humi))
{
 // Serial.println("Inside loop");
  
  msg=msg+"Intensity is ";
  msg=msg+ldr;//
  msg=msg+". Temperature is ";
  msg=msg+temp;
  msg=msg+". Moisture is ";
  msg=msg+output_value;
  msg=msg+". Humidity is ";
  msg=msg+hum;
}
    if(gsm.available())
    {
        char c=(char)gsm.read();
        Serial.write(c);        
        delay(400);
        gsm.print("AT+CMGS=\"7385029262\"\r\n");
        delay(400);
        gsm.print(msg);
        gsm.write(26);        
        delay(1000);
        
    }
    Serial.println(msg);
    Serial.flush();
      
      msg="";

    
       switch(count)
        {
          case 0:
          Serial.println("Count is ");
          Serial.println(count);
          gsm.print("ATZ\r\n");
          delay(1000);          
          count++;
          break;
          case 1:
          Serial.println("case is ");
          Serial.println(count);
          gsm.print("AT+CMGF=1\r\n");
          delay(400);
          break;
     }
    }
