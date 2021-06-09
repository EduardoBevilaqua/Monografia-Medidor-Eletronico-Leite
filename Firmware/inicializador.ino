void inicializaBalaca(){
  display("Iniciando Balanca!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
  fatorCalibracao = lerEeprom(10);  
  balanca.begin(OUT_Balanca, CLK_Balanca);      // inicializa a balança
  balanca.set_scale();                                             // configura a escala da Balança
  balanca.tare();                                                 // zera a Balança
  balanca.set_scale(fatorCalibracao);                     // ajusta fator de calibração
  
}
void conectarWifi(){
  display("Conectando Wifi!", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
  int cont = 0;
  WiFi.begin("Eduardoo", "123eduardo2017");
  while (WiFi.status() != WL_CONNECTED) {
    cont ++;
    delay(400);
    if(cont>=8){
      esp_restart();
    }
   }
}
