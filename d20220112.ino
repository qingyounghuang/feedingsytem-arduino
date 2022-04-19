String comdata = "";
long mark=0,d,r=0,counter[5]={0};
float numdata[120]={0},point=0.1;
static  long number[120]={0};
int val=1;//分配器传感器
  int c=0;//计数两次触碰传感器的脉冲数
void serial()
{
 int j = 0;//j是分拆之后数字数组的位置记数  
      while (Serial.available() > 0)//不断循环检测串口缓存，一个个读入字符串，
      {
        comdata += char(Serial.read()); //读入之后将字符串，串接到comdata上面。  
        delay(2);//延时一会，让串口缓存准备好下一个数字，不延时会导致数据丢失，  
        mark = 1; //标记串口读过数据，如果没有数据的话，直接不执行这个while了。
      }
 if(mark == 1)  //如果接收到数据则执行comdata分析操作，否则什么都不做。
      { 
        if(comdata.length()>3)
        {
        for(int i=0;i<120;i++)
        {numdata[i] = 0;}
    /*******************下面是重点*******************/
    //以串口读取字符串长度循环，
        for(int i = 0; i < comdata.length()-1 ; i++)
        {
       
          if(comdata[i] == ',')
          {
            j++;
            point=0.1;
            d=0;
          }
          else
          {
              if(comdata[i]=='.')
             {
               d=1;
             }
            
             if(comdata[i]!='.'&& d==0)
             {
                numdata[j] = numdata[j] * 10 + (comdata[i] - '0');
             }
          if(comdata[i]!='.'&& d==1)
           {
                numdata[j] = numdata[j] + (comdata[i] - '0')*point;
                point=point*0.1;
           }   
          }
        }
        comdata = String("");
        point=0.1;
        mark=0;

      for(int i = 0; i < 10; i++)
      {number[i]=numdata[i];
     // Serial.print(number[i]);
      }
    }
    else
    {r =comdata[0] - '0';
   // Serial.println(r);
    comdata = String("");
    point=0.1;
    mark=0;
    }


      }
}

void motor(int t,int i,int j,int d,int v,long k)//t为任务，i为脉冲输出端口,j为方向端口,,d为方向，v为电机速度，k为脉冲数
{
    digitalWrite(j, d); // Set Enable low
    k=k*100;
   for (int x = 0; x < k; x++) // Loop 200 times
  {
       digitalWrite(i,HIGH ); // Output high
       delayMicroseconds(v); // Wait 1/2 a ms
       digitalWrite(i, LOW); // Output low
       delayMicroseconds(v); // Wait 1/2 a ms
  }
  }

void motorback(int t,int i,int j,int d,int v,int k)//t为任务，i为脉冲输出端口,j为使能端口,k为传感器输入端口
{

  digitalWrite(j, d); // 
  while(val==1)
  {
       digitalWrite(i, HIGH); // Output high
       delayMicroseconds(v); // Wait 1/2 a ms
       digitalWrite(i, LOW); // Output low
       delayMicroseconds(v); // Wait 1/2 a ms
       val=digitalRead(k);   
  }
  
val=1;
   delay(1000); // pause one second
  }

//某端口输出高低电平
void outputD(int t,int i,int j)//t为任务，i为端口，j为电平高低
{

digitalWrite(i, j); // Output low

}
//某端口输出模拟变量
void outputA(int t,int i,int j)//t为任务，i为端口，j为输出模拟量
{
analogWrite(i,j);
}
//风机运动和送料
void windtrans(int t,int i,int j,int k,int l,int m,int n,long p,int q)
{
  analogWrite(i,j);
  digitalWrite(q,1);
  delay(6000); // pause one second
  
  digitalWrite(l, m); // Set Enable low
  p=p*100;
   for (int x = 0; x < p; x++) // Loop 200 times
  {
       digitalWrite(k,HIGH ); // Output high
       delayMicroseconds(n); // Wait 1/2 a ms
       digitalWrite(k, LOW); // Output low
       delayMicroseconds(n); // Wait 1/2 a ms
  }
  delay(1000); // pause one second
   digitalWrite(q,0);
  delay(6000); // pause one second
  digitalWrite(i,0);
 
  delay(6000); // pause one second
 }
//void(* resetFunc) (void) = 0;

void setup() 
{ 

  Serial.begin(9600);
    
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
 
 // pinMode(27, OUTPUT);
 // pinMode(28, OUTPUT);
  digitalWrite(2,0);
  digitalWrite(3,0);
  digitalWrite(4,0);
  digitalWrite(5,0);
  digitalWrite(6,0);
  digitalWrite(7,0);
  digitalWrite(8,0);
  digitalWrite(9,0);
  digitalWrite(10,0);
  digitalWrite(11,0);

  digitalWrite(12, 1);
  delay(200); 
  pinMode(12, OUTPUT); 
 
} 


void loop() 
{ 
serial();
  digitalWrite(2,0);
  digitalWrite(3,0);
  digitalWrite(4,0);
  digitalWrite(5,0);
  digitalWrite(6,0);
  digitalWrite(7,0);
  digitalWrite(8,0);
  digitalWrite(9,0);
  digitalWrite(10,0);

if(number[0]!=0)
{
  //控制电机(1-3为电机旋转多少圈任务，4-5为电机复位任务，6-为高低电平输出任务)
  //电机旋转多少圈的任务
  if(number[0]>0&&number[0]<4)
  {
motor(number[0],number[1],number[2],number[3],number[4],number[5]);//t为任务，i为脉冲输出端口,j为方向端口,,d为方向，v为电机速度，k为脉冲数
     delay(1000);
      Serial.print(number[0]);
      number[0]=0;
  }
  //电机复位任务
  if(number[0]>3&&number[0]<6)
  {
    motorback(number[0],number[1],number[2],number[3],number[4],number[5]);//t是任务，i为脉冲输出端口,j为使能端口,k为传感器输入端口

    delay(1000);
    Serial.print(number[0]);
  
    number[0]=0;
    }
    //端口输出高低电平任务
    if(number[0]>5&&number[0]<7)
    {
      windtrans(number[0],number[1],number[2],number[3],number[4],number[5],number[6],number[7],number[8]);
     delay(1000);
     //outputD(number[0],number[1],number[2]);//t为任务，i为端口，j为电平高低
      Serial.print(number[0]);
      number[0]=0;

      }
     //端口输出模拟量任务
    if(number[0]>6&&number[0]<8)
    {
      
      if(number[2]=0)
      {
        digitalWrite(number[1], 0); 
       }
       else
       {
        outputA(number[0],number[1],number[2]);//t为任务，i为端口，j为模拟量值
        }
      Serial.print(number[0]);
      number[0]=0;
      }

          if(number[0]>7&&number[0]<9)
    {
     outputD(number[0],number[1],number[2]);
       delay(20);
     Serial.print(number[0]);
      number[0]=0;
      }
      
  //端口输出模拟量任务
    if(number[0]>8)
    {
   //    resetFunc();
       delay(20);
      }
      
}


}
