
//CONTADOR DE PULSOS DE UN VNTILADOR DE COMPUTADORA SIN ESCOBILLAS

const int hardwareCounterPin = 5;   // Entrada del pin para el Timer(Contador)
int P_entrada = 8;     //Pines utilzados para mostrar la lectura y  
int P_salida = 9;      //escritura del arduino en cuanto a la señal
int Valor = 0;         
int pin_c = 12;        //Pin utilizado para saber si el contador funciona bien
int RPM =0;            //Variable para almacenar el valor de las RPM

const int samplePeriod = 1000;   // muestra de tiempo (1s)
unsigned int count;              //Variable del contador


void setup()
{
  Serial.begin(9600);
  pinMode(P_entrada, INPUT);
  pinMode(P_salida, OUTPUT);
  pinMode(pin_c, OUTPUT);
  
  TCCR1A=0;        // reset timer/counter control register A
}  

void loop()
{
  Valor = digitalRead(P_entrada);   //Se lee la entrada y se asigna a Valor
  digitalWrite(P_salida,Valor);     //Se desplega en una salida
  digitalWrite(pin_c,HIGH);         //Se pone en alto para conocer cuando comienza a contar 
  // Comienza el conteo
  bitSet(TCCR1B ,CS12);  // Counter Clock source is external pin
  bitSet(TCCR1B ,CS11);  // Clock on rising edge  
  delay(samplePeriod);   //Tiempo que cuenta
  // Para de contar 
  digitalWrite(pin_c,LOW);         //Se pone en bajo para fijar el periodo para comparar el conteo
  //delay(samplePeriod);   //Este retardo es para notar el cambio
  TCCR1B = 0;           
  count = TCNT1;
  TCNT1 = 0;  // reset the hardware counter

  RPS = count / 12;     // Se calculan las RPS--Revoluciones por segundo
  
  //Nota... el valor "12" puede cambiar depende del numero de dientes que tenga
  //el encoder
  
     Serial.println(count);
     Serial.println(RPS);    //Se despliega el valor obtenido
}
