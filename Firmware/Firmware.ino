#include <Arduino.h>
#include <U8g2lib.h>
#include <Adafruit_VL53L0X.h>
#include <SPI.h>
#include <Wire.h>
#include <MPU6050_tockn.h>
 
#define botaoVoltar 19
#define botaoCima 4
#define botaoBaixo 18
#define botaoOk 15

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 32, /* data=*/ 33, /* CS=*/ 25, /* reset=*/ 27);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define MPU6050_ADDR 0x68
MPU6050 mpu6050(Wire);

float anguloX;
float anguloY;

String Texto;

unsigned long timeAtual;
unsigned long timeAnterior;
unsigned long intervalo;
int controleInicializacao = 0, posMenu = 0, menu = 10;

void display();

void inicializaLaser(){
  timeAnterior = millis();
  while(!lox.begin()&& controleInicializacao == 0) {
    timeAtual = millis();
    display("Iniciando Sensor Laser!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
    if((timeAtual - timeAnterior) >= 1000){
       display("Falha ao Iniciar Sensor!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
       delay(500);
       controleInicializacao = 1;  
    }    
  } 
}
void inicializaGiroscopio(){
  display("Iniciando Giroscopio!", 5, 35,".",62,45,"",50,50,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
  Wire.begin();
  display("Iniciando Giroscopio!", 5, 35,"..",62,45,"",50,50,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
  mpu6050.begin();
  display("Iniciando Giroscopio!", 5, 35,"...",62,45,"",50,50,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
  mpu6050.calcGyroOffsets(true);
  display("Iniciando Giroscopio!", 5, 35,"....",62,45,"",50,50,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
}
void setup(void) {
  Serial.begin(115200);
  u8g2.begin(); 
  display("Iniciando Dispositivo!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
  delay(500);
  inicializaLaser();
  inicializaGiroscopio();
}
void display(String Texto1,int x1, int y1,String Texto2,int x2, int y2,String Texto3,int x3, int y3,String Texto4,int x4, int y4,String Texto5,int x5, int y5,String Texto6,int x6, int y6,String Texto7,int x7, int y7,String Texto8,int x8, int y8,String Texto9,int x9, int y9){
   u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(x1,y1, Texto1.c_str());
    u8g2.drawStr(x2,y2, Texto2.c_str());
    u8g2.drawStr(x3,y3, Texto3.c_str());
    u8g2.drawStr(x4,y4, Texto4.c_str());
    u8g2.drawStr(x5,y5, Texto5.c_str());
    u8g2.drawStr(x6,y6, Texto6.c_str());
    u8g2.drawStr(x7,y7, Texto7.c_str());
    u8g2.drawStr(x8,y8, Texto8.c_str());
    u8g2.drawStr(x9,y9, Texto9.c_str());
    Serial.println(Texto);
  } while ( u8g2.nextPage() );
}

float dadosLaser(){
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); 
     
  return (measure.RangeMilliMeter/10);
}

void exibeDadosGiroscopio(){
  mpu6050.update();
  anguloX = mpu6050.getAngleX();
  anguloY = mpu6050.getAngleY();
  
  display("Angulo X = " + String(anguloX), 5, 10,"Angulo Y = " + String(anguloY),5,20,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
}

void menuPrincipal(){
  if(menu == 10){
    if(posMenu == 0){
      display("* Iniciar medicao * ", 5, 10,"Configurar Som",5,20,"Configurar Brilho",5,30,"Calibrar Giroscopio",5,40,"Calibrar Laser",5,50,"Calibrar Pressao",5,60,"",0,0,"",0,0,"",0,0); 
    }
    if(posMenu == 1){
      display("Iniciar medicao", 5, 10,"* Configurar Som *",5,20,"Configurar Brilho",5,30,"Calibrar Giroscopio",5,40,"Calibrar Laser",5,50,"Calibrar Pressao",5,60,"",0,0,"",0,0,"",0,0); 
    }
    if(posMenu == 2){
      display("Iniciar medicao", 5, 10,"Configurar Som",5,20,"* Configurar Brilho *",5,30,"Calibrar Giroscopio",5,40,"Calibrar Laser",5,50,"Calibrar Pressao",5,60,"",0,0,"",0,0,"",0,0); 
    }
    if(posMenu == 3){
      display("Iniciar medicao", 5, 10,"Configurar Som",5,20,"Configurar Brilho",5,30,"* Calibrar Giroscopio *",5,40,"Calibrar Laser",5,50,"Calibrar Pressao",5,60,"",0,0,"",0,0,"",0,0); 
    }
    if(posMenu == 4){
      display("Iniciar medicao", 5, 10,"Configurar Som",5,20,"Configurar Brilho",5,30,"Calibrar Giroscopio",5,40,"* Calibrar Laser *",5,50,"Calibrar Pressao",5,60,"",0,0,"",0,0,"",0,0); 
    }
    if(posMenu == 5){
     display("Iniciar medicao", 5, 10,"Configurar Som",5,20,"Configurar Brilho",5,30,"Calibrar Giroscopio",5,40,"Calibrar Laser",5,50,"* Calibrar Pressao *",5,60,"",0,0,"",0,0,"",0,0); 
    }
  }
  else if(menu == 0){
      display("Iniciando Medicao!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
  }
  else if(menu == 1){
      display("Funcao som OFF!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
  }
  else if(menu == 2){
      display("Funcao brilho OFF!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
  }
  else if(menu == 3){
      exibeDadosGiroscopio();
  }
  else if(menu == 4){
      display("Funcao Laser OFF!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
  }
  else if(menu == 5){
      display("Funcao pressão OFF!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
  }
}

void controleBotoes(){
  if(digitalRead(botaoCima) == HIGH){
    if(posMenu == 5){    
    }
    else{
      posMenu ++;
    }  
  }
  else if(digitalRead(botaoBaixo) == HIGH){
    if(posMenu == 0){    
    }
    else{
      posMenu --;
    }  
  }
  else if(digitalRead(botaoOk) == HIGH){
    menu = posMenu;
  }
  else if(digitalRead(botaoVoltar) == HIGH){
    menu = 10;
    posMenu = 0;
  }
}
void loop(void) {
  controleBotoes();
  menuPrincipal();
  
  delay(15);
    
}
