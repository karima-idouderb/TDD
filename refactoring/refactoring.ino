#include <SoftwareSerial.h>
#include <DHT.h>

#define Lora_RX D6       
#define Lora_TX D7        
#define DHTPIN D3        
#define DHTTYPE DHT22     
#define SEND_INTERVAL 60000 // Intervalle pour l'envoi des données (en ms)

const String DEVEUI = "70B3D57ED006B8DA";  
const String APPEUI = "0123456789ABCDEF";  
const String APPKEY = "BC7FFB46A5A428B734ED6939AA1790B4";

SoftwareSerial loraSerial(Lora_RX, Lora_TX);
DHT dht(DHTPIN, DHTTYPE);                    // Initialisation du capteur DHT

void initLoRa();
void readSensorData(float &temperature, float &humidity);
String prepareMessage(float temperature, float humidity);
void sendLoRaMessage(const String &message);
void sendATCommand(const String &command);

void setup() {
  Serial.begin(115200);         // Moniteur série pour l'ESP8266
  loraSerial.begin(9600);       // Port série pour le module LoRa
  dht.begin();                  
  delay(1000);

  initLoRa();                  
}

void loop() {
  float temperature, humidity;

  readSensorData(temperature, humidity);

  String message = prepareMessage(temperature, humidity);
  sendLoRaMessage(message);

  delay(SEND_INTERVAL);  // Attendre avant de relire
}

void initLoRa() {
  sendATCommand("AT");
  sendATCommand("AT+MODE=LWOTAA");
  sendATCommand("AT+ID=DevEUI," + DEVEUI);
  sendATCommand("AT+ID=AppEUI," + APPEUI);
  sendATCommand("AT+KEY=APPKEY," + APPKEY);
  sendATCommand("AT+ID");
  sendATCommand("AT+JOIN");
}

void readSensorData(float &temperature, float &humidity) {
  humidity = dht.readHumidity();        
  temperature = dht.readTemperature(); 

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Échec de lecture du capteur DHT!");
    temperature = humidity = -1; // Valeurs invalides
  } else {
    Serial.print("Température : ");
    Serial.print(temperature);
    Serial.print(" °C, Humidité : ");
    Serial.print(humidity);
    Serial.println(" %");
  }
}

String prepareMessage(float temperature, float humidity) {
  if (temperature < 0 || humidity < 0) {
    return "";  // Évite d'envoyer des données invalides
  }

  String tempHex = String((int)(temperature * 100), HEX);
  String humHex = String((int)(humidity * 100), HEX);
  return tempHex + humHex;
}

void sendLoRaMessage(const String &message) {
  if (message.isEmpty()) {
    Serial.println("Message vide, envoi annulé.");
    return;
  }

  sendATCommand("AT+MSGHEX=" + message);
}

void sendATCommand(const String &command) {
  Serial.print("Envoi de la commande : "); 
  Serial.println(command);
  loraSerial.println(command);  
  delay(1000);

  while (loraSerial.available()) {
    String response = loraSerial.readStringUntil('\n');
    Serial.print("Réponse du module : ");
    Serial.println(response);
  }
}