//https://www.youtube.com/watch?v=qK2e3KzXCH0


#define boton 12
int lectura = 0;
int a = 0;

void setup() {
  pinMode(boton,INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  lectura=digitalRead(boton);
  if(lectura==LOW){
      a=!a;
      delay(300);}
   
   if(a==1){
        digitalWrite(LED_BUILTIN, HIGH);
        }
    
  else{
    digitalWrite(LED_BUILTIN, LOW);
    }
}
