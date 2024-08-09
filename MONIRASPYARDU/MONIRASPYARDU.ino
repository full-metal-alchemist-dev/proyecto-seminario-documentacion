#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#define LED 5 //led regulado por el potenciometro (este led varia su intensidad segun el valor de corriente leido)
#define boton 12 // boton  para  re-iniciar el proceso 
#define DAC1 25 //led que varia su intensidad - pin similar a un pwm en arduino

int contador=0;

const int freq = 500;
const int canal_led = 0;
const int resolucion = 12; //estos tres valores se utilizan para simular la disminucion o aumento del brillo (corriente) que estara sensando el circuito
int lectura = 1;//valor de lectura del boton
int a = 0;//estado del boton(lectura a su estado anterior)
void lectura_analogica(); //llamado a funcion lectura para configurarla en el proceso de setup del micro-controlador
void enviar_recibir(int valorv); //llamado a funcion lectura para configurarla en el proceso de setup del micro-controlador

//URL PARA NUESTRO IDE
//https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
//MODELO ESP32 30 PINES
//ESP32 GPIOs 30

const char* ssid = "CLARO_6d475a";    // NOMBRE DE TU RED WIFI
const char* password = "519b0515Dd";  // WIFI 

//Your Domain name with URL path or IP address with path
String serverName = "https://moniraspyardu.000webhostapp.com/app/productos/04agregar.php";
const char* serverName2 = "http://moniraspyardu.000webhostapp.com/app/productos/02datav2.php?id=140&tabla=producto";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

String sensorReadings;
String sensorReadingsArr[3];



void setup() {

  Serial.begin(115200); // TENER EN CUENTA ESTE VALOR PARA ABRIR EL MONITOR SERIE DEL IDE DE ARDUINO PARA VER LAS RESPUESTAS POR CONSOLA.

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP()); 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  
  
  pinMode(LED,OUTPUT);//configurando el pin conectado al led indicador (intensidad) como salida
  pinMode(boton,INPUT_PULLUP);//configurando el pin vinculado al boton como punto de entrada  
  pinMode(LED_BUILTIN, OUTPUT);// led que indica si el sistema esta bloqueado y amerita reseto manual
  ledcSetup(canal_led, freq, resolucion);//configurando el valor que se enviara a la salidad(intensidad)
  ledcAttachPin(LED, canal_led);//seteando la salida en el pin (intensidad, corriente , brillo)
}

void loop() {
  lectura=digitalRead(boton);
    if(lectura==LOW)
      {
        a=!a;
        delay(300);
      }
   
   if(a==1)
     {
        digitalWrite(LED_BUILTIN, HIGH);
        lectura_analogica();
     }
      
   else
    {
       digitalWrite(LED_BUILTIN, LOW);
    }

    
}


void lectura_analogica(){
           
ledcWrite(canal_led, analogRead(A0));

//-----------------------------------------------
//probar si esto es un fadin y sino es necesario
//  int x = 1;
//  for (int i = 0; i > -1; i = i + x) {
//    dacWrite(DAC1, i);
//    if (i == 254) {
//      x = -1;  
//    }
//    delay(0.01);
//  }
  //probar si esto es un fadin y sino es necesario
  //----------------------------------------------
  
  Serial.print("Digital in: ");
  Serial.print(digitalRead(boton));
  Serial.print(" Analog in: ");
  Serial.print(analogRead(A0));
  Serial.print(" PWM out: ");
  Serial.println(analogRead(A0));

    if(analogRead(A0)<120)
     {
      a==0;
        digitalWrite(LED_BUILTIN, LOW);
     }
      
   else
    {
      contador++;
            if(contador == 2000)
           {
           enviar_recibir(analogRead(A0));
            contador=0;  
           }
            
         else
          {
            //no enviar dato
          }
    }

   delay(0.01);
   
  }



  void enviar_recibir(int valorv) {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      
      HTTPClient http;
      String serverPath = serverName + "?add=0&tabla=producto&descripcion=pruebadesdeurl&costo1="+valorv+"&costo2="+valorv+"";      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);


      sensorReadings = httpGETRequest(serverName2);
      Serial.println(sensorReadings);
      JSONVar myObject = JSON.parse(sensorReadings);

      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }

      Serial.print("JSON object = ");
      Serial.println(myObject);

      // myObject.keys() can be used to get an array of all the keys in the object
      JSONVar keys = myObject.keys();
    
      for (int i = 0; i < keys.length(); i++) {
        JSONVar value = myObject[keys[i]];
        Serial.print(keys[i]);
        Serial.print(" = ");
        Serial.println(value);
        sensorReadingsArr[i] = value;
      
    }

 Serial.print("1 = ");
      Serial.println(sensorReadingsArr[0]);
      Serial.print("2 = ");
      Serial.println(sensorReadingsArr[1]);
      Serial.print("3 = ");
      Serial.println(sensorReadingsArr[2]);

        
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  
}



String httpGETRequest(const char* serverName2) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName2);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
  }
