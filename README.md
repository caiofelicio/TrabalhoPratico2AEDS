### CSI 488 – Algoritmos e Estruturas de Dados I

# Trabalho Prático 2

```
Prof. Mateus Ferreira Satler
DECSI – ICEA - UFOP
```

## Descrição

O trabalho consiste na implementação de um Sistema de Votação usando **ÁRVORES BINÁRIAS DE BUSCA (ABB)**.

Imagine que um grupo de pessoas irá participar de uma eleição. Para votar e ser votado, e necessário ter um número
de título de eleitor válido (o número de título pode ser um inteiro simples). Além disso, qualquer pessoa pode ser
eleita para a função. Nesta votação, uma pessoa pode **votar em alguém** ou, a qualquer momento, decidir **retirar seu
voto** por qualquer que seja o motivo. Contudo, apenas um voto por pessoa pode estar armazenado no sistema num
dado momento.

Essas verificações podem ser feitas da seguinte forma:

- Criar uma ABB para armazenar os números de todos os títulos válidos.
- Criar outra ABB para armazenar os números de todos os títulos que já votaram até o momento.

Para evitar redundância de dados (informações iguais armazenadas em locais diferentes), o cadastro dos votantes
deverá ser feito em uma estrutura separada que será **referenciada** pelas árvores (\*info). Utilize as estruturas abaixo:

```c
typedef struct Info_Est {
    int titulo_eleitor;
    char Nome[50];
    int voto;
}Info;

typedef struct No_Est {
    Info *info;
    struct No_Est *esq;
    struct No_Est *dir;
}No;

No *arvoreTitulos;
No *arvoreVotos;
```

**Observação:** Não permita que sejam cadastrados dois números de título de eleitor iguais. Ao final do programa,
libere todos os endereços de memória alocados.

## Funcionalidades Esperadas

Seu programa deve conter um **menu** com as seguintes opções:

**1. Cadastrar um título:** ```insere o título e nome na árvore de títulos válidos (se esse não estiver lá)```<br><br>
**2. Descadastrar um título:** ```retira o título da árvore de títulos válidos (se esse estiver lá) e apaga os dados.```<br><br>
**3. Iniciar nova votação:** ```inicializa/esvazia a ABB que guarda os títulos que já votaram.```<br><br>
**4. Votar:** ```lê o número do título e o voto. Se o número é válido e se ainda não votou, atualiza a ABB que armazena
os títulos de quem já votou e computa o voto (em quem votou). Se o número não é válido ou já votou, emite
mensagem de erro.```<br><br>
**5. Retirar voto:** ```lê o número do título e verifica se já votou. Se já votou, retira o título e o voto. Caso contrário,
emite mensagem de erro.```

**6. Mostrar resultado parcial das eleições** ```(títulos e nomes dos votados e quantidade de votos de cada um),
ordenados de forma decrescente em relação ao número de votos.```<br><br>
7. ```Listar todos os números de títulos e nomes** das pessoas que já votaram.```<br><br>
8. ```Liberar todas as estruturas e encerrar o programa.```

## O que deve ser entregue

Código fonte do programa em C (bem indentado e comentado) e documentação do trabalho. Entre outras coisas, a
documentação deve conter:

**1. Introdução:** ```descrição do problema a ser resolvido e visão geral sobre o funcionamento do programa.```<br><br>
**2. Implementação:** ```descrição sobre a implementação do programa. Deve ser detalhada a estrutura de dados
utilizada (de preferência com diagramas ilustrativos), o funcionamento das principais sub-rotinas utilizadas,
bem como decisões tomadas relativas aos casos e detalhes de especificação que porventura estejam omissos
no enunciado. **Muito importante:** os códigos utilizados nas implementações devem ser inseridos na
documentação.```<br><br>
**3. Listagem de testes executados:** ```os testes executados devem ser apresentados, analisados e discutidos.```<br><br>
**4. Conclusão:** ```comentários gerais sobre o trabalho e as principais dificuldades encontradas em sua
implementação.```<br><br>
**5. Bibliografia:** ```bibliografia utilizada para o desenvolvimento do trabalho, incluindo sites da Internet se for o
caso. Uma referência bibliográfica deve ser citada no texto quando da sua utilização.```<br><br>
