
//Components

struct Wheel{
  int x,y;
  char dirn;
  void setWheel(int i,int j)
    {
      pinMode(i,OUTPUT);
      pinMode(j,OUTPUT);
      x=i;y=j;
    }
  void runWheel(char dirn)
    {
      if(dirn=='f')
      {
      digitalWrite(x,HIGH); 
      digitalWrite(y,LOW);
      }
      else
      if(dirn=='b')
      {
        digitalWrite(x,LOW);
        digitalWrite(y,HIGH);
      }
      else
      if(dirn=='n')
      {
        digitalWrite(x,LOW);
        digitalWrite(y,LOW);
      }
    }      
};

class Car
{
private:
  Wheel Left,Right;
  bool isStarted=false;
  int n;
public:
  void Setup(int Left0,int Left1,int Right0,int Right1)
  {
     Left.setWheel(Left0,Left1);
     Right.setWheel(Right0,Right1);
     isStarted=true;
     n=0;
  }

  void Count(int N)
  {
    if(n>=N)
    {
      isStarted=false;
    }
    n++;
  }

  void MoveUp(int t) const
  {
    if(isStarted)
    {
     Left.runWheel('f');
     Right.runWheel('f');
     digitalWrite(4,HIGH);
     delay(t);
     digitalWrite(4,LOW);
    }
    else DoNothing();
  }

  void MoveDown(int t) const
  {
    if(isStarted)
    {
     Left.runWheel('b');
     Right.runWheel('b');
     delay(t);
    }
    else DoNothing();
  }

  void TurnRight(int degree) const
  {
    float t= (degree/3)* 52;
    if(isStarted)
    {    
     Left.runWheel('f');
     Right.runWheel('b');
     digitalWrite(3,HIGH);
     delay(t);
     digitalWrite(3,LOW);
    }
    else DoNothing();
  }

  void TurnLeft(int degree) const
  {
    float t=(degree/3)*46;
    if(isStarted)
    {
     Left.runWheel('b');
     Right.runWheel('f');
     pinMode(2,OUTPUT);
     digitalWrite(2,HIGH);
     delay(t);
     digitalWrite(2,LOW);
    }
    else DoNothing();
  }

  void DoNothing() const
  {
      Left.runWheel('n');
      Right.runWheel('n');
  }

    void DoNothing(int t) const
  {
      DoNothing();
      delay(t);
  }
};

class IRSensor
{
private:
  int i,o;

public:
  void Setup(int pinIn,int pinOut)    
  {
    i=pinIn;
    o=pinOut;
    pinMode(i,INPUT);  
    pinMode(o,OUTPUT);
    digitalWrite(o,HIGH);
  }

  bool GetsBlack()
  {
    if(digitalRead(i)==0)
    {
      return false;
    }
    if(digitalRead(i)==1)
    {
      return true;
    }
  }
};

//Main Logic

Car car;
IRSensor IR1,IR2;

void setup() {
  car.Setup(7,8,6,5);
  IR1.Setup(13,A0);
  IR2.Setup(12,A1);
}

void loop() {
  if(IR1.GetsBlack())
  {
    car.TurnLeft(120);
  }
  else car.MoveUp(5);

}
