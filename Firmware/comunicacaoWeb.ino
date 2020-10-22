IPAddress server(172,20,161,101); 

void enviarMedidas(String nome, float medida){
  String readString;
  Serial.println("--- Recebendo Lista de Animais ---");
  String link = "GET /AplicacaoTCC/public/Medidas/inserir/ABC123/" + nome + "/" + String(medida) + " HTTP/1.1";
  if(client.connect(server, 80)){
    client.println(link); 
    client.println("Host: 192.168.137.1");
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

void receberAnimais(){
  
  String readString;
  Serial.println("--- Recebendo Lista de Animais ---");
  String link = "GET /AplicacaoTCC/public/Animais/listaAnimais HTTP/1.1";
  if(client.connect(server, 80)){
    client.println("GET /AplicacaoTCC/public/Animais/listaAnimais HTTP/1.1"); 
    client.println("Host: 172.20.161.101");
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
