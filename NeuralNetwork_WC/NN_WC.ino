int n=9; //no of example parameters
double in_pram[9][4];
double theta1[5][4];
double theta2[3][6];
int output[1][3];
int target[9][3];
int hidden_lay1[9][5];
double error=0;
int trained = 0;
void setup() {
  // put your setup code here, to run once:
  if(trained=0)
  {
for(int i=0;i<5;i++)
{
  for(int j=0;j<3;j++)
  {
    theta1[i][j]=rand()*10;
    theta2[j][i]=rand()*10;
    }
  }
  }
}
double sigmoid(double x)
{
  double sigmoid_x=1/(1+ exp(-x));
  return sigmoid_x;
  }

void loop() {
  if(trained=0) //checking if the wheelchair is trained or not;0=No and 1=Yes
  {
  for(int i=0;i<1;)
  {
    //feed-forward section
    for(int j=0;j<n;j++) //will run as many times as there are example parameters
    {
      for(int k=0;k<5;k++) //to find the values of the hidden layer
      {
      hidden_lay1[j][k]=sigmoid(theta1[k][0]*in_pram[k][0]+theta1[k][1]*in_pram[k][1]+theta1[k][2]*in_pram[k][2]+theta1[k][3]*in_pram[k][3]);
      }
      for(int k=0;k<3;k++) //to find the values of the output layer
      {
      output[j][k]=sigmoid(theta2[k][0]*in_pram[k][0]+theta2[k][1]*in_pram[k][1]+theta2[k][2]*in_pram[k][3]+theta2[k][3]*in_pram[k][3]);
      }
      
      //Error in target output and current output
    }
    trained = 1;
    exit(0);
    }
  }
  // put your main code here, to run repeatedly:
}
