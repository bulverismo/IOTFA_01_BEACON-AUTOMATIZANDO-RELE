//IOTFA
#include "SoftwareSerial.h"

SoftwareSerial bluetooth(2, 3); //TX, RX (Bluetooth)

String retornadoTotal = "";
String teste = "nul";
String comandoAt = "AT+DISI?";
int contador = 0;
String meuBeacon = "6F538F759708";
int naoEncontrou = 0;

void testaFimRetorno(char letra);
String comando(String comandoAt);
int encontrou(String retornoTotal);
void acendeLuz();
void apagaLuz();

void setup() {

  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(4, OUTPUT);

}

void loop() {

  retornadoTotal = comando(comandoAt);
  //Serial.println("saiu legal\n");
  //Serial.print("retonoTotal == ");
  //Serial.println(retornadoTotal);

  //Serial.println(encontrou(retornadoTotal));
  if (encontrou(retornadoTotal)) {
    Serial.println("Encontrou");
    naoEncontrou=0;
    acendeLuz();
    // afazer
  } else {
    Serial.println("Não encontrou");
    if (naoEncontrou==12){
      apagaLuz();
    }else{
      naoEncontrou++;
    }

  }
  delay(1);
}
void acendeLuz(){
  digitalWrite(4, HIGH);
}
void apagaLuz(){
  digitalWrite(4, LOW);
}
int encontrou(String retornoTotal) {
  int qtdIguais = 0;
  int l = 1;
  //Serial.print("retornoTotal.length = ");
  //Serial.println(retornoTotal.length());
  for (int i = 0; i < retornoTotal.length(); i++) {
    //Serial.print("primeiro for = ");
    //Serial.println(i);
    if (retornoTotal[i] == meuBeacon[0]) {
      qtdIguais = 1;
      int p = i + meuBeacon.length();
      for (int h = i + 1; h < p; h++) {
        //Serial.print("segundo for = ");
        //Serial.println(h);
        if (retornoTotal[h] == meuBeacon[l]) {
          qtdIguais++;
        } else {
          i = h - 1;
          h = p;
        }
        l++;
      }
      if (qtdIguais == meuBeacon.length()) {
        return 1;
      }
      l = 1;
    }
  }
  return 0;
}
String comando(String comandoAt) {
  int chave = 1;
  String retorno = "";
  while (contador < comandoAt.length()) {
    bluetooth.print(comandoAt[contador]);
    //Serial.print(comandoAt[contador]);
    contador++;
  }
  delay(10);
  while (chave) {
    if (bluetooth.available()) {
      char r = bluetooth.read();
      //Serial.print(r);
      retorno += r;
      testaFimRetorno(r);
      delay(1);
    }
    if (teste == "DISCE") {
      //Serial.println("Chegou ao fim do retorno");
      chave = 0;
      teste = "nul";
    }
  }
  delay(10);
  contador = 0;
  return retorno;
}


void testaFimRetorno(char letra) {
  if (teste.length() < 5) {
    teste += letra;
  } else {
    int x = 0;
    while (x < 5) {
      teste[x] = teste[x + 1];
      x++;
    }
    teste[4] = letra;
  }
}


