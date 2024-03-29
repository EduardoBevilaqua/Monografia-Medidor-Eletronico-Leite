void calibraBalanca(){
  int mult = 0;
  
  while(true){
    balanca.set_scale(fatorCalibracao);                     // ajusta fator de calibração
    float litros = 0, peso = 0;
    for(int i=0;i<5;i++){
      peso = peso + balanca.get_units();
      delay(0.5);
      Serial.println(String(i) + " " + String(peso));
    }
    peso = (peso / 5);
    Serial.println(peso);
    litros = peso;
    display("Peso: " + String(peso,3) + " KG" , 5, 10,"Litros: " + String(litros,3) + " Litros",5,25,"",70,10,"Fator: " + String(fatorCalibracao),5,40,"",5,40);
    delay(100) ;                                               // atraso de 0,5 segundos
    
    if(digitalRead(botaoCima) == HIGH && digitalRead(botaoBaixo) == HIGH){
      if(mult == 0){
         mult = 1;
      }
      else{
        mult = 0;
      } 
    }
    else if(digitalRead(botaoVoltar) == HIGH && digitalRead(botaoOk) == HIGH){
       balanca.tare();
    }
    else if(digitalRead(botaoCima) == HIGH){
      if(mult == 0){
        fatorCalibracao += 100;
      }
      else{
        fatorCalibracao += 10;
      }
    }
    else if(digitalRead(botaoBaixo) == HIGH){
      if(mult == 0){
        fatorCalibracao -= 100;
      }
      else{
        fatorCalibracao -= 10;
      }
    }
    else if(digitalRead(botaoOk) == HIGH){
     gravarEeprom(fatorCalibracao, 10);
    }
    else if(digitalRead(botaoVoltar) == HIGH){
      break;
    }
  }
}
