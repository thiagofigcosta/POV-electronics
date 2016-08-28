//LIBS---------------------------------------------------------------------------------------------------------------------
#include <Wire.h>
#include <RTClib.h>
//-------------------------------------------------------------------------------------------------------------------------

//VARS---------------------------------------------------------------------------------------------------------------------
RTC_DS1307 RTC;
const int RPM = 7200;
int detailDegrees=0;//648
unsigned long int USPR;
int currentDegree=0;

unsigned long timer;
boolean halfsec=false;
unsigned halfsecCount=0;

short int hora1;
short int minuto1;
short int segundo1;
short int hora2;
short int minuto2;
short int segundo2;
//-------------------------------------------------------------------------------------------------------------------------

//PIN OUT------------------------------------------------------------------------------------------------------------------
unsigned short led[10]={2,3,4,5,6,7,8,9,10,11};
//-------------------------------------------------------------------------------------------------------------------------

//CARACTERES---------------------------------------------------------------------------------------------------------------
//byte zero[60]={1,2,3,4,5,6,
//                  11,12,13,14,15,16,
//                  21,22,23,24,25,26,
//                  31,32,33,34,35,36,
//                  41,42,43,44,45,46,
//                  51,52,53,54,55,56,
//                  61,62,63,64,65,66,
//                  71,72,73,74,75,76,
//                  81,82,83,84,85,86,
//                  91,92,93,94,95,96};

byte cora[60]={  0,0,1,1,0,0,
                  0,1,1,1,1,0,
                  1,1,1,1,1,1,
                  1,1,1,1,1,1,
                  1,1,1,1,1,1,
                  0,1,1,1,1,1,
                  0,0,1,1,1,1,
                  0,0,0,1,1,1,
                  0,0,0,0,1,1,
                  0,0,0,0,0,1};
byte corb[60]={   0,0,1,1,0,0,
                  0,1,1,1,1,0,
                  1,1,1,1,1,1,
                  1,1,1,1,1,1,
                  1,1,1,1,1,1,
                  1,1,1,1,1,0,
                  1,1,1,1,0,0,
                  1,1,1,0,0,0,
                  1,1,0,0,0,0,
                  1,0,0,0,0,0};

byte zero[60]={1,1,1,1,1,1,
                  1,1,1,1,1,1,
                  1,1,0,0,1,1,
                  1,1,0,0,1,1,
                  1,1,0,0,1,1,
                  1,1,0,0,1,1,
                  1,1,0,0,1,1,
                  1,1,0,0,1,1,
                  1,1,1,1,1,1,
                  1,1,1,1,1,1};
                  
byte um[60]={  0,0,1,1,0,0,
                  0,1,1,1,0,0,
                  1,1,1,1,0,0,
                  1,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  1,1,1,1,1,1};

byte dois[60]={0,0,1,1,0,0,
                  0,1,1,1,1,0,
                  1,1,0,0,1,1,
                  1,0,0,0,1,1,
                  0,0,0,0,1,1,
                  0,0,0,1,1,0,
                  0,0,1,1,0,0,
                  0,1,1,0,0,0,
                  1,1,1,1,1,0,
                  1,1,1,1,1,1};
                  
byte tres[60]={0,1,1,1,1,0,
                  1,1,1,1,1,1,
                  1,0,0,0,1,1,
                  0,0,0,0,1,1,
                  0,0,1,1,1,0,
                  0,0,1,1,1,0,
                  0,0,0,0,1,1,
                  1,0,0,0,1,1,
                  1,1,1,1,1,1,
                  0,1,1,1,1,0};

byte quatro[60]={0,0,0,0,1,1,
                    0,0,0,1,1,0,
                    0,0,1,1,0,0,
                    0,1,1,0,0,0,
                    1,1,0,0,1,0,
                    1,1,1,1,1,1,
                    0,1,1,1,1,1,
                    0,0,0,0,1,0,
                    0,0,0,0,1,0,
                    0,0,0,0,1,0};
                  
byte cinco[60]={0,1,1,1,1,1,
                  1,1,1,1,1,1,
                  1,1,0,0,0,0,
                  1,1,0,0,0,0,
                  0,1,1,1,1,0,
                  0,1,1,1,1,1,
                  0,0,0,0,1,1,
                  0,0,0,0,1,1,
                  1,1,1,1,1,0,
                  1,1,1,1,0,0};

byte seis[60]={0,0,1,1,1,1,
                  0,1,1,0,0,0,
                  1,1,0,0,0,0,
                  1,0,0,0,0,0,
                  1,1,1,1,1,1,
                  1,1,1,1,1,1,
                  1,1,0,0,1,1,
                  1,1,0,0,1,1,
                  1,1,1,1,1,1,
                  1,1,1,1,1,1};
                  
