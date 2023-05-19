//#include <SoftwareSerial.h>
#include<Servo.h>

//SoftwareSerial softSerial(2,3);   //设置一个软串口,Rx:2 , Tx:3

const char smml[20]={0x7E,0x00,0x08,0x01,0x00,0x02,0x01,0xAB,0xCD}; //扫码命令

char ma0[30]={'\0'};//储存条形码数据
//要抓物块的条码数据
const char ma[3][20]={{"ZJGXDS05"},{"ZJGXDS03"},{"ZJGXDS07"}};
int bidui=0;
int geshu=0;     //已扫条码的个数
int weizhi=0;    //小车到达的位置
int zwjd=0;      //小车已经抓物(放物)个数

const int left_go=11;
const int left_back=10;
const int right_back=9;
const int right_go=8;
const int djd=6;

Servo dj0;
Servo dj1;
Servo dj2;
Servo dj3;
Servo dj4;
const int KS=36;//15
Servo dj5;

const int ce_qian=12;
const int ce_hou=13;
const int ce_hl=7;

const int xj_left3=33;
const int xj_left2=31;
const int xj_left1=29;
const int xj_left=27;
const int xj_right=32;
const int xj_right1=30;
const int xj_right2=28;
const int xj_right3=26;

const int hw_bz_hou=4;  //左侧红外避障
const int hw_bz_qian=5; //右侧红外避障
const int hw_bz_fist=35;  //最前面红外防撞

const int cs_help_Trig=2;  //侧面超声波避障
const int cs_help_Echo=3;

const int csleft_Trig=22;
const int csleft_Echo=23;
const int csright_Trig=24;
const int csright_Echo=25;

int xjl;   //左循迹红外传感器状态
int xjl1;
int xjl2;
int xjl3;

int xjr;   //右循迹红外传感器状态
int xjr1;
int xjr2;
int xjr3;

int cq;    //右侧前循迹红外传感器状态
int ch;    //右侧后循迹红外传感器状态
int chl;   //右侧后轮处循迹红外传感器状态

int bz_qian;   //左侧红外避障状态
int bz_hou;    //右侧红外避障状态
int bz_fist;   //右侧超声的红外远距离探头状态

float x1;    //左测距离
float x2;    //右测距离
float x3;    //辅助避障距离

int t;
//===============//=============//=============//=============
int saoma();
void more_saoma();

int saoma()
{
  char c;
  char data[5]="DATA";
  int i=0,a=1;
  for(i=strlen(ma0);i>=0;i--)  //清空ma0中的信息
    ma0[i]='\0';
  //扫码命令
  
  while(Serial1.available()>0)  //每次发送扫码命令前清空串口信息
  {
    c=(char)Serial1.read();
  }
  c='\0';
  
  for(i=0;i<sizeof(smml);i++)  //发送扫码指令
  {
    Serial1.write(smml[i]);
  }
  delay(1000);
  
  i=0;
  
  while(Serial1.available()>0)      //将串口中的信息储存到m[]中
  {
    c=(char)Serial1.read();
    if((c>47 && c<58)||(c>64 && c<123)) //只提取数字与字母
    {
      ma0[i]=c;
      i++;
    }
  }
  i=strlen(ma0);
  if(strcmp(data,ma0+i-4)==0)
  {
    a=0;
    strcpy(ma0+i-4,ma0+i+1);
    strcpy(ma0,ma0+2);       //m中为二维码信息
    //Serial.println(ma0);
  }
  else
  {
    a=1;
    strcpy(ma0,ma0+i+5);
  }
  
  return a;   //0=成功  1=失败
}

void more_saoma()
{
  for(t=0;t<8;t++)
  {
    if(saoma()==0)
      break;
    dj0.write(84+t*2);  //原是82
    delay(5);
  }
}


//===============//============//=============//==============
void srun();
void llrun();
void run();
void frun();
void back();
void left();
void sleft();
void sfleft();
void right();
void rightback();
void sright();
void brake();
void ceju();
void help_ceju();


void frun()
{
  digitalWrite(right_go,HIGH);
  digitalWrite(right_back,LOW);     
  analogWrite(right_go,255);
  
  digitalWrite(left_go,HIGH);
  digitalWrite(left_back,LOW);     
  analogWrite(left_go,255);
  
  digitalWrite(djd,HIGH);
  delayMicroseconds(1484);
  digitalWrite(djd,LOW);
  delay(5);
}

void run()
{
  digitalWrite(right_go,HIGH);
  digitalWrite(right_back,LOW);     
  analogWrite(right_go,195);
  
  digitalWrite(left_go,HIGH);
  digitalWrite(left_back,LOW);     
  analogWrite(left_go,195);
  
  digitalWrite(djd,HIGH);
  delayMicroseconds(1484);
  digitalWrite(djd,LOW);
  delay(5);
}

void llrun()
{
  digitalWrite(right_go,HIGH);
  digitalWrite(right_back,LOW);     
  analogWrite(right_go,165);
  
  digitalWrite(left_go,HIGH);
  digitalWrite(left_back,LOW);     
  analogWrite(left_go,165);
  
  digitalWrite(djd,HIGH);
  delayMicroseconds(1484);
  digitalWrite(djd,LOW);
  delay(5);
}

void srun()
{
  digitalWrite(right_go,HIGH);
  digitalWrite(right_back,LOW);     
  analogWrite(right_go,100);
  
  digitalWrite(left_go,HIGH);
  digitalWrite(left_back,LOW);     
  analogWrite(left_go,100);
  
  digitalWrite(djd,HIGH);
  delayMicroseconds(1484);
  digitalWrite(djd,LOW);
  delay(5);
}


void back()
{
  digitalWrite(right_go,LOW);
  digitalWrite(right_back,HIGH);     
  analogWrite(right_back,200);
  
  digitalWrite(left_go,LOW);
  digitalWrite(left_back,HIGH);     
  analogWrite(left_back,200);
  
  digitalWrite(djd,HIGH);
  delayMicroseconds(1484);
  digitalWrite(djd,LOW);
  delay(5);
}

void left()
{
  digitalWrite(right_go,HIGH);
  digitalWrite(right_back,LOW);     
  analogWrite(right_go,255);
  
  digitalWrite(left_go,LOW);
  digitalWrite(left_back,LOW);     
  //analogWrite(left_go,0);
  
  digitalWrite(djd,HIGH);
  delayMicroseconds(800);
  digitalWrite(djd,LOW);
  delay(5);
}

void sleft()
{
  digitalWrite(right_go,HIGH);
  digitalWrite(right_back,LOW);     
  analogWrite(right_go,255);
  
  digitalWrite(left_go,LOW);
  digitalWrite(left_back,HIGH);     
  analogWrite(left_back,90);
  
  digitalWrite(djd,HIGH);
  delayMicroseconds(800);
  digitalWrite(djd,LOW);
  delay(5);
}

