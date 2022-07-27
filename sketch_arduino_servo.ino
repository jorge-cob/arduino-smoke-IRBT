#include <Servo.h> 

#include "IRremote.h"
#include "IR.h"

#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  


Servo servo1;
Servo servo2;

int pos = 0;


IRrecv irrecv(RECEIVER);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'


SoftwareSerial BT(5,6);

void setup() {
  BT.begin(9600); 
  Serial.begin(38400);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn();
  servo1.attach(9);
  servo2.attach(10);
}

void loop() {
   if(BT.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    Serial.println("llega un dato por el puerto BT");
    Serial.write(BT.read());
  }
 
  if(Serial.available())  // Si llega un dato por el monitor serial se envía al puerto BT
  {
     Serial.println("llega un dato por el monitor serial");
     BT.write(Serial.read());
  }
  int tmpValue;
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    for (int i = 0; i < 21; i++)
    {
      if ((keyValue[i] == results.value) && (i<KEY_NUM))
      {

        if (keyValue[i] == 16753245) {
          servo1.write(14);
          servo2.write(30);
          delay(2000);
          servo1.write(0);
          servo2.write(0);
        }
        if (keyValue[i] == 167532477) {
            for (pos = 0; pos <= 180; pos += 1) {
              servo1.write(pos);
              servo2.write(pos);
              delay(15);
            }
            delay(5000);
            for (pos = 180; pos >= 0; pos -= 1) {
              servo1.write(pos);
              servo2.write(pos);
              delay(15);
            }
        }
        Serial.println(keyBuf[i]);
        tmpValue = results.value;
      }
      else if(REPEAT==i)
      {
        results.value = tmpValue;
      }
    }
    irrecv.resume(); // receive the next value
  }


}
