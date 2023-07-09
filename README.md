# trabalho-oficina-computacao
Trabalhos Final da disciplina de Oficina de Computação(CI067) pelo curso de Bacharelado em Ciência da Computação UFPR 2018 

**Objetivo**: introduzir aos alunos sobre a linguagem **C**, além de introduzir novas estruturas de dados como listas encadeadas, alocação dinâmica e uso de ponteiros. O código busca uma sequência de caracteres em uma string, simulando a análise de sequências de DNA.

- O código pode ser compilado utilizando o comando **make**
- Pode ser executado com o comando **./DNAcrack -opção arquivo_sequência1 arquivo_sequência2 arquivo_sequência3**
- Argumento **opção** pode ser *-analyze, -cut, -glue* e *-recombine*
- *-analyze*: encontra uma sequência do arquivo_sequência2 dentro do arquivo_sequência1, indica na saída padrão se uma sequência for encontrada
- *-cut*: encontra uma sequência do arquivo_sequência2 dentro do arquivo_sequência1, se encontrar retira a sequência encontrada da sequência original e imprime a nova sequência resultante na saída padrão
- *-glue*: encontra uma sequência do arquivo_sequência2 dentro do arquivo_sequência1, se encontrar retira a sequência encontrada da sequência original e cola a sequência em alguma parte outra parte da sequência original
- *-recombine*: encontra uma sequência do arquivo_sequência2 dentro do arquivo_sequência1, é a mesma função da opção *-glue* porém agora considera cadeias circulares , se encontrar retira a sequência encontrada da sequência original e cola a sequência em alguma parte outra parte da sequência original no arquivo_sequencia3
  
Período original em que o projeto foi feito: 2° Sem. 2018
