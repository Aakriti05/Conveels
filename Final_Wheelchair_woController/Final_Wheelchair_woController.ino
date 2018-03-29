int lmot1=6;
int lmot2=5;
int rmot1=10;
int rmot2=11;
int trigPinf=12;
int echoPinf=13;
int trigPinr=4;
int echoPinr=9;
int trigPinl=2;
int echoPinl=3;
int trigPinb=A0;
int echoPinb=A1;
int pwm_int=200, pwma=0;
char CurrentInput = 'x';
char LastInput = 'x';
char mode;
char directions[1000];
char last;
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
  pinMode(trigPinl, OUTPUT);
  pinMode(echoPinl, INPUT);
  pinMode(trigPinb, OUTPUT);
  pinMode(echoPinb, INPUT);
  directions[0] = '\0';
  Serial.begin(9600);
  Serial.println("Enter mode of the wheelchair : \n 0 for self-driven mode \n 1 for giving directions (Teach Mode) "); 
}

void loop() 
{
// put your main code here, to run repeatedly:
while(!Serial.available());
   
   mode = Serial.read();
   Serial.println(mode);
   if(mode == '0')
   {
      for(int i=0;directions[i]!='\0';i++)
      {
        float distf=ultrasonic_dist(trigPinf,echoPinf);
        float distb=ultrasonic_dist(trigPinb,echoPinb);
        float distl=ultrasonic_dist(trigPinl,echoPinl)-3.5;
        float distr=ultrasonic_dist(trigPinr,echoPinr)-4.5;
        if(distb<=15) pwma=pwm_int+55;
        else pwma=pwm_int;
        
        if(directions[i]=='w' ) 
          {
          if(distf<=18)
            {
            if(distr>=distl)
            {
               rotateright(pwma);
               int t1=millis();
               while(distl<18)
                   {
                   forward(pwma);
                   float distl=ultrasonic_dist(trigPinr,echoPinr)-4.5;
                   }
              int t2=millis();
              rotateleft(pwma);
              int t3=millis();
              float distl=ultrasonic_dist(trigPinr,echoPinr)-4.5;
              while(distl<10)
            {
              forward(pwma);
              float distl=ultrasonic_dist(trigPinr,echoPinr)-4.5;
              }
              int t4=millis();
              rotateleft(pwma);
              forward(pwma);
              delay(t2-t1);
              rotateright(pwma);
              i=(t4-t3)/500;
          }
            
            else
            { 
              rotateleft(pwma);
              int t1=millis();
            while(distr<18)
            {
              forward(pwma);
              float distr=ultrasonic_dist(trigPinr,echoPinr)-4.5;
              }
              int t2=millis();
              rotateright(pwma);
              int t3=millis();
              float distr=ultrasonic_dist(trigPinr,echoPinr)-4.5;
              while(distl<10)
            {
              forward(pwma);
              float distr=ultrasonic_dist(trigPinr,echoPinr)-4.5;
              }
              int t4=millis();
              rotateright(pwma);
              forward(pwma);
              delay(t2-t1);
              rotateleft(pwma);
              i=(t4-t3)/500;
          }
            }
          else
            forward(pwma);
        }
        else if(directions[i] =='a') left();
        else if(directions[i] == 'd') right();
        else if(directions[i] == 's') backward(pwma);
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
        if(c=='w') forward(pwm_int);
        else if(c =='a') left();
        else if(c == 'd') right();
        else if(c == 's') backward(pwm_int);
        }
        Serial.println(j);
        delay(500);
      }while(c!='e');
      pause();
      directions[++j]='\0';    
    }
    
    Serial.println("Enter mode of the wheelchair : \n 0 for self-driven mode \n 1 for giving directions(Teach Mode) ");
}


void forward(int pwm)
{
    analogWrite(rmot1, pwm);
    analogWrite(lmot1, pwm);
    delay(500);
    
}

void backward(int pwm)
{
   analogWrite(rmot2, pwm);
   analogWrite(lmot2, pwm);
   delay(500);
   
}

void right()
{
  digitalWrite(rmot1, HIGH);
  digitalWrite(lmot1, LOW);
  delay(500);
  
}

void left()
{
  digitalWrite(rmot1, LOW);
  digitalWrite(lmot1, HIGH);
  delay(500);
  
}

void pause()
{

  digitalWrite(rmot1, LOW);
  digitalWrite(lmot1, LOW);
  digitalWrite(rmot2, LOW);
  digitalWrite(lmot2, LOW);
  delay(500);
}

void rotateleft(int pwm)
{
  analogWrite(lmot1,pwm);
  analogWrite(lmot2,0);
  analogWrite(rmot1,0);
  analogWrite(rmot2,pwm);
  delay(750);
  }
  
void rotateright(int pwm)
{
  analogWrite(lmot1,0);
  analogWrite(lmot2,pwm);
  analogWrite(rmot1,pwm);
  analogWrite(rmot2,0);
  delay(750);
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
