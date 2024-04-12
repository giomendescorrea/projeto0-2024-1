#define TOTAL 100
#define DESCRICAO 300
#define CATEGORIA 100

typedef struct {
    int prioridade;
    char descricao[DESCRICAO];
    char categoria[CATEGORIA];
} Tarefa;

typedef enum {OK, MAX_TAREFA, SEM_TAREFAS, NAO_ENCONTRADO, ABRIR, FECHAR, ESCREVER, LER, PRIORIDADE, TAREFAS_CATEGORIA_NAO_ENCONTRADA, EXPORTAR_ARQUIVO} ERROS;

typedef ERROS (*funcao)(Tarefa[], int*);

ERROS criar(Tarefa tarefas[], int *pos);
ERROS deletar(Tarefa tarefas[], int *pos);
ERROS listar(Tarefa tarefas[], int *pos);
ERROS salvar(Tarefa tarefas[], int *pos);
ERROS carregar(Tarefa tarefas[], int *pos);
ERROS exportar(Tarefa tarefas[], int *pos);
ERROS exportar_binario(Tarefa tarefas[], int pos);
ERROS carregar_binario(Tarefa tarefas[], int *pos);

void clearBuffer();
