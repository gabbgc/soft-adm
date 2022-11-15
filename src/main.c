#include <stdio.h>
#include <string.h>

struct compra {
    char fornecedor[50];
    char nomeProduto[50];
    int quantidade;
    double valorUnitario;
    int codigoCompra;
};

void CadastrarCompra(struct compra compras[], int nCompra) {
    printf("\n");
    printf("Cadastrar compra.\n");
    printf("Fornecedor : ");
    fflush(stdin);
    scanf("%[^\n]s", &compras[nCompra].fornecedor);
    printf("Nome : ");
    fflush(stdin);
    scanf("%[^\n]s", &compras[nCompra].nomeProduto);
    printf("Quantidade Comprada : ");
    fflush(stdin);
    scanf("%d", &compras[nCompra].quantidade);
    printf("Valor Unitario : ");
    fflush(stdin);
    scanf("%lf", &compras[nCompra].valorUnitario);
    compras[nCompra].codigoCompra = nCompra;
}

void ConfigurarMargem(double *margem) {
    printf("\n");
    printf("Markup Desejado(Margem de Venda, ex: 0.50, 0.40...) : ");
    fflush(stdin);
    scanf("%lf", margem);
}

void QuantidadeEstoque(struct compra compras[], int nCompra) {
    printf("\n");
    struct produto {
        char nome[50];
        int quantidadeDisponivel;
    };
    int contadorProdutos = 0;
    int buffer = 0;
    struct produto produtos[100];
    for(int i = 0; i < nCompra; i++) {
        buffer = 0;
        for(int n = 0; n < contadorProdutos; n++) {
            if(strcmp(compras[i].nomeProduto, produtos[n].nome) == 0) {
                produtos[n].quantidadeDisponivel += compras[i].quantidade;
                buffer = 1;
            }
        }
        if(buffer == 0) {
            for(int z = 0; z < 50; z++) {
                produtos[contadorProdutos].nome[z] = compras[i].nomeProduto[z];
            }
            produtos[contadorProdutos].quantidadeDisponivel = 0;
            produtos[contadorProdutos].quantidadeDisponivel += compras[i].quantidade;
            contadorProdutos++;
        }
    }
    for(int i = 0; i < contadorProdutos; i++) {
        printf("Produto: %s\n", produtos[i].nome);
        printf("Quantidade Disponivel: %d\n", produtos[i].quantidadeDisponivel);
    }
}

void MostrarRelatorios(struct compra compras[], int nCompra) {
    printf("\n");
    int opcao;
    printf("Digite o relatorio desejado.\n");
    printf("[1] - Quantidade Disponivel por produto.\n");
    printf("Opcao : ");
    fflush(stdin);
    scanf("%d", &opcao);
    switch(opcao) {
        case 1:
            QuantidadeEstoque(compras, nCompra);
            break;
        default:
            printf("Opcao invalida, tente novamente.\n");
            break;
    }
}

int main() {
    struct compra compras[100];
    double margem;
    int nCompra = 0;
    int opcao;
    while(1) {
        printf("\n");
        printf("Selecione a opcao desejada.\n");
        printf("[1] - Cadastrar compra.\n");
        printf("[2] - Configurar margem.\n");
        printf("[3] - Relatorios.\n");
        printf("Opcao : ");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:
                CadastrarCompra(compras, nCompra);
                nCompra++;
                break;
            case 2:
                ConfigurarMargem(&margem);
                break;
            case 3:
                MostrarRelatorios(compras, nCompra);
                break;
        }
    }
    return 0;
}