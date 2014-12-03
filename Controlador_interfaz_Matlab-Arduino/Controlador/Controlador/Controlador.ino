//CONTADOR DE PULSOS DE UN VNTILADOR DE COMPUTADORA SIN ESCOBILLAS

const int hardwareCounterPin = 5;   // Entrada del pin para el Timer(Contador)
int Valor = 0;         
int RPS =0;            //Variable para almacenar el valor de las RPM
const int samplePeriod = 1000;   // muestra de tiempo (1s)
unsigned int count;              //Variable del contador
int PW_MA = 6;
int Duty=0;
int Dato=0;
int v_inicio = 150;
int error = 0;
int incremento = 0;
int n=0;

void setup()
{
  Serial.begin(9600);
  pinMode(PW_MA, OUTPUT); 
  TCCR1A=0;        // reset timer/counter control register A
}  

void loop()
{
    n=1;
    incremento=16;
    analogWrite(PW_MA,v_inicio);

    Dato = Serial.parseInt();
    delay(1000);
    contador();
    Serial.println(RPS);
    
    if(Dato==0)
      {
        error=0;
      }
    else
      {    
        error = RPS - Dato;
      }
      //  Duty = map(Dato,0,34,0,255);
      //  analogWrite(PW_MA,Duty);
  
     if (error < 0)
       {
         v_inicio=Aumenta_PWM(v_inicio);
       } 
     if (error > 0)
       {
         v_inicio=Disminuye_PWM(v_inicio);
       }
        // Serial.println(count);
        // Serial.println(RPS);    //Se despliega el valor obtenido
}

void contador(void)
{
  for (int i=0; i <= 1; i++)
    {
      //  TCNT1 = 0;
      // Comienza el conteo
      bitSet(TCCR1B ,CS12);  // Counter Clock source is external pin
      bitSet(TCCR1B ,CS11);  // Clock on rising edge  
      delay(samplePeriod);   //Tiempo que cuenta
      // Para de contar 
       //delay(samplePeriod);   //Este retardo es para notar el cambio
      TCCR1B = 0;           
      count = TCNT1;
      TCNT1 = 0;  // reset the hardware counter
    }
  
    RPS = count / 12;     // Se calculan las RPS--Revoluciones por segundo
  
}

int Aumenta_PWM(int)
{
  do
    {
     if (abs(error)==1 && n < 3)
       {
         incremento=incremento/2;
         n=n+1;
       }
     
     v_inicio = v_inicio + incremento;
     analogWrite(PW_MA,v_inicio);
     delay(1000);
 
     contador();
     Dato = Serial.parseInt();
     error = RPS - Dato;
     Serial.println(RPS);
  }while(error < 0);
  
      return v_inicio;
}

int Disminuye_PWM(int)
{
  do
    {
     if (abs(error)==1 && n < 3)
     {
         incremento=incremento/2;
         n=n+1;
      } 
  
     v_inicio = v_inicio - incremento;
     analogWrite(PW_MA,v_inicio);
     delay(1000);
 
     contador();
     Dato = Serial.parseInt();
     error = RPS - Dato; 
     Serial.println(RPS);
   }while(error > 0);

      return v_inicio;
}

