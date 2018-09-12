## BBB Joystick

Implementar um joystick utilizando potenciometro, LDR e push button na BBB.

---

TODO:
  + ler entradas
    + potenciometro
      + output: [0;4000]
        + 3 faixas de valores (Low, Med, High)
        + 2 faixas de valores (Low, High)
    + push button
      + output: {0;1}
        + mudar de valor enquanto pressionado
        + mudar valor permanentemente após pressionar
    + LDR
      + output: [0;4000] (?)
        + mudar de valor enquanto pressionado
        + mudar valor permanentemente após pressionar
  + tranformar em sinal
    + simular Key input events
  + testar no jogo
    + 2048
