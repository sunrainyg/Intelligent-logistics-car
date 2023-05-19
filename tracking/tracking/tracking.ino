//#include <Servo.h> 
const int Left_motor=8;          //左电机(IN3) 输出0  前进   输出1 后退
const int Left_motor_pwm=9;      //左电机PWM调速
 
const int Right_motor_pwm=10;    // 右电机PWM调速
const int Right_motor=11;        // 右电机后退(IN1)  输出0  前进   输出1 后退

const int key=A2;                //定义按键 数字A2 接口

const int SensorRight = 3;   	//右循迹红外传感器(P3.2 OUT1)
const int SensorLeft = 4;     	//左循迹红外传感器(P3.3 OUT2)

const int ceqian = 6;     //右侧前循迹红外传感器
//const int cehou = 5;     //右侧后循迹红外传感器

const int Echo = A1;  // Echo回声脚(P2.0)
const int Trig =A0;  //  Trig触发脚(P2.1)

int SL;    //左循迹红外传感器状态
int SR;    //右循迹红外传感器状态
int CQ;    //右侧前循迹红外传感器状态
//int CH;    //右侧后循迹红外传感器状态


//==============================================================

void setup()
{
  //初始化电机驱动IO为输出方式
  pinMode(Left_motor,OUTPUT);      //PIN 8 8脚无PWM功能
  pinMode(Left_motor_pwm,OUTPUT);  //PIN 9 (PWM)
  pinMode(Right_motor_pwm,OUTPUT); //PIN 10 (PWM) 
  pinMode(Right_motor,OUTPUT);     //PIN 11 (PWM)
  
  pinMode(key,INPUT);              //定义按键接口为输入接口

  pinMode(SensorRight, INPUT);     //定义右循迹红外传感器为输入
  pinMode(SensorLeft, INPUT);      //定义左循迹红外传感器为输入
  pinMode(ceqian,INPUT);          //定义右侧前循迹红外传感器为输入
  //pinMode(cehou,INPUT);           //定义右侧后循迹红外传感器为输入
  
  pinMode(Echo, INPUT);    // 定义超声波输入脚
  pinMode(Trig, OUTPUT);   // 定义超声波输出脚
}

//=====================基本动作=====================

void run();        //前进
void frun();       //快速前进
void brake();      //停止
void left();       //左转
void spin_left();  //小半径左转
void yd_left();    //原地左转
void right();      //右转
void spin_right(); //小半径右转
void yd_right();   //原地右转
void back();       //后退


void run()     //前进
{
  digitalWrite(Right_motor,LOW);       // 右电机前进
  digitalWrite(Right_motor_pwm,HIGH);  // 右电机前进     
  analogWrite(Right_motor_pwm,100);     //PWM比例0~255调速，左右轮差异略增减
  
  digitalWrite(Left_motor,LOW);        // 左电机前进
  digitalWrite(Left_motor_pwm,HIGH);   //左电机PWM     
  analogWrite(Left_motor_pwm,100);      //PWM比例0~255调速，左右轮差异略增减
}

void frun()
{
  digitalWrite(Right_motor,LOW);       // 右电机前进
  digitalWrite(Right_motor_pwm,HIGH);  // 右电机前进     
  analogWrite(Right_motor_pwm,200);     //PWM比例0~255调速，左右轮差异略增减
  
  digitalWrite(Left_motor,LOW);        // 左电机前进
  digitalWrite(Left_motor_pwm,HIGH);   //左电机PWM     
  analogWrite(Left_motor_pwm,200);     //PWM比例0~255调速，左右轮差异略增减
}

void brake()         //刹车，停车
{
  digitalWrite(Right_motor_pwm,LOW);  // 右电机PWM 调速输出0      
  analogWrite(Right_motor_pwm,0);     //PWM比例0~255调速，左右轮差异略增减

  digitalWrite(Left_motor_pwm,LOW);   //左电机PWM 调速输出0          
  analogWrite(Left_motor_pwm,0);      //PWM比例0~255调速，左右轮差异略增减
}

