#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

//CRIANDO AS ESTRUTURAS QUE UTILIZAREMOS PARA REGISTRAR O QUERIDO HOSPEDE NO HOTEL.
// criando estrutura de dados para registro de quarto, quantidade de camas e quanto seria o valor de sua diaria
typedef struct {
    int numeroDoQuarto;
    int quantidadeDeCamas;
    float precoDiaria;
} Quarto;
/* criando estrutura de dados para registrar o veículo do hospede no estacionamento,
adicionando a placa, o numero da vaga, o modelo e a cor do carro.*/
typedef struct {
    int numeroDaVaga;
    char placaDoCarro[7];
    char modeloDoCarro[20];
    char corDoCarro[20];
} Estacionamento;
/*cria uma estrutura show de bola de dados
 que registra o hospede com todas suas informações pessoais,
 se possui um carro para o nosso chique estacionamento e a forma de pagamento*/
typedef struct {
    int id;
    char nome[50];
    int telefone;
    int cpf;
    int cep;
    char endereco[70];
    char acompanhante[50];
    int numeroDoCartao;
    int cvv;
    Quarto quarto;
    int possuiCarro;
    Estacionamento estacionamento;
} Hospede;

/*cria uma estrutura de dados contendo os dados do hospede, implementada por meio de nós encadeados,
no caso, *prox é um ponteiro para o próximo no da fila*/


typedef struct no {
    Hospede dado;
    struct no *prox;
} No;
/*cria uma estrutura de dados contendo um ponteiro
um para o inicio e um para o fim, acrescentando uma variavel inteira que armazenará o tamanho para a Fila*/
typedef struct {
    No *inicio;
    No *fim;
    int tamFila;
} Fila;
// cria uma variavel para o ultimo id
int ultimoId = 0;

void menuPrincipal();

Hospede checkInNovoCliente();

void cria(Fila *fila);

int estaVazia(Fila fila);

int insere(Fila *fila, Hospede dado);

int procurarRemoverHospede(Fila *fila, int id);
//Função responsavel por remover os dados do hospede da fila.

void mostrarClientesEstacionamento(Fila fila);

void QuartosOcupados(int quantidade, Fila *fila);

int main() {
    menuPrincipal();
    return 0;
}


// função responsável por inicializar a fila, definindo o início e o fim como NULL e o tamanho da fila como 0.
void cria(Fila *fila){

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamFila = 0;
}
//função que solicita informações sobre um novo cliente para o check-in e retorna um Hospede preenchido com essas informações.
Hospede checkInNovoCliente() {
    Hospede hospede;

    printf("Para adicionar um novo cliente, complete as informacoes a seguir\n");

    ultimoId++;
    hospede.id = ultimoId;

    getchar();
    printf("Nome do cliente:\n");
    fgets(hospede.nome, 50, stdin);

    printf("Numero do telefone:\n");
    scanf("%d", &hospede.telefone);

    printf("CPF:\n");
    scanf("%d", &hospede.cpf);

    printf("Cep:\n");
    scanf("%d", &hospede.cep);

    getchar();
    printf("Endereco:\n");
    fgets(hospede.endereco, 70, stdin);

    printf("Acompanhante:\n");
    fgets(hospede.acompanhante, 50, stdin);

    printf("Numero do cartao para pagamento:\n");
    scanf("%d", &hospede.numeroDoCartao);

    printf("Codigo CVV:\n");
    scanf("%d", &hospede.cvv);

    printf("Numero do quarto:\n");
    scanf("%d", &hospede.quarto.numeroDoQuarto);

    printf("Preco diaria:\n");
    scanf("%f", &hospede.quarto.precoDiaria);

    printf("Quantidade camas:\n");
    scanf("%d", &hospede.quarto.quantidadeDeCamas);

    printf("Cliente possui carro?\n");
    printf("0 - Nao\n");
    printf("1 - Sim\n");
    scanf("%d", &hospede.possuiCarro);

    if(hospede.possuiCarro == 1) {
        printf("Numero da vaga do estacionamento:\n");
        scanf("%d", &hospede.estacionamento.numeroDaVaga);

        getchar();
        printf("Cor do carro:\n");
        fgets(hospede.estacionamento.corDoCarro, 20, stdin);

        printf("Modelo do carro:\n");
        fgets(hospede.estacionamento.modeloDoCarro, 20, stdin);

        printf("Placa do carro:\n");
        fgets(hospede.estacionamento.placaDoCarro, 7, stdin);
    }


    return hospede;
}
/*funcao que exibirá o menu principal do programa com todas as opções de check in,
 mostrar hospedes, estacionamento e check out*/

