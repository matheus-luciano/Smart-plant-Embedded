  void config_inicial(){

      Serial.begin(115200); //Configuração da UART
      Serial.print("Conectando na rede "); //print na Serial de conexão na rede wifi alocada
      Serial.println(ssid); //Print do SSID da rede Wifi
      
      //Inicia o WiFi
      WiFi.begin(ssid, password); //inicializando a comunicação com a rede local wifi
      
      //Loop até conectar no WiFi
      while (WiFi.status() != WL_CONNECTED) { //loop ate que seja feita a conexao com o wifi
        delay(500);
        Serial.print("."); //print . na serial
  }

  //Inicia o sensor de umidade e temperatura
  
  dht.begin();
  
  //prints via comunicação Serial
  Serial.println("Conectado na rede local");
  Serial.print(ssid);  //print na Serial do SSID da rede
  Serial.print(" IP: ");//print na Serial da mensagem IP:
  Serial.println(WiFi.localIP()); //print na Serial do IP que o dispositivo pegou na rede
  Serial.println(); //pulando linha
  
  pinMode(LDR, INPUT);
  pinMode(higrometro, INPUT);

  pinMode(rele, OUTPUT);
  digitalWrite(rele, HIGH); //relé é ativado com nível 0
}
