#include "tarefas.h"
#include <stdio.h>
#include <string.h>

ERROS criar(Tarefa tarefas[], int *pos) {
  if (*pos >= TOTAL)
    return MAX_TAREFA;

  printf("Entre com a prioridade: ");
  scanf("%d", &tarefas[*pos].prioridade);
  if (tarefas[*pos].prioridade < 1 || tarefas[*pos].prioridade > 10) {
    printf("Prioridade inválida\n");
    return PRIORIDADE;
  }
  clearBuffer();
  printf("Entre com a categoria: ");
  fgets(tarefas[*pos].categoria, CATEGORIA, stdin);
  int pos_categoria = strcspn(tarefas[*pos].categoria, "\n");
  tarefas[*pos].categoria[pos_categoria] = '\0';
  
  printf("Entre com a descricao: ");
  fgets(tarefas[*pos].descricao, DESCRICAO, stdin);
  int pos_descricao = strcspn(tarefas[*pos].descricao, "\n");
  tarefas[*pos].descricao[pos_descricao] = '\0';

  *pos = *pos + 1;
  printf("Tarefa criada com sucesso.\n");

  return OK;
}

ERROS deletar(Tarefa tarefas[], int *pos) {
  // teste se existem tarefas
  if (*pos == 0)
    return SEM_TAREFAS;

  // verifica se a tarefa escolhida existe
  int pos_deletar;
  printf("Entre com a posicao da tarefa a ser deletada: ");
  scanf("%d", &pos_deletar);
  pos_deletar--; // garantir posicao certa no array
  if (pos_deletar >= *pos || pos_deletar < 0)
    return NAO_ENCONTRADO;

  for (int i = pos_deletar; i < *pos; i++) {
    tarefas[i].prioridade = tarefas[i + 1].prioridade;
    strcpy(tarefas[i].categoria, tarefas[i + 1].categoria);
    strcpy(tarefas[i].descricao, tarefas[i + 1].descricao);
  }

  *pos = *pos - 1;
  printf("Tarefa deletada com sucesso.\n");
  return OK;
}

ERROS listar(Tarefa tarefas[], int *pos) {
  if (*pos == 0) {
    return SEM_TAREFAS;
  }
  char categoria[CATEGORIA];
  printf("Entre com a categoria: ");
  clearBuffer();
  fgets(categoria, CATEGORIA, stdin);
  int pos_categoria = strcspn(categoria, "\n");
  categoria[pos_categoria] = '\0';
  
  int tarefasencontradas = 0;

  for (int i = 0; i < *pos; i++) {
    
    if (strcmp(tarefas[i].categoria, categoria) == 0) {
      printf("Pos: %d\t", i + 1);
      printf("Prioridade: %d\t", tarefas[i].prioridade);
      printf("Categoria: %s\t", tarefas[i].categoria);
      printf("Descricao: %s\n", tarefas[i].descricao);
      tarefasencontradas++;
    }
  }
  if (tarefasencontradas == 0) {
    printf("Nenhuma tarefa encontrada na categoria '%s'", categoria);
    return TAREFAS_CATEGORIA_NAO_ENCONTRADA;
  }
  return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos) {
  FILE *f = fopen("tarefas.bin", "wb");
  if (f == NULL)
    return ABRIR;

  int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
  if (qtd == 0)
    return ESCREVER;

  qtd = fwrite(pos, 1, sizeof(int), f);
  if (qtd == 0)
    return ESCREVER;

  if (fclose(f))
    return FECHAR;

  return OK;
}

ERROS exportar(Tarefa tarefas[], int *pos) {
  char categoria[CATEGORIA]; // usa a mesm logica da criação que lista categoria
  printf("Digite a categoria que deseja exportar: ");
  clearBuffer();
  fgets(categoria, CATEGORIA, stdin);
  int pos_categoria = strcspn(categoria, "\n");
  categoria[pos_categoria] = '\0';
  
  int categoria_encontrada = 0;
  for (int i = 0; i < *pos; i++) {
    if (strcmp(tarefas[i].categoria, categoria) == 0) {
      categoria_encontrada = 1;
      break;
    }
  }
  if (!categoria_encontrada) {
    printf("Categoria não encontrada\n");
    return TAREFAS_CATEGORIA_NAO_ENCONTRADA;
  }

  char nome_arquivo[100]; // caracteres para o usuario nomear
  printf("Digite o nome do arquivo para exportar as tarefas: ");
  fgets(nome_arquivo, 100, stdin);
  nome_arquivo[strcspn(nome_arquivo, "\n")] = 0;

  FILE *arquivo = fopen(nome_arquivo, "w");
  if (arquivo == NULL) {
    printf("Erro ao criar o arquivo.\n");
    return EXPORTAR_ARQUIVO;
  }
  int tarefas_exportadas = 0;
  
  for (int i = 0; i < *pos; i++) {
    if (strcmp(tarefas[i].categoria, categoria) == 0) {
      fprintf(arquivo, "Prioridade: %d\n", tarefas[i].prioridade);
      fprintf(arquivo, "Categoria: %s\n", tarefas[i].categoria);
      fprintf(arquivo, "Descricao: %s", tarefas[i].descricao);
      fprintf(arquivo, "\n");
      tarefas_exportadas++;
    }
  }
  fclose(arquivo);
  printf("Tarefas exportadas com sucesso para o arquivo '%s'\n", nome_arquivo);
  return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos) {
  FILE *f = fopen("tarefas.bin", "rb");
  if (f == NULL)
    return ABRIR;

  int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
  if (qtd == 0)
    return LER;

  qtd = fread(pos, 1, sizeof(int), f);
  if (qtd == 0)
    return LER;

  if (fclose(f))
    return FECHAR;

  return OK;
   }  

ERROS exportar_binario(Tarefa tarefas[], int pos) {
  FILE *arquivo =
      fopen("tarefas.bin", "wb"); // Abre o arquivo para escrita binária

  if (arquivo == NULL) {
    return ABRIR;
    }

    // Escreve os dados das tarefas no arquivo
  int qtd = fwrite(tarefas, sizeof(Tarefa), pos, arquivo);

  if (qtd != pos) {
    fclose(arquivo);
    return ESCREVER;
  }

  fclose(arquivo);
  printf("Tarefas exportadas para arquivo binário com sucesso.\n");
  return OK;
  }

ERROS carregar_binario(Tarefa tarefas[], int *pos) {
  FILE *arquivo =
      fopen("tarefas.bin", "rb"); // Abre o arquivo para leitura binária

  if (arquivo == NULL) {
    return ABRIR;
  }

    // Lê os dados das tarefas do arquivo
  int qtd = fread(tarefas, sizeof(Tarefa), TOTAL, arquivo);

  if (qtd <= 0) {
    fclose(arquivo);
    return LER;
  }

  *pos = qtd; // Atualiza o número de tarefas carregadas

  fclose(arquivo);
  printf("Tarefas carregadas de arquivo binário com sucesso.\n");
  return OK;
  }

  void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    }