void sfleft()
{
  digitalWrite(right_go,HIGH);
  digitalWrite(right_back,LOW);     
  analogWrite(right_go,255);
  
  digitalWrite(left_go,LOW);
  digitalWrite(left_back,HIGH);     
  analogWrite(left_back,70);
  
  digitalWrite(djd,HIGH);
  delayMicroseconds(800);
  digitalWrite(djd,LOW);
  delay(5);
}

void right()
{
  digitalWrite(right_go,LOW);
  digitalWrite(right_back,LOW);     
  //analogWrite(right_go,200);
  
  digitalWrite(left_go,HIGH);
  digitalWrite(left_back,LOW);     
  analogWrite(left_go,250);
  
  digitalWrite(djd,HIGH);
  delayMicroseconds(2100);
  digitalWrite(djd,LOW);
  delay(5);
}

void rightback()
{
  digitalWrite(right_go,LOW);
  digitalWrite(right_back,LOW);     
  //analogWrite(right_go,200);
  
  digitalWrite(left_go,LOW);
  digitalWrite(left_back,HIGH);     
  analogWrite(left_back,250);
  
  digitalWrite(djd,HIGH);
  delayMicroseconds(2100);
  digitalWrite(djd,LOW);
  delay(5);
}

void sright()
{
  digitalWrite(right_go,LOW);
  digitalWrite(right_back,HIGH);     
  analogWrite(right_back,100);
  
  digitalWrite(left_go,HIGH);
  digitalWrite(left_back,LOW);     
  analogWrite(left_go,250);
  
  digitalWrite(djd,HIGH);
  delayMicroseconds(1490);
  digitalWrite(djd,LOW);
  delay(5);
}

void brake()
{
  digitalWrite(right_go,LOW);
  digitalWrite(right_back,LOW);
  
  digitalWrite(left_go,LOW);
  digitalWrite(left_back,LOW);
  
  for(t=0;t<200;t++)
  {
    digitalWrite(djd,HIGH);
    delayMicroseconds(1484);
    digitalWrite(djd,LOW);
    delayMicroseconds(19000);
  }
}

void ceju()
{
  digitalWrite(csleft_Trig,LOW);                // 给触发脚低电平2μs
  delayMicroseconds(2);
  digitalWrite(csleft_Trig,HIGH);               // 给触发脚高电平10μs，这里至少是10μs
  delayMicroseconds(10);
  digitalWrite(csleft_Trig,LOW);                // 持续给触发脚低电
  x1=pulseIn(csleft_Echo,HIGH)/58;  // 读取高电平时间(单位：微秒),除以58等于厘米
  
  delay(1);
  
  digitalWrite(csright_Trig,LOW);                // 给触发脚低电平2μs
  delayMicroseconds(2);
  digitalWrite(csright_Trig,HIGH);               // 给触发脚高电平10μs，这里至少是10μs
  delayMicroseconds(10);
  digitalWrite(csright_Trig,LOW);                // 持续给触发脚低电
  x2=pulseIn(csright_Echo,HIGH)/58;  // 读取高电平时间(单位：微秒),除以58等于厘米
}

void help_ceju()
{
  digitalWrite(cs_help_Trig,LOW);                // 给触发脚低电平2μs
  delayMicroseconds(2);
  digitalWrite(cs_help_Trig,HIGH);               // 给触发脚高电平10μs，这里至少是10μs
  delayMicroseconds(10);
  digitalWrite(cs_help_Trig,LOW);                // 持续给触发脚低电
  x3=pulseIn(cs_help_Echo,HIGH)/58;       // 读取高电平时间(单位：微秒),除以58等于厘米
}


//==============//============//=============//===============

void bizhang();
void xunji();
void lxunji();
void llxunji();
void slxunji();

void slxunji()
{
  xjr = digitalRead(xj_right);    //有信号表明在白色区域，车子底板上L1亮；没信号表明压在黑线上，车子底板上L1灭
  xjr1 = digitalRead(xj_right1);
  xjr2 = digitalRead(xj_right2);
  xjl = digitalRead(xj_left);     //有信号表明在白色区域，车子底板上L2亮；没信号表明压在黑线上，车子底板上L2灭
  xjl1 = digitalRead(xj_left1);
  xjl2 = digitalRead(xj_left2);
  xjl3 = digitalRead(xj_left3);
  xjr=xjr+xjr1+xjr2;
  xjl=xjl+xjl1+xjl2;
  if (xjl!=0 && xjr!=0)     //黑为HIGH,白为LOW
    srun();   //调用前进函数
  else if (xjl!=0 && xjr==0 && xjl3==0) // 左循迹红外传感器,检测到信号，车子向右偏离轨道，向左转 
    sfleft();
  else if (xjr!=0 && xjl==0 && xjl3==0) // 右循迹红外传感器,检测到信号，车子向左偏离轨道，向右转  
    right();
  else if(xjl3==1)
    sleft();
  else // 都是白色
  {
    ;//brake();
  }
}

void llxunji()
{
  xjr = digitalRead(xj_right);    //有信号表明在白色区域，车子底板上L1亮；没信号表明压在黑线上，车子底板上L1灭
  xjr1 = digitalRead(xj_right1);
  xjr2 = digitalRead(xj_right2);
  xjl = digitalRead(xj_left);     //有信号表明在白色区域，车子底板上L2亮；没信号表明压在黑线上，车子底板上L2灭
  xjl1 = digitalRead(xj_left1);
  xjl2 = digitalRead(xj_left2);
  xjl3 = digitalRead(xj_left3);
  xjr=xjr+xjr1+xjr2;
  xjl=xjl+xjl1+xjl2;
  if (xjl!=0 && xjr!=0)     //黑为HIGH,白为LOW
    llrun();   //调用前进函数
  else if (xjl!=0 && xjr==0 && xjl3==0) // 左循迹红外传感器,检测到信号，车子向右偏离轨道，向左转 
    sfleft();
  else if (xjr!=0 && xjl==0 && xjl3==0) // 右循迹红外传感器,检测到信号，车子向左偏离轨道，向右转  
    right();
  else if(xjl3==1)
    sleft();
  else // 都是白色,
  {
    ;//brake();
  }
}

void lxunji()
{
  xjr = digitalRead(xj_right);    //有信号表明在白色区域，车子底板上L1亮；没信号表明压在黑线上，车子底板上L1灭
  xjr1 = digitalRead(xj_right1);
  xjr2 = digitalRead(xj_right2);
  xjl = digitalRead(xj_left);     //有信号表明在白色区域，车子底板上L2亮；没信号表明压在黑线上，车子底板上L2灭
  xjl1 = digitalRead(xj_left1);
  xjl2 = digitalRead(xj_left2);
  xjl3 = digitalRead(xj_left3);
  xjr=xjr+xjr1+xjr2;
  xjl=xjl+xjl1+xjl2;
  if (xjl!=0 && xjr!=0)     //黑为HIGH,白为LOW
    run();   //调用前进函数
  else if (xjl!=0 && xjr==0 && xjl3==0) // 左循迹红外传感器,检测到信号，车子向右偏离轨道，向左转 
    left();
  else if (xjr!=0 && xjl==0 && xjl3==0) // 右循迹红外传感器,检测到信号，车子向左偏离轨道，向右转  
    right();
  else if(xjl3==1)
    sleft();
  else // 都是白色,
  {
    ;//brake();
  }
}

