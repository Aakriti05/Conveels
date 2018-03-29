int trigPinf=12;
int echoPinf=13;
int trigPinr=4;
int echoPinr=9;
int trigPinl=2;
int echoPinl=3;
int trigPinb=A0;
int echoPinb=A1;
int LeftMotorForward = 10; 
int LeftMotorBackward = 11;
int RightMotorForward = 6;
int RightMotorBackward = 5;
char CurrentInput = 'x';
char LastInput = 'x';
char mode;
char directions[1000];
int j=0;

void setup() 
{// put your setup code here, to run once:
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  directions[0] = '\0';
  Serial.begin(9600);
  Serial.println("Enter mode of the wheelchair : \n 0 for self-driven mode \n 1 for giving directions (Teach Mode) ");  
}

int forward()
{
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorForward, HIGH);
    delay(500);
    return 0;
}

int backward()
{
   digitalWrite(RightMotorBackward, HIGH);
   digitalWrite(LeftMotorBackward, HIGH);
   delay(500);
   return 0;
}

int right()
{
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  delay(500);
  return 0;
}

int left()
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  delay(500);
  return 0;
}

void pause()
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  delay(500);
}


void loop() 
{ // put your main code here, to run repeatedly:
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  
   while(!Serial.available());
   
   mode = Serial.read();
   Serial.println(mode);
   if(mode == '0')
   {
      for(int i=0;directions[i]!='\0';i++)
      {
        if(directions[i]=='w') 
          {
           float distf=ultrasonic_dist(trigPinf,echoPinf);
           float distb=ultrasonic_dist(trigPinb,echoPinb);
           float distl=ultrasonic_dist(trigPinl,echoPinl)-3.5;
           float distr=ultrasonic_dist(trigPinr,echoPinr)-4.5;
           Serial.print(distl);
           Serial.print(" ");
           Serial.println(distr);
           Serial.print(" ");
           Serial.print(distf);
           Serial.print(" ");
           Serial.println(distb);
           Serial.print(" ");
           if (distf<=18)
             {
             if (distr>=distl)
                {
                right();
                delay(50);
                left();
                delay(50);
                forward();
                }           
            }
         }
        else if(directions[i] =='a') {int j=left();}
        else if(directions[i] == 'd') {int j=right();}
        else if(directions[i] == 's') {int j=backward();}
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
        if(c=='w') int i=forward();
        else if(c =='a') int i=left();
        else if(c == 'd') int i=right();
        else if(c == 's') int i=backward();
        if (j==1000)
        {
          pause();
          }
        }
        Serial.println(j);
        //delay(500);
      }while(c!='e');
      pause();
      directions[++j]='\0';    
    }
    
    Serial.println("Enter mode of the wheelchair : \n 0 for self-driven mode \n 1 for giving directions(Teach Mode) ");     
}
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
  return microseconds / 29 / 2;
  }

