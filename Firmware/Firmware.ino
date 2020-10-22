//----- Bibliotecas ------//
#include <HX711.h> //Biblioteca Celula de carga https://github.com/bogde/HX711
#include <Arduino.h>
#include <U8g2lib.h> //Biblioteca Display
#include <Adafruit_VL53L0X.h> //Biblioteca Sensor de Distancia a Laser
#include <SPI.h>
#include <Wire.h>
#include <MPU6050_tockn.h> //Biblioteca Giroscopio
#include <WiFi.h> //Biblioteca WiFi
#include <EEPROM.h>
//#include <SharpIR.h>

//----- Difinição de Pinos -----//
//Pinos da Balaça
#define OUT_Balanca  13                      
#define CLK_Balanca  14                        

#define DT_PIN 13
#define SCK_PIN 12

//Botões
#define botaoVoltar 15
#define botaoCima 18
#define botaoBaixo 4
#define botaoOk 19

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 32, /* data=*/ 33, /* CS=*/ 25, /* reset=*/ 27);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define MPU6050_ADDR 0x68
MPU6050 mpu6050(Wire);

//SharpIR SharpIR(13, 1080);

HX711 balanca;          // define instancia balança HX711

IPAddress server(172,20,161,101); 
WiFiClient client;

//----- Variaveis -----//
float anguloX;
float anguloY;
String Texto;
int offset = 0;
unsigned long timeAtual;
unsigned long timeAnterior;
unsigned long intervalo;
int controleInicializacao = 0, posMenu = 0,posMenu1 = 0,op = 10,menu = 10;
int statusOrdenha;
String vaca1,vaca2,vaca3;
float laserInicio, pressaoInicio, cargaInicio;
float laserFim, pressaoFim, cargaFim;
float calibration_factor = 42130;     // fator de calibração para teste inicial

HX711 scale;