void xunji()
{
  xjr = digitalRead(xj_right);    //有信号表明在白色区域，车子底板上L1亮；没信号表明压在黑线上，车子底板上L1灭
  xjr1 = digitalRead(xj_right1);
  xjr2 = digitalRead(xj_right2);
  xjl = digitalRead(xj_left);     //有信号表明在白色区域，车子底板上L2亮；没信号表明压在黑线上，车子底板上L2灭
  xjl1 = digitalRead(xj_left1);
  xjl2 = digitalRead(xj_left2);
  xjl3 = digitalRead(xj_left3);
  xjr=xjr+xjr1+xjr2;
  xjl=xjl+xjl1+xjl2;
  if (xjl!=0 && xjr!=0)     //黑为HIGH,白为LOW
    frun();   //调用前进函数
  else if (xjl!=0 && xjr==0 && xjl3==0) // 左循迹红外传感器,检测到信号，车子向右偏离轨道，向左转 
    left();
  else if (xjr!=0 && xjl==0 && xjl3==0) // 右循迹红外传感器,检测到信号，车子向左偏离轨道，向右转  
    right();
  else if(xjl3==1)
    sleft();
  else // 都是白色,
  {
    ;//brake();
  }
}


void bizhang()
{
  int ks;
  ceju();
  while(x2>38 && x1>38)//原是35
  {
    run();
    ceju();
  }
  while(x1<35 || x2<35) //原是30
  {
    back();
    ceju();
  }
  
  if(x1>60)  //左小避障
  {
    ceju();
    while(x2>25)
    {
      run();
      ceju();
    }
    while(x2<60)
    {
      left();
      ceju();
    }
    help_ceju();
    while(x3>20)
    {
      run();
      bz_qian=digitalRead(hw_bz_qian);
      while(bz_qian==LOW)
      {
        left();
        bz_qian=digitalRead(hw_bz_qian);
      }
      help_ceju();
    }
    while(x3<20)
    {
      run();
      bz_qian=digitalRead(hw_bz_qian);
      while(bz_qian==LOW)
      {
        left();
        bz_qian=digitalRead(hw_bz_qian);
      }
      help_ceju();
    }
    while(1)
    {
      right();
      bz_hou=digitalRead(hw_bz_hou);
      while(bz_hou==LOW)
      {
        left();
        bz_hou=digitalRead(hw_bz_hou);
      }
      xjr3 = digitalRead(xj_right3);
      xjl3 = digitalRead(xj_left3);
      if(xjl3==1 || xjr3==1)
        break;
    }
    left();
    delay(240);
  }
  else   //左大避障
  {
    while(x1<60)
    {
      left();
      ceju();
    }
    while(x2<60)
    {
      left();
      ceju();
    }
    /*for(t=0;t<3;t++)
    {
      right();
    }*/
    help_ceju();
    while(x3>35)
    {
      run();
      bz_fist=digitalRead(hw_bz_fist);
      while(bz_fist==LOW)
      {
        bz_fist=digitalRead(hw_bz_fist);
        left();
      }
      bz_qian=digitalRead(hw_bz_qian);
      while(bz_qian==LOW)
      {
        left();
        bz_qian=digitalRead(hw_bz_qian);
      }
      help_ceju();
    }
    delay(50);
    while(x3<40)
    {
      run();
      bz_fist=digitalRead(hw_bz_fist);
      while(bz_fist==LOW)
      {
        bz_fist=digitalRead(hw_bz_fist);
        left();
      }
      bz_qian=digitalRead(hw_bz_qian);
      while(bz_qian==LOW)
      {
        left();
        bz_qian=digitalRead(hw_bz_qian);
      }
      help_ceju();
    }
    while(1)
    {
      right();
      bz_hou=digitalRead(hw_bz_hou);
      while(bz_hou==LOW)
      {
        left();
        bz_hou=digitalRead(hw_bz_hou);
      }
      xjr3 = digitalRead(xj_right3);
      xjl3 = digitalRead(xj_left3);
      if(xjl3==1 || xjr3==1)
        break;
    }
    
    for(t=0;t<90;t++)
    {
      left();
    }
    for(t=0;t<80;t++)
    {
      rightback();
      ks=digitalRead(KS);
      if(ks==LOW)
        break;
    }
    for(t=0;t<80;t++)
    {
      left();
    }
    for(t=0;t<70;t++)
    {
      rightback();
      ks=digitalRead(KS);
      if(ks==LOW)
        break;
    }
  }
  do
  {
    xunji();
    xjr = digitalRead(xj_right);    //有信号表明在白色区域，车子底板上L1亮；没信号表明压在黑线上，车子底板上L1灭
    xjr1 = digitalRead(xj_right1);
    xjr2 = digitalRead(xj_right2);
    xjr3 = digitalRead(xj_right3);
    xjl = digitalRead(xj_left);     //有信号表明在白色区域，车子底板上L2亮；没信号表明压在黑线上，车子底板上L2灭
    xjl1 = digitalRead(xj_left1);
    xjl2 = digitalRead(xj_left2);
    xjl3 = digitalRead(xj_left3);
  }while(xjr==HIGH && xjr1==LOW && xjr2==LOW && xjr3==LOW && xjl==HIGH && xjl1==LOW && xjl2==LOW && xjl3==LOW);
}

//==============================================================================================//*************
void begin_sj();   //从扫码准备去扫近处的物块
void begin_sy();   //从扫码准备去扫远处的物块
void sj_to_sy();   //从扫近位置去扫远
void sy_to_sj();   //从扫远位置去扫近
void fcs_to_sj();    //从载完物块去扫近
void fcs_to_sy();    //从载完物块去扫远
void fcs_to_start(); //从载完物块到机械手归位


void begin_sj()          //0:85/1:132/2:0/3:65/4:165  ->  0:85/1:102/2:50/3:75/4:15
{
  for(t=0;t<150;t++)
  {
    dj1.write(132-t*30/150);
    dj2.write(t*50/150);
    dj3.write(65+t*10/150);
    dj4.write(165-t);
    delay(10);
  }
  dj0.write(88);
  dj1.write(102);
  dj2.write(50);
  dj3.write(75);
  dj4.write(15);
}

void begin_sy()        //0:85/1:132/2:0/3:65/4:165  ->  0:85/1:74/2:80/3:70/4:18
{
  for(t=0;t<147;t++)
  {
    dj1.write(132-t*58/147);
    dj2.write(t*80/147);
    dj3.write(65+t*5/147);
    dj4.write(165-t);
    delay(14);
  }
  dj0.write(88);
  dj1.write(74);
  dj2.write(80);
  dj3.write(70);
  dj4.write(18);
}