byte sete[60]={1,1,1,1,1,1,
                  1,1,1,1,1,1,
                  0,0,0,0,1,1,
                  0,0,0,1,1,0,
                  0,0,1,1,0,0,
                  0,1,1,0,0,0,
                  0,1,1,0,0,0,
                  1,1,0,0,0,0,
                  1,1,0,0,0,0,
                  1,1,0,0,0,0};

byte oito[60]={0,1,1,1,1,0,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  0,1,1,1,1,0,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  0,1,1,1,1,0};
                  
byte nove[60]={1,1,1,1,1,1,
                  1,1,1,1,1,1,
                  1,1,0,0,1,1,
                  1,1,0,0,1,1,
                  1,1,1,1,1,1,
                  1,1,1,1,1,1,
                  0,0,0,0,0,1,
                  0,0,0,0,1,1,
                  0,0,0,1,1,0,
                  1,1,1,1,0,0};
                  

byte dponto[60]={0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0};
                  
byte blank[60]={0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0};
byte A[60]={	  0,0,1,1,0,0,
                  0,1,0,0,1,0,
                  0,1,0,0,1,0,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,1,1,1,1,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1};
byte B[60]={	  1,1,0,1,1,0,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,1,1,1,1,0,
                  1,1,1,1,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,1,1,1,1,0};
byte C[60]={	  1,1,1,1,1,1,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,1,1,1,1,0};
byte D[60]={	  1,1,1,1,0,0,
                  1,0,0,0,1,0,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,1,0,
                  1,1,1,1,0,0};
byte E[60]={	  1,1,1,1,1,1,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,1,1,1,1,0,
                  1,1,1,1,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,1,1,1,1,1};
byte F[60]={	  1,1,1,1,1,1,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,1,1,1,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0};
byte G[60]={	  1,1,1,1,1,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,1,1,1,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,1,1,1,1,1};
byte H[60]={	  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,1,1,1,1,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1};
byte I[60]={	  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0};
byte J[60]={	  1,1,1,1,1,1,
                  1,1,1,1,1,1,
                  0,0,0,0,0,1,
                  0,0,0,0,0,1,
                  0,0,0,0,0,1,
                  0,0,0,0,0,1,
                  1,0,0,0,1,0,
                  1,0,0,0,1,0,
                  1,0,0,0,1,0,
                  0,1,1,1,0,0};
byte K[60]={	  1,0,0,0,0,1,
                  1,0,0,0,1,0,
                  1,0,0,1,1,0,
                  1,0,0,1,0,0,
                  1,1,1,0,0,0,
                  1,1,1,0,0,0,
                  1,0,1,0,0,0,
                  1,0,1,1,0,0,
                  1,0,0,1,1,0,
                  1,0,0,0,1,1};
byte L[60]={	  1,1,0,0,0,0,
                  1,1,0,0,0,0,
                  1,1,0,0,0,0,
                  1,1,0,0,0,0,
                  1,1,0,0,0,0,
                  1,1,0,0,0,0,
                  1,1,0,0,0,0,
                  1,1,0,0,0,0,
                  1,1,1,1,1,1,
                  1,1,1,1,1,1};
byte M[60]={	  1,0,0,0,0,1,
                  1,1,0,0,1,1,
                  1,1,0,0,1,1,
                  1,0,1,1,0,1,
                  1,0,1,1,0,1,
                  1,0,1,1,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1};
byte N[60]={	  1,0,0,0,0,1,
                  1,1,0,0,0,1,
                  1,0,1,0,0,1,
                  1,0,1,0,0,1,
                  1,0,0,1,0,1,
                  1,0,0,1,0,1,
                  1,0,0,0,1,1,
                  1,0,0,0,1,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1};
byte O[60]={	  1,1,1,1,1,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,1,1,1,1,1};
byte P[60]={	  1,1,1,1,1,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,1,1,1,1,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0};
byte Q[60]={	  1,1,1,1,1,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,1,0,0,1,
                  1,0,1,0,0,1,
                  1,0,0,1,0,1,
                  1,0,0,1,0,1,
                  1,0,0,0,1,1,
                  1,1,1,1,1,0};
byte R[60]={	  1,1,1,1,1,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,1,1,1,1,0,
                  1,1,0,0,0,0,
                  1,0,1,0,0,0,
                  1,0,0,1,0,0,
                  1,0,0,1,0,0,
                  1,0,0,0,1,0};