//----- Funções -----//

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
  display("Iniciando Giroscopio!", 5, 35,"",62,45,"",50,50,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void conectarWifi(){
  int cont = 0;
  WiFi.begin("Eduardo", "123eduardo2017");
  while (WiFi.status() != WL_CONNECTED) {
    cont ++;
    Serial.println(cont);
    delay(400);
    if(cont>=5){
      esp_restart();
    }
   }
}
void setup(void) {
  Serial.begin(115200);
  u8g2.begin(); 
  display("Iniciando Dispositivo!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
  Wire.begin();
  conectarWifi();
  
  balanca.begin(OUT_Balanca, CLK_Balanca);      // inicializa a balança
  balanca.set_scale();                                             // configura a escala da Balança
  balanca.tare();                                                 // zera a Balança
  balanca.set_scale(calibration_factor);                     // ajusta fator de calibração
  
  //inicializaLaser();
  inicializaGiroscopio();
  //receberAnimais();
  
  //scale.begin(DT_PIN,SCK_PIN);
  
  //0offset = scale.read_average(3);
}

/*float dadosLaser(){
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); 
     
  return (measure.RangeMilliMeter);
}*/

float dadosLaser(){
  //float distancia = SharpIR.getDistance();
  //return distancia;
}

float dadosCelulaCarga(){
  float kg = 0;
  kg     = scale.read_average(1) - offset;
  kg    /= 1000;

  return kg;
}
int verificaInclinacao(){
  mpu6050.update();

  if(mpu6050.getAngleX()> -5 && mpu6050.getAngleX()< 5){
    if(mpu6050.getAngleY()> -5 && mpu6050.getAngleY()< 5){
      return 1;
    }
    else{
       return 0;
    }
  }
  else{
    return 0;
  }
}
void exibeDadosGiroscopio(){
  mpu6050.update();
  anguloX = mpu6050.getAngleX();
  anguloY = mpu6050.getAngleY();
  
  display("Angulo X = " + String(anguloX), 5, 10,"Angulo Y = " + String(anguloY),5,20,"OK: " + String(verificaInclinacao()),5,30,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
}

void ordenha(String Vaca){
  if(verificaInclinacao() == 1){
    display("Iniciando Ordenha!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
    laserInicio = dadosLaser();
    cargaInicio = dadosCelulaCarga();
    
    while(statusOrdenha == 1){
      display("Ordenha Iniciada! ", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
      if(digitalRead(botaoOk) == HIGH){
        statusOrdenha = 0;
      }
      delay(50);
    }
    display("Finalizando Ordenha! ", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
    delay(500);
  }
  else{
    display("Taro em Desnivel", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
    delay(200);
  }
 
}
void Menu2(){
  statusOrdenha = 1;
  if(posMenu1 == 0){
    display("-> " + vaca1 + " *", 5, 10,vaca2,5,20,vaca3,5,30,"",5,40,"",5,50,"",5,60,"",0,0,"",0,0,"",0,0); 
  }
  else if(posMenu1 == 1){
    display(vaca1, 5, 10,"-> " + vaca2 + " *",5,20,vaca3,5,30,"",5,40,"",5,50,"",5,60,"",0,0,"",0,0,"",0,0);
  }
  else if(posMenu1 == 2){
    display(vaca1, 5, 10,vaca2,5,20,"-> " + vaca3 + " *",5,30,"",5,40,"",5,50,"",5,60,"",0,0,"",0,0,"",0,0);
  }
  if(op==0){
    ordenha(vaca1);
  }
  else if(op==0){
    ordenha(vaca2);
  }
  else if(op==0){
    ordenha(vaca3);
  }
}
void menuPrincipal(){
  if(menu == 10){
    if(posMenu == 0){
      display("* Iniciar medicao * ", 5, 10,"Calibrar Peso",5,20,"Configurar Brilho",5,30,"Calibrar Giroscopio",5,40,"Calibrar Laser",5,50,"Calibrar Pressao",5,60,"",0,0,"",0,0,"",0,0); 
    }
    if(posMenu == 1){
      display("Iniciar medicao", 5, 10,"* Calibrar Peso *",5,20,"Configurar Brilho",5,30,"Calibrar Giroscopio",5,40,"Calibrar Laser",5,50,"Calibrar Pressao",5,60,"",0,0,"",0,0,"",0,0); 
    }
    if(posMenu == 2){
      display("Iniciar medicao", 5, 10,"Calibrar Peso",5,20,"* Configurar Brilho *",5,30,"Calibrar Giroscopio",5,40,"Calibrar Laser",5,50,"Calibrar Pressao",5,60,"",0,0,"",0,0,"",0,0); 
    }
    if(posMenu == 3){
      display("Iniciar medicao", 5, 10,"Calibrar Peso",5,20,"Configurar Brilho",5,30,"* Calibrar Giroscopio *",5,40,"Calibrar Laser",5,50,"Calibrar Pressao",5,60,"",0,0,"",0,0,"",0,0); 
    }
    if(posMenu == 4){
      display("Iniciar medicao", 5, 10,"Calibrar Peso",5,20,"Configurar Brilho",5,30,"Calibrar Giroscopio",5,40,"* Calibrar Laser *",5,50,"Calibrar Pressao",5,60,"",0,0,"",0,0,"",0,0); 
    }
    if(posMenu == 5){
     display("Iniciar medicao", 5, 10,"Calibrar Peso",5,20,"Configurar Brilho",5,30,"Calibrar Giroscopio",5,40,"Calibrar Laser",5,50,"* Calibrar Pressao *",5,60,"",0,0,"",0,0,"",0,0); 
    }
  }
  else if(menu == 0){      
      Menu2();
  }
  else if(menu == 1){
      calibraBalanca();
  }
  else if(menu == 2){
      display("Funcao brilho OFF!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);
  }
  else if(menu == 3){
      exibeDadosGiroscopio();
  }
  else if(menu == 4){
      display("Distancia = " + String(dadosLaser()) + " MM", 5, 10,"Litros = ",5,20,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0);   
  }
  else if(menu == 5){
     //display("Valor = " + String(hx711.read()) + "", 5, 10,"Litros = ",5,20,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0); 
  }
}

void controleBotoes(){
  if(digitalRead(botaoCima) == HIGH){
    if(menu == 0){
      if(posMenu1 == 3){    
      }
      else{
        posMenu1 ++;
      }  
    }
    else{
      if(posMenu == 5){    
      }
      else{
        posMenu ++;
      }  
    }
  }
  else if(digitalRead(botaoBaixo) == HIGH){
    if(menu == 0){
      if(posMenu1 == 0){    
      }
      else{
        posMenu1 --;
      }  
    }
    else{
      if(posMenu == 0){    
      }
      else{
        posMenu --;
      }  
    }
  }
  else if(digitalRead(botaoOk) == HIGH){
    if(menu == 0){
      op = posMenu1;
    }
    else{
      menu = posMenu;
    }
  }
  else if(digitalRead(botaoVoltar) == HIGH){
    menu = 10;
    op = 10;
    posMenu1 = 0;
    posMenu = 0;
  }
}
void loop(void) {
  
  controleBotoes();
  menuPrincipal();
  delay(15);
}