void sj_to_sy()                //0:85/1:102/2:50/3:80/4:15 ->  0:85/1:74/2:80/3:70/4:18
{
  for(t=0;t<30;t++)
  {
    dj0.write(85);
    dj1.write(102-t*28/30);
    dj2.write(50+t);
    dj3.write(75-t*5/30);
    dj4.write(15+t*3/30);
    delay(14);
  }
}

void sy_to_sj()         //0:85/1:74/2:80/3:70/4:18  ->  0:85/1:102/2:50/3:80/4:15
{
  for(t=0;t<30;t++)
  {
    dj0.write(85);
    dj1.write(74+t*28/30);
    dj2.write(80-t);
    dj3.write(70+t*5/30);
    dj4.write(18-t*3/30);
    delay(14);
  }
  dj0.write(88);
  dj1.write(102);
  dj2.write(50);
  dj3.write(75);
  dj4.write(15);
}

void fcs_to_sj()          //0:85/1:132/2:50/3:46/4:56  ->  0:85/1:102/2:50/3:75/4:15
{
  for(t=0;t<41;t++)
  {
    dj1.write(132-t*30/41);
    dj3.write(46+t*29/41);
    dj4.write(56-t);
    delay(15);
  }
  dj0.write(88);
  dj1.write(102);
  dj2.write(50);
  dj3.write(75);
  dj4.write(15);
}

void fcs_to_sy()          //0:85/1:132/2:50/3:46/4:56  ->  0:85/1:74/2:80/3:70/4:18
{
  for(t=0;t<58;t++)
  {
    dj1.write(132-t);
    dj1.write(50+t*30/58);
    dj3.write(46+t*24/58);
    dj4.write(56-t*38/58);
    delay(14);
  }
}

void fcs_to_start()         //0:85/1:132/2:50/3:46/4:56  ->  0:165/1:132/2:0/3:65/4:165  
{
  for(t=0;t<109;t++)
  {
    dj0.write(85+t*80/109);
    dj2.write(50-t*50/109);
    dj3.write(46+t*19/109);
    dj4.write(56+t);
    delay(10);
  }
}

//============================================================//***
void begin_ss();    //从扫码准备去扫上处的条码
void begin_sx();    //从扫码准备去扫下处的条码
void ss_to_sx();    //从扫上位置去扫下
void sx_to_ss();    //从扫下位置去扫上
void fs_to_ss();    //从放上完后去扫上处的条码
void fs_to_sx();    //从放上完后去扫下处的条码
void fx_to_ss();    //从放下完后去扫上处的条码
void fx_to_sx();    //从放下完后去扫下处的条码

void begin_ss()     //0:85/1:132/2:0/3:65/4:165  ->  0:85/1:132/2:50/3:65/4:41
{
  for(t=0;t<20;t++)
  {
    dj2.write(t);
    delay(14);
  }
  for(t=0;t<124;t++)
  {
    dj2.write(20+t*30/124);
    dj4.write(165-t);
    delay(14);
  }
  dj0.write(88);
  dj1.write(132);
  dj2.write(49);
  dj3.write(64);
  dj4.write(42);
}

void begin_sx()      //0:85/1:132/2:0/3:65/4:165  ->  0:85/1:132/2:60/3:5/4:96
{
  for(t=0;t<20;t++)
  {
    dj2.write(t);
    dj3.write(65-t);
    delay(14);
  }
  for(t=0;t<69;t++)
  {
    dj2.write(20+t*40/69);
    dj3.write(45-t*40/69);
    dj4.write(165-t);
    delay(14);
  }
  dj0.write(88);
  dj1.write(132);
  dj2.write(60);
  dj3.write(6);
  dj4.write(96);
}

void ss_to_sx()    //0:85/1:132/2:50/3:65/4:41  ->  0:85/1:132/2:60/3:5/4:96
{
  for(t=0;t<60;t++)
  {
    dj2.write(50+t*10/60);
    dj3.write(65-t);
    dj4.write(41+t*55/60);
    delay(14);
  }
  dj0.write(88);
  dj1.write(132);
  dj2.write(60);
  dj3.write(6);
  dj4.write(96);
}

void sx_to_ss()    //0:85/1:132/2:60/3:5/4:96  ->  0:85/1:132/2:50/3:65/4:41
{
  for(t=0;t<60;t++)
  {
    dj2.write(60-t*10/60);
    dj3.write(5+t);
    dj4.write(96-t*55/59);
    delay(14);
  }
  dj0.write(88);
  dj1.write(132);
  dj2.write(49);
  dj3.write(64);
  dj4.write(42);
}

void fs_to_ss()      //0:86/1:117/2:79/3:7/4:91  ->  0:85/1:132/2:50/3:65/4:41
{
  dj0.write(86);
  for(t=0;t<58;t++)
  {
    dj1.write(117+t*15/58);
    dj2.write(79-t*29/58);
    dj3.write(7+t);
    dj4.write(91-t*50/58);
    delay(14);
  }
  dj0.write(88);
  dj1.write(132);
  dj2.write(49);
  dj3.write(64);
  dj4.write(42);
}

void fs_to_sx()    //0:86/1:117/2:79/3:7/4:91  ->  0:85/1:132/2:60/3:5/4:96
{
  dj0.write(85);
  for(t=0;t<19;t++)
  {
    dj1.write(117+t*15/19);
    dj2.write(79-t);
    dj3.write(7-t*2/19);
    dj4.write(91+t*5/19);
    delay(14);
  }
  dj0.write(88);
  dj1.write(132);
  dj2.write(60);
  dj3.write(6);
  dj4.write(96);
}

void fx_to_ss()              //0:86/1:132/2:46/3:17/4:91  ->  0:85/1:132/2:50/3:65/4:41
{
  dj0.write(85);
  for(t=0;t<50;t++)
  {
    dj2.write(46+t*4/50);
    dj3.write(17+t*48/50);
    dj4.write(91-t);
    delay(14);
  }
  dj0.write(88);
  dj1.write(132);
  dj2.write(49);
  dj3.write(64);
  dj4.write(42);
}

void fx_to_sx()              //0:86/1:132/2:46/3:17/4:91  ->  0:85/1:132/2:60/3:5/4:96
{
  dj0.write(85);
  for(t=0;t<14;t++)
  {
    dj2.write(46+t);
    dj3.write(17-t*12/14);
    dj4.write(91+t*5/14);
    delay(14);
  }
  dj0.write(88);
  dj1.write(132);
  dj2.write(60);
  dj3.write(6);
  dj4.write(96);
}


//====================================//*********
void fs_to_start();         //放上到机械手归位
void fx_to_start();         //放下到机械手归位

void fs_to_start()       //0:86/1:117/2:79/3:7/4:91  ->  0:165/1:132/2:0/3:65/4:165
{
  for(t=0;t<74;t++)
  {
    dj4.write(91+t);
    delay(14);
  }
  for(t=0;t<79;t++)
  {
    dj0.write(86+t);
    dj1.write(117+t*15/79);
    dj2.write(79-t);
    dj3.write(7+t*58/79);
    delay(14);
  }
}

