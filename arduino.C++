#include <dht.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//potenciometro 
int pot = A3;
int valorPot = 0;
int potenValor = 0;



//botão iniciar
int btIniciar = 13;
int contBtIniciar = 0;
int valorBtIniciar = 0;


//botão cancelar
int btCancelar = 8;
int valorBtCancelar = 0;


//Sensor
const int pinoDHT11 = A2;
dht DHT;

//Relé-Peltier
int peltierEsf = 10;

int peltierEsq = 11;


//FUNÇÕES
  void Inicio(){
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("PRESSIONE");
  lcd.setCursor(2, 1);
  lcd.print("BOTAO BRANCO");
  //fazer função iniciar pelo valor 0 e passar parametros de entrada
}




  void MdEsq( int potQ){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEMP:  TR    AJT");
    lcd.setCursor(0,1);
    lcd.print("ESQ");
    lcd.setCursor(13,1);
    lcd.print(potQ);
    lcd.setCursor(7,1);
    lcd.print(DHT.temperature, 0);
    lcd.setCursor(9, 1);
    lcd.print("C");
    lcd.setCursor(15, 1);
    lcd.print("C");
    delay(500);
    lcd.clear();

    digitalWrite(peltierEsq, 1);
    digitalWrite(peltierEsf, 0);
}

void MdEsf(int potF){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEMP:  TR    AJT");
    lcd.setCursor(0,1);
    lcd.print("ESF");
    lcd.setCursor(12,1);
    lcd.print(potF);
    lcd.setCursor(7,1);
    lcd.print(DHT.temperature, 0);
    lcd.setCursor(9, 1);
    lcd.print("C");
    lcd.setCursor(15, 1);
    lcd.print("C");
    delay(500);
    lcd.clear();

    digitalWrite(peltierEsf, 1);
    digitalWrite(peltierEsq, 0);
}

void neutro(int potN){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEMP:  TR    AJT");
    lcd.setCursor(0,1);
    lcd.print("NEU");
    lcd.setCursor(13,1);
    lcd.print(potN);
    lcd.setCursor(7,1);
    lcd.print(DHT.temperature, 0);
    lcd.setCursor(9, 1);
    lcd.print("C");
    lcd.setCursor(15, 1);
    lcd.print("C");
    delay(500);
    lcd.clear();

    digitalWrite(peltierEsf, 0);
    digitalWrite(peltierEsq, 0);
  }
  
  
void setup()
{
  //Relé
  pinMode(9, OUTPUT);


  //botões
  pinMode(btIniciar, INPUT_PULLUP);
  pinMode(btCancelar, INPUT_PULLUP);

  //ponte-H
  pinMode(peltierEsf, OUTPUT);
  pinMode(peltierEsq, OUTPUT);
  
  

  
  //declação do lcd
  lcd.begin(A5, A4);
  lcd.setBacklight(1);
  
  Serial.begin(9600);

}

void loop()
{

  int conta = valorPot - DHT.temperature;
  
  
  //declaração dos botões
  valorBtIniciar = !digitalRead(btIniciar);
  valorBtCancelar = !digitalRead(btCancelar);
  
  //Mapeamento do potenciometro esquentar
  valorPot = analogRead(pot);
  
  //Mapeamento do potenciomentro esfriar
  valorPot = analogRead(pot);
  
  //declaração DHT
  DHT.read11(pinoDHT11);

  //mapeamento do potenciometro
  potenValor = analogRead(pot);
  valorPot = map(potenValor, 0, 1023, -41, 71);
    
    
Serial.print(contBtIniciar); //Ver a contagem

  if(valorBtIniciar == 1){
    contBtIniciar++;
    delay(1000);
    }
  
  if(contBtIniciar >= 2){
    contBtIniciar = 1;
  }
  
 
  
  if (contBtIniciar < 0){
    contBtIniciar = 0;
  }
  
  if(contBtIniciar == 0){
  Inicio();
  }
  
  if(valorBtCancelar == 1){
    contBtIniciar--;
    delay(1000);
    }
  
  if(contBtIniciar == 1){
    if(conta > 1){
  MdEsq(valorPot);
    }else if(conta < -1){
  MdEsf(valorPot);
    }else{
  neutro(valorPot);
      }
    }
   }