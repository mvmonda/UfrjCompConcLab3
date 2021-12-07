# Computação Concorrent UFRJ - Lab 3

### Matheus Veras Mondaini - DRE 119030209

#

## Utilização do programa:

`$ gcc lab3.c -o lab3 -lpthread`
`$ ./lab3 <tamanho array> <limite inferior> <limite superior> <número de threads>`

## Desempenho:

### $10^5$

- 1 thread: `./lab3 10000 0.0 500.0 1`
    - Sequencial: 0.000030 segundos
    - Paralelo: 0.000352 segundos
    - Sequencial / Paralelo = 0.085

- 2 threads: `./lab3 10000 0.0 500.0 2`
    - Sequencial: 0.000019 segundos
    - Paralelo: 0.000236 segundos
    - Sequencial / Paralelo = 0.08

- 4 threads: `./lab3 10000 0.0 500.0 2`
    - Sequencial: 0.000027 segundos
    - Paralelo: 0.000317 segundos
    - Sequencial / Paralelo = 0.085

### $10^7$

- 1 thread: `./lab3 1000000 0.0 500.0 1`
    - Sequencial: 0.002125 segundos
    - Paralelo: 0.002626 segundos
    - Sequencial / Paralelo = 0.8

- 2 threads: `./lab3 1000000 0.0 500.0 2`
    - Sequencial: 0.002433 segundos
    - Paralelo: 0.001670 segundos
    - Sequencial / Paralelo = 1.45

- 4 threads: `./lab3 1000000 0.0 500.0 4`
    - Sequencial: 0.002778 segundos
    - Paralelo: 0.000919 segundos
    - Sequencial / Paralelo = 3.02

### $10^8$

- 1 thread: `./lab3 10000000 0.0 500.0 1`
    - Sequencial: 0.021230 segundos
    - Paralelo: 0.024744 segundos
    - Sequencial / Paralelo = 0.85

- 2 threads: `./lab3 10000000 0.0 500.0 1`
    - Sequencial: 0.020846 segundos
    - Paralelo: 0.011863 segundos
    - Sequencial / Paralelo = 1.75

- 4 threads: `./lab3 10000000 0.0 500.0 1`
    - Sequencial: 0.020764 segundos
    - Paralelo: 0.006571 segundos
    - Sequencial / Paralelo = 3.15