#include <TimerOne.h>

#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

const int led = 2; //Verde carro
const int led2 = 3;//Amarelo carro
const int led3 = 4;//Vermelho carro
const int led1pedestre = 5; //Verde Pedestre
const int led2pedestre = 6; //Vermelho Pedestre
const int ldr = 0; // sensor de luminosidade 
const int buzzer = 10; // buzzer
const int solicitado = 7; // luz de solicitação pedestre 
const int avisocarro = 8; // luz de solicitação do carro
int bloqueio;
int aberto = 0;
int valor = 0; 
void setup(){
  irrecv.enableIRIn();
  Timer1.initialize(200000);
  Timer1.attachInterrupt(callback); 
  pinMode(led,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(solicitado,OUTPUT);
  pinMode(avisocarro,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led1pedestre,OUTPUT);
  pinMode(led2pedestre,OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);  
}
void loop(){
  valor = analogRead(ldr); 
 
    digitalWrite(led2,LOW);
    digitalWrite(led,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led1pedestre,LOW);
    digitalWrite(led2pedestre,LOW);
    
   
  if(valor > 150){
    if(aberto == 1){
    vermelhoDia();
    aberto = 0;
    }
    else{
  semaforo(led,led2,led3);
  }
  }
  
 if(valor < 151){
   digitalWrite(avisocarro,LOW); 
   if(aberto == 1){
     if(bloqueio != 1){
      digitalWrite(led2,HIGH);
      digitalWrite(led2pedestre,HIGH);
      delay(2000);
      digitalWrite(solicitado,LOW);
     vermelhoNoite();
     delay(1000);
      digitalWrite(buzzer,HIGH);
      delay(1000);
      digitalWrite(buzzer,LOW);
      delay(3000);
  alertatotal();
    aberto = 0;
     }
     else{
     digitalWrite(solicitado,LOW);
     vermelhoNoite();
     delay(3000);
     alertatotal();
     aberto = 0;
     }
    }
    else{
  pisca(led2,led2pedestre);
  }
 }
    }
  

void pisca(int ledin,int ledin2){
bloqueio = 0;
digitalWrite(ledin,HIGH);
digitalWrite(ledin2,HIGH);
delay(200);
digitalWrite(ledin,LOW);
digitalWrite(ledin2,LOW);
delay(200);
}
void semaforo(int ledin1,int ledin2,int ledin3){
bloqueio = 0;
digitalWrite(avisocarro,LOW);
digitalWrite(ledin1,HIGH);
digitalWrite(ledin2,LOW);
digitalWrite(ledin3,LOW);
digitalWrite(led1pedestre,LOW);
digitalWrite(led2pedestre,HIGH);
delay(4000);
digitalWrite(ledin2,HIGH);
digitalWrite(ledin3,LOW);
digitalWrite(ledin1,LOW);
digitalWrite(led1pedestre,LOW);
digitalWrite(led2pedestre,HIGH);
delay(3000);
if(aberto!=1){
digitalWrite(ledin3,HIGH);
bloqueio = 1;
digitalWrite(ledin2,LOW);
digitalWrite(ledin1,LOW);
digitalWrite(led1pedestre,HIGH);
digitalWrite(led2pedestre,LOW);
delay(3000);
digitalWrite(led1pedestre,LOW);
piscaalerta();
}
else{
  bloqueio = 1;
  digitalWrite(avisocarro,HIGH);
  digitalWrite(ledin3,HIGH);
digitalWrite(ledin2,LOW);
digitalWrite(ledin1,LOW);
digitalWrite(led1pedestre,HIGH);
digitalWrite(led2pedestre,LOW);
digitalWrite(buzzer,HIGH);
 digitalWrite(solicitado,LOW);
  delay(500);
  digitalWrite(buzzer,LOW);
delay(1500);
}
digitalWrite(ledin3,HIGH);
digitalWrite(ledin2,LOW);
digitalWrite(ledin1,LOW);

}

void vermelhoDia(){
digitalWrite(led3,HIGH);
digitalWrite(led2,LOW);
digitalWrite(led,LOW);
digitalWrite(led1pedestre,HIGH);
digitalWrite(led2pedestre,LOW);
apitoAtravessando();
  alertatotal();  
}

void vermelhoNoite(){
digitalWrite(avisocarro,HIGH);
digitalWrite(led3,HIGH);
bloqueio = 1;
digitalWrite(avisocarro,HIGH);
digitalWrite(led2,LOW);
digitalWrite(led,LOW);
digitalWrite(led1pedestre,HIGH);
digitalWrite(led2pedestre,LOW);  
}

void apitaalerta(){
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  delay(500);
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  delay(500); 
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  delay(500); 
}

void piscaalerta(){
  bloqueio = 1;
digitalWrite(led2pedestre,HIGH);
  delay(500);
  digitalWrite(led2pedestre,LOW);
  delay(500);
  digitalWrite(led2pedestre,HIGH);
  delay(500);
  digitalWrite(led2pedestre,LOW);
  delay(500);

}

void alertatotal(){
  digitalWrite(led1pedestre,LOW);
  digitalWrite(led2pedestre,HIGH);
   for(int i=0;i<16;i++){
   digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
  delay(50); 
  }
}
void apitoAtravessando(){
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  delay(500);
  for(int i=0;i<6;i++){
   digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  delay(200); 
  }
  
}

void callback(){
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
     irrecv.resume();
  if ((results.value == 0xD7E84B1B)  and (bloqueio == 0))  {  
   
     aberto = 1; 
    digitalWrite(solicitado,HIGH);
  } 
    
}
}
