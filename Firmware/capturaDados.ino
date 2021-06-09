float dadosBalaca(){
  float litros = 0;
  float peso = 0;
  for(int i=0;i<5;i++){
    peso = peso + balanca.get_units();
    delay(0.5);
  }
  peso = peso / 5;
  //litros = peso / 1,032;
  litros = peso / 1,0;
  return (litros);
}
