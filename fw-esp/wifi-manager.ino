#include <FS.h>

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>        //https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <WiFiUdp.h>


#include <ArduinoJson.h>        //https://github.com/bblanchon/ArduinoJson

#define PIN_RST 0
#define INPUT_SIZE 30

/* Serial */
SoftwareSerial swSer(5, 4, false, 128);   // (RX, TX, Invert, buffersize)
char input[INPUT_SIZE + 1];
char* command;
int i = 0;

/* JSON */
char json[100];
char ID[3], temp[5], humi[5], light[5], stt1[5], stt2[5];
StaticJsonBuffer<200> jsonBuffer;
//JsonObject& payload = jsonBuffer.createObject();

boolean statusWifi = 0;
long lastMsg = 0;

/* Wifi manager*/
WiFiManager wifiManager;
char mqtt_server[40] = "m12.cloudmqtt.com";
char mqtt_port[6] = "12111";
char mqtt_topic_pub[20] = "device1";
char mqtt_topic_sub[20] = "ctrldev1";
char mqtt_user[20] = "espdev1";
char mqtt_pass[20] = "123456";
bool shouldSaveConfig = false;

void saveConfigCallback() {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}
void SetUpWifi();


/* MQTT Setting */
WiFiClient espClient;
PubSubClient client(espClient);
void MQTTconnect();
char msg[128];
char msg_r[128];
void callback(char* topic, byte* payload, unsigned int length);

void setup() {
  /// put your setup code here, to run once:
  Serial.begin(115200);
  swSer.begin(115200);
  Serial.println("start");
  
  pinMode(PIN_RST, INPUT);
  SetUpWifi();
  statusWifi = 1;

  client.setServer(mqtt_server, atoi(mqtt_port));
  client.setCallback(callback);
  MQTTconnect();
}

void loop() {
  client.loop();
  delay(10); 
  if (!client.connected())  {
    Serial.println("Disconnect...");
    MQTTconnect();
    }
  while (swSer.available()) {
    byte size = swSer.readBytes(input, INPUT_SIZE);
    // Add the final 0 to end.
    input[size] = 0;
    // Read each command pair
    command = strtok(input, ",");
    while (command != 0) {
      if (i == 0)
        strcpy(ID, command);
      else if (i == 1)
        strcpy(temp, command);
      else if (i == 2)
        strcpy(humi, command);
      else if (i == 3)
        strcpy(light, command);
      else if (i == 4)
        strcpy(stt1,command);
      else if (i == 5)
        strcpy(stt2,command);
      i++;
      command = strtok(0, ",");
    }
    i = 0;
    sprintf(msg, "ID: %d, temp: %d oC, Humi: %d %RH, Light: %d LUX, TB1: %s, TB2: %s", atoi(ID), atoi(temp), atoi(humi), atoi(light), stt1,stt2);
    Serial.println(msg);
    client.publish(mqtt_topic_pub, msg);
  }
  if (WiFi.status() != WL_CONNECTED)  {
    statusWifi = 0;
    delay(500);
  }
  else
    statusWifi = 1;

  if ( digitalRead(PIN_RST) == LOW)
  {
    Serial.println("Reset settings wifi configs");
    wifiManager.resetSettings();
    delay(1000);
    ESP.reset();
    
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    swSer.print((char)payload[i]);
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/* Connect to broker MQTT */
void MQTTconnect()  {
  Serial.print("\nConnecting..");
  while (!client.connected())  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_pass)) {
      Serial.println("Connected");
      client.publish(mqtt_topic_pub, "ESP_connected");
      client.subscribe(mqtt_topic_sub);
    }
    else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 5 seconds");
    delay(5000);
    }
  Serial.println("\nConected MQTT Server!");

  // client.subscribe("/example");
  // client.unsubscribe("/example");
  }
}



void SetUpWifi()  {
  //clean FS, for testing
  //SPIFFS.format();

  //read configuration from FS json
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");

          strcpy(mqtt_server, json["mqtt_server"]);
          strcpy(mqtt_port, json["mqtt_port"]);
          strcpy(mqtt_topic_pub, json["mqtt_topic_pub"]);
          strcpy(mqtt_topic_sub, json["mqtt_topic_sub"]);
          strcpy(mqtt_user, json["mqtt_user"]);
          strcpy(mqtt_pass, json["mqtt_pass"]);

        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read

  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 6);
  WiFiManagerParameter custom_mqtt_topic_pub("mqtt_topic_pub", "mqtt_topic_pub", mqtt_topic_pub, 40);
  WiFiManagerParameter custom_mqtt_topic_sub("mqtt_topic_sub", "mqtt_topic_sub", mqtt_topic_sub, 40);
  WiFiManagerParameter custom_mqtt_user("user", "mqtt_user", mqtt_user, 20);
  WiFiManagerParameter custom_mqtt_pass("pass", "mqtt_pass", mqtt_pass, 20);
  

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  

  
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  //set static ip
  //wifiManager.setSTAStaticIPConfig(IPAddress(10,0,1,99), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
  
  //add all your parameters here
  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_mqtt_topic_pub);
  wifiManager.addParameter(&custom_mqtt_topic_sub);
  wifiManager.addParameter(&custom_mqtt_user);
  wifiManager.addParameter(&custom_mqtt_pass);


  //reset settings - for testing
  //wifiManager.resetSettings();

  //defaults to 8%
  wifiManager.setMinimumSignalQuality(30);
  
  wifiManager.setTimeout(180);

  if (!wifiManager.autoConnect("nhantt","password")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("Connected!");
  swSer.print("Connected\n");

  //read updated parameters
  strcpy(mqtt_server, custom_mqtt_server.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());
  strcpy(mqtt_topic_pub, custom_mqtt_topic_pub.getValue());
  strcpy(mqtt_topic_sub, custom_mqtt_topic_sub.getValue());
  strcpy(mqtt_user, custom_mqtt_user.getValue());
  strcpy(mqtt_pass, custom_mqtt_pass.getValue());

  //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["mqtt_server"] = mqtt_server;
    json["mqtt_port"] = mqtt_port;
    json["mqtt_topic_pub"] = mqtt_topic_pub;
    json["mqtt_topic_sub"] = mqtt_topic_sub;
    json["mqtt_user"] = mqtt_user;
    json["mqtt_pass"] = mqtt_pass;
    

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  }

  Serial.println("\nLocal ip");
  Serial.println(WiFi.localIP());
  
}

