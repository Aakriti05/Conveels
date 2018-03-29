/*Obstacle avoider using 4 ultrasonic sensor v1.0
 * Author: TheRandomDude
 * Credits: To the random dude who wrote the ultrasonic code Its pretty darn accurate.
 */
int lmot1=10;
int lmot2=11;
int rmot1=6;
int rmot2=5;
int trigPinf=12;
int echoPinf=13;
int trigPinr=4;
int echoPinr=9;
int trigPinl=2;
int echoPinl=3;
int trigPinb=A0;
int echoPinb=A1;
int pwm_int=200, pwma=0;

void setup() {
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
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(7,HIGH);
digitalWrite(8,HIGH);
float distf=ultrasonic_dist(trigPinf,echoPinf);
Serial.print(distf);
Serial.print(" ");
float distb=ultrasonic_dist(trigPinb,echoPinb);
float distl=ultrasonic_dist(trigPinl,echoPinl)-3.5;
float distr=ultrasonic_dist(trigPinr,echoPinr)-4.5;
Serial.print(distl);
Serial.print(" ");
Serial.println(distr);
if(distb<=15)
{
  pwma=pwm_int+55;
  }
  else 
  {
    pwma=pwm_int;
    }
    
if(distl<3)
{
  rotateright(140);
  }  
else if(distr<3)
{
  rotateleft(140);
  }
  
if(distf<=18)
{
  if(distr>=distl)
  {
    rotateright(pwma);
    }
    else
    { 
      rotateleft(pwma);
      }
  }
  else
  {
    go_straight(pwma);
    }
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


  void go_straight(int pwm)
  {
  analogWrite(lmot1,pwm);
  analogWrite(lmot2,0);
  analogWrite(rmot1,pwm);
  analogWrite(rmot2,0);
    }
