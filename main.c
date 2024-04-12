#include <stdio.h>
#include "tarefas.h"

int main() {
    Tarefa tarefas[TOTAL];
    int pos = 0;
    int opcao;
    ERROS resultado;

  do {
    printf("\nMenu principal\n");
    printf("1 - Criar tarefa\n");
    printf("2 - Deletar tarefa\n");
    printf("3 - Listar tarefas\n");
    printf("4 - Exportar tarefas\n");
    printf("5 - Exportar tarefas para binário\n");
    printf("6 - Carregar tarefas de binário\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");

    scanf("%d", &opcao);
    switch (opcao) { // switch case vai armazenar o resultado de cada função para tratar no próximo switch case
      case 1:
        resultado = criar(tarefas, &pos);
        break;
      case 2:
        resultado = deletar(tarefas, &pos);
        break;
      case 3:
        resultado = listar(tarefas, &pos);
        break;
      case 4:
        resultado = exportar(tarefas, &pos);
        break;
      case 5:
        resultado = exportar_binario(tarefas, pos);
        break;
      case 6:
        resultado = carregar_binario(tarefas, &pos);
        break;
      case 0:
        printf("Saindo...\n");
        resultado = OK;
        break;
      default:
        printf("Opcao invalida\n");
        resultado = OK;
        break;
  }
  switch (resultado)  { // caso o resultado seja diferente de ok, ele vai tratar conforme o erro que foi armazenado na variável resultado (valor que cada função retornou)
    case OK:
      break;
    case MAX_TAREFA:
      printf("Erro: Limite máximo de tarefas atingido.\n");
      break;
    case SEM_TAREFAS:
      printf("Erro: Não há tarefas a serem  ou listadas.\n");
      break;
    case NAO_ENCONTRADO:
      printf("Erro: Tarefa não encontrada.\n");
      break;
    case ABRIR:
      printf("Erro: Não foi possível abrir o arquivo.\n");
      break;
    case FECHAR:
      printf("Erro: Não foi possível fechar o arquivo.\n");
      break;
    case ESCREVER:
      printf("Erro: Não foi possível escrever no arquivo.\n");
      break;
    case LER:
      printf("Erro: Não foi possível ler do arquivo.\n");
      break;
    case PRIORIDADE:
      printf("Erro: Prioridade inválida.\n");
      break;
    case TAREFAS_CATEGORIA_NAO_ENCONTRADA:
      printf("Erro: Nenhuma tarefa encontrada na categoria especificada.\n");
      break;
    case EXPORTAR_ARQUIVO:
      printf("Erro: Não foi possível exportar as tarefas para o arquivo.\n");
      break;
    default:
      printf("Erro desconhecido.\n");
      break;
   }
    } while (opcao != 0);

    return 0;
}