void left()         //左转(左轮不动，右轮前进)
{
  digitalWrite(Right_motor,LOW);       //右电机前进
  digitalWrite(Right_motor_pwm,HIGH);  //右电机前进     
  analogWrite(Right_motor_pwm,150);    //PWM比例0~255调速，左右轮差异略增减
  
  digitalWrite(Left_motor,LOW);        // 左电机前进
  digitalWrite(Left_motor_pwm,LOW);    //左电机PWM     
  analogWrite(Left_motor_pwm,0);       //PWM比例0~255调速，左右轮差异略增减
}

void spin_left()         //左转(左轮后退，右轮前进)
{
  digitalWrite(Right_motor,LOW);        // 右电机前进
  digitalWrite(Right_motor_pwm,HIGH);   // 右电机前进     
  analogWrite(Right_motor_pwm,150);     //PWM比例0~255调速，左右轮差异略增减
  
  digitalWrite(Left_motor,HIGH);        // 左电机后退
  digitalWrite(Left_motor_pwm,HIGH);    //左电机PWM     
  analogWrite(Left_motor_pwm,50);       //PWM比例0~255调速，左右轮差异略增减
}

void yd_left()    //原地左转
{
  digitalWrite(Right_motor,LOW);        // 右电机前进
  digitalWrite(Right_motor_pwm,HIGH);   // 右电机前进     
  analogWrite(Right_motor_pwm,150);     //PWM比例0~255调速，左右轮差异略增减
  
  digitalWrite(Left_motor,HIGH);        // 左电机后退
  digitalWrite(Left_motor_pwm,HIGH);    //左电机PWM     
  analogWrite(Left_motor_pwm,150);      //PWM比例0~255调速，左右轮差异略增减
}

void right()        //右转(右轮不动，左轮前进)
{
   digitalWrite(Right_motor,LOW);     // 右电机不转
  digitalWrite(Right_motor_pwm,LOW);  // 右电机PWM输出0     
  analogWrite(Right_motor_pwm,0);     //PWM比例0~255调速，左右轮差异略增减
  
  digitalWrite(Left_motor,LOW);       // 左电机前进
  digitalWrite(Left_motor_pwm,HIGH);  //左电机PWM     
  analogWrite(Left_motor_pwm,150);    //PWM比例0~255调速，左右轮差异略增减
}

void spin_right()        //右转(右轮后退，左轮前进)
{
  digitalWrite(Right_motor,HIGH);      // 右电机后退
  digitalWrite(Right_motor_pwm,HIGH);  // 右电机PWM输出1     
  analogWrite(Right_motor_pwm,50);     //PWM比例0~255调速，左右轮差异略增减
  
  digitalWrite(Left_motor,LOW);       // 左电机前进
  digitalWrite(Left_motor_pwm,HIGH);  //左电机PWM     
  analogWrite(Left_motor_pwm,150);    //PWM比例0~255调速，左右轮差异略增减 
}

void yd_right()       //原地右转
{
  digitalWrite(Right_motor,HIGH);      // 右电机后退
  digitalWrite(Right_motor_pwm,HIGH);  // 右电机PWM输出1     
  analogWrite(Right_motor_pwm,150);    //PWM比例0~255调速，左右轮差异略增减
  
  digitalWrite(Left_motor,LOW);       // 左电机前进
  digitalWrite(Left_motor_pwm,HIGH);  //左电机PWM     
  analogWrite(Left_motor_pwm,150);    //PWM比例0~255调速，左右轮差异略增减
}

void back()          //后退
{
  digitalWrite(Right_motor,HIGH);      // 右电机后退
  digitalWrite(Right_motor_pwm,HIGH);  // 右电机前进     
  analogWrite(Right_motor_pwm,150);    //PWM比例0~255调速，左右轮差异略增减
  
  digitalWrite(Left_motor,HIGH);      // 左电机后退
  digitalWrite(Left_motor_pwm,HIGH);  //左电机PWM     
  analogWrite(Left_motor_pwm,150);    //PWM比例0~255调速，左右轮差异略增减
}