void menuPrincipal() {
    Hospede hospede;
    Fila fila;
    int sucesso;
    cria(&fila);
    int idHospedeSelecionado;
    int seletorMenuPrincipal;

    do {
        printf("Bem-vindo a Hotelar\n");
        printf("O que deseja fazer?\n");
        printf("1 - Check-in novo cliente\n");
        printf("2 - Check-out cliente\n");
        printf("3 - Verificar vagas na garagem\n");
        printf("4 - Listar clientes\n");
        printf("5 - Sair\n");
        scanf("%d", &seletorMenuPrincipal);
        switch (seletorMenuPrincipal) {
            case 1:
                system("cls");
                hospede = checkInNovoCliente();
                sucesso = insere(&fila, hospede);
                if(sucesso) {
                    printf("Hospede cadastrado com sucesso\n");
                } else {
                    printf("Hospede nao encontrado\n");
                }
                break;
            case 2:
                system("cls");
                if(estaVazia(fila)) {
                    printf("Nao possui nenhum cliente cadastrado!\n\n");
                } else {
                    printf("********************\n");
                    mostra(fila);
                    printf("\n\n\n Digite o id do cliente que deseja retirar...\n\n");
                    scanf("%d", &idHospedeSelecionado);
                    sucesso = procurarRemoverHospede(&fila, idHospedeSelecionado);
                    if(sucesso) {
                        printf("Hospede removido com sucesso\n");
                    } else {
                        printf("Hospede nao encontrado\n");
                    }
                    sucesso = 0;
                }
                break;
            case 3:
                system("cls");
                mostrarClientesEstacionamento(fila);
                break;
            case 4:
                system("cls");
                printf("\n*************CLIENTES***************\n");
                QuartosOcupados(4, &fila);
                mostra(fila);
                break;
            default:
                break;
        }

    } while (seletorMenuPrincipal != 5);

}
//função que verifica se a fila está vazia, ou seja, se o início da fila é NULL. Retorna 1 se a fila estiver vazia e 0 caso contrário.
int estaVazia(Fila fila){

    if(fila.inicio == NULL)
        return 1;

    return 0;
}
/*função que insere um novo hóspede no final da fila. Cria um nó auxiliar, preenche seus dados
 com o Hospede fornecido e o adiciona no final da fila. Retorna 1 em caso de sucesso na inserção e 0 em caso de falha.*/
int insere(Fila *fila, Hospede dado){

    No *aux;
    aux = (No *) malloc(sizeof(No));
    if(aux == NULL)
        return 0;

    aux->dado = dado;
    aux->prox = NULL;

    fila->tamFila++;

    if(fila->inicio == NULL){
        fila->inicio = aux;
        fila->fim = aux;
        return 1;
    }

    fila->fim->prox = aux;
    fila->fim = aux;
    return 1;
}

