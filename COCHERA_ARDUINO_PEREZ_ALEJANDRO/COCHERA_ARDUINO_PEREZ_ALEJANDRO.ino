#include <IRremote.h>
#include <Servo.h>

const int trigPin = 7;
const int echoPin = 6;

long duracion;
int distancia;

int receptor = 11;
int led = 5;

Servo myServo;

IRrecv irrecv(receptor);
decode_results codigo;


void setup() {

  Serial.begin(9600);
  irrecv.enableIRIn();
  
  pinMode(led, OUTPUT);

  myServo.attach(8);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {

  sensor();

  if (distancia > 2){
    if (distancia < 8){
      
      abrir_puerta();
      precaucion();
      delay(1000);
      cerrar_puerta();
      precaucion();
      
    }else{
      
      digitalWrite(led, LOW);
      
    }
  }  

  if (irrecv.decode(&codigo)){

    Serial.println(codigo.value, HEX);

    if (codigo.value == 0xFF6897){

      abrir_puerta();

    }

    if (codigo.value == 0xFFA25D){

      cerrar_puerta();

    }

    delay(500);
    irrecv.resume();
    
  }

}


void abrir_puerta(){

  precaucion();
  myServo.write(90);
  delay(500);
  myServo.write(80);
  delay(500);
  myServo.write(70);
  delay(500);
  myServo.write(60);
  delay(500);
  myServo.write(50);
  delay(500);
  myServo.write(40);
  delay(500);
  myServo.write(30);
  delay(500);
  myServo.write(20);
  delay(500);
  myServo.write(10);
  delay(500);
  myServo.write(0);
  delay(500);
}


void cerrar_puerta(){

  precaucion();  
  myServo.write(0);
  delay(500);
  myServo.write(10);
  delay(500);
  myServo.write(20);
  delay(500);
  myServo.write(30);
  delay(500);
  myServo.write(40);
  delay(500);
  myServo.write(50);
  delay(500);
  myServo.write(60);
  delay(500);
  myServo.write(70);
  delay(500);
  myServo.write(80);
  delay(500);
  myServo.write(90);
  delay(500);
}


void precaucion(){

  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);


}


void sensor(){

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracion = pulseIn(echoPin, HIGH);
  distancia = (duracion * 0.034) / 2;
  Serial.println(distancia);
  delay(500);

}