//============================================================

float ceju()   //量出前方距离 
{
  float juli;
  
  digitalWrite(Trig, LOW);                // 给触发脚低电平2μs
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);               // 给触发脚高电平10μs，这里至少是10μs
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);                // 持续给触发脚低电
  
  juli = pulseIn(Echo, HIGH)/58;  // 读取高电平时间(单位：微秒),除以58等于厘米

  return juli;
}  

//=======================模块动作=============================

void go();          //循迹
void bizhang();     //避障1
void bizhang2();    //避障2

void go();        //寻迹
void bizhang();   //避障
//void wt();        //微调动作
//void weitiao();   //位置微调函数

void go()
{
  SR = digitalRead(SensorRight);    //有信号表明在白色区域，车子底板上L1亮；没信号表明压在黑线上，车子底板上L1灭
  SL = digitalRead(SensorLeft);     //有信号表明在白色区域，车子底板上L2亮；没信号表明压在黑线上，车子底板上L2灭
  if (SL == HIGH && SR == HIGH)     //黑为HIGH,白为LOW
    run();   //调用前进函数
  else if (SL == HIGH && SR == LOW) // 左循迹红外传感器,检测到信号，车子向右偏离轨道，向左转 
    left();
  else if (SR == HIGH && SL == LOW) // 右循迹红外传感器,检测到信号，车子向左偏离轨道，向右转  
    right();
  else // 都是白色,
  spin_left();
}

void bizhang()
{
  float x1,x2;
  yd_left();
  delay(150);    //控制探测时转弯角度
  brake();
  x1=ceju();
  yd_right();
  delay(230);    //控制探测时转弯角度
  brake();
  x2=ceju();
  
  if(x1<x2)        //向右避障
  {
    yd_right();
    delay(400);     //控制避障转弯角度
    brake();
    run();
    delay(580);     //控制斜向前进距离
    brake();
    
    yd_left();
    delay(300);    //控制左转角度
    brake();
    run();
    delay(1500);    //控制直行距离
    brake();
    
    yd_left();
    delay(380);    //控制左转角度
    brake();
    
    do
    {
      SR = digitalRead(SensorRight);
      SL = digitalRead(SensorLeft);
      run();
    }while(SL==LOW && SR==LOW);
    brake();
    
    yd_right();
    delay(360);
    brake();
  }
  else if(x1>x2)   //向左避障
  {
    yd_left();
    delay(320);    //控制避障转弯角度
    brake();
    run();
    delay(540);     //控制斜向前进距离
    brake();
    
    yd_right();
    delay(280);    //控制右转角度
    brake();
    run();
    delay(1500);    //控制直行距离
    brake();
    
    yd_right();
    delay(400);    //控制右转角度
    brake();
    
    do
    {
      SR = digitalRead(SensorRight);
      SL = digitalRead(SensorLeft);
      run();
    }while(SL==LOW && SR==LOW);
    brake();
    
    yd_left();
    delay(300);
    brake();
  }
  brake();
}

//========//=========//==========//=
void bizhang2()
{
  float d1,d2;
  
  while(1)
  {
    d1=ceju();
    run();
    delay(60);
    brake();
    if(d1<40)
      break;
  }
  
  yd_left();
  delay(200);    //控制探测时转弯角度
  brake();
  d1=ceju();  //左边障碍物的距离
  yd_right();
  delay(320);    //控制探测时转弯角度
  brake();
  d2=ceju();  //右边障碍物的距离
  
  if(d1>d2)         //***向左避障***//
  {
    yd_left();
    delay(380);    //控制避障转弯角度
    brake();
    run();
    delay(550);     //控制斜向前进距离
    brake();
    
    yd_right();
    delay(280);    //控制右转角度
    brake();
    run();
    delay(600);    //控制直行距离
    brake();
    
    yd_right();
    delay(360);    //控制右转角度
    brake();
    
    do
    {
      SR = digitalRead(SensorRight);
      SL = digitalRead(SensorLeft);
      run();
    }while(SL==LOW && SR==LOW);
    brake();
    
    yd_left();
    delay(300);
    brake();
  }
  else if(d1<d2)    //***向右避障***//
  {
    yd_right();
    delay(60);     //控制避障转弯角度
    brake();
    run();
    delay(580);     //控制斜向前进距离
    brake();
    
    yd_left();
    delay(300);    //控制左转角度
    brake();
    run();
    delay(600);    //控制直行距离
    brake();
    
    yd_left();
    delay(380);    //控制左转角度
    brake();
    
    do
    {
      SR = digitalRead(SensorRight);
      SL = digitalRead(SensorLeft);
      run();
    }while(SL==LOW && SR==LOW);
    brake();
    
    yd_right();
    delay(360);
    brake();
  }
  brake();
}

