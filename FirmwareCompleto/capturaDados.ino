void exibeDadosLaser(){
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); 
  float distanciaMM=0;
  for(int i=0;i<3000;i++){
    distanciaMM = distanciaMM + measure.RangeMilliMeter;
    delay(0.5);
  }
  distanciaMM = distanciaMM/3000;
  distanciaMM = (0.9065 * distanciaMM) - 0.9082; 
  float distanciaCM = distanciaMM / 10;
  float nivel = 36 - distanciaCM;
  display("Distancia MM: "+String(distanciaMM),5,10,"Distancia CM: "+String(distanciaCM),5,25,"Nivel: "+String(nivel),5,40,"",0,0,"",0,0);
}

void exibeDadosGiroscopio(){
  mpu6050.update();
  anguloX = mpu6050.getAngleX();
  anguloY = mpu6050.getAngleY();
  
  display("Angulo X = " + String(anguloX), 5, 10,"Angulo Y = " + String(anguloY),5,20,"",5,30,"",0,0,"",0,0);
}

void exibeDadosPressao(){
  float Volt = 0.0; 
  adc0 = ads.readADC_SingleEnded(0);
  Volt = (adc0 * 0.1875)/1000;
  double pressao = (( Volt - 0.04 * 5 ) / (0.009 * 5)) + (2.5 * 1 * 0.009 * 5);
  double nivel = ((pressao * 1000) / (997 * 9.8)) * 100;
  float litros = (3.14 * (14.75 * 14.75) * nivel)/1000;
  litros = 0.8999 * litros + 0.3502;
  display("Pressao: " + String(pressao), 5, 10,"Nivel: " + String(nivel),5,25,"Qtd: " + String(litros,3),5,40,"Tensao: " + String(Volt, 6),5,55,"",0,0);
}
