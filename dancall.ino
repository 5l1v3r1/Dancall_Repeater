#define TX LOW
#define RX HIGH
#define STB   8
#define CLK   7
#define DAT   6
#define COR   5
#define TXENABLE   4


void sendBit(bool s)
{
digitalWrite(DAT,s);
delayMicroseconds(10);
digitalWrite(CLK,HIGH);  
delayMicroseconds(3);
digitalWrite(CLK,LOW);  
}

void sendNAR(int _n,int _a, int _r,bool TXRX)   //TXRX: Low for Tx,High for Rx
{
  int i;
  for(i=0;i<12;i++)
   { sendBit(bitRead(_r,i));}    //send ref div
    sendBit(0);sendBit(0);sendBit(0);sendBit(1);

   digitalWrite(DAT,TXRX);
   delayMicroseconds(15);
   digitalWrite(STB,HIGH);    //Data High STB for RX PLL  
   delayMicroseconds(15);
   digitalWrite(STB,LOW);
   delayMicroseconds(5);

    for(i=0;i<7;i++)
   {
    sendBit(bitRead(_a,i));          //send swallow
    }

   for(i=0;i<11;i++)          
   {
    sendBit(bitRead(_n,i));          //send prog divider
    }
  sendBit(1);sendBit(0);

   digitalWrite(DAT,TXRX);
   delayMicroseconds(15);
   digitalWrite(STB,HIGH);    //Data High STB for RX PLL  
   delayMicroseconds(15);
   digitalWrite(STB,LOW);
   delayMicroseconds(5);
  
}



void setup() {
  int a;
  Serial.begin(9600);
  pinMode(STB,OUTPUT);
  pinMode(CLK,OUTPUT);
  pinMode(DAT,OUTPUT);
  pinMode(TXENABLE,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(COR,INPUT_PULLUP);

  digitalWrite(TXENABLE,LOW);
  digitalWrite(STB,LOW);
  digitalWrite(CLK,LOW);
  digitalWrite(DAT,LOW);


 //  a=76;   //439.150
   a=80;   //439.200
 //  a=84;   //439.250
 //  a=88;   //439.300
 //  a=90;   //439.325
 //  a=92;   //439.350
 //  a=96;   //439.400
 //  a=98;   //439.425


  sendNAR(566,a,2048,RX);
  sendNAR(1024,63,552,TX);
}

void loop() {


  if(digitalRead(COR))                  
    {
      digitalWrite(TXENABLE,HIGH);
      digitalWrite(LED_BUILTIN,HIGH);
      while (digitalRead(COR));
      //delay(300);       //kuyruk suresi
      digitalWrite(TXENABLE,LOW);
      digitalWrite(LED_BUILTIN,LOW);
     }




/*
while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();

    switch(inChar)
    {
      case 'a': n+=5; break;
      case 'z': n-=5; break;
      case 's': a+=5; break;
      case 'x': a-=5; break;
      case 'd': r+=5; break;
      case 'c': r-=5; break;
      case 'f': n+=1; break;
      case 'v': n-=1; break;
      case 'g': a+=1; break;
      case 'b': a-=1; break;
      case 'h': r+=1; break;
      case 'n': r-=1; break;
    }
      Serial.print("N:");Serial.print(n);Serial.print(" A:");Serial.print(a);Serial.print(" R:");Serial.println(r);
     sendNAR(n,a,r,RX);  
    }
*/

  
}
