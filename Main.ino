
#include <WiFi.h>
#include "DHT.h"
#define DHTTYPE DHT11


#define LDR 34 //pino gpio34
#define higrometro 35 //pino gpio35
#define dhPin 32 //pino gpio32
#define rele 23 //pino gpio23

//limites de umidade
#define limiteSeco 10 
#define limiteUmido 85 

float umidadeSolo = 0;
float luminosidade = 0;
float umidadeAmb = 0;
float temperatura = 0; 

bool automatico = false;

DHT dht(dhPin,DHTTYPE);

//Configurações de rede
const char* ssid = "xxx"; //Definir o SSID da rede Wifi
const char* password = "xxx"; //Definir a senha da rede WiFi
const char* server = "api.tago.io"; //Inserir o domínio da Tago.io
int porta = 80; //Inserir a porta de comunicaçao. Para a tago, utiliza-se a porta padrão (80)
WiFiClient client; // Inicializando a comunicação WiFi como cliente (vai pegar um IP da rede)

long previousMillis = 0;           //Variável de controle de tempo
long Interval = 1000;       // Tempo em ms do intervalo a ser executado



void setup() {
 config_inicial(); // Configuraçoes iniciais de setup
}

void loop() {
  
  unsigned long currentMillis = millis(); //variavel para armazenar o millis() atual

  if (currentMillis - previousMillis > Interval){ //condicional sendo executada a cada intervalo/1000 segundos
    previousMillis = currentMillis; //Salva o tempo atual da variavel previousMillis

    umidadeSolo = (analogRead(higrometro))*100/4095;
    luminosidade = (analogRead(LDR))*100/4095;
    umidadeAmb = dht.readHumidity();
    temperatura = dht.readTemperature();

    post_tago();
    
    get_tago(); //chamada da funcao post_tago() para enviar as informaçoes

    if (automatico==true){
      //Solo seco
      if (umidadeSolo < limiteSeco)
      { 
        digitalWrite(rele, LOW);
      }
      //Solo seco
      if (umidadeSolo > limiteUmido)
      { 
        digitalWrite(rele, HIGH);
      }
  
  
     
    }
    
  }
  

}
