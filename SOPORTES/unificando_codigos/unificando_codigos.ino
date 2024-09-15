#define LED 5 //led regulado por el potenciometro (este led varia su intensidad segun el valor de corriente leido)
#define boton 12 // boton  para  re-iniciar el proceso 
#define DAC1 25 //led que varia su intensidad - pin similar a un pwm en arduino

int contador=0;

const int freq = 500;
const int canal_led = 0;
const int resolucion = 12; //estos tres valores se utilizan para simular la disminucion o aumento del brillo (corriente) que estara sensando el circuito
int lectura = 0;//valor de lectura del boton
int a = 0;//estado del boton(lectura a su estado anterior)
void lectura_analogica(); //llamado a funcion lectura para configurarla en el proceso de setup del micro-controlador



void setup() {
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

    if(analogRead(A0)<12)
     {
      a==0;
        
     }
      
   else
    {
      contador++;
            if(contador == 1000)
           {
           //mandar_dato
            contador=0;  
           }
            
         else
          {
            //no enviar dato
          }
    }

   delay(0.01);
   
  }
