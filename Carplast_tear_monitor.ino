const int pinos[]{ 16, 5, 4, 2, 14, 12, 13 };  //D0 D1 D2 D4 D5 D6 D7

const String paradas[6] = { "1100000", "1110000", "1000001", "1100001", "1010001", "1000100" }; // Modelo: "1000100" cada constante deve iniciar com o digito 1, caso contrario, os caracteres antes de algum digito "1" serão descartados,
//os proximos 6 digitos significam "1" = sensor ativado, "0" sensor desativado, cada tipo de parada do tear é representado por uma sequencia de 6 sensores ativados ou desativados.

unsigned int qntParadas[6];
float tempoParadas[6], eficienciaTotal = 0, perdasEficienciaParadas[6], tempoMedio[6], tempoParado = 0, tempoLigado = 0;
unsigned long tempoInicial, tempoFinal, decorrido = 0, horaDeLigacao = 0;



void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 6; i++) {
    pinMode(pinos[i], INPUT);
  }

  horaDeLigacao = (millis() / 1000); //captura milissegundos decorridos antes do loop para calcular o tempo ligado.
}

void loop() {
  if (analogRead(13) != 0) {
    mostrador();
  }

  comparador();
  delay(10);
  yield();
}

//lê as o estado de cada sensor. (leitura = "1000000" == maquina em funcionamento pleno)
String leitura() {
  String sequencia = "1";

  for (int i = 0; i < 6; i++) {
    sequencia = sequencia + digitalRead(pinos[i]);
  }

  return sequencia;
}

//exibe via serial monitor as metricas obtidas.
void mostrador() {
  calculador();

  for (int i = 0; i < 30; i++){
    Serial.println("\n");
  }

  Serial.println("==========================================================================================================================================================================================================================");
  Serial.println("Eficiencia: " + String(eficienciaTotal));
  Serial.println("tempo ligado: " + String(tempoLigado));
  Serial.println("tempo em paradas: " + String(tempoParado));


  for (int i = 0; i < 6; i++) {
    String codParada = paradas[i];
    codParada.remove(0, 1);
    Serial.println("parada" + String((i + 1)) + ": " + codParada + " paradas: " + String(qntParadas[i]) + " tempo total: " + String(tempoParadas[i]) + " tempo medio: " + String(tempoMedio[i]) + " perda de eficiencia causada: " + perdasEficienciaParadas[i] + "\%");
  }
  Serial.println("==========================================================================================================================================================================================================================");
}

//calcula todas as eficiencias e parametros.
void calculador() {
  tempoParado = 0;
  tempoLigado = 0;
  eficienciaTotal = 0;

  tempoLigado = ((millis() / 1000) - horaDeLigacao);

  for (int i = 0; i < 6; i++) {
    tempoParado = tempoParado + tempoParadas[i];
  }

  eficienciaTotal = 100 - ((tempoParado * 100) / tempoLigado);

  for (int i = 0; i < 6; i++) {
    tempoMedio[i] = tempoParadas[i] / qntParadas[i];
  }

  for (int i = 0; i < 6; i++) {
    perdasEficienciaParadas[i] = ((tempoParadas[i] * 100) / tempoLigado);
  }
}

//conta o tempo de cada tipo de parada assim que um sensor sinaliza.
void comparador() {
  if (leitura() != "000000") {
    delay(100);

    for (int i = 0; i < 6; i++) {
      if (leitura() == paradas[i]) {
        tempoInicial = millis();
        qntParadas[i] = qntParadas[i] + 1;

        while (leitura() == paradas[i]) {
          delay(10);
          tempoFinal = millis();
        }

        decorrido = decorrido + ((tempoFinal / 1000) - (tempoInicial / 1000));
        tempoParadas[i] = tempoParadas[i] + decorrido;
        decorrido = 0;
      }
    }
  }
}
