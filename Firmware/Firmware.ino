
#include <Arduino.h>
#include <U8g2lib.h>
#include <Adafruit_VL53L0X.h>
 
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define botaoVoltar 
#define botaoCima 
#define botaoBaixo
#define botaoOk

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 32, /* data=*/ 33, /* CS=*/ 25, /* reset=*/ 27);
String Texto;

void setup(void) {

  Serial.begin(115200);
  Serial.println("-------Iniciando!-------\n"); 
  if (!lox.begin()) {
    Serial.println("-------aqui!-------\n"); 
    while(1);
  }
  u8g2.begin(); 
}
void display(String Texto,int x, int y){
   u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(x,y, Texto.c_str());
    Serial.println(Texto);
  } while ( u8g2.nextPage() );
}
void loop(void) {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); 
     
  String distancia = String(measure.RangeMilliMeter/10) + " Cm";
  display(distancia, 0, 20);    
}
