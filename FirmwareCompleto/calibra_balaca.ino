void calibraBalanca(){
  int mult = 0;
  while(true){
    balanca.set_scale(calibration_factor);              
    float litros = 0, peso = 0;
    for(int i=0;i<5;i++){
      peso = peso + balanca.get_units();
      delay(0.5);
    }
    peso = (peso / 5);
    litros = peso;
    display("Peso: "+String(peso,3)+" KG" ,5,10,"Litros: "+String(litros,3)+" Litros",5,25,"",70,10,"Fator: " + String(calibration_factor),5,40,"",5,40);
    delay(100) ;                                           
    
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
        calibration_factor += 100;
      }
      else{
        calibration_factor += 10;
      }
    }
    else if(digitalRead(botaoBaixo) == HIGH){
      if(mult == 0){
        calibration_factor -= 100;
      }
      else{
        calibration_factor -= 10;
      }
    }
    else if(digitalRead(botaoOk) == HIGH){
     gravarEeprom(calibration_factor, 10);
    }
    else if(digitalRead(botaoVoltar) == HIGH){
      break;
    }
  }
}
