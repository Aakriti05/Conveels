#include <EEPROM.h>
float Q[6][3]={0};
double reward=0;
float a=0.5,y=0.4;
int state;
float epsilon=0.2;
int action=0;
int store_loc=1;
int loc_togo=0;
int loc_at=0;
int for_eeprom=0;
int count=0;
void setup() 
{
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() 
{
  double punishment=0;
  // put your main code here, to run repeatedly:
  if(count==0)
  {
    EEPROM.put(store_loc,1);
    count++
    }
  EEPROM.get(store_loc,loc_at);
  Serial.print("You are at location : ");
  Serial.println(loc_at);
  if(loc_at==1)
  {
    Serial.print("Enter 2 for location 2 or 3 for location 3");
    while(!Serial.available()){}
    loc_togo=Serial.parseInt();
  }
  else if(loc_at==2)
  {
    Serial.print("Enter 1 for location 1 or 3 for location 3");
    while(!Serial.available()){}
    loc_togo=Serial.parseInt();
  }
  else if(loc_at==3)
  {
  Serial.print("Enter 1 for location 1 or 2 for location 2");
  while(!Serial.available()){}
  loc_togo=Serial.parseInt();
  }
  if(loc_at==1 && loc_togo==2)
  {
    state=0;
    Serial.println("Going from location 1 to 2");
    float temp=random(0,100000) ;
    temp=temp/100000;
    if(temp<epsilon)
    action=random(0,3);
    else
    action=selectmaxaction();
    Serial.println(action);
    if(action==0)
    {
      Serial.println("Path 1. Enter time, dist and double u_i.Press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println( u_i);
      punishment=time_taken+ dist_trav+ u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
      else if(action==1)
      {
      Serial.println("Path 2. Enter time, dist and double u_i.press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println(u_i);
      punishment=time_taken+dist_trav+ u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
      else if(action==2)
      {
      Serial.println("Path 3. Enter time, dist and double u_i.press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println( u_i);
      punishment=   time_taken + dist_trav + u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
    QLearning();
    }
    else if(loc_at==2 && loc_togo==3)
{
  state=1;
  Serial.println("Going from location 2 to 3");
  float temp=random(0,100000) ;
  temp=temp/100000;
  if(temp<epsilon) 
    action=random(0,3);
  else
    action=selectmaxaction();
    Serial.println(action);
    if(action==0)
    {
      Serial.println("Path 1. Enter time, dist and double u_i.Press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println( u_i);
      punishment=time_taken+ dist_trav+ u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
     else if(action==1)
      {
      Serial.println("Path 2. Enter time, dist and double u_i.press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println(u_i);
      punishment=time_taken+dist_trav+ u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
      else if(action==2)
      {
      Serial.println("Path 3. Enter time, dist and double u_i.press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println( u_i);
      punishment=   time_taken + dist_trav + u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
    QLearning();
    }
  else if(loc_at==1 && loc_togo==3)
  {
    state=2;
    Serial.println("Going from location 1 to 3");
    float temp=random(0,100000) ;
    temp=temp/100000;
    if(temp<epsilon)
    action=random(0,3);
    else
    action=selectmaxaction();
    Serial.println(action);
    if(action==0)
    {
      Serial.println("Path 1. Enter time, dist and double u_i.Press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println( u_i);
      punishment=time_taken+ dist_trav+ u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
     else if(action==1)
    {
      Serial.println("Path 2. Enter time, dist and double u_i.press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println(u_i);
      punishment=time_taken+dist_trav+ u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
      else if(action==2)
    {
      Serial.println("Path 3. Enter time, dist and double u_i.press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println( u_i);
      punishment=   time_taken + dist_trav + u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
      QLearning();
}
      else if(loc_at==2 && loc_togo==1)
{
  state=3;
  Serial.println("Going from location 2 to 1");
  float temp=random(0,100000) ;
  temp=temp/100000;
  if(temp<epsilon)
    action=random(0,3);
  else
    action=selectmaxaction();
    Serial.println(action);
    if(action==0)
    {
      Serial.println("Path 1. Enter time, dist and double u_i.Press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println( u_i);
      punishment=time_taken+ dist_trav+ u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
     else if(action==1)
    {
      Serial.println("Path 2. Enter time, dist and double u_i.press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println(u_i);
      punishment=time_taken+dist_trav+ u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
      else if(action==2)
    {
      Serial.println("Path 3. Enter time, dist and double u_i.press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println( u_i);
      punishment=   time_taken + dist_trav + u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
            QLearning();
}

else if(loc_at==3 && loc_togo==2)
{
  state=4;
  Serial.println("Going from location 3 to 2");
  float temp=random(0,100000) ;
  temp=temp/100000;
  if(temp<epsilon)
    action=random(0,3);
  else
    action=selectmaxaction();
    Serial.println(action);
    if(action==0)
    {
      Serial.println("Path 1. Enter time, dist and double u_i.Press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println( u_i);
      punishment=time_taken+ dist_trav+ u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
     else if(action==1)
     {
      Serial.println("Path 2. Enter time, dist and double u_i.press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println(u_i);
      punishment=time_taken+dist_trav+ u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
      else if(action==2)
     {
      Serial.println("Path 3. Enter time, dist and double u_i.press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println( u_i);
      punishment=   time_taken + dist_trav + u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
            QLearning();
}
else if(loc_at==3 && loc_togo==1)
{
  state=5;
  Serial.println("Going from location 3 to 1");
  float temp=random(0,100000) ;
  temp=temp/100000;
  if(temp<epsilon)
    action=random(0,3);
  else
    action=selectmaxaction();
    Serial.println(action);
    if(action==0)
    {Serial.println("Path 1. Enter time, dist and double u_i.Press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println( u_i);
      punishment=time_taken+ dist_trav+ u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
     else if(action==1)
    {
      Serial.println("Path 2. Enter time, dist and double u_i.press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
      Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println(u_i);
      punishment=time_taken+dist_trav+ u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
      else if(action==2)
    {
      Serial.println("Path 3. Enter time, dist and double u_i.press enter after each input. make sure time+dist+double u_i is not greater than 100.");
      while(!Serial.available())
      {}
      double time_taken=Serial.parseFloat();
     Serial.println( time_taken);
      while(!Serial.available()){}
      double dist_trav=Serial.parseFloat();
      Serial.println( dist_trav);
      while(!Serial.available()){}
      double u_i=Serial.parseFloat();
      Serial.println( u_i);
      punishment=   time_taken + dist_trav + u_i;
      Serial.print("punish: ");
      Serial.println(punishment);
      reward=map(punishment,0,100,100,0);
      Serial.print("reward: ");
      Serial.println(reward);
      }
    QLearning();
    }

  }

int selectmaxaction()
{
  float max_q=max(Q[state][0],max(Q[state][1],Q[state][2]));
  for(int i =0;i<6;i++)
  {
    if(Q[state][i]==max_q)
    {return i;
      }
    }
  }
void  QLearning()
  {
  Serial.println("Went into QLearning");  
  int best_possible_action=selectmaxaction();
  Serial.println(best_possible_action);
    Q[state][action]=Q[state][action] + a*(reward + y*(best_possible_action) - Q[state][action]);
    EEPROM.put(2,Q);
    for(int i=0;i<6;i++)
    {
      for(int j=0;j<3;j++)
      {
        Serial.print(Q[i][j]);
        Serial.print(" ");
        }
        Serial.println();
      }
    }
