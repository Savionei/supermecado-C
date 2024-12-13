#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto{
char Nome[50];
float Preco;
int Quantidade;
struct Produto *Prox;
}Produto;

typedef struct st_SumarioP{
Produto *Topo;
int Qtd_ProdutoPilha;
}Pilha_Produtos;

typedef struct st_Cliente{
char Nome[50];
int Cod_Cliente;
Pilha_Produtos PilhaProdutos;
struct Cliente *Prox;
}Cliente;

Cliente *Cliente_temp;

typedef struct st_Sumario{
Cliente *Primeiro;
Cliente *Ultimo;
int Qtd_ClientesFila;
}Fila_Cliente;

//escopo das funçoes
void inserir_cliente(Fila_Cliente *FilaCliente);
void incluir_produto(Fila_Cliente *FilaCliente);
void atender_cliente(Fila_Cliente *FilaCliente);


int main()
{ //alocando a memoria para liSTa de clientes
    Fila_Cliente *FilaCliente = (Fila_Cliente*) calloc(1,sizeof(Fila_Cliente));
    FilaCliente ->Primeiro = NULL;
    FilaCliente ->Qtd_ClientesFila = 0;



    int menu;
    do{

    system("cls");
    printf("SUPERMECADO SAVIONEI\n");
    printf("\n\n");
    printf("1-INCLUIR CLIENTE:\n");
    printf("2-ATENDER CLIENTE:\n");
    printf("3-INCLUIR PRODUTO PARA UM CLIENTE:\n");
    printf("0-SAIR DO PROGAMA:\n");
    scanf("%d",&menu);


    if(menu==1){

        system("cls");
            inserir_cliente(FilaCliente);
                printf("\nCLIENTE INSERIDO COM SUCESSO NA FILA!!!!\n\n");
   }

    if(menu==2){
        system("cls");
            atender_cliente(FilaCliente);
    }

    if(menu==3){

        system("cls");
            incluir_produto(FilaCliente);
    }


    if(menu==0){

        printf("OBRIGADO POR USAR ESTE HUMILDE PROGRAMA S2!!!! \n");

    }

    }while(menu!=0);

    return 0;
}

    void inserir_cliente(Fila_Cliente *FilaCliente){
       char Nome[50];
       int Cod_Cliente;

       Cliente *novoCliente = (Cliente*) calloc(1,sizeof(Cliente));

       printf("DIGITE O NOME DO CLIENTE: ");
        fflush(stdin); // limpa o buffer do teclado:
            scanf("%s",Nome);

       printf("DIGITE O CODIGO DO CLIENTE: ");
        fflush(stdin); // limpa o buffer do teclado:
            scanf("%i",&Cod_Cliente);

       novoCliente ->Cod_Cliente = Cod_Cliente;
            strcpy(novoCliente -> Nome,Nome);
                novoCliente->Prox = FilaCliente->Primeiro;

       if(FilaCliente->Primeiro==NULL){
            FilaCliente->Primeiro = novoCliente;
        }else{
            FilaCliente ->Ultimo->Prox=novoCliente;
        }
            FilaCliente->Qtd_ClientesFila++;
                FilaCliente ->Ultimo=novoCliente;

                printf("\nCLIENTE INSERIDO COM SUCESSO NA FILA");
                printf("\nQUANTIDADE DE CLIENTES NA FILA: = %i\n\n",FilaCliente->Qtd_ClientesFila);
                    system("pause");
                        return;
    }

    void incluir_produto(Fila_Cliente *FilaCliente){
        int aux=1;
            Cliente_temp = FilaCliente->Primeiro;
                Produto *Produto_temp = (Produto*) calloc(1,sizeof(Produto));

        while(aux!=0){
            system("cls");
                printf("ESCOLHA O CLIENTE PARA ADICIONAR PRODUTOS:\n");
                printf("\tNOME DO CLIENTE: %s\n",Cliente_temp->Nome);
                printf("\tCODIGO DO CLIENTE: %i\n\n",Cliente_temp->Cod_Cliente);

                printf("1-SELECIONAR CLIENTE:\n");
                printf("2-PROXIMO CLIENTE\n");
                printf("0-SAIR DA PILHA DE PRODUTOS:\n");
                    scanf("%d",&aux);

            if(aux==1){
                  printf("\n\nINSIRA O NOME DO PRODUTO DESEJADO:");
                    scanf("%s",Produto_temp->Nome);

                  printf("INSIRA O PRECO DO PRODUTO:");
                    scanf("%f",&Produto_temp->Preco);

                  printf("INSIRA A QUANTIDADE DO PRUDUTO:");
                    scanf("%d",&Produto_temp->Quantidade);

                    Produto_temp->Prox=Cliente_temp->PilhaProdutos.Topo;
                    Cliente_temp->PilhaProdutos.Topo=Produto_temp;
                    Cliente_temp ->PilhaProdutos.Qtd_ProdutoPilha++;

              printf("\n\nPRODUTO CADASTRADO COM SUCESSO!");
                  printf("\nQUANTIDADE DE PROTUTOS NO CARRINHO: = %d\n",Cliente_temp->PilhaProdutos.Qtd_ProdutoPilha);
                  system("pause");
                return;
            }
            if(aux==2){
                Cliente_temp = Cliente_temp->Prox;
            }
        }
    }

void atender_cliente(Fila_Cliente *FilaCliente){

    float total = 0;
    Cliente_temp = FilaCliente->Primeiro;

    if(Cliente_temp == NULL){
        printf("\nERRO! FILA VAZIA...!\n\n");
            system("pause");
                return;
    }

    if(Cliente_temp->PilhaProdutos.Topo == NULL){
        printf("\nESTE CLIENTE NAO POSSUI PRODUTO\n");
            system("pause");
                return;

    }else{

    printf("\nNome do Cliente: %s",Cliente_temp->Nome);
    printf("\nCodigo do Cliente: %d",Cliente_temp->Cod_Cliente);

    Produto *Produto_temp;
    Produto_temp = Cliente_temp->PilhaProdutos.Topo;
    do{
        printf("\n\nNOME DO PRODUTO: %s",Cliente_temp->PilhaProdutos.Topo->Nome);
        printf("\nPRECO DO PRODUTO: %.2f",Cliente_temp->PilhaProdutos.Topo->Preco);
        printf("\nQUANTIDADE DO PRODUTO: %d",Cliente_temp->PilhaProdutos.Topo->Quantidade);
        float subtotal = Cliente_temp->PilhaProdutos.Topo->Preco * Cliente_temp->PilhaProdutos.Topo->Quantidade;
        total+=subtotal;

        Cliente_temp->PilhaProdutos.Topo=Cliente_temp->PilhaProdutos.Topo->Prox;
        free(Produto_temp);
        Produto_temp = Cliente_temp->PilhaProdutos.Topo;

    }while(Produto_temp!= NULL);

    printf("\n\n\t TOTAL DA COMPRA = %.2f\n",total);
        system("pause");

    FilaCliente->Primeiro=FilaCliente->Primeiro->Prox;
        free(Cliente_temp);
            FilaCliente->Qtd_ClientesFila--;
                return;
    }
}
