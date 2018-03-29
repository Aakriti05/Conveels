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

char last;
int lcount=0,fcount=0,ltime=0,ftime=0;
char cal;
int turndelr=1000;
int turndell=1000;


//from here

int loc[3][3]={(-1,0,5),(1,-1,2),(4,3,-1)};
int from=0;
int to=0;
int i,j;
int pathindexes[9][3];
int path_index;
char paths[27][100];
char directions[100];
int path;
int epsilon = 0.2;
int epsilonGreedyfunction();
int selectmaxaction();

double Q[6][3]={0};

//till here

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


 Serial.flush();
}

void loop()

{ 
    Serial.println("Press 0 to caliberate 90 degree turn.");
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
   digitalWrite(rmot1, LOW);
   turndelr=delfr-delir;
   Serial.flush();
   Serial.println("Press q to stop turning left.");
   pause();
   int delil=millis();
   do
   {
    digitalWrite(rmot1, LOW);
    digitalWrite(lmot1, HIGH);
   }while(Serial.read()!='q');
   int delfl=millis();
   digitalWrite(lmot1, LOW);
   int turndell=delfl-delil;
  }
  Serial.flush();
  Serial.println("Enter 0 to caliberate again or q to proceed.");
  while(!Serial.available()); 
  cal=Serial.read();
 }while(cal=='0');
 Serial.println("Enter mode of the wheelchair : \n 0 for self-driven mode \n 1 for giving directions (Teach Mode)");
 while(!Serial.available());
   
   mode = Serial.read();
   Serial.println(mode);
   if(mode == '0')
   {
     
     
      //add from here
      
      Serial.print("Enter from location 0 1 or 2");
      while(!Serial.available()){}
      from=Serial.parseInt();
      Serial.print("Enter to location 0 1 or 2");
      while(!Serial.available()){}
      to=Serial.parseInt();
      j=epsilonGreedyfunction();
      i=loc[from][to];
      path_index=pathindexes[i][j];
       for(int i=0;paths[path_index][i]!='\0';i++)
        {
            directions[i]=paths[path_index][i];
        }
        directions[i]='\0';
        
        // till here
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
   
   else if(mode == '1')
   { 
      Serial.println("Enter directions : w/a/s/d for forward/left/backward/right and e to exit Teach Mode");
      Serial.flush();
      while(!Serial.available());
      int j=0;
      char c;
      do 
      {
        c = Serial.read();
        if(c!='e')
        {
          directions[j++]=c;  
        if(c=='w') forward();
        else if(c =='a') left();
        else if(c == 'd') right();
        else if(c == 's') backward();
        }
        Serial.println(j);
        delay(500);
      }while(c!='e');
      pause();
      directions[++j]='\0';    
    }
    
  
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

void obstavoid()
{
 lcount=0, fcount=0;
 rotateleft();
 do
 {
  digitalWrite(rmot1,HIGH);
  digitalWrite(lmot1,HIGH);
  delay(100);
  lcount++;
 }while(ultrasonic_dist(trigPinr,echoPinr)<=5);
 delay(1000);
 
 rotateright();
 
 //do
 //{
  //digitalWrite(rmot1,HIGH);
  //digitalWrite(lmot1,HIGH);
  //delay(100);
 //}while(ultrasonic_dist(trigPinr,echoPinr)<=5);
 //delay(100);
 digitalWrite(rmot1,HIGH);
 digitalWrite(lmot1,HIGH);
 delay(1000);
 rotateright();
 
 digitalWrite(rmot1,HIGH);
 digitalWrite(lmot1,HIGH);
 delay(lcount*100);
 delay(1000);
 
 rotateleft();
} 

void rotateright()
{
  digitalWrite(rmot1, HIGH);
  digitalWrite(lmot1, LOW);
  delay(turndell); 
}

void rotateleft()
{
  digitalWrite(rmot1, LOW);
  digitalWrite(lmot1, HIGH);
  delay(turndelr);
}

void right()
{
  rotateright();
  forward();
}

void left()
{
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
// from here
int epsilonGreedyfunction()
{
  float temp=random(0,100000) ;
  temp=temp/100000;
  if(temp<epsilon)
    path=random(0,3);
  else
    path=selectmaxaction();
    
  return path;
}

int selectmaxaction()
{
  float max_q=max(Q[i][0],max(Q[i][1],Q[i][2]));
  for(int f =0;f<6;f++)
  {
    if(Q[i][f]==max_q)
    {
      return i;
      }
  }
}
  
  
   // till here
