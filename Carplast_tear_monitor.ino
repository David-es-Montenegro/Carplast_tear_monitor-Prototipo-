const int pinos[]{ 16, 5, 4, 2, 14, 12, 13 };  //D0 D1 D2 D4 D5 D6 D7

const String paradas[6] = { "1100000", "1110000", "1000001", "1100001", "1010001", "1000100" };
unsigned int qntParadas[6];
float tempoParadas[6], eficienciaTotal = 0, perdasEficienciaParadas[6], tempoMedio[6];
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

  comparador();





  delay(10);
  yield();
}

String leitura() {
  String sequencia = "1";

  sequencia = sequencia + digitalRead(pinos[0]);
  sequencia = sequencia + digitalRead(pinos[1]);
  sequencia = sequencia + digitalRead(pinos[2]);
  sequencia = sequencia + digitalRead(pinos[3]);
  sequencia = sequencia + digitalRead(pinos[4]);
  sequencia = sequencia + digitalRead(pinos[5]);

  return sequencia;
}

void mostrador() {
  calculador();
  Serial.println(eficienciaTotal);
  Serial.println(tempoLigado);
  Serial.println(tempoParado);

  for (int i = 0; i <= 5; i++) {
    String codParada = paradas[i];
    codParada.remove(0,1);
    Serial.println("parada" + String((i + 1)) + ": " + codParada + " paradas: " + String(qntParadas[i]) + " tempo total: " + String(tempoParadas[i]) + " tempo medio: " + String(tempoMedio[i]));
  }
}

void calculador() {
  tempoLigado = ((millis() / 1000) - (horaDeLigacao / 1000));

  for (int i = 0; i < 6; i++) {
    tempoParado = tempoParado + tempoParadas[i];
  }

  eficienciaTotal = ((tempoParado * 100) / tempoLigado);
}

void comparador() {
  if (leitura() != "000000") {
    delay(100);
    if (leitura() == paradas[0]) {
      tempoInicial = millis();
      qntParadas[0] = qntParadas[0] + 1;

      while (leitura() == paradas[0]) {
        delay(10);
        tempoFinal = millis();
      }

      decorrido = decorrido + ((tempoFinal / 1000) - (tempoInicial / 1000));
      tempoParadas[0] = tempoParadas[0] + decorrido;
      decorrido = 0;
    }
    if (leitura() == paradas[1]) {
      tempoInicial = millis();
      qntParadas[1] = qntParadas[1] + 1;

      while (leitura() == paradas[1]) {
        delay(10);
        tempoFinal = millis();
      }

      decorrido = decorrido + ((tempoFinal / 1000) - (tempoInicial / 1000));
      tempoParadas[1] = tempoParadas[1] + decorrido;
      decorrido = 0;
    }
    if (leitura() == paradas[2]) {
      tempoInicial = millis();
      qntParadas[2] = qntParadas[2] + 1;

      while (leitura() == paradas[2]) {
        delay(10);
        tempoFinal = millis();
      }

      decorrido = decorrido + ((tempoFinal / 1000) - (tempoInicial / 1000));
      tempoParadas[2] = tempoParadas[2] + decorrido;
      decorrido = 0;
    }
    if (leitura() == paradas[3]) {
      tempoInicial = millis();
      qntParadas[3] = qntParadas[3] + 1;

      while (leitura() == paradas[3]) {
        delay(10);
        tempoFinal = millis();
      }

      decorrido = decorrido + ((tempoFinal / 1000) - (tempoInicial / 1000));
      tempoParadas[3] = tempoParadas[3] + decorrido;
      decorrido = 0;
    }
    if (leitura() == paradas[4]) {
      tempoInicial = millis();
      qntParadas[4] = qntParadas[4] + 1;

      while (leitura() == paradas[4]) {
        delay(10);
        tempoFinal = millis();
      }

      decorrido = decorrido + ((tempoFinal / 1000) - (tempoInicial / 1000));
      tempoParadas[4] = tempoParadas[4] + decorrido;
      decorrido = 0;
    }
    if (leitura() == paradas[5]) {
      tempoInicial = millis();
      qntParadas[5] = qntParadas[5] + 1;

      while (leitura() == paradas[5]) {
        delay(10);
        tempoFinal = millis();
      }

      decorrido = decorrido + ((tempoFinal / 1000) - (tempoInicial / 1000));
      tempoParadas[5] = tempoParadas[5] + decorrido;
      decorrido = 0;
    }
  }
}