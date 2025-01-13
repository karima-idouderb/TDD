#include <SoftwareSerial.h>
#include <DHT.h>

#define Lora_RX D6         // Broche RX de l'ESP8266 connectée au TX du module LoRa
#define Lora_TX D7         // Broche TX de l'ESP8266 connectée au RX du module LoRa
#define DHTPIN D3          // Pin où le DHT22 est connecté
#define DHTTYPE DHT22      // Type de capteur DHT

SoftwareSerial loraSerial(Lora_RX, Lora_TX); // RX, TX
DHT dht(DHTPIN, DHTTYPE);                    // Initialisation du capteur DHT

// Identifiants pour la connexion LoRa via OTAA
String deveui = "70B3D57ED006B8DA";  
String appeui = "0123456789ABCDEF";  
String appkey = "BC7FFB46A5A428B734ED6939AA1790B4";

void setup() {
  Serial.begin(115200);         // Moniteur série pour l'ESP8266
  loraSerial.begin(9600);       // Port série pour le module LoRa
  dht.begin();                  // Initialisation du capteur DHT22

  delay(1000);                  // Attendre un instant pour s'assurer que la communication est prête

  // Initialisation du module LoRa pour TTN
  sendATCommand("AT");                  // Vérifier la connexion
  sendATCommand("AT+MODE=LWOTAA");      // Mode OTAA
  sendATCommand("AT+ID=DevEUI," + deveui);
  sendATCommand("AT+ID=AppEUI," + appeui);
  sendATCommand("AT+KEY=APPKEY," + appkey);
  sendATCommand("AT+ID");
  sendATCommand("AT+JOIN");             // Joindre le réseau
}

void loop() {
  float humidity = dht.readHumidity();        // Lire l'humidité
  float temperature = dht.readTemperature();  // Lire la température en °C
  
  // Vérifier si la lecture a réussi
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Échec de lecture du capteur DHT!");
    return;
  }

  // Affichage des valeurs sur le moniteur série
  Serial.print("Température : ");
  Serial.print(temperature);
  Serial.print(" °C, Humidité : ");
  Serial.print(humidity);
  Serial.println(" %");

  // Convertir les valeurs en hexadécimal pour TTN
  String tempHex = String((int)(temperature * 100), HEX);  // Température en centièmes, convertie en hexadécimal
  String humHex = String((int)(humidity * 100), HEX);      // Humidité en centièmes, convertie en hexadécimal
  String message = tempHex + humHex;                       // Concaténer les valeurs

  // Envoi des données à TTN via LoRa
  sendATCommand("AT+MSGHEX=" + message);

  delay(60000);  // Attendre 1 minute avant de relire les données
}

// Fonction pour envoyer une commande AT et afficher la réponse
void sendATCommand(String command) {
  Serial.print("Envoi de la commande : "); 
  Serial.println(command);
  loraSerial.println(command);  // Envoi de la commande au module LoRa avec saut de ligne
  delay(1000);                  // Attendre la réponse

  // Lecture de la réponse du module LoRa
  while (loraSerial.available()) {
    String response = loraSerial.readStringUntil('\n');
    Serial.print("Réponse du module : ");
    Serial.println(response);
  }
  Serial.println("Fin de la commande");
}