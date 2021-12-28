void get_tago(void){ //inicializaçao da funçao post_tago()
  
  
  String token = "1a8395de-15f7-4342-9a3b-8b818caf30ef"; //token do dispositivo na Tago
  String variavel[] = {"atuador","automatico"}; //nome da variável cujo valor é desejado obter
  
  int comprimento; //variável para armazenar o comprimento do arquivo Json
  String string_atuador; // recebe a palavra true or false
  String string_automatico; // recebe a palavra true or false
   //recebe um inteiro 0 ou 1

  if (client.connect(server, porta)){ //iniciando o soquete TCP IP, mandando IP e servidor como parametros

    Serial.print("Conectado na Tago.io!\n"); //Exibe a mensagem 'Conectado na Tago'

    //aqui começa a montagem do GET via protocolo HTTP e JSON

    String url = "/data";
    url += "?variable[]=";
    url += variavel[0];
    url += "&variable[]=";
    url += variavel[1];
    url += "&query=";
    url += "last_value";

    //Serial.print("URL requisitada: ");
    Serial.println(url);

    //Requisição GET para o servidor da Tago

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + server + "\r\n" +
                 "Content-Type: application/json\r\n" +
                 "Device-Token: " + token + "\r\n"
                 "Connection: close\r\n\r\n");

    /*print na Serial do que foi enviado pelo ESP8266 ao servidor da Tago
    Serial.println(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + server + "\r\n" +
                   "Content-Type: application/json\r\n" +
                   "Device-Token: " + token + "\n"
                   "Connection: close\r\n\r\n"); */

     //verificacao de timeout
     unsigned long timeout = millis(); //na variavel 'timeout' e armazenado o valor da funcao milis()
     while (client.available() == 0) { // se o cliente nao estiver disponível
          if (millis() - timeout > 5000){ //verifica se o servidor ficou 5 segundos sem responder
              Serial.println(">>>timeout !"); //exibe a mensagem 'timeout'
              client.stop(); //finaliza a conexao com o Tago
              digitalWrite(rele, HIGH);
              automático = false;
              return ; // sai da funcao de conexao com o Tago
        
           }
           
     }

     String resposta = ""; //String que vai armazenar a resposta do servidor. Com base nela, faremos uma tratativa para coletar apenas o valor da variavel na Tago.
     while (client.available()) { //se o cliente estiver disponivel
          
          resposta = client.readStringUntil('\r'); //Ler a String de resposta do servidor Tago até encontrar um \r (caractere de retorno de carro, 13 ASCII)
          
     }

     Serial.print("Resposta da Tago: ");
     Serial.println(resposta); //print da resposta do servidor Tago

    
    comprimento = resposta.length(); //coletando o comprimento da resposta do servidor da Tago
    
    int resp = resposta.indexOf("atuador"); //procura onde está o valor da variavel na string
    string_atuador = (resposta.substring(resp-18,resp-14));
    
    resp = resposta.indexOf("automatico"); //procura onde está o valor da variavel na string
    string_automatico = (resposta.substring(resp-18,resp-14));
     //Serial.println(string_atuador); 
     //Serial.println(string_automatico);
    
    if (string_atuador == ":tru") { 
        digitalWrite(rele, LOW);//o módulo de relé utilizado é ativado por nível baixo
        Serial.println("Relé: ativado\n");
      
    } else if (string_atuador == "fals"){  
         digitalWrite(rele, HIGH); 
         Serial.println("Relé: desativado\n");
    }
    
     if (string_automatico == ":tru") { 
        automatico = true;
        Serial.println("Modo automatico: ativado\n");
      
    } else if (string_atuador == "fals"){  
          automatico = false;
         Serial.println("Modo automatico: desativado\n");
    }
    
    client.stop(); //finalizando a comunicacao com o servidor
 
  }
  
}