void fx_to_start()     //0:86/1:132/2:46/3:17/4:91  ->  0:165/1:132/2:0/3:65/4:165 
{
  for(t=0;t<74;t++)
  {
    dj4.write(91+t);
    delay(14);
  }
  for(t=0;t<79;t++)
  {
    dj0.write(86+t);
    dj2.write(46-t*46/79);
    dj3.write(17+t*48/79);
    delay(14);
  }
}


//==================================================================================//*************
void sj_to_zj();         //从扫近完了后抓近
void sy_to_zy();         //从扫远完了后抓远
void fs();
void fx();

void sj_to_zj()          //0:85/1:102/2:50/3:80/4:15  ->  0:87/1:80/2:70/3:45/4:41  ->  0:87/1:132/2:54/3:0/4:177
{
  dj0.write(87);
  dj5.write(90);
  delay(6);
  for(t=0;t<35;t++)
  {
    dj1.write(102-t*22/35);
    dj2.write(50+t*20/35);
    dj3.write(80-t);
    dj4.write(15+t*26/35);
    delay(14);
  }
  dj1.write(80);
  dj2.write(70);
  dj3.write(45);
  dj4.write(41);
  delay(100);
  for(t=0;t<55;t++)
  {
    dj5.write(90+t);
    delay(15);
  }
  for(t=0;t<26;t++)
  {
    dj3.write(45+t*25/26);
    dj4.write(41-t);
    delay(15);
  }
  for(t=0;t<52;t++)
  {
    dj1.write(80+t);
    delay(4);
    dj2.write(70-t*16/52);
    delay(4);
    dj3.write(70-t*2/3);
    delay(3);
    dj4.write(15+t);
    delay(4);
  }
  for(t=0;t<110;t++)
  {
    dj4.write(67+t);
    delay(8);
    dj3.write(36-t/3);
    delay(7);
  }
}

void sy_to_zy()           //0:85/1:74/2:80/3:70/4:18  ->  0:86/1:64/2:74/3:80/4:23  ->  0:86/1:132/2:54/3:0/4:177
{
  dj0.write(86);
  dj5.write(90);
  delay(6);
  for(t=0;t<10;t++)
  {
    dj1.write(74-t);
    dj2.write(80-t*6/10);
    dj3.write(70+t);
    dj4.write(18+t*5/10);
    delay(14);
  }
  for(t=0;t<55;t++)
  {
    dj5.write(90+t);
    delay(15);
  }
  for(t=0;t<10;t++)
  {
    dj3.write(80+t);
    dj4.write(23-t*8/10);
    delay(15);
  }
  for(t=0;t<120;t++)
  {
    dj1.write(64+t*68/120);
    dj2.write(74-t*34/120);
    dj3.write(90-t*80/120);
    dj4.write(15+t);
    delay(15);
  }
  for(t=0;t<81;t++)
  {
    dj2.write(40+t*14/81);
    dj3.write(10-t*10/84);
    dj4.write(135+t*42/81);
    delay(8);
  }
}

void fs()             //0:86/1:107/2:99/3:32/4:41  ->  0:86/1:117/2:79/3:7/4:91
{
  dj0.write(86);
  for(t=0;t<30;t++)
  {
    dj3.write(32-t*20/30);
    dj4.write(41+t);
    delay(15);
  }
  for(t=0;t<20;t++)
  {
    dj2.write(99-t);
    dj3.write(12+t*5/20);
    dj4.write(71+t);
    delay(15);
  }
  for(t=0;t<25;t++)
  {
    dj5.write(145-t);
    delay(15);
  }
  for(t=0;t<10;t++)
  {
    dj1.write(107+t);
    dj3.write(17-t);
    delay(15);
  }
      // 之后换成接下去是直接扫码的
}


void fx()         //0:86/1:107/2:99/3:32/4:41  ->  0:86/1:132/2:46/3:17/4:91
{
  dj0.write(86);
  for(t=0;t<25;t++)
  {
    dj1.write(107+t);
    dj2.write(99-t);
    dj3.write(32-t);
    dj4.write(41+t);
    delay(20);
  }
  for(t=0;t<20;t++)
  {
    dj2.write(74-t);
    dj3.write(7+t*9/20);
    dj4.write(66+t);
    delay(15);
  }
  for(t=0;t<15;t++)
  {
    dj3.write(16-t*10/15);
    dj4.write(86+t);
    delay(15);
  }
  for(t=0;t<8;t++)
  {
    dj4.write(101+t);
    dj3.write(6+t);
    delay(7);
    dj2.write(54-t);
    delay(8);
  }
  for(t=0;t<20;t++)
  {
    dj2.write(46-t);
    dj3.write(14+t);
    delay(14);
  }
  for(t=0;t<25;t++)
  {
    dj5.write(145-t);
    delay(15);
  }
  for(t=0;t<20;t++)
  {
    dj2.write(26+t);
    dj3.write(34-t*17/20);
    dj4.write(109-t*18/20);
    delay(14);
  }
          //之后换成接下去是直接扫码的
}

//=================================//
void fql();
void fqz();
void fqr();
void fhl();
void fhz();
void fhr();

void fql()              //0:88/1:132/2:54/3:0/4:176  ->  0:85/1:132/2:50/3:46/4:56
{
  for(t=0;t<120;t++)
  {
    dj1.write(132-t*60/120);
    dj2.write(54+t*60/120);
    dj3.write(t);
    delay(15);
  }
  for(t=0;t<20;t++)
  {
    dj3.write(120+t);
    dj4.write(176-t*15/20);
    dj0.write(87-t*15/20);
    delay(15);
  }
  for(t=0;t<20;t++)
  {
    dj0.write(72-t*6/20);
    dj1.write(72+t*16/20);
    dj3.write(140+t*16/20);
    dj4.write(161-t);
    delay(15);
  }
  for(t=0;t<25;t++)
  {
    dj5.write(145-t);
    delay(15);
  }
  for(t=0;t<20;t++)
  {
    dj3.write(156-t*16/20);
    dj4.write(141+t);
    delay(15);
  }
  for(t=0;t<40;t++)
  {
    dj2.write(114-t*20/40);
    dj3.write(140-t);
    dj0.write(66+t*19/40);
    delay(15);
  }
  for(t=0;t<105;t++)
  {
    dj1.write(88+t*44/105);
    dj2.write(94-t*44/105);
    dj3.write(100-t*54/105);
    dj4.write(161-t);
    delay(15);
  }
}

void fhl()          //0:88/1:132/2:54/3:0/4:176  ->  0:85/1:132/2:50/3:46/4:56
{
  for(t=0;t<120;t++)
  {
    dj1.write(132-t*60/120);
    dj2.write(54+t*60/120);
    dj3.write(t);
    delay(15);
  }
  for(t=0;t<20;t++)
  {
    dj3.write(120+t);
    dj4.write(176-t*15/20);
    dj0.write(88+t*15/20);
    delay(15);
  }
  for(t=0;t<20;t++)
  {
    dj0.write(104+t*4/20);
    dj1.write(72+t*16/20);
    dj3.write(140+t*16/20);
    dj4.write(161-t);
    delay(15);
  }
  for(t=0;t<25;t++)
  {
    dj5.write(145-t);
    delay(15);
  }
  for(t=0;t<20;t++)
  {
    dj3.write(156-t*16/20);
    dj4.write(141+t);
    delay(15);
  }
  for(t=0;t<40;t++)
  {
    dj2.write(114-t*20/40);
    dj3.write(140-t);
    dj0.write(108-t*23/40);
    delay(15);
  }
  for(t=0;t<105;t++)
  {
    dj1.write(88+t*44/105);
    dj2.write(94-t*44/105);
    dj3.write(100-t*54/105);
    dj4.write(161-t);
    delay(15);
  }
}

