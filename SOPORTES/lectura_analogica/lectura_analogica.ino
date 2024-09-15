const int LED =3;  // indicando que el led se encuentra en el pin3
const int potenciometro =0; // el potenciometro esta conectado al pin A0
int intensidad;  //variable para la intensidad de brillo

void setup() {

// put your setup code here, to run once:
// No se necesitan declaran los pines analogicos
//ya que se realiza automáticamente
pinMode (LED, OUTPUT);  // declaramos el led como salida

}

void loop() {

// put your main code here, to run repeatedly:
//los valores analogicos se usan entre 0 y 255
//asi que el valor del potenciometro lo dividos en 4
intensidad = analogRead (potenciometro) / 4;
//analogWrite recibe los valores analogicos del pin
analogWrite(LED, intensidad);

}
