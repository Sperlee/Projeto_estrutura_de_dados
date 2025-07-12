📌 Descrição do Trabalho: Estruturas de Armazenamento de Registros em C

Este projeto tem como objetivo implementar e comparar diferentes estruturas de dados para armazenamento e gerenciamento de registros em linguagem C. Cada registro contém:

- Nome: sequência aleatória de 50 caracteres;
- CPF: 11 dígitos consecutivos (os 9 primeiros formam a chave);
- Nota: número real entre 0 e 100.

Ao todo, são gerados 10.000 registros aleatórios, que são inicialmente salvos em um arquivo. A partir desse arquivo, os dados são inseridos e manipulados por três diferentes estruturas de armazenamento:

1. Árvore B+
- Armazena os registros em uma estrutura de árvore B+ com os dados em um arquivo e os índices em outro.
- Suporta operações de:
  - Inserção
  - Consulta por chave (CPF)
  - Remoção de registros

2. Tabela Hash com Endereçamento Aberto
- Usa uma função hash baseada em rand() e srand(chave) para distribuir os registros.
- Tamanho da tabela: 100.000 posições.
- Resolve colisões com endereçamento aberto (linear ou quadrático).
- Suporta operações de:
  - Inserção
  - Consulta
  - Remoção

3. Heap com Prioridade por Nota
- Estrutura de heap máximo, onde a nota define a prioridade dos registros.
- Permite:
  - Inserção
  - Consulta ao topo (maior nota)
  - Remoção do elemento de maior prioridade

Documentação e Arquivos
A entrega inclui:
- Códigos-fonte comentados em C (.c e .h)
- Arquivo inicial com os 10.000 registros gerados
- Arquivos auxiliares usados por cada estrutura (ex: dados.bin, índice.idx, hash.dat, heap.dat etc.)
- Documentação explicando:
  - A estrutura e funcionamento de cada abordagem
  - Detalhes da geração de dados
  - Explicação das funções hash e de comparação
  - Exemplos de uso das operações

Este projeto tem o intuito de exercitar o uso prático de estruturas de dados clássicas em aplicações reais, com foco em eficiência, organização de arquivos e gerenciamento de grandes volumes de dados. É também uma excelente preparação para sistemas de banco de dados e organização de arquivos.