void fhz()       //0:88/1:132/2:54/3:0/4:176  ->  0:85/1:132/2:50/3:46/4:56
{
  for(t=0;t<120;t++)
  {
    dj1.write(132-t/2);
    dj2.write(54+t/2);
    dj3.write(t);
    delay(15);
  }
  for(t=0;t<48;t++)
  {
    dj3.write(120+t/2);
    dj4.write(176-t/2);
    dj0.write(88+t);
    delay(15);
  }
  for(t=0;t<20;t++)
  {
    dj2.write(114+t);
    dj4.write(152-t);
    delay(15);
  }
  for(t=0;t<25;t++)
  {
    dj5.write(145-t);
    delay(15);
  }
  for(t=0;t<44;t++)
  {
    dj4.write(132+t);
    dj3.write(144-t*2);
    dj2.write(134-t);
    dj1.write(72+t/2);
    delay(20);
  }
  for(t=0;t<120;t++)
  {
    dj0.write(136-t*51/120);
    dj4.write(176-t);
    dj3.write(66-t*20/120);
    dj2.write(90-t*40/120);
    dj1.write(94+t*38/120);
    delay(15);
  }
}

//===============================//
void zql();
void zqz();
void zqr();
void zhl();
void zhz();
void zhr();

void zql()                      //0:85/1:132/2:50/3:65/4:41  ->  0:85/1:107/2:99/3:32/4:41
{
  for(t=0;t<100;t++)
  {
    dj0.write(85-t*19/100);
    dj1.write(132-t*50/100);
    dj2.write(50+t*50/100);
    dj3.write(65+t);
    dj4.write(41+t*99/100);
    delay(15);
  }
  for(t=0;t<10;t++)
  {
    dj1.write(82-t);
    dj2.write(100+t*29/10);
    dj3.write(165-t*8/5);
    delay(33);
  }
  for(t=0;t<15;t++)
  {
    dj3.write(149+t*12/15);
    dj4.write(140-t*13/15);
    delay(13);
  }
  for(t=0;t<25;t++)
  {
    dj5.write(120+t);
    delay(15);
  }
  for(t=0;t<27;t++)
  {
    dj2.write(128-t*21/27);
    dj3.write(161-t*20/27);
    dj4.write(128+t);
    delay(15);
  }
  for(t=0;t<65;t++)
  {
    dj0.write(66+t*19/65);
    dj1.write(72+t*18/65);
    dj2.write(107-t*8/65);
    dj3.write(141-t*51/65);
    dj4.write(155-t);
    delay(15);
  }
  for(t=0;t<40;t++)
  {
    dj1.write(90+t*25/40);
    dj3.write(90-t);
    dj4.write(90-t);
    delay(15);
  }
  for(t=0;t<18;t++)
  {
    dj3.write(50-t);
    dj4.write(50-t*9/18);
    delay(15);
  }
  for(t=0;t<8;t++)
  {
    dj1.write(115-t);
    delay(15);
  }
}

void zhl()                      //0:85/1:132/2:50/3:65/4:41  ->  0:85/1:107/2:99/3:32/4:41
{
  for(t=0;t<100;t++)
  {
    dj0.write(85+t*24/100);
    dj1.write(132-t*50/100);
    dj2.write(50+t*50/100);
    dj3.write(65+t);
    dj4.write(41+t*99/100);
    delay(15);
  }
  for(t=0;t<27;t++)
  {
    dj1.write(82-t*10/27);
    dj2.write(100+t);
    dj3.write(165-t*16/27);
    delay(15);
  }
  for(t=0;t<15;t++)
  {
    dj3.write(149+t*12/15);
    dj4.write(140-t*13/15);
    delay(13);
  }
  for(t=0;t<25;t++)
  {
    dj5.write(120+t);
    delay(15);
  }
  for(t=0;t<30;t++)
  {
    dj2.write(127-t*20/30);
    dj3.write(161-t*20/30);
    dj4.write(127+t*28/30);
    delay(15);
  }
  for(t=0;t<65;t++)
  {
    dj0.write(109-t*24/65);
    dj1.write(72+t*18/65);
    dj2.write(107-t*8/65);
    dj3.write(141-t*51/65);
    dj4.write(155-t);
    delay(15);
  }
  for(t=0;t<40;t++)
  {
    dj1.write(90+t*25/40);
    dj3.write(90-t);
    dj4.write(90-t);
    delay(15);
  }
  for(t=0;t<18;t++)
  {
    dj3.write(50-t);
    dj4.write(50-t*9/18);
    delay(15);
  }
  for(t=0;t<8;t++)
  {
    dj1.write(115-t);
    delay(15);
  }
}

void zhz()                      //0:85/1:132/2:50/3:65/4:41  ->  0:85/1:107/2:99/3:32/4:41
{
  for(t=0;t<111;t++)
  {
    dj0.write(85+t*51/111);
    dj1.write(132-t*60/111);
    dj2.write(50+t*64/111);
    dj3.write(65+t*76/111);
    dj4.write(41+t);
    delay(15);
  }
  for(t=0;t<21;t++)
  {
    dj2.write(114+t*24/21);
    dj3.write(141+t*4/21);
    dj4.write(152-t*19/21);
    delay(14);
  }
  for(t=0;t<25;t++)
  {
    dj5.write(120+t);
    delay(15);
  }
  for(t=0;t<19;t++)
  {
    dj3.write(145-t*20/19);
    dj4.write(133+t*15/19);
    delay(13);
  }
  for(t=0;t<50;t++)
  {
    dj1.write(72+t);
    dj2.write(138-t*107/50);
    dj4.write(148+t*2/50);
    delay(27);
  }
  for(t=0;t<110;t++)
  {
    dj0.write(136-t*51/110);
    dj1.write(122+t*10/110);
    dj2.write(31+t*43/110);
    dj3.write(125-t*108/110);
    delay(15);
  }
  for(t=0;t<50;t++)
  {
    dj1.write(132-t*25/50);
    dj2.write(74+t*25/50);
    dj3.write(17+t*15/50);
    dj4.write(150-t*109/50);
    delay(24);
  }
}


//===========//********//===================================//
void help_qw();   //取物舵机动作拼接函数
void help_fw();   //放物舵机动作拼接函数

