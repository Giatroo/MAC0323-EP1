# Relatório do Exercício-Projeto 1 de Estruturas de Dados II

O professor requisitou que fizéssemos a leitura de um arquivo  de texto grande e também que disponibilizássemos um modo iterativo pelo qual se pudesse fazer mudanças *on the way* na estrutura de dados informada na chamada do programa. 

Tudo foi implementado de acordo com as normas do exercício, contudo, achei melhor implementar uma forma de efetivamente testar as complexidades assintóticas das estruturas de dados. Por isso, meu relatório será focado no chamado *"modo clássico"* do programa. 

Ao chamar o programa com 
``` ./main --classic <estrutura> ```

o programa realizará uma sequência de testes brutos em cima da estrutura de dados selecionada.

Os testes podem ser encontradas no arquivo `main.cpp` e a quantidade de vezes que  cada operação será realizada é definido com base nas constantes definidas no começo do arquivo. (Algumas estruturas começam a ficar tão lentas que precisamos colocar números baixos de operações)

Além disso, a ordem em que as operações são executadas podem ser definidas na função `teste()`.

Como a estrutura foi feita de modo que a chave seja uma `string`, criei uma função que gera aleatoriamente palavras de até uma certa quantidade de caracteres (que pode ser facilmente editável no código).

Vamos agora começar com os testes (os tempos estão todos em segundos):

## Vetor Desordenado

### Insere

| num_elementos |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      10       | 1.1e-05  |     1.1e-06 |
|      100      | 0.000242 |    2.42e-06 |
|     1000      | 0.010692 |  1.0692e-05 |
|     10000     | 0.716965 | 7.16965e-05 |
|    100000     | 48.7466  | 0.000487466 |


### Remove

Os testes foram feitos sobre um Vetor Desordenado de 10.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      10       | 0.00253  |    0.000253 |
|      100      | 0.028916 |  0.00028916 |
|     1000      | 0.278059 | 0.000278059 |
|     10000     | 2.15159  | 0.000215159 |
|    100000     | 16.3828  | 0.000163828 |

### Seleciona 

Os teste abaixo foram feitos sobre um Vetor Desordenado de 1.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      10       | 0.136059 |   0.0136059 |
|      100      | 1.08513  |   0.0108513 |
|     1000      | 12.6586  |   0.0126586 |

Os testes abaixo foram feitos sobre um Vetor Desordenado de 10.000 elementos.

| num_operacoes |  tempo  | tempo médio |
| :-----------: | :-----: | ----------: |
|      10       | 4.65263 |    0.465263 |
|      50       | 36.4731 |    0.729462 |
|      100      | 68.078  |     0.68078 |

### Ranking 

Os testes abaixo foram feitos sobre um Vetor Desordenado de 10.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      10       | 0.001995 |   0.0001995 |
|      100      | 0.02041  |   0.0002041 |
|     1000      | 0.20298  |  0.00020298 |
|     10000     | 2.07947  | 0.000207947 |
|    100000     | 22.4653  | 0.000224653 |

### Devolve

Os testes abaixo foram feitos sobre um Vetor Desordenado de 10.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      10       | 0.002457 |   0.0002457 |
|      100      | 0.024132 |  0.00024132 |
|     1000      | 0.20954  | 0.000209542 |
|     10000     | 2.06739  | 0.000206739 |
|    100000     | 20.7593  | 0.000207593 |

## Vetor Ordenado

### Insere

| num_elementos |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      100      | 0.000254 |    2.54e-06 |
|     1000      | 0.010856 |  1.0856e-05 |
|     10000     | 0.727104 | 7.27104e-05 |
|    100000     | 51.4637  | 0.000514637 |

### Remove

Os testes foram feitos sobre um Vetor Ordenado de 10.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      100      | 0.005383 |   5.383e-05 |
|     1000      | 0.038187 |  3.8187e-05 |
|     10000     | 0.157745 | 1.57745e-05 |
|    100000     | 0.481091 | 4.81091e-06 |

### Seleciona

Os testes abaixo foram feitos sobre um Vetor Ordenado de 10.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      100      | 1.3e-05  |     1.3e-07 |
|     1000      | 0.000113 |    1.13e-07 |
|     10000     | 0.001214 |   1.214e-07 |
|    100000     | 0.01391  |   1.391e-07 |
|    1000000    | 0.130581 | 1.30581e-07 |
|   10000000    | 1.29158  | 1.29159e-07 |

### Ranking 

Os testes abaixo foram feitos sobre um Vetor Ordenado de 10.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      100      | 0.000124 |    1.24e-06 |
|     1000      | 0.001123 |   1.123e-06 |
|     10000     | 0.010764 |  1.0764e-06 |
|    100000     | 0.129626 | 1.29626e-06 |
|    1000000    | 1.17064  | 1.17064e-06 |
|   10000000    | 11.7863  | 1.17863e-06 |

### Devolve

Os testes abaixo foram feitos sobre um Vetor Ordenado de 10.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      10       | 0.002457 |   0.0002457 |
|      100      | 0.024132 |  0.00024132 |
|     1000      | 0.20954  | 0.000209542 |
|     10000     | 2.06739  | 0.000206739 |
|    100000     | 20.7593  | 0.000207593 |

## Lista Ligada Desordenada

### Inserção

| num_elementos |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      10       | 1.2e-05  |     1.2e-06 |
|      100      | 0.000345 |    3.45e-06 |
|     1000      | 0.012649 |  1.2649e-05 |
|     10000     | 0.818695 | 8.18695e-05 |
|    100000     | 50.2449  | 0.000502449 |

### Remove

