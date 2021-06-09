void enviarMedidas(String nome, float medida){
  String readString;
  String data = "chave=";
  data += "ABC123";
  data += "&quantidade=";
  data += medida;
  data += "&nome_animal=";
  data += nome;
  display("Enviando Dados ", 5, 35,"",0,0,"",0,0,"",0,0,"",0,0);
  String link = "POST /AplicacaoTCC/public/Medidas/inserir HTTP/1.1";
  if(client.connect("192.168.0.199", 80)){
    client.println(link); 
    client.println("Host: 192.168.0.199");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
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
  Serial.println(readString);
  client.stop();
  readString = "";
}

void receberAnimais(){
  StaticJsonDocument<300> doc;
  char json[500] = {0};
  const char* serverName = "http://192.168.0.199/AplicacaoTCC/public/Animais/listaAnimais"; 
  HTTPClient http;
  http.begin(serverName);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST("chave=ABC123");  
  if(httpResponseCode>0){
    String resposta = http.getString();                       
    int lim1 = resposta.indexOf("<");
    resposta = resposta.substring(0,lim1 - 2);
    resposta.replace(" ", "");
    resposta.replace("\n", "");
    resposta.trim();
    resposta.toCharArray(json, 500); 
    deserializeJson(doc, json);   
    String vaca11 = doc["vaca1"]; 
    String vaca22 = doc["vaca2"]; 
    String vaca33 = doc["vaca3"]; 
    vaca1 = vaca11;
    vaca2 = vaca22;
    vaca3 = vaca33;
  }
  http.end();
}
