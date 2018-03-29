int trig=11;
int echo=10;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
  double duration = (pulseIn(echo, HIGH))/(1000);
  double dist=(340*duration/2)*100;
Serial.println(duration);
delay(300);
}
