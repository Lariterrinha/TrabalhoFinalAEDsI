#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Chamada de funções do menu
void Compras();
void Venda();
void Taxa();

//_______________________________________________________________________________

// Estruturas
// VEICULO
struct veiculo{
  int preco;
  int ano;
  char marca[50];
  char modelo[50];
  char condicao[50];
  char combustivel[50];
  int odometro;
  int status[50];
  char cambio[50];
  char tamanho[50];
  char tipo[50];
  char cor[50];
};

//MARCA
struct Marca {
  char marca[50];
  float taxa;
};

//_______________________________________________________________________________
int main(void) {
  
  setlocale(LC_ALL,"Portuguese");
  
  int funcionalidade;

  // Escolhe no Menu qual função quer fazer
  do{
    printf("[1] - Compra de Veicúlos\n"
           "[2] - Venda de Veiuculos\n"
           "[3] - Taxas\n"
           "[4] - Alteração de Dados\n"
           "[5] - Filtro de Busca\n"
           "[6] - Relatórios de compras e vendas\n"
           "[0] - Sair\n");
    printf("\nDigite a opção que deseja fazer: ");
    scanf("%d",&funcionalidade);
    system("clear");

    // Menu de funcionalidades do Sistema VRUM VRUM
    switch(funcionalidade){
      
      //[1] - Compra de Veicúlos
      case 1:
        Compra();
        break;

      //[2] - Venda de Veiuculos
      case 2:
        Venda();
        break;

      //[3] - Taxas
      case 3:
        Taxa();
        break;

      //[4] - Alteração de Dados
      case 4:
        AlteracaoDeDados();
        break;

      //[5] - Filtro de Busca
      case 5:
        FiltroDeBusca();
        break;

      //[6] - Relatórios de compras e vendas
      case 6:
        RelatoriosCv();
        break;

      // Padrão
      default:
        break;
    }
    
  }while(funcionalidade != 9 );
  
  return 0;

}

//_______________________________________________________________________________

/******************************************************************************
  Nome: 1 - Compra de Veicúlos
  Entrada: 
  Saida:
  Descrição: *Bloco para realizar a compra de veiuculos ofertados no arquivo veiclos_ofertas.csv
  
             *Sempre que um compra é efetuada os dados do veículo são removidos do arquivo veiculos_oferta.csv
             e adicionados em um arquivo "veiculos_estoque.csv" com o novo preço de venda pretendido

             *Os veículos no arquivo "veiculos_estoque.csv", devem ser mantidos ordenados em ordem alfabética por               marca, e veículos da mesma marca são mantidos ordenados em ordem alfabética por modelo

             *a compra deve ser registrada no histórico de compras da empresa,no arquivo "historico_compras.csv".               Todo registro de compra deve conter data e hora atual.

             *Um arquivo "marcas.csv" deverá ser mantido com as marcas dos veículos em estoque. Além da         
             marca,esse arquivo deve armazenar um valor de taxa aplicável, a partir de 0%, que será aplicado no 
             momento da venda

             *Caso a loja não possua outros veículos da mesma marca em estoque, é necessário adicionar a marca
             no arquivo "marcas.csv".

             *Caso a loja venda o último veículo da marca do estoque, será necessário remover o veículo do                     arquivo "marcas.csv".

             ***(filtro de busca deve ser integrado)***
             
*******************************************************************************/
void Compras(){

  printf("")

}
//_______________________________________________________________________________


