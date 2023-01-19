
#include <LedControlMS.h>              //Includes the library that controls the LED Display
LedControl lc=LedControl(12,11,10,1);  //Defines the LED Display pins

const int pump=2;       //pot
const int relay=3;      //tank

const int trigPin=5;
const int echoPin=6;
const int sensorPin = A5;              //Defines the Moisture Sensor pins

const unsigned int delaytime=1000;   //Sets a delaytime

int sensorValue=0;                    // Moisture Sensor
String sensorValueS="0";

int UltraSensorValue=0;               // Ultrasonic Sensor
String UltraSensorValueS="0";

String potStatus="0";
String tankStatus="0";
boolean WaterSupply=false;

long duration;
int distance;

int dataRecived=0;
String dataToSend=(String)(00);

byte smile[4]={B00000100,B00110010,B01100100,B01100000};
byte surprise[4]={B00001110,B00001010,B01101110,B10010000};
byte meh[4]={B00000100,B00100100,B00100100,B00100000};
byte sad[4]={B00000010,B01100100,B00110010,B00110000};
byte dead[6]={B00001010,B00100100,B00101010,B00100000,B01100000,B01101010};
byte error[8]={B00111100,B01000010,B10100001,B10010001,B10001001,B10000101,B01000010,B00111100};

void setup()
{
 
  Serial.begin(9600);      //MS Serial Output

  pinMode(pump,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(pump,HIGH);  //Switching pump OFF
  digitalWrite(relay, HIGH);
   
  lc.shutdown(0,false);    //LED Matrix Setup
  lc.setIntensity(0,4);
  lc.clearDisplay(0);

  
}

void broken()
{
  lc.setRow(0,0,error[0]);
  lc.setRow(0,1,error[1]);
  lc.setRow(0,2,error[2]);
  lc.setRow(0,3,error[3]);
  lc.setRow(0,4,error[4]);
  lc.setRow(0,5,error[5]);
  lc.setRow(0,6,error[6]);
  lc.setRow(0,7,error[7]);
}

void happy()
{
  lc.setRow(0,0,smile[0]);
  lc.setRow(0,1,smile[1]);
  lc.setRow(0,2,smile[2]);
  lc.setRow(0,3,smile[3]);
  lc.setRow(0,4,smile[3]);
  lc.setRow(0,5,smile[2]);
  lc.setRow(0,6,smile[1]);
  lc.setRow(0,7,smile[0]);
}

void plain()
{
  lc.setRow(0,0,meh[0]);
  lc.setRow(0,1,meh[1]);
  lc.setRow(0,2,meh[2]);
  lc.setRow(0,3,meh[3]);
  lc.setRow(0,4,meh[3]);
  lc.setRow(0,5,meh[2]);
  lc.setRow(0,6,meh[1]);
  lc.setRow(0,7,meh[0]);
}

void surprised()
{
  lc.setRow(0,0,surprise[0]);
  lc.setRow(0,1,surprise[1]);
  lc.setRow(0,2,surprise[2]);
  lc.setRow(0,3,surprise[3]);
  lc.setRow(0,4,surprise[3]);
  lc.setRow(0,5,surprise[2]);
  lc.setRow(0,6,surprise[1]);
  lc.setRow(0,7,surprise[0]);
}

void dying()
{
  lc.setRow(0,0,dead[0]);
  lc.setRow(0,1,dead[1]);
  lc.setRow(0,2,dead[2]);
  lc.setRow(0,3,dead[3]);
  lc.setRow(0,4,dead[4]);
  lc.setRow(0,5,dead[5]);
  lc.setRow(0,6,dead[1]);
  lc.setRow(0,7,dead[0]);
}

void crying()
{
  lc.setRow(0,0,sad[0]);
  lc.setRow(0,1,sad[1]);
  lc.setRow(0,2,sad[2]);
  lc.setRow(0,3,sad[3]);
  lc.setRow(0,4,sad[3]);
  lc.setRow(0,5,sad[2]);
  lc.setRow(0,6,sad[1]);
  lc.setRow(0,7,sad[0]);
}

void evilsmile()
{
  lc.setRow(0,0,esmile[0]);
  lc.setRow(0,1,esmile[1]);
  lc.setRow(0,2,esmile[2]);
  lc.setRow(0,3,esmile[3]);
  lc.setRow(0,4,esmile[3]);
  lc.setRow(0,5,esmile[2]);
  lc.setRow(0,6,esmile[1]);
  lc.setRow(0,7,esmile[0]);
}

void evillaugh()
{
  lc.setRow(0,0,elaugh[0]);
  lc.setRow(0,1,elaugh[1]);
  lc.setRow(0,2,elaugh[2]);
  lc.setRow(0,3,elaugh[3]);
  lc.setRow(0,4,elaugh[3]);
  lc.setRow(0,5,elaugh[2]);
  lc.setRow(0,6,elaugh[1]);
  lc.setRow(0,7,elaugh[0]);
}

void evilplain()
{
  lc.setRow(0,0,eplain[0]);
  lc.setRow(0,1,eplain[1]);
  lc.setRow(0,2,eplain[2]);
  lc.setRow(0,3,eplain[3]);
  lc.setRow(0,4,eplain[3]);
  lc.setRow(0,5,eplain[2]);
  lc.setRow(0,6,eplain[1]);
  lc.setRow(0,7,eplain[0]);
}

void evilyell()
{
  lc.setRow(0,0,eyell[0]);
  lc.setRow(0,1,eyell[1]);
  lc.setRow(0,2,eyell[2]);
  lc.setRow(0,3,eyell[3]);
  lc.setRow(0,4,eyell[3]);
  lc.setRow(0,5,eyell[2]);
  lc.setRow(0,6,eyell[1]);
  lc.setRow(0,7,eyell[0]);
}

void eviltalk()
{
  lc.setRow(0,0,etalk[0]);
  lc.setRow(0,1,etalk[1]);
  lc.setRow(0,2,etalk[2]);
  lc.setRow(0,3,etalk[3]);
  lc.setRow(0,4,etalk[3]);
  lc.setRow(0,5,etalk[2]);
  lc.setRow(0,6,etalk[1]);
  lc.setRow(0,7,etalk[0]);
}

void writeArduinoOnMatrix()  // Displays faces on LED Matrix
{
  if(sensorValue>= 0 && sensorValue<=50)        surprised();
  else if (sensorValue>50 && sensorValue <=150) happy();
  else if (sensorValue>150 && sensorValue<=250) plain();
  else if (sensorValue>250 && sensorValue<=350) crying();
  else if (sensorValue>350 && sensorValue<=450) dying();
  else broken();
  
}

void loop()
{
  sensorValue = analogRead(sensorPin);
  delay(delaytime);
  writeArduinoOnMatrix();

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  
if(distance<=5)
{
  digitalWrite(pump,HIGH);  //Switching pump OFF
  tankStatus="0";
}
  


  if(Serial.available() > 0) // Checks whether data is comming from the serial port
{
  delay(10); //Delay to make it stable
  
  dataRecived=Serial.read(); // Reads the data from the serial port
}

if(dataRecived=='0')
{
  digitalWrite(pump,HIGH);  //Switching pump OFF
  potStatus="0";
}
else if(dataRecived=='1')
{
  digitalWrite(pump,LOW);  //Switching pump ON
  potStatus="1";
}
else if(dataRecived=='2')
{
  digitalWrite(relay,HIGH);  //Switching relay OFF
  tankStatus="0";
}
else if(dataRecived=='3')
{
  digitalWrite(relay,LOW);  //Switching relay ON
  tankStatus="1";
}

 sensorValueS=String(sensorValue);
 UltraSensorValueS=String(distance);
 if((sensorValueS+"|"+potStatus+"|"+UltraSensorValueS+"|"+tankStatus+"|")!=dataToSend)
 {
 dataToSend=sensorValueS+"|"+potStatus+"|"+UltraSensorValueS+"|"+tankStatus+"|";
 Serial.println(dataToSend);
 }
}
