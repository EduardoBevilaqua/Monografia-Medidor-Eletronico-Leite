void inicializaLaser(){
  display("Iniciando Sensor Laser!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
  lox.begin();
  delay(1000); 
}
void inicializaGiroscopio(){
  display("Iniciando Giroscopio!", 5, 35,"",62,45,"",50,50,"",0,0,"",0,0);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}
void inicializaBalaca(){
  display("Iniciando Balanca!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
  calibration_factor = lerEeprom(10);  
  balanca.begin(OUT_Balanca, CLK_Balanca);      
  balanca.set_scale();                                             
  balanca.tare();                                                
  balanca.set_scale(calibration_factor);                
}
