//----- Bibliotecas ------//
#include <HX711.h> //Biblioteca Celula de carga https://github.com/bogde/HX711
#include <Arduino.h>
#include <U8g2lib.h> //Biblioteca Display
#include <WiFi.h> //Biblioteca WiFi
#include <EEPROM.h> //Biblioteca para manipular EEPROM
#include <HTTPClient.h> //Biblioteca Para requisição HTTP
#include <ArduinoJson.h> //Biblioteca para manipular Json

//----- Difinição de Pinos -----//
//Pinos da Balaça
#define OUT_Balanca  13                      
#define CLK_Balanca  14                        

//Botões
#define botaoVoltar 22
#define botaoCima 18
#define botaoBaixo 4
#define botaoOk 19

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 32, /* data=*/ 33, /* CS=*/ 25, /* reset=*/ 27);

HX711 balanca; // define instancia balança HX711
 
WiFiClient client;

//----- Funções -----//

void display();
void menuServico();
int lerEeprom(int pos);

//----- Variaveis -----//
int statusOrdenha;
float cargaInicio;
int fatorCalibracao = 0; // fator de calibração para teste inicial
int statusMenuServico = 0;

String vaca1,vaca2,vaca3; 

void setup(void) {
  Serial.begin(115200);
  pinMode(22, INPUT);
  display("Iniciando Dispositivo!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
  u8g2.begin(); 
  conectarWifi();
  if(digitalRead(botaoVoltar) == HIGH && digitalRead(botaoOk) == HIGH){
      statusMenuServico = 1;
      display("Modo Servico!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
      delay(700);
  }
  receberAnimais();
  inicializaBalaca();
  if(statusMenuServico == 1){
    calibraBalanca();
  }
}

void ordenha(String Vaca){
    float quantidade;
    display("Iniciando Ordenha!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
    delay(100);
    display("Capturando Dados...", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
    delay(100);
    balanca.tare();
    while(statusOrdenha == 1){
      quantidade  = dadosBalaca();
      display("Ordenha Iniciada! ", 5, 20,"Litros: "+String(quantidade,3)+" L",5,35,"",45,35,"",0,0,"",0,0);
      if(digitalRead(botaoOk) == HIGH){
        display("Finalizando Ordenha! ", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
        delay(100);
        enviarMedidas(Vaca, quantidade);
        statusOrdenha = 0;
      }
       if(digitalRead(botaoVoltar) == HIGH){
        display("Ordenha Cancelada! ", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
        delay(500);
        statusOrdenha = 0;
      }
      delay(50);
    }
    display("Finalizando Ordenha! ", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
    delay(500);
}
void MenuOrdenha(){
  int controle = 1, posMenu = 0, op = 10;
  while(controle == 1){
      if(digitalRead(botaoCima) == HIGH){
         if(posMenu == 4){    
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
        op = posMenu;
      }
      else if(digitalRead(botaoVoltar) == HIGH){
  
      }
    statusOrdenha = 1;
    if(posMenu == 0){
      display("-> " + String(vaca1), 5, 10,String(vaca2),5,20,String(vaca3),5,30,"",5,40,"",5,50); 
    }
    else if(posMenu == 1){
      display(String(vaca1), 5, 10,"-> " + String(vaca2),5,20,String(vaca3),5,30,"",5,40,"",5,50);
    }
    else if(posMenu == 2){
      display(String(vaca1), 5, 10,String(vaca2),5,20,"-> " + String(vaca3),5,30,"",5,40,"",5,50);
    }
    if(op==0){
      ordenha(vaca1);
      vaca1 = vaca1 + " X";
      op = 10;
      
    }
    else if(op==1){
      ordenha(vaca2);
      vaca2 = vaca2 + " X";
      op = 10;
     
    }
    else if(op==2){
      ordenha(vaca3);
      vaca3 = vaca3 + " X";
      op = 10;
     
    }
  }
}

void loop(void) {
  MenuOrdenha();
  delay(15);
}