void help_qw()
{
  more_saoma();
  for(bidui=0;bidui<3;bidui++)
  {
    if(strcmp(ma0,*(ma+bidui))==0)
      break;
  }
  if(bidui<3)
  {
    switch(bidui)
    {
      case 0:
      {
        sj_to_zj();
        fql();
        break;
      }
      case 1:
      {
        sj_to_zj();
        fhl();
        break;
      }
      case 2:
      {
        sj_to_zj();
        fhz();
        break;
      }
    }
    zwjd++;
    if(zwjd<3)
    {
      if(weizhi<5)
        fcs_to_sj();
      else if(weizhi==5)
        fcs_to_start();
    }
  }
  geshu++;
}

/*void help_qw()   //第二轮取物
{
  
}*/

void help_fw()
{
  more_saoma();
  //Serial.println(ma0);
  for(bidui=0;bidui<3;bidui++)
  {
    if(strcmp(ma0,*(ma+bidui))==0)
      break;
  }
  switch(bidui)
  {
    case 0:
    {
      if((geshu+weizhi)%2==1)
      {
        sx_to_ss();
        zql();
        fx();
      }
      if((geshu+weizhi)%2==0)
      {
        zql();
        fs();
      }
      break;
    }
    case 1:
    {
      if((geshu+weizhi)%2==1)
      {
        sx_to_ss();
        zhl();
        fx();
      }
      if((geshu+weizhi)%2==0)
      {
        zhl();
        fs();
      }
      break;
    }
    case 2:
    {
      if((geshu+weizhi)%2==1)
      {
        sx_to_ss();
        zhz();
        fx();
      }
      if((geshu+weizhi)%2==0)
      {
        zhz();
        fs();
      }
      break;
    }
  }
  if(bidui<3)
    zwjd++;
  if(zwjd<3)
  {
    if(bidui<3)
    {
      if(geshu==0 || geshu==4 || geshu==8)
        fx_to_ss();
      else if(geshu==1 || geshu==5)
        fs_to_ss();
      else if(geshu==2 || geshu==6)
        fs_to_sx();
      else if(geshu==3 || geshu==7)
        fx_to_sx();
    }
    else if(bidui==3)
    {
      if(geshu==0 || geshu==4 || geshu==8)
        sx_to_ss();
      if(geshu==2 || geshu==6)
        ss_to_sx();
    }
  }
  geshu++;
}

//==========//*******//===========//
void qw();
void fw();

void qw()
{
  geshu=0;
  zwjd=0;
  //1位
  weizhi=1;
  do
  {
    xunji();
    xjr3=digitalRead(xj_right3);
  }while(xjr3==LOW);
  do
  {
    lxunji();
    xjr3=digitalRead(xj_right3);
  }while(xjr3==HIGH);
  if(zwjd<3)
  {
    back();
    delay(140);
    brake();
    for(t=0;t<80;t++)
    {
      dj0.write(165-t);
      delay(13);
    }
    begin_sj();
    help_qw();
  }
  
  //2位
  weizhi=2;
  do
  {
    xunji();
    ch=digitalRead(ce_hou);
  }while(ch==LOW);
  if(zwjd<3)
  {
    back();
    delay(200);
    brake();
    help_qw();
  }
  
  //3位
  weizhi=3;
  do
  {
    lxunji();
    ch=digitalRead(ce_hou);
  }while(ch==HIGH);
  do
  {
    xunji();
    xjr3=digitalRead(xj_right3);
  }while(xjr3==LOW);
  if(zwjd<3)
  {
    back();
    delay(140);
    delay(40);
    brake();
    help_qw();
  }
  
  //4位
  weizhi=4;
  do
  {
    xunji();
    xjr3=digitalRead(xj_right3);
  }while(xjr3==HIGH);
  do
  {
    xunji();
    cq=digitalRead(ce_qian);
  }while(cq==LOW);
  if(zwjd<3)
  {
    back();
    delay(130);
    brake();
    help_qw();
  }
  
  //5位
  weizhi=5;
  do 
  {
    xunji();
    cq=digitalRead(ce_qian);
  }while(cq==HIGH);
  delay(50);
  do 
  {
    xunji();
    ch=digitalRead(ce_hou);
  }while(ch==HIGH);
  delay(50);
  do 
  {
    xunji();
    chl=digitalRead(ce_hl);
  }while(chl==LOW);
  if(zwjd<3)
  {
    back();
    delay(250);
    //delay(30);
    brake();
    help_qw();
  }
  brake();
  fcs_to_start();
}

/*void qw()   //第二轮取物
{
  geshu=0;
  zwjd=0;
  //1位
  weizhi=1;
  do
  {
    xunji();
    xjr3=digitalRead(xj_right3);
  }while(xjr3==LOW);
  do
  {
    lxunji();
    xjr3=digitalRead(xj_right3);
  }while(xjr3==HIGH);
  if(zwjd<3)
  {
    back();
    delay(140);
    brake();
    for(t=0;t<80;t++)
    {
      dj0.write(165-t);
      delay(13);
    }
    begin_sj();
    help_qw();
  }
  if(zwjd<3)
    help_qw();
  
  //2位
  weizhi=2;
  do
  {
    xunji();
    ch=digitalRead(ce_hou);
  }while(ch==LOW);
  if(zwjd<3)
  {
    back();
    delay(200);
    brake();
    help_qw();
  }
  if(zwjd<3)
    help_qw();
  
  //3位
  weizhi=3;
  do
  {
    lxunji();
    ch=digitalRead(ce_hou);
  }while(ch==HIGH);
  do
  {
    xunji();
    xjr3=digitalRead(xj_right3);
  }while(xjr3==LOW);
  if(zwjd<3)
  {
    back();
    delay(140);
    delay(40);
    brake();
    help_qw();
  }
  if(zwjd<3)
    help_qw();
  
  //4位
  weizhi=4;
  do
  {
    xunji();
    xjr3=digitalRead(xj_right3);
  }while(xjr3==HIGH);
  do
  {
    xunji();
    cq=digitalRead(ce_qian);
  }while(cq==LOW);
  if(zwjd<3)
  {
    back();
    delay(225);
    delay(30);
    brake();
    help_qw();
  }
  if(zwjd<3)
    help_qw();
  
  //5位
  weizhi=5;
  do 
  {
    xunji();
    cq=digitalRead(ce_qian);
  }while(cq==HIGH);
  delay(50);
  do 
  {
    xunji();
    ch=digitalRead(ce_hou);
  }while(ch==HIGH);
  do 
  {
    xunji();
    chl=digitalRead(ce_hl);
  }while(chl==LOW);
  if(zwjd<3)
  {
    back();
    delay(180);
    //delay(30);
    brake();
    help_qw();
  }
  if(zwjd<3)
    help_qw();
  brake();
  fcs_to_start();
}*/

