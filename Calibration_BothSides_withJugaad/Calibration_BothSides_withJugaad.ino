int lmot1=6;
int lmot2=5;
int rmot1=10;
int rmot2=11;
int trigPinf=12;
int echoPinf=13;
int trigPinr=4;
int echoPinr=9;
//int trigPinl=2;
//int echoPinl=3;
//int trigPinb=A0;
//int echoPinb=A1;
char CurrentInput = 'x';
char LastInput = 'x';
char mode;
char directions[100];
char last;
int lcount=0,fcount=0,ltime=0,ftime=0;
int turndell=1000;
int turndelr=1000;
char cal='0';
char c='e';

void setup()
{
  // put your setup code here, to run once:
 pinMode(lmot1,OUTPUT);
 pinMode(lmot2,OUTPUT);
 pinMode(rmot1,OUTPUT);
 pinMode(rmot2,OUTPUT);
 pinMode(7,OUTPUT);
 pinMode(8,OUTPUT);
 pinMode(trigPinf, OUTPUT);
 pinMode(echoPinf, INPUT);
 pinMode(trigPinr, OUTPUT);
 pinMode(echoPinr, INPUT);
 //pinMode(trigPinl, OUTPUT);
 //pinMode(echoPinl, INPUT);
 //pinMode(trigPinb, OUTPUT);
 //pinMode(echoPinb, INPUT);
 directions[0] = '\0';
 Serial.begin(9600);
 Serial.println("Press 0 to caliberate 90 degree turn.");
 Serial.println(Serial.available());
 while(!Serial.available());
 do
 {
  cal=Serial.read();
  if(cal ='0')
  {
   Serial.println("Press q to stop turning.");
   int delir=millis();
   do
   {
    digitalWrite(rmot1, HIGH);
    digitalWrite(lmot1, LOW);
   }while(Serial.read()!='q');
   int delfr=millis();
   turndelr=delfr-delir;
   Serial.println("Press q to stop turning left.");
   pause();
   delay(1500);
   int delil=millis();
   do
   {
    digitalWrite(rmot1, LOW);
    digitalWrite(lmot1, HIGH);
   }while(Serial.read()!='q');
   int delfl=millis();
   pause();
   int turndell=delfl-delil;
  }
  Serial.flush();
  Serial.println("Enter 0 to calibrate again or q to proceed.");
  while(!Serial.available()); 
  cal=Serial.read();
 }while(cal=='0');
 Serial.println("Enter mode of the wheelchair : \n 0 for self-driven mode \n 1 for giving directions (Teach Mode)"); 
 Serial.flush();
}

void loop()
{
   while(!Serial.available());
   
   mode = Serial.read();
   Serial.println(mode);
   if(mode == '0') selfdrive();
   
   
   else if(mode == '1')
   { 
      Serial.flush();
      Serial.println("Enter directions : w/a/s/d for forward/left/backward/right and e to exit Teach Mode");
      delay(10000);
      int j=0;
      do 
      {
        c = Serial.read();
        Serial.println(c);
        if(c!='e') directions[j++]=c;  
        Serial.println(j);
        delay(500);
      }while(c!='e');
      pause();
      directions[++j]='\0'; 
      selfdrive();   
    } 
    Serial.println("Enter mode of the wheelchair : \n 0 for self-driven mode \n 1 for giving directions(Teach Mode)");
}


void forward()
{
    int distf=ultrasonic_dist(trigPinf,echoPinf);
    if(distf<=15) obstavoid();
    else
    {
    digitalWrite(rmot1, HIGH);
    digitalWrite(lmot1, HIGH);
    delay(500);   
    }
}

void backward()
{
   digitalWrite(rmot2, HIGH);
   digitalWrite(lmot2, HIGH);
   delay(500);
   
}

void selfdrive()
{
      for(int i=0;directions[i]!='\0';i++)
      {
        int distf=ultrasonic_dist(trigPinf,echoPinf);
        //int distr=ultrasonic_dist(trigPinr,echoPinr);
        if(directions[i]=='w') forward();
        else if(directions[i] =='a') left();
        else if(directions[i] == 'd') right();
        else if(directions[i] == 's') backward();
       }  
      pause();
}

void obstavoid()
{
 Serial.println("Obstacle dekha!");
 lcount=0, fcount=0;
 rotateleft();
 do
 {
  digitalWrite(rmot1,HIGH);
  digitalWrite(lmot1,HIGH);
  delay(100);
  lcount++;
 }while(ultrasonic_dist(trigPinr,echoPinr)<=5);
 delay(300);
 
 rotateright();
 
 //do
 //{
  //digitalWrite(rmot1,HIGH);
  //digitalWrite(lmot1,HIGH);
  //delay(200);
 //}while(ultrasonic_dist(trigPinr,echoPinr)<=5);
 //delay(200);
 
 digitalWrite(rmot1,HIGH);
 digitalWrite(lmot1,HIGH);
 delay(1500);
 
 rotateright();
 
 digitalWrite(rmot1,HIGH);
 digitalWrite(lmot1,HIGH);
 delay(lcount*100);
 
 
 rotateleft();
 delay(200);
} 

void rotateright()
{
  digitalWrite(rmot1, HIGH);
  digitalWrite(lmot1, LOW);
  delay(turndelr);
}

void rotateleft()
{
  digitalWrite(rmot1,LOW);
  digitalWrite(lmot1, HIGH);
  delay(turndell);
}

void right()
{
  digitalWrite(rmot1,LOW);
  digitalWrite(lmot1,LOW);
  digitalWrite(rmot2,LOW);
  digitalWrite(lmot2,LOW);
  rotateright();
  forward();
}

void left()
{
 digitalWrite(rmot1,LOW);
 digitalWrite(lmot1,LOW);
 digitalWrite(rmot2,LOW);
 digitalWrite(lmot2,LOW);
 rotateleft();
 forward();
}

void pause()
{
  digitalWrite(rmot1, LOW);
  digitalWrite(lmot1, LOW);
  digitalWrite(rmot2, LOW);
  digitalWrite(lmot2, LOW);
  delay(500);
}

//void rotateleft()
//{
  //digitalWrite(lmot1,LOW);
  //digitalWrite(lmot2,LOW);
  //digitalWrite(rmot1,HIGH);
  //digitalWrite(rmot2,LOW);
  //delay(500);
//}
  
//void rotateright()
//{
  //digitalWrite(lmot1,LOW);
  //digitalWrite(lmot2,LOW);
  //digitalWrite(rmot1,HIGH);
  //digitalWrite(rmot2,LOW);
  //delay(500);
//}
 
int ultrasonic_dist(int trigPin,int echoPin)
{
  long duration, inches, cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  return cm;
}
  
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds/29/2;
}
