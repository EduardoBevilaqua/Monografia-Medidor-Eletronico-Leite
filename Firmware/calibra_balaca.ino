void calibraBalanca(){
  while(true){
    balanca.set_scale(calibration_factor);                     // ajusta fator de calibração
    display("Peso: ", 5, 10,String(balanca.get_units()),40,10," KG",70,10,"Fator de Calibração: ",5,20,String(calibration_factor),5,30,"",0,0,"",0,0,"",0,0,"",0,0);
    delay(100) ;                                               // atraso de 0,5 segundos
    
    if(digitalRead(botaoCima) == HIGH && digitalRead(botaoBaixo) == HIGH){
      balanca.tare(); 
    }
    else if(digitalRead(botaoCima) == HIGH){
      calibration_factor += 100;
    }
    else if(digitalRead(botaoBaixo) == HIGH){
      calibration_factor -= 100;
    }
    else if(digitalRead(botaoOk) == HIGH){
      //gravarSerial(calibration_factor);
    }
    else if(digitalRead(botaoVoltar) == HIGH){
      break;
    }
  }
}
