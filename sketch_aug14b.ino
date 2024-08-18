//Projeto Agrobot.

//Inclui as bibliotecas.
#include <Ultrasonic.h>
#include <Servo.h>

//Declara as portas dos pinos trig e echo.
#define pin_trig 13
#define pin_echo 12

//Declara o objeto do sensor Ultrasonico.
Ultrasonic Sensor_Utrasonico(pin_trig, pin_echo);

//Declara os 3 objetos de Servo motor.
Servo Servo_Sensor;
Servo Servo_Armazenamento;
Servo Servo_Graos;

//Declara as portas da ponte H.
#define IN1 10
#define IN2 9
#define IN3 6
#define IN4 5

//Define o pino da bomba de água.
#define pin_bomba_de_agua 7

//Declaração das variaveis globais para os servos motores.
int posicao_Sensor = 90;
int posicao_Armazenamento = 0;
int posicao_Graos = 0;

//Declara a variável distancia e a variável potencia.
int distancia;
int potencia = 200;

//Só é repetido uma vez.
void setup() {
  //Coloca os servos para funcionarem.
  Servo_Sensor.attach(1);
  Servo_Armazenamento.attach(2);
  Servo_Graos.attach(3);

  //define o pino 0 como saída de energia.
  pinMode(pin_bomba_de_agua, OUTPUT);
}

//É repetido infinitas vezes.
void loop() {
  //Atribui valor a variável distancia como o valor da leitura do objeto Sensor_Ultrasonic.
  distancia = Sensor_Utrasonico.read();

  //Declara a posição inicial dos servos.
  Servo_Sensor.write(posicao_Sensor);
  Servo_Armazenamento.write(posicao_Armazenamento);
  Servo_Graos.write(posicao_Graos);

  if (distancia > 40) {
    Movimento_Frente(potencia / 5);
    delay(250);
  } else {
    verificacao_do_sensor();
  }
}

//Movimenta o robô para a frente.
void Movimento_Frente(int velocidade) {
  //Movimenta o robô para a frente.
  digitalWrite(IN1, velocidade);
  digitalWrite(IN2, 0);

  digitalWrite(IN3, velocidade);
  digitalWrite(IN4, 0);
  delay(1000);
  //Para o movimento para frente do robô.
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  //Libera a semente.
  Servo_Graos.write(90);
  Servo_Armazenamento.write(90);
  delay(250);
  Servo_Graos.write(posicao_Graos);
  Servo_Armazenamento.write(posicao_Armazenamento);
  //Liga a bomba de água.
  digitalWrite(pin_bomba_de_agua, HIGH);
  delay(1000);
  digitalWrite(pin_bomba_de_agua, LOW);
  delay(1000);
}

//Movimenta o robô para a direita.
void Movimento_Direita(int velocidade) {
  digitalWrite(IN1, velocidade);
  digitalWrite(IN2, 0);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, velocidade);
}
//Movimenta o robô para a esquerda.
void Movimento_Esquerda(int velocidade) {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, velocidade);

  digitalWrite(IN3, velocidade);
  digitalWrite(IN4, 0);
  delay(1000);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  delay(1000);
}

//Vericação do sensor.
void verificacao_do_sensor() {
  Servo_Sensor.write(180);
  digitalWrite(pin_bomba_de_agua, LOW);
  delay(2000);
  if (distancia <= 60) {
    Movimento_Esquerda(potencia / 5);
  } else {
    Movimento_Direita(potencia / 5);
  }
}
