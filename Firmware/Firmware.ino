#include <HX711.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <Adafruit_VL53L0X.h>
#include <SPI.h>
#include <Wire.h>
#include <MPU6050_tockn.h>
#include <WiFi.h>


#define DT_PIN 13
#define SCK_PIN 12

#define botaoVoltar 15
#define botaoCima 18
#define botaoBaixo 4
#define botaoOk 19

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 32, /* data=*/ 33, /* CS=*/ 25, /* reset=*/ 27);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define MPU6050_ADDR 0x68
MPU6050 mpu6050(Wire);

IPAddress server(192,168,0,199); 
WiFiClient client;

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

HX711 scale;


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
  inicializaLaser();
  inicializaGiroscopio();
  receberAnimais();
  
  //scale.begin(DT_PIN,SCK_PIN);
  //offset = scale.read_average(3);
}

void receberAnimais(){
  
  String readString;
  Serial.println("--- Recebendo Lista de Animais ---");
  String link = "GET /AplicacaoTCC/public/Animais/listaAnimais HTTP/1.1";
  if(client.connect(server, 80)){
    client.println("GET /AplicacaoTCC/public/Animais/listaAnimais HTTP/1.1"); 
    client.println("Host: 192.168.0.199");
    client.println("Connection: close");
    client.println();
  }
  if(client){   
    while(client.connected()){
      while(client.available()){
        char c = client.read();
        readString += c;
      }
    }
  }
  readString.trim();
  int lim1 = readString.indexOf("--");
  int lim2 = readString.indexOf("---");
  int lim3 = readString.indexOf("----");
  int lim4 = readString.indexOf("-----");
  vaca1 = readString.substring(lim1 + 2,lim2) + "\n";
  vaca2 = readString.substring(lim2 + 3,lim3) + "\n";
  vaca3 = readString.substring(lim3 + 4,lim4) + "\n";
  client.stop();
  readString = "";
}

void enviarMedidas(String nome, float medida){
  
  String readString;
  Serial.println("--- Recebendo Lista de Animais ---");
  String link = "GET /AplicacaoTCC/public/Medidas/inserir/ABC123/" + nome + "/" + String(medida) + " HTTP/1.1";
  if(client.connect(server, 80)){
    client.println(link); 
    client.println("Host: 192.168.0.199");
    client.println("Connection: close");
    client.println();
  }
  if(client){   
    while(client.connected()){
      while(client.available()){
        char c = client.read();
        readString += c;
      }
    }
  }
  readString.trim();
  client.stop();
  readString = "";
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
  } while ( u8g2.nextPage() );
}

float dadosLaser(){
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); 
     
  return (measure.RangeMilliMeter);
}

float dadosCelulaCarga(){
  int kg = 0;
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
      display("Peso = " + String(dadosCelulaCarga()) + "", 5, 10,"",5,20,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0,"",0,0); 
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