Os testes foram feitos sobre um Lista Ligada Desordenada de 10.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      10       | 0.001086 |   0.0001086 |
|      100      | 0.016166 |  0.00016166 |
|     1000      | 0.195502 | 0.000195502 |
|     10000     | 1.93913  | 0.000193913 |
|    100000     | 15.3604  | 0.000153604 |

### Seleciona

Os testes abaixo foram feitos sobre uma Lista Ligada Desordenada de 1.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      10       | 0.147735 |    0.506788 |
|      100      | 0.988949 |  0.00988949 |
|     1000      | 13.9009  |   0.0139009 |

Os testes abaixo foram feitos sobre uma Lista Ligada Desordenada de 10.000 elementos.

| num_operacoes |  tempo  | tempo médio |
| :-----------: | :-----: | ----------: |
|      10       | 5.06788 |    0.506788 |
|      50       | 35.7377 |    0.714753 |
|      100      | 69.2971 |    0.692971 |

### Ranking 

Os testes abaixo foram feitos sobre uma Lista Ligada Desordenada de 10.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      10       | 0.00197  |    0.000197 |
|      100      | 0.021138 |  0.00021138 |
|     1000      | 0.225289 | 0.000225289 |
|     10000     | 2.34567  | 0.000234567 |
|    100000     | 23.4503  | 0.000234503 |

### Devolve

Os testes abaixo foram feitos sobre uma Lista Ligada Desordenada de 10.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      10       | 0.001512 |   0.0001512 |
|      100      | 0.015278 |  0.00015278 |
|     1000      | 0.140162 | 0.000140162 |
|     10000     | 1.43704  | 0.000143704 |
|    100000     |  15.41   |   0.0001541 |

## Lista Ligada Ordenada

### Insere

| num_elementos |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      10       | 1.3e-05  |     1.3e-06 |
|      100      | 0.000142 |    1.42e-06 |
|     1000      | 0.010921 |  1.0921e-05 |
|     10000     | 0.604607 | 6.04607e-05 |
|    100000     | 52.3571  | 0.000523571 |

### Remove

Os testes foram feitos sobre uma Lista Ligada Ordenada de 10.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      100      | 0.011609 |  0.00011609 |
|     1000      | 0.104716 | 0.000104716 |
|     10000     | 0.971136 | 9.71136e-05 |
|    100000     | 8.10268  | 8.10268e-05 |
|    1000000    | 63.5266  | 6.35266e-05 |

### Seleciona

Os testes foram feitos sobre uma Lista Ligada Ordenada de 10.000 elementos.


| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      100      | 2.7e-05  |     2.7e-07 |
|      100      | 0.002961 |   2.961e-06 |
|     1000      | 0.543452 | 5.43452e-05 |
|     10000     | 8.52858  | 8.52858e-05 |
|    100000     | 84.7425  | 8.47425e-05 |

### Ranking 

Os testes abaixo foram feitos sobre uma Lista Ligada Ordenada de 10.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      10       | 0.001349 |   0.0001349 |
|      100      | 0.010336 |  0.00010336 |
|     1000      | 0.104488 | 0.000104488 |
|     10000     | 1.09732  | 0.000109732 |
|    100000     |  11.441  |  0.00011441 |

### Devolve

Os testes abaixo foram feitos sobre uma Lista Ligada Ordenada de 10.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|      10       | 0.001252 |   0.0001252 |
|      100      | 0.012748 |  0.00012748 |
|     1000      | 0.109983 | 0.000109983 |
|     10000     | 1.20515  | 0.000120515 |
|    100000     | 11.5805  | 0.000115805 |

## Árvore Binária não Balanceada

### Insere

| num_elementos |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|     10000     | 0.014905 |  1.4905e-06 |
|    100000     | 0.189932 | 1.89932e-06 |
|    1000000    | 2.03931  | 2.03931e-06 |
|   10000000    | 22.7167  | 2.27167e-06 |

### Remove

Os testes foram feitos sobre uma Árvore Binária de 1.000.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|     10000     | 0.056553 |  5.6553e-06 |
|    100000     | 0.464744 | 4.64744e-06 |
|    1000000    | 4.08616  | 4.08616e-06 |
|   10000000    | 38.1435  | 3.81435e-06 |

### Seleciona 

Os testes foram feitos sobre uma Árvore Binária de 1.000.000 elementos.

| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|     10000     | 0.004366 |  1.8227e-06 |
|    100000     | 0.069448 |   4.366e-07 |
|    1000000    | 0.41652  |  6.9448e-07 |
|   10000000    | 1.87706  | 1.87706e-07 |
|   100000000   | 16.2934  | 1.62934e-07 |

### Ranking 

Os testes foram feitos sobre uma Árvore Binária de 1.000.000 elementos.


| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|     10000     | 0.02111  |   2.111e-06 |
|    100000     | 0.213149 | 2.13149e-06 |
|    1000000    | 2.49504  | 2.49504e-06 |
|   10000000    | 23.2999  | 2.32999e-06 |

### Devolve 

Os testes foram feitos sobre uma Árvore Binária de 1.000.000 elementos.


| num_operacoes |  tempo   | tempo médio |
| :-----------: | :------: | ----------: |
|     10000     | 0.019701 |  1.9701e-06 |
|    100000     | 0.189666 | 1.89666e-06 |
|    1000000    |  2.0817  |  2.0817e-06 |
|   10000000    | 21.9777  | 2.19777e-06 |

## Treap

Os testes foram feitos sobre uma Treap de 1.000.000 elementos.



## Créditos

Lucas Paiolla Forastiere - NUSP 11221911