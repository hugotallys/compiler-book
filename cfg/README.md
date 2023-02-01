# Gramaticas livre de contexto

Descreva a linguagem gerada pelas gramáticas abaixo e depois implemente um programa reconhecedor da mesma. Podem usar qualquer linguagem, e permitam que entre os simbolos terminais seja possivel ter ou não espaço em branco, tabulação e símbolo da próxima linha.

```console
G1::
S --> bB 
B --> Baa
B --> a
```

A expressao regular que define a linguagem gerada por G1 eh dada por: `b(aa)*a`. Esquematizando o seu DFA temos:

![](g1.png)

```console
G2::
S --> AB
A --> aAb
A --> ^
B --> Bb
B --> b
```

```console
G3::
S' --> Sc
S  --> SA
S  --> A
A  --> aSb
A  --> ab
```

```console
G4::
S --> E + S
S --> E * S 
S --> E
E --> a
```

```console
G5:: 
S --> 0A1
A --> 0A1
A --> 0
```
