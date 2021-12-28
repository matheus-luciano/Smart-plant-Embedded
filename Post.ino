// Post das infornalções na plataforma Tago.io via TCP/IP atrelado ao protocolo JSON
   
void post_tago(void) {

  String token = "1a8395de-15f7-4342-9a3b-8b818caf30ef"; //token do dispositivo na Tago
  String variaveis[] = {"umidadeSolo", "luminosidade","umidadeAmb", "temperatura"}; // Vetor String para armazenar as chaves dos itens
  float valores[] = {umidadeSolo,luminosidade,umidadeAmb,temperatura}; // Vetor para armazenar os valores dos itens

  for (int i=0; i<(sizeof(valores)/sizeof(int)); i++){ // Loop executado de acordo com o tamanho do vetor valores[]. Vai postar todos os itens e chaves configurados

    if (client.connect(server, porta)) { //iniciando o soquete TCP/IP, mandando IP e servidor como parametros
        Serial.print("Conectado na Tago.io!\n");

        String tago = "";

        // Aqui começa a montagem do Post via protocolo HTTP e JSON
        
        String PostData = String("{\"variable\":")  + String("\"") + String(variaveis[i]) + String("\"") + String(",\"value\":") + String(valores[i]) + String("}");

        tago = "POST /data? HTTP/1.1\n";
        tago += "Host: api.tago.io\n";
        tago += "_ssl: false\n";
        tago += "Device-Token: " + token + "\n";
        tago += "Content-Type: application/json\n";
        tago += "Content-Length: " + String(PostData.length()) + "\n";
        tago += "\n";
        tago += PostData;

        //Serial.println("Post via HTTP POST: "); //print na Serial da mensagem: 'Post via HTTP POST: '
        //Serial.println(tago);
        client.print(tago); // Envia as informações para Tago via POST HTTP

        tago = ""; // Limpa a String 'zabbix' para que possa ser utilizada na proxima iteração do laço FOR

        //verificacao de timeout
        unsigned long timeout = millis(); //na variavel 'timeout' e armazenado o valor da funcao milis()
        while (client.available() == 0) { // se o cliente nao estiver disponível
              if (millis() - timeout > 5000){ //verifica se o servidor ficou 5 segundos sem responder
                  Serial.println(">>>timeout !"); //exibe a mensagem 'timeout'
                  client.stop(); //finaliza a conexao com o Tago
                  return ; // sai da funcao de conexao com o Tago
        
              }
           
        }

        String resposta = ""; //String que vai armazenar a resposta do servidor. Com base nela, faremos uma tratativa para coletar apenas o valor da variavel na Tago.
        while (client.available()) { //se o cliente estiver disponivel
          
            resposta = client.readStringUntil('\r'); //Ler a String de resposta do servidor Tago até encontrar um \r (caractere de retorno de carro, 13 ASCII)
           // Serial.print("Resposta da Tago: ");
           // Serial.println(resposta); //print da resposta do servidor Tago

        }
        
        
    }
    Serial.print("Umidade do Solo = ");
    Serial.println(umidadeSolo);
    Serial.print("Luminosidade = ");
    Serial.println(luminosidade);
    Serial.print("Umidade Ambiente = ");
    Serial.println(umidadeAmb);
    Serial.print("Temperatura = ");
    Serial.println(temperatura);
    Serial.println();
    client.stop(); //finalizando a comunicação com o servidor
  }


  
}