void fw()
{
  geshu=0;
  zwjd=0;
  //1位
  weizhi=1;
  do
  {
    lxunji();
    xjr3=digitalRead(xj_right3);
  }while(xjr3==LOW);
  do
  {
    lxunji();
    xjr3=digitalRead(xj_right3);
  }while(xjr3==HIGH);
  back();
  delay(200);
  brake();
  for(t=0;t<80;t++)
  {
    dj0.write(165-t);
    delay(13);
  }
  for(t=0;t<30;t++)
  {
    dj5.write(90+t);
    delay(10);
  }
  begin_sx();
  help_fw();
  help_fw();
  
  //2位
  weizhi=2;
  do
  {
    lxunji();
    ch=digitalRead(ce_hou);
  }while(ch==LOW);
  back();
  delay(210);
  //delay(30);
  brake();
  if(zwjd<3)
    help_fw();
  if(zwjd<3)
    help_fw();
  
  //3位
  weizhi=3;
  do
  {
    lxunji();
    ch=digitalRead(ce_hou);
  }while(ch==HIGH);
  do
  {
    xunji();
    xjr3=digitalRead(xj_right3);
  }while(xjr3==LOW);
  if(zwjd<3)
  {
    back();
    delay(200);
    brake();
    help_fw();
  }
  if(zwjd<3)
    help_fw();
  
  //4位
  weizhi=4;
  do
  {
    lxunji();
    xjr3=digitalRead(xj_right3);
  }while(xjr3==HIGH);
  do 
  {
    xunji();
    cq=digitalRead(ce_qian);
  }while(cq==LOW);
  if(zwjd<3)
  {
    back();
    delay(150);
    brake();
    help_fw();
  }
  if(zwjd<3)
    help_fw();
  
  //5位
  weizhi=5;
  do 
  {
    xunji();
    cq=digitalRead(ce_qian);
  }while(cq==HIGH);
  delay(50);
  do 
  {
    xunji();
    ch=digitalRead(ce_hou);
  }while(ch==HIGH);
  do 
  {
    xunji();
    chl=digitalRead(ce_hl);
  }while(chl==LOW);
  if(zwjd<3)
  {
    back();
    delay(190);
    //delay(60);
    brake();
    help_fw();
  }
  if(zwjd<3)
    help_fw();
  brake();
  
  if(geshu==1 || geshu==4 || geshu==5 || geshu==8 || geshu==9)
    fx_to_start();
  if(geshu==2 || geshu==3 || geshu==6 || geshu==7 || geshu==10)
    fs_to_start();

}



//==============//===========//==============//===============//*********//*********//**********//

void keysacn()//按键扫描
{
  int ks;
  ks=digitalRead(KS);       //读取数字7 口电平值赋给val，按下为HIGH
  while(digitalRead(KS));    //当KS为黑HIGH时，一直循环
  
  while(!digitalRead(KS))//当KS为白时，循环
  {
    delay(10);	            //延时10ms
    ks=digitalRead(KS);
    if(ks==LOW)           //第二次判断按键是否被按下
    {
      while(!digitalRead(KS));	//判断按键是否被松开
    }
  }
}

//*******************************************************************************//
void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  
  pinMode(left_go,OUTPUT);
  pinMode(right_go,OUTPUT);
  pinMode(left_back,OUTPUT);
  pinMode(right_back,OUTPUT);
  pinMode(djd,OUTPUT);
  pinMode(csleft_Trig,OUTPUT);
  pinMode(csright_Trig,OUTPUT);
  
  pinMode(cs_help_Trig,OUTPUT);
  pinMode(cs_help_Echo,INPUT);
  
  pinMode(hw_bz_qian,INPUT);
  pinMode(hw_bz_hou,INPUT);
  pinMode(hw_bz_fist,INPUT);
  pinMode(KS,INPUT);
  
  pinMode(ce_qian,INPUT);
  pinMode(ce_hou,INPUT);
  pinMode(xj_left3,INPUT);
  pinMode(xj_left2,INPUT);
  pinMode(xj_left1,INPUT);
  pinMode(xj_left,INPUT);
  pinMode(xj_right,INPUT);
  pinMode(xj_right1,INPUT);
  pinMode(xj_right2,INPUT);
  pinMode(xj_right3,INPUT);
  pinMode(csleft_Echo,INPUT);
  pinMode(csright_Echo,INPUT);
  
  dj5.attach(34);//14
  dj4.attach(38);//16
  dj3.attach(40);//17
  dj2.attach(42);//18
  dj1.attach(44);//19
  dj0.attach(46);//20
  
  for(t=0;t<500;t++)
  {
    digitalWrite(djd,HIGH);
    delayMicroseconds(1489);
    digitalWrite(djd,LOW);
    delayMicroseconds(19000);
  }
  
  dj5.write(90);
  for(t=0;t<75;t++)
  {
    dj0.write(90+t);
    dj4.write(90+t);
    dj3.write(90-t);
    delay(24);
  }
  for(t=0;t<43;t++)
  {
    dj2.write(90-t*5/2);
    dj3.write(22+t);
    dj1.write(89+t);
    delay(24);
  }
  
}

//==============//===========//==============//===============//***********//**********//**********//

  
int y;

void loop()
{
  
  keysacn();
  
  /*int n=0,i;
  
  do
  {
    xjr = digitalRead(xj_right);    //有信号表明在白色区域，车子底板上L1亮；没信号表明压在黑线上，车子底板上L1灭
    xjr1 = digitalRead(xj_right1);
    xjr2 = digitalRead(xj_right2);
    xjl = digitalRead(xj_left);     //有信号表明在白色区域，车子底板上L2亮；没信号表明压在黑线上，车子底板上L2灭
    xjl1 = digitalRead(xj_left1);
    xjl2 = digitalRead(xj_left2);
    xjl3 = digitalRead(xj_left3);
    xjr=xjr+xjr1+xjr2;
    xjl=xjl+xjl1+xjl2+xjl3;
    
    frun();
  }while(xjr==0 && xjl==0);      //黑为HIGH,白为LOW
  
  delay(20);
  
  while(1)
  {
    xunji();
    
    cq=digitalRead(ce_qian);
    
    if(cq==HIGH)
    {
      n=n+1;
      if(n==2)
      {
        frun();
        delay(100);   //控制冲上斜坡的距离
        qw();
        do
        {
          xjr3=digitalRead(xj_right3);
          xunji();
        }while(xjr3==LOW);
        bizhang();
        fw();
        do
        {
          xjr3=digitalRead(xj_right3);
          lxunji();
        }while(xjr3==LOW);
        run();
        delay(900);
        back();
        delay(130);
        brake();
        while(1);
      }
    }
    do
    {
      cq=digitalRead(ce_qian);
      xunji();
    }while(cq==HIGH);
    delay(20);
    //brake();
  }*/
  
  
  
  
  
  
  /*for(t=0;t<10;t++)
  {
    saoma();
    delay(1500);
  }*/
  
  /*for(t=0;t<80;t++)
  {
    dj0.write(165-t);
    delay(13);
  }
  begin_sy();*/
  //saoma();
  //sy_to_zy();
  //fhl();
  //fx();
  //fx_to_sx();
  //fs();
  
  //saoma();
  //qw();
  //fw();
  bizhang();
  //brake();
  /*while()
  {
    Serial.println(1);
    delay(1000);
  }*/
  
  
  while(1);
}



