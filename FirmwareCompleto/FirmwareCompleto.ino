//----- Bibliotecas ------//
#include <HX711.h> //Biblioteca Celula de carga https://github.com/bogde/HX711
#include <U8g2lib.h> //Biblioteca Display
#include <Adafruit_VL53L0X.h> //Biblioteca Sensor de Distancia a Laser
#include <SPI.h> //SPI
#include <Wire.h> //Biblioteca I2C
#include <MPU6050_tockn.h> //Biblioteca Giroscopio
#include <EEPROM.h> // Biblioteca para Manipular EEPROM
#include <Adafruit_ADS1015.h> //Biblioteca conversor ADC

//----- Difinição de Pinos -----//
//Pinos da Balaça
#define OUT_Balanca  13                      
#define CLK_Balanca  14

#define MPU6050_ADDR 0x68 //Define Giroscopio
#define   ADC_16BIT_MAX   65536  //Define converso ADC                      

//Botões
#define botaoVoltar 15
#define botaoCima 18
#define botaoBaixo 4
#define botaoOk 19

//----- Instancia Sensores -----//
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0,/*clock=*/32,/*data=*/33,/*CS=*/25,/*reset=*/27);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
MPU6050 mpu6050(Wire);
Adafruit_ADS1115 ads(0x48);
HX711 balanca; 

//----- Funções -----//
void display();
void menuServico();
int lerEeprom(int pos);

//----- Variaveis -----//
float anguloX, anguloY;
String Texto;
int calibration_factor = 0; // fator de calibração para teste inicial
int statusMenuServico = 0;
int16_t adc0;


void setup(void) {
  Serial.begin(115200);
  display("Iniciando Dispositivo!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
  u8g2.begin(); 
  Wire.begin();
  //Verifica se os botoes estão precionados para entrar em modo serviço
  if(digitalRead(botaoVoltar) == HIGH && digitalRead(botaoOk) == HIGH){
      statusMenuServico = 1;
      display("Modo Servico!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
      delay(700);
  }
  // inicia Sensores
  ads.begin();
  inicializaLaser();
  inicializaGiroscopio();
  inicializaBalaca();
  if(statusMenuServico == 1){
    menuServico();
  }
}

void menuServico(){
  int controle = 1, posMenu = 0, menu = 10;
  while(controle == 1){
    if(digitalRead(botaoCima) == HIGH){
       if(posMenu == 3){    
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
      if(menu == 10){
        controle = 0;
      }
      else{
        menu = 10;
        posMenu = 0;
      }
    }
    if(menu == 10){
      if(posMenu == 0){
        display("* Calibrar Pressao * ", 5, 10,"Calibrar Peso",5,20,"Calibrar Giroscopio",5,30,"Calibrar Laser",5,40,"",5,50); 
      }
      if(posMenu == 1){
        display("Calibrar Pressao", 5, 10,"* Calibrar Peso *",5,20,"Calibrar Giroscopio",5,30,"Calibrar Laser",5,40,"",5,50); 
      }
      if(posMenu == 2){
        display("Calibrar Pressao", 5, 10,"Calibrar Peso",5,20,"* Calibrar Giroscopio *",5,30,"Calibrar Laser",5,40,"",5,50); 
      }
      if(posMenu == 3){
        display("Calibrar Pressao", 5, 10,"Calibrar Peso",5,20,"Calibrar Giroscopio",5,30,"* Calibrar Laser *",5,40,"",5,50); 
      }
    }
    else if(menu == 0){
        exibeDadosPressao();
    }
    else if(menu == 1){
        calibraBalanca();
    }
    else if(menu == 2){
        exibeDadosGiroscopio();
    }
    else if(menu == 3){
        exibeDadosLaser();
    }
  }
}
void loop(void) {
  display("Presione a tecla verde para iniciar!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
  delay(15);
}