//========//=========//========//====

/*void wt()
{
  SR = digitalRead(SensorRight);
  SL = digitalRead(SensorLeft);
  CQ = digitalRead(ceqian);
  CH = digitalRead(cehou);
  
  if(CQ==HIGH && CH==HIGH)
  {
    if (SL == HIGH && SR == LOW) // 左循迹红外传感器,检测到信号，车子向右偏离轨道，向左转
    {
      yd_left();
      delayMicroseconds(400);
      brake();
    }
    else if (SR == HIGH && SL == LOW) // 右循迹红外传感器,检测到信号，车子向左偏离轨道，向右转
    {  
      yd_right();
      delayMicroseconds(400);
      brake();
    }
  }
  else if(CQ==HIGH && CH==LOW)
  {
    run();
    delayMicroseconds(400);
    brake;
  }
  else if(CQ==LOW && CH==HIGH)
  {
    back();
    delayMicroseconds(200);
    brake();
  }
}

void weitiao()
{
  SR = digitalRead(SensorRight);
  SL = digitalRead(SensorLeft);
  CQ = digitalRead(ceqian);
  CH = digitalRead(cehou);
  
  while(SR==LOW || SL==LOW || CQ==LOW || CH==LOW)
  {
    wt();
  }
  brake();
}*/

//==========================================================

void keysacn()//按键扫描
{
  int val;
  val=digitalRead(key);       //读取数字7 口电平值赋给val，按下为HIGH
  while(!digitalRead(key));    //当按键没被按下时，一直循环
  
  while(digitalRead(key))//当按键被按下时
  {
    delay(10);	            //延时10ms
    val=digitalRead(key);   //读取数字7 口电平值赋给val
    if(val==HIGH)           //第二次判断按键是否被按下
    {
      while(!digitalRead(key));	//判断按键是否被松开
    }
  }
  
  delay(2000);
}

//======================================================

void loop()
{ 
  int n=0,i;
  keysacn();    //调用按键扫描函数
  
  do
  {
    SR = digitalRead(SensorRight);
    SL = digitalRead(SensorLeft);
    run();
  }while(SL==LOW && SR==LOW);
  delay(10);


  while(1)       //从起点开始跑全程
  {
    go();
    
    CQ=digitalRead(ceqian);
    
    if(CQ==HIGH)
    {
      brake();
    
      if(n==4 || n==9)
      {
        back();    //刹车
        delay(60);
        brake();
        //weitiao();
        delay(2000);
      }
      else if(n==2)
      {
        back();    //刹车
        delay(60);
        brake();
        //weitiao();
        delay(80);
        frun();
        delay(900);
        brake();
      }
      else if(n==7)
      {
        back();   //刹车
        delay(80);
        brake();
        //weitiao();
        bizhang();     //执行避障
      }
      else if(n==11)
      {
        brake();
        //yd_right();   //右转弥补寻迹到最后左转的不足
        //delay(180);
        brake();
        for(i=0;i<1;i++)
        {
          run();
          delay(300);
        }
        brake();
        while(n==11);
      }
      
      do
      {
        CQ=digitalRead(ceqian);
        go();
      }while(CQ==HIGH);
      delay(130);
      brake();
      
      n=n+1;
      
    }
    
   /* while(n==12)
    brake();*/
  }
}