byte S[60]={	  1,1,1,1,1,1,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,0,0,0,0,0,
                  1,1,1,1,1,1,
                  0,0,0,0,0,1,
                  0,0,0,0,0,1,
                  0,0,0,0,0,1,
                  0,0,0,0,0,1,
                  1,1,1,1,1,1};
byte T[60]={	  0,0,1,1,0,0,
                  1,1,1,1,1,1,
                  1,1,1,1,1,1,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0};
byte U[60]={	  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,1,1,1,1,1};
byte V[60]={	  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  0,1,0,0,1,0,
                  0,1,0,0,1,0,
                  0,1,0,0,1,0,
                  0,1,0,0,1,0,
                  0,1,0,0,1,0,
                  0,0,1,1,0,0};
byte W[60]={	  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  1,0,1,1,0,1,
                  1,0,1,1,0,1,
                  1,0,1,1,0,1,
                  1,1,0,0,1,1,
                  1,1,0,0,1,1,
                  1,0,0,0,0,1};
byte X[60]={	  1,0,0,0,0,1,
                  0,1,0,0,1,0,
                  0,1,0,0,1,0,
                  0,1,0,0,1,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0,
                  0,1,0,0,1,0,
                  0,1,0,0,1,0,
                  0,1,0,0,1,0,
                  1,0,0,0,0,1};
byte Y[60]={	  1,0,0,0,0,1,
                  1,0,0,0,0,1,
                  0,1,0,0,0,1,
                  0,0,1,0,1,0,
                  0,0,0,1,1,0,
                  0,0,0,1,0,0,
                  0,0,0,1,0,0,
                  0,0,1,0,0,0,
                  0,1,1,0,0,0,
                  0,1,0,0,0,0};
byte Z[60]={	  1,1,1,1,1,1,
                  0,0,0,0,0,1,
                  0,0,0,0,1,0,
                  0,0,0,1,0,0,
                  0,0,0,1,0,0,
                  0,0,1,0,0,0,
                  0,0,1,0,0,0,
                  0,1,0,0,0,0,
                  1,0,0,0,0,0,
                  1,1,1,1,1,1};
byte interrogacao[60]={0,0,1,1,0,0,
                  0,1,1,1,1,0,
                  1,1,0,0,1,1,
                  1,0,0,0,0,1,
                  1,0,0,0,1,1,
                  0,0,0,1,1,0,
                  0,0,1,1,0,0,
                  0,0,0,0,0,0,
                  0,0,1,1,0,0,
                  0,0,1,1,0,0};
byte ponto[60]={0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  0,0,0,0,0,0,
                  1,1,0,0,0,0,
                  1,1,0,0,0,0};
                  

//-------------------------------------------------------------------------------------------------------------------------

//SETUP--------------------------------------------------------------------------------------------------------------------
void setup () {
    timer=millis();
    Serial.begin(9600);
    Wire.begin();
    RTC.begin();
    if (!RTC.isrunning())
      RTC.adjust(DateTime(__DATE__, __TIME__));
    setupMotorConfig();
}
//-------------------------------------------------------------------------------------------------------------------------

//LOOP---------------------------------------------------------------------------------------------------------------------
void loop () {

  relogio();
 //letras();
// letrasbug();
 calculate(12);
}
//-------------------------------------------------------------------------------------------------------------------------

//FUNÇOES------------------------------------------------------------------------------------------------------------------
void setupMotorConfig(){  
 USPR=1000000000/(RPM*360/60);//tempo para girar 1 grau em uS  1000000/(RPM*detailDegrees/60) USPR=740.370370370;
 for (int i=0; i<10; i++){
    pinMode(led[i],OUTPUT);
  }
}

void calculate(int peso){    
    detailDegrees=currentDegree*peso;
    USPR=(40000*peso)/detailDegrees;  
    currentDegree=0;
}
void letras(){
  if(timer<=millis()-500){
    timer=millis();
    halfsecCount++;
  }
  if(halfsecCount/2<5){
    printChar('?');
    printChar('h');
    printChar('h');
    printChar('s');
    printChar('i');
    printChar('m');//32
  }else if(halfsecCount/2>5){
    printChar('s');
    printChar('e');
    printChar('d');
    printChar('u');
    printChar('n');//32  
    printChar(' ');
    printChar('a');
    printChar('d');
    printChar('n');
    printChar('a');
    printChar('m');//32  
  }
  if(halfsecCount/2>10)halfsecCount=0;
     for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
     }
    delayMicroseconds(USPR*(detailDegrees-currentDegree));
    
}
void relogio(){
  if(timer<=millis()-500){
    timer=millis();
    halfsec=!halfsec;
    halfsecCount++;
  }
if(currentDegree>=detailDegrees){
    DateTime now = RTC.now();
    hora1=now.hour()/10;
    minuto1=now.minute()/10;
    segundo1=now.second()/10;
    hora2=now.hour()%10;
    minuto2=now.minute()%10;
    segundo2=now.second()%10;
    }
    Serial.println(String(hora1,DEC)+String(hora2,DEC)+":"+String(minuto1,DEC)+String(minuto2,DEC)+":"+String(segundo1,DEC)+String(segundo2,DEC));
    printPOV(segundo2);
    printPOV(segundo1);  
    printPOV(-11);
     printPOV(minuto2);
     printPOV(minuto1);
      printPOV(-1);
      printPOV(hora2);
    printPOV(hora1);//54 graus
       
     for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
    delayMicroseconds(USPR*(detailDegrees-currentDegree));
   
}
    
    
    
