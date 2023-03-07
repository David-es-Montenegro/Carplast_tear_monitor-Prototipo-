#define pino1 16 //D0
#define pino2 5  //D1

const unsigned int paradas[6] = {100000, 110000, 000001, 100001,010001, 000100};
unsigned int qntParadas[6];
float tempoParadas[6], eficienciaTotal = 0; perdasEficienciaParadas[6];
unsigned long tempoInicial, tempoFinal, decorrido = 0, horaDeLigacao = 0, tempoParado = 0, tempoLigado = 0;



void setup() {
  Serial.begin(115200);
  pinMode(16, INPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
  pinMode(0, INPUT);
  pinMode(2, INPUT);
  pinMode(14, INPUT);
  horaDeLigacao = (millis() / 1000);
}

void loop() {

  

  if (analogRead(13) != 0) {
    mostrador();
  }

  if (leitura() != "000000") {
    delay(100);
    if (leitura() == parada1) {
      tempoInicial = millis();
      countParada1 = countParada1 + 1;

      while (leitura() == parada1) {
        delay(10);
        tempoFinal = millis();
      }

      decorrido = decorrido + ((tempoFinal / 1000) - (tempoInicial / 1000));
      tempoParada1 = tempoParada1 + decorrido;
      decorrido = 0;
    }
    if (leitura() == parada2) {
      tempoInicial = millis();
      countParada2 = countParada2 + 1;

      while (leitura() == parada2) {
        delay(10);
        tempoFinal = millis();
      }

      decorrido = decorrido + ((tempoFinal / 1000) - (tempoInicial / 1000));
      tempoParada2 = tempoParada2 + decorrido;
      decorrido = 0;
    }
    if (leitura() == parada3) {
      tempoInicial = millis();
      countParada3 = countParada3 + 1;

      while (leitura() == parada3) {
        delay(10);
        tempoFinal = millis();
      }

      decorrido = decorrido + ((tempoFinal / 1000) - (tempoInicial / 1000));
      tempoParada3 = tempoParada3 + decorrido;
      decorrido = 0;
    }
    if (leitura() == parada4) {
      tempoInicial = millis();
      countParada4 = countParada4 + 1;

      while (leitura() == parada4) {
        delay(10);
        tempoFinal = millis();
      }

      decorrido = decorrido + ((tempoFinal / 1000) - (tempoInicial / 1000));
      tempoParada4 = tempoParada4 + decorrido;
      decorrido = 0;
    }
    if (leitura() == parada5) {
      tempoInicial = millis();
      countParada5 = countParada5 + 1;

      while (leitura() == parada5) {
        delay(10);
        tempoFinal = millis();
      }

      decorrido = decorrido + ((tempoFinal / 1000) - (tempoInicial / 1000));
      tempoParada5 = tempoParada5 + decorrido;
      decorrido = 0;
    }
    if (leitura() == parada6) {
      tempoInicial = millis();
      countParada6 = countParada6 + 1;

      while (leitura() == parada6) {
        delay(10);
        tempoFinal = millis();
      }

      decorrido = decorrido + ((tempoFinal / 1000) - (tempoInicial / 1000));
      tempoParada6 = tempoParada6 + decorrido;
      decorrido = 0;
    }
  }


  delay(10);
  yield();
}

String leitura() {
  String sequencia;

  sequencia = sequencia + digitalRead(16);
  sequencia = sequencia + digitalRead(5);
  sequencia = sequencia + digitalRead(4);
  sequencia = sequencia + digitalRead(12);
  sequencia = sequencia + digitalRead(2);
  sequencia = sequencia + digitalRead(14);


  return sequencia;
}

String armazenador() {
  String parada;
  parada = leitura();
  return parada;
}

void mostrador() {
  calculadora();
  Serial.println(eficienciaTotal);
  Serial.println(tempoLigado);
  Serial.println(tempoParado);
  Serial.println("parada1: " + parada1 + " paradas: " + String(countParada1) + " tempo total: " + String(tempoParada1) + " tempo medio: " + String((tempoParada1 / countParada1)));
  Serial.println("parada2: " + parada2 + " paradas: " + String(countParada2) + " tempo total: " + String(tempoParada2) + " tempo medio: " + String((tempoParada2 / countParada2)));
  Serial.println("parada3: " + parada3 + " paradas: " + String(countParada3) + " tempo total: " + String(tempoParada3) + " tempo medio: " + String((tempoParada3 / countParada3)));
  Serial.println("parada4: " + parada4 + " paradas: " + String(countParada4) + " tempo total: " + String(tempoParada4) + " tempo medio: " + String((tempoParada4 / countParada4)));
  Serial.println("parada5: " + parada5 + " paradas: " + String(countParada5) + " tempo total: " + String(tempoParada5) + " tempo medio: " + String((tempoParada5 / countParada5)));
  Serial.println("parada6: " + parada6 + " paradas: " + String(countParada6) + " tempo total: " + String(tempoParada6) + " tempo medio: " + String((tempoParada6 / countParada6)));
}

void calculadora (){
  tempoLigado = ((millis() / 1000) - (horaDeLigacao / 1000));
  tempoParado = (tempoParada1 + tempoParada2 + tempoParada3 + tempoParada4 + tempoParada5 + tempoParada6);
  eficienciaTotal = ((tempoParado * 100) / tempoLigado);
}