void mostra(Fila fila){

    No *aux;
    aux = fila.inicio;
    if (aux == NULL){
        printf("Fila vazia!\n");
    }

    while(aux != NULL){
        printf("Id: %d\n", aux->dado.id);
        printf("Nome: %s\n", aux->dado.nome);
        printf("Telefone: %d\n", aux->dado.telefone);
        printf("Cpf: %d\n", aux->dado.cpf);
        printf("Cep: %d\n", aux->dado.cep);
        printf("Endereco: %s\n", aux->dado.endereco);
        printf("Acompanhante: %s\n", aux->dado.acompanhante);
        printf("Numero cartao: %d\n", aux->dado.numeroDoCartao);
        printf("Cvv: %d\n", aux->dado.cvv);
        printf("Numero quarto: %d\n", aux->dado.quarto.numeroDoQuarto);
        printf("Preco diaria: %f\n", aux->dado.quarto.precoDiaria);
        printf("Quantidade camas: %d\n", aux->dado.quarto.quantidadeDeCamas);
        if(aux->dado.possuiCarro == 1) {
            printf("Cor carro: %s\n", aux->dado.estacionamento.corDoCarro);
            printf("Modelo carro: %s\n", aux->dado.estacionamento.modeloDoCarro);
            printf("Numero vaga: %d\n", aux->dado.estacionamento.numeroDaVaga);
            printf("Placa carro: %s\n", aux->dado.estacionamento.placaDoCarro);
        }
        printf("********************\n");
        aux = aux->prox;
    }
}
//Imprimir os clientes do estacionamento
void mostrarClientesEstacionamento(Fila fila){

    No *aux;
    aux = fila.inicio;
    if (aux == NULL){
        printf("Fila vazia!\n");
    }
    printf("********************\n");
    while(aux != NULL){
        if(aux->dado.possuiCarro == 1) {
            printf("Nome: %s\n", aux->dado.nome);
            printf("Cor carro: %s\n", aux->dado.estacionamento.corDoCarro);
            printf("Modelo carro: %s\n", aux->dado.estacionamento.modeloDoCarro);
            printf("Numero vaga: %d\n", aux->dado.estacionamento.numeroDaVaga);
            printf("Placa carro: %s\n", aux->dado.estacionamento.placaDoCarro);
        }
        printf("********************\n");
        aux = aux->prox;
    }
}
//criando os clientes para ocupar os quartos.
void QuartosOcupados( int quantidade, Fila *fila) {
    Hospede hospedes[quantidade];



    hospedes[0].id = 1;
    strcpy(hospedes[0].nome, "Jorge Vercillo");
    hospedes[0].telefone = 123456789;
    hospedes[0].cpf = 987654321;
    hospedes[0].cep = 12345678;
    strcpy(hospedes[0].endereco, "Rua Monalisa, 123");
    strcpy(hospedes[0].acompanhante, "Sandra Anemberg");
    hospedes[0].numeroDoCartao = 123456789;
    hospedes[0].quarto.numeroDoQuarto = 1;
    hospedes[0].quarto.quantidadeDeCamas = 1;
    hospedes[0].quarto.precoDiaria = 100.0;

    hospedes[1].id = 2;
    strcpy(hospedes[1].nome, "Camila Zombolorg");
    hospedes[1].telefone = 456879258;
    hospedes[1].cpf = 254125413;
    hospedes[1].cep = 111111111;
    strcpy(hospedes[1].endereco, "Rua Prisioneiro Fajuto, 222");
    strcpy(hospedes[1].acompanhante, "sem acompanhante");
    hospedes[1].numeroDoCartao = 666999988;
    hospedes[1].quarto.numeroDoQuarto = 2;
    hospedes[1].quarto.quantidadeDeCamas = 2;
    hospedes[1].quarto.precoDiaria = 500.0;

    hospedes[2].id = 3;
    strcpy(hospedes[2].nome, "Dani Bond");
    hospedes[2].telefone = 1234567894;
    hospedes[2].cpf = 987654321;
    hospedes[2].cep = 333333333;
    strcpy(hospedes[2].endereco, "Rua das Rãs Divertidas, 8");
    strcpy(hospedes[2].acompanhante, "Fatima");
    hospedes[2].numeroDoCartao = 987456321;
    hospedes[2].quarto.numeroDoQuarto = 3;
    hospedes[2].quarto.quantidadeDeCamas = 3;
    hospedes[2].quarto.precoDiaria = 300.0;

    hospedes[3].id = 4;
    strcpy(hospedes[3].nome, "Carla Perez");
    hospedes[3].telefone = 12584564;
    hospedes[3].cpf = 256396564;
    hospedes[3].cep = 748574544;
    strcpy(hospedes[3].endereco, "Avenida Caverna, 1853");
    strcpy(hospedes[3].acompanhante, "Faustao");
    hospedes[3].numeroDoCartao = 987456321;
    hospedes[3].quarto.numeroDoQuarto = 3;
    hospedes[3].quarto.quantidadeDeCamas = 4;
    hospedes[3].quarto.precoDiaria = 400.0;

    insere(fila, hospedes[0]);
    insere(fila, hospedes[1]);
    insere(fila, hospedes[2]);
    insere(fila, hospedes[3]);

}
/*Essa função procura um hospede com base no ID fornecido. Caso encontrado,
remove o hospede da fila e calcula o valor total da estadia com base no numero de dias e no preço da diaria*/
int procurarRemoverHospede(Fila *fila, int id) {
    No *atual = fila->inicio;
    No *anterior = NULL;
    int sucesso = 0;
    int dias;

    while (atual != NULL) {
        if (atual->dado.id == id) {
            if (anterior == NULL) {

                fila->inicio = atual->prox;
                if (fila->inicio == NULL) {

                    fila->fim = NULL;
                }
            } else {

                anterior->prox = atual->prox;
                if (atual == fila->fim) {

                    fila->fim = anterior;
                }
            }
            printf("Quantos dias de hospedagem?\n");
            scanf("%d", &dias);
            printf("\n\n\nValor total das diarias: %f\n\n", dias * atual->dado.quarto.precoDiaria);
            free(atual);
            fila->tamFila--;
            sucesso = 1;
            break;
        }

        anterior = atual;
        atual = atual->prox;
    }

    return sucesso;
}