void printChar(char letra){
  switch (letra){
    case 'a':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(A[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    
    case 'b':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(B[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    
    case 'c':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(C[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    
    case 'd':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(D[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    
    case 'e':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(E[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    
    case 'f':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(F[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    
    case 'g':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(G[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    
    case 'h':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(H[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 'i':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(I[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 'j':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(J[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 'k':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(K[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    
    case 'l':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(L[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    
    case 'm':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(M[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    
    case 'n':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(N[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 'o':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(O[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    
    case 'p':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(P[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 'q':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(Q[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 'r':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(R[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 's':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(S[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    
    case 't':
for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(T[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 'u':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(U[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 'v':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(V[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    case 'w':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(W[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 'x':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(X[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 'y':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(Y[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    case 'z':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(Z[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case '?':                          
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(interrogacao[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR); 
      currentDegree+=7;
    break;
    
    case '.':
       for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(ponto[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=6;
    break;
    
    case '5':
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(cora[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case '7':
    for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(corb[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);
            }
        delayMicroseconds(USPR);
      }
      currentDegree+=6;
    break;
    
    case ' ':
    for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(blank[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);
            }
        delayMicroseconds(USPR);
      }
      currentDegree+=6;
    break;
    
  }
  
  
}

void printPOV(int n){
  switch (n){
    case 0:
      for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(zero[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 1:
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(um[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 2:
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(dois[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 3:
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(tres[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 4:
   for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(quatro[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 5:
   for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(cinco[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 6:
   for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(seis[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 7:
   for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(sete[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 8:
   for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(oito[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case 9:
    for (int i=0; i<10; i++){
        digitalWrite(led[i],LOW);
      }
      delayMicroseconds(USPR);                           
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(nove[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=7;
    break;
    
    case -1:                       
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(dponto[(6*j)+(5-x)]==1)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=6;
    break;
    
    case -11:                       
      for(int x=0; x<6; x++){
          for (int j=0; j<10; j++){
            if(dponto[(6*j)+(5-x)]==1&&halfsec==true)
              digitalWrite(led[j],HIGH);
            else
              digitalWrite(led[j],LOW);}
        delayMicroseconds(USPR);
      }
      currentDegree+=6;
    break;
  }
}
//-------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

/*void letrasbug(){  
  if(timer<=millis()-500){
    timer=millis();
    halfsecCount++;
  }
  
   if(halfsecCount/2<7){
                                            for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(interrogacao[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              currentDegree+=7;
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(L[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              currentDegree+=7;
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(O[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              currentDegree+=7;
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(R[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              currentDegree+=7;
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(A[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              currentDegree+=7;
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(C[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              currentDegree+=7;    
                                           for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }                                   
     
  }else if(halfsecCount/2<14){
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(S[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              currentDegree+=7*11;
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(E[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(D[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(U[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(N[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              
                                              
                                              
                                              
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(blank[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              
                                              
                                              
                                              
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(A[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(D[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(N[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(A[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(M[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
  }else{
  
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(blank[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              currentDegree+=7;
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(blank[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              currentDegree+=7;
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(blank[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              currentDegree+=7;
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(blank[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              currentDegree+=7;for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(blank[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              currentDegree+=7;
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(corb[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              currentDegree+=6;
                                              delayMicroseconds(USPR);                           
                                              for(int x=0; x<6; x++){
                                                  for (int j=0; j<10; j++){
                                                    if(cora[(6*j)+(5-x)]==1)
                                                      digitalWrite(led[j],HIGH);
                                                    else
                                                      digitalWrite(led[j],LOW);}
                                                delayMicroseconds(USPR);
                                              }
                                              currentDegree+=7;
                                              for (int i=0; i<10; i++){
                                                digitalWrite(led[i],LOW);
                                              }
  }*/

