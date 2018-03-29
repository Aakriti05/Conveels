int LeftMotorForward = 10; 
int LeftMotorBackward = 11;
int RightMotorForward = 6;
int RightMotorBackward = 5;
char CurrentInput = 'x';
char LastInput = 'x';
char mode;
char directions[1000];
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

void forward()
{
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorForward, HIGH);
    delay(500);
}

void backward()
{
   digitalWrite(RightMotorBackward, HIGH);
   digitalWrite(LeftMotorBackward, HIGH);
   delay(500);
}

void right()
{
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  delay(500);
}

void left()
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  delay(500);
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
  
  
   while(!Serial.available());
   
   mode = Serial.read();
   Serial.println(mode);
   if(mode == '0')
   {
      for(int i=0;directions[i]!='\0';i++)
      {
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
        }
        Serial.println(j);
        delay(500);
      }while(c!='e');
      directions[++j]='\0';    
    }
    
    Serial.println("Enter mode of the wheelchair : \n 0 for self-driven mode \n 1 for giving directions(Teach Mode) ");     
}
