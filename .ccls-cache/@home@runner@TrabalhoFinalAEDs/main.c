#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

// Chamada de funções do menu
void Compras();
void Venda();
void relatorioCv();
void Taxa();
void Backup();
void ordenarArquivoCSV();
void Criabackup();
struct Marca LeMarca();
char *pesquisaMarcaTaxa();
char* pesquisa();
struct veiculo LeVeiculo();
int contalinhas();
void printVeiculo();
struct veiculo Criafiltro();
struct Marca CriafiltroM();
void adicionarLinha();
void adicionarLinhaM();
void removerLinha();
void CadastrarMarca();
void FiltroDeBusca();
void AlteracaoDeDados();
void ordenabarato();
void ordenacaro();
void orenaalfabetico();
void relatorio(float saldo, char datafim,char datacomeco);

//_______________________________________________________________________________

// Estruturas
// VEICULO
struct veiculo{
  char data[20];
  char hora[20];
  float preco;
  float preco_base;
  float preco_venda;
  int ano;
  char marca[50];
  char modelo[50];
  char condicao[50];
  char combustivel[50];
  int odometro;
  char status[50];
  char cambio[50];
  char tamanho[50];
  char tipo[50];
  char cor[50];
  char cliente[50];
  //char data[50];
  time_t data_compra;
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
    printf("\n");
    system("clear");
      
    printf("\n  V   V   rrr   u   u   m   m    V   V   rrr   u   u   m   m\n");
    printf("   V V   r   r  u   u   mm mm     V V   r   r  u   u   mm mm\n");
    printf("    V    rrrr   u   u   m m m      V    rrrr   u   u   m m m\n");
    printf("    v    r  r    uuu    m   m      v    r  r    uuu    m   m\n");
    printf("\n\n");
    
    printf("[1] - Compra de Veiculos\n"              // OK
           "[2] - Venda de Veiuculos\n"              // OK
           "[3] - Alteração de Dados\n"              // OK
           "[4] - Consulta ao Catalogo\n"            // OK
           "[5] - Relatórios de compras e vendas\n"  // OK
           "[6] - Realizar/Apagar Backups\n"         // OK
           "[0] - Sair\n");                          // OK
    printf("\nDigite a opção que deseja fazer: ");
    scanf("%d",&funcionalidade);
    printf("\n");
    system("clear");

    // Menu de funcionalidades do Sistema VRUM VRUM
    switch(funcionalidade){
      
      //[1] - Compra de Veicúlos
      case 1:
       Compras();
        break;

      //[2] - Venda de Veiuculos
      case 2:
        Venda();
        break;

      //[3] - Alteração de Dados
      case 3:
        AlteracaoDeDados();
        break;

      //[4] - Filtro de Busca/consulta ao catalago
      case 4:
        FiltroDeBusca();
        break;

      //[5] - Relatórios de compras e vendas
      case 5:
        relatorioCv();
        break;

      //[6] - Backup
      case 6:
        Backup();
        break;

      /* Debug de função
      case 7:
        ordenarArquivoCSV("veiculos_estoque.csv");
        break;*/
      
      // Padrão
      default:
        break;
    }
    printf("\n");
    system("clear");
    
  }while(funcionalidade != 0 );

  // Mensagem de saida
  printf("\n  V   V   rrr   u   u   m   m    V   V   rrr   u   u   m   m\n");
  printf("   V V   r   r  u   u   mm mm     V V   r   r  u   u   mm mm\n");
  printf("    V    rrrr   u   u   m m m      V    rrrr   u   u   m m m\n");
  printf("    v    r  r    uuu    m   m      v    r  r    uuu    m   m\n");
  printf("\n");
  printf("\t\t ______________________________________\n");
  printf("\t\t|                                      |\n");
  printf("\t\t|   Obrigado por usar nosso sistema!   |\n");
  printf("\t\t|______________________________________|\n");
  return 0;

}

//____________________________________________________________________________

//////////////////////////////////////////////////////////////////////////////
/*
                      FUNÇÕES DO MENU DE COMPRAS
*/
//////////////////////////////////////////////////////////////////////////////


/*****************************************************************************
                       1 - COMPRAS DE VEICULOS
*****************************************************************************/

/*____________________________________________________________________________
  Nome: 1 - Compra de Veicúlos
  Entrada: 
  Saida:
  Descrição:
  
*Bloco para realizar a compra de veiuculos ofertados no arquivo veiclos_ofertas.csv

*Sempre que um compra é efetuada os dados do veículo são removidos do arquivo veiculos_oferta.csv e adicionados em um arquivo "veiculos_estoque.csv" com o novo preço de venda pretendido 

*a compra deve ser registrada no histórico de compras da empresa,no arquivo "historico_compras.csv". Todo registro de compra deve conter data e hora atual.

*Um arquivo "marcas.csv" deverá ser mantido com as marcas dos veículos em estoque. Além da  marca,esse arquivo deve armazenar um valor de taxa aplicável, a partir de 0%, que será aplicado no momento da venda
             
_____________________________________________________________________________*/

void Compras(){

  FILE *estoque = fopen("veiculos_estoque.csv", "a");
  
  char *linha;
  char achou;
  struct veiculo veiculosX;   // veiculo lido
  struct veiculo veiculoF;    // veiculo filtro

  if (estoque == NULL ){
      printf("Erro ao abrir os arquivos de estoque ou histórico de vendas.\n");
      //Espera
      printf("\nPressione qualquer tecla para continuar\n");
      scanf(" %[^\n]",&achou);
      fflush(stdin);
  }
  else{

    printf("\n\t\t ______________________________________\n");
    printf("\t\t|                                      |\n");
    printf("\t\t|   Você entrou no menu de Compras!    |\n");
    printf("\t\t|______________________________________|\n");
    
    // Exibir oque vamos fazer
    printf("\nQual veiculo você procura? \n");

    // Cria um filtro
    veiculoF = Criafiltro();

    // A função retona uma linha do veiculo que o usuario procura (malloc)
    linha = pesquisa(veiculoF,"veiculos_ofertas.csv", 5);

    do{
      // Solicitar ao usuário a escolha do veículo para venda ()
      printf("\nEsse é o veiculo que deseja comprar? (s/n): ");
      scanf(" %c",&achou);
      fflush(stdin);
    }while (achou != 's' && achou != 'n');
  }

  printf("\n");
  system("clear");

  // Prossegue venda
  if(achou == 's'){

    // Extrair informações da linha do arquivo de estoque
    veiculosX = LeVeiculo(linha);

    struct Marca marcaX;

    FILE *arqMarcas = fopen("Marcas.csv", "r");
    char linhamarca[150];

    if (arqMarcas == NULL ) {
      printf("\nErro ao abrir o aqruivo de Marcas.");
      printf("\nNão foi possivel concluir essa transação\n");
      //Espera
      printf("\nPressione qualquer tecla para continuar\n");
      getchar();
      getchar();
      fflush(stdin);
    }
    else{ 
      // "PROCV" de marca que o cliente vai comprar
      while (fgets(linhamarca, 150, arqMarcas) != NULL) {
        marcaX = LeMarca(linhamarca);
        if(strcmp(marcaX.marca,veiculosX.marca) == 0){
          veiculosX.preco_venda = veiculosX.preco_base * (1.0 + marcaX.taxa); // Aplica a taxa      
          break;
        }
        
      }

      // Insere no historico de vendas
      fprintf(estoque, "%0.4f,", veiculosX.preco_venda);
      fprintf(estoque, "%s", 1 + strchr(linha, ','));   // +1 pq a função retorna o ponteiro logo em cima da virgula

      // Apaga no estoque de veiculos
      removerLinha("veiculos_ofertas.csv",linha);

      // Mensagem de venda bem sucedida
      printf("\nVeiculo:");
      printVeiculo(veiculosX,1);
      printf("\nAdicionado ao estoque com sucesso\n"); 
      printf("\nTaxa: %0.4f \t\t Preço para venda: %0.2f\n\n",marcaX.taxa,veiculosX.preco_venda);
      
      FILE *historicoCompras = fopen("historico_compras.csv", "a");

      if (historicoCompras == NULL) {
          printf("Erro ao abrir os arquivos de histórico de compras.\n");
      }
      else{

        // Obtem data da compra        
        time_t agora;
        struct tm *tm_info;
        char data_e_hora[20];

        time(&agora);
        tm_info = localtime(&agora);

        strftime(data_e_hora, 20, "%d/%m/%Y,%H:%M:%S", tm_info);

        // Insere no historico de compras
        fprintf(historicoCompras, "%s,",data_e_hora);
        fprintf(historicoCompras, "%0.3f,", veiculosX.preco_venda);
        fprintf(historicoCompras, "%s", linha); 
      }
      fclose(historicoCompras);

    }

    fclose(arqMarcas);

    free(linha);  
  }
  // Se não achar não tem venda
  else{
    printf("\nNão foi possivel concluir essa transação");
  }

  //Espera
  printf("\nPressione qualquer tecla para continuar\n");
  getchar( );
  getchar( );
  
  fflush(stdin);

  // Fechar os arquivos
  fclose(estoque);
  
}


/*****************************************************************************
                       2 - VENDAS DE VEICULOS
*****************************************************************************/

//____________________________________________________________________________
/*
  Nome: [2] - Venda de veículos
  Entrada: 
  Saida:
  Descrição:

  Seu sistema também deve permitir a venda de veículos. Sempre que uma venda for efetuada, ela deve ser registrada no arquivo historico_vendas.csv e o veículo adquirido deve ser removido do arquivo veiculos_estoque.csv. Todo registro de venda deve conter data e hora atual.

*/

void Venda(){

  // Ordenar arquivo csv
  ordenarArquivoCSV("veiculos_estoque.csv");
  
  FILE *estoque = fopen("veiculos_estoque.csv", "r");
  FILE *historicoVendas = fopen("historico_vendas.csv", "a");

  char *linha;
  char achou;
  struct veiculo veiculosX;
  
  if (estoque == NULL || historicoVendas == NULL) {
      printf("Erro ao abrir os arquivos de estoque ou histórico de vendas.\n");
  }
  else{
    
    // Exibir oque vamos fazer
    printf("\nQual veiculo você procura? \n");

    // Cria um filtro
    struct veiculo veiculoF;
    veiculoF = Criafiltro();

    // A função retona uma linha do veiculo que o usuario procura (malloc)
    linha = pesquisa(veiculoF,"veiculos_estoque.csv", 5);
      
    // Extrair informações da linha do arquivo de estoque
    veiculosX = LeVeiculo(linha);

    do{
      // Solicitar ao usuário a escolha do veículo para venda ()
      printf("\nEsse é seu veiculo? (s/n): ");
      scanf(" %c",&achou);
      fflush(stdin);
    }while (achou != 's' && achou != 'n');
  }

  // Prossegue venda
  if(achou == 's'){
    printf("Qual o nome do cliente? ");
    scanf(" %[^\n]",veiculosX.cliente);
    fflush(stdin);
    
    struct Marca marcaX;
      
    // Obtem data da compra
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    strftime(veiculosX.data, sizeof(veiculosX.data), "%d/%m/%Y", t);
    strftime(veiculosX.hora, sizeof(veiculosX.hora), "%H:%M:%S", t);


    // Insere no historico de vendas
    fprintf(historicoVendas, "%s,", veiculosX.cliente);
    fprintf(historicoVendas, "%s,", veiculosX.data);
    fprintf(historicoVendas, "%s,", veiculosX.hora);
    fprintf(historicoVendas, "%s", linha); 

    // Apaga no estoque de veiculos
    removerLinha("veiculos_estoque.csv",linha);

    // Mensagem de venda bem sucedida
    printf("\nVeiculo:");
    printVeiculo(veiculosX,1);
    printf("\nVendido para %s\n\n",veiculosX.cliente);  
  
  }
  // Se não achar não tem venda
  else{
    printf("\nNão foi possivel concluir essa transação");
  }
  
  //Espera
  printf("\nPressione qualquer tecla para continuar\n");
  getchar();
  getchar( );
  fflush(stdin);

  free(linha);      // Libera oq a função alocou 
  
  // Fechar os arquivos
  fclose(estoque);
  fclose(historicoVendas);
  
}


/*****************************************************************************
                     3 - Alteração de dados
*****************************************************************************/

//____________________________________________________________________________
/*______________________________________________________________________________
Nome: Alteração de Dados
Entrada: 
Saida: 
Descrição: Altera o dado de um determinado carro a qualquer momento apó ser adquirido.
*/

// Cadastro de marca
void CadastrarMarca() {
  
  FILE *arq  = fopen("Marcas.csv", "a");

  struct Marca cadastro;

  if (arq == NULL) {
    perror("Erro ao abrir o arquivo");
  }
  else{
    // Lê a marca que se quer cadastrar
    printf("\nQual a Marca que você quer cadastrar? ");
    scanf(" %s", cadastro.marca);
    fflush(stdin);

    printf("Qual a taxa sobre essa marca? ");
    scanf("%f",&cadastro.taxa);
    fflush(stdin);

    // Coloca no arquivo
    fprintf(arq, "%s", cadastro.marca);
    fprintf(arq, ",");
    fprintf(arq, "%0.4f\n", cadastro.taxa);

    //Operação bem sucedida
    printf("Marca Cadastrada");
    printf("\nPressione qualquer tecla para continuar\n");
    getchar();
    getchar( );
    fflush(stdin);
  }

  fclose(arq);

}
//_________________________________________________________________________________

void AlteracaoDeDados(){
  
  char *Asermod, *Asermod2;
  int op;
  
  struct veiculo veiculoD;
  struct Marca marcaD;
 
 
  do {
    system("clear");
  printf("[1] - Criar Cadastro Marca\n");
  printf("[2] - Alterar Cadastro Veiuculo em Estoque\n");
  printf("[3] - Alterar cadastro Marca\n");
  printf("Escolha o numero da opção que deseja realizar:");
  //scanf("%d",&op);
    if (scanf("%d", &op) != 1) {
      // Limpa o buffer de entrada (para evitar loop infinito)
      while (getchar() != '\n');
      // Informa ao usuário que a entrada foi inválida
      printf("Entrada inválida. Por favor, digite um número.\n");
      // Reinicia o loop
      continue;
    }
  }while(op < 1 || op > 3);

  switch (op){
    case 1:
      CadastrarMarca();
    break;
    
    case 2:
      
      printf("\nVoce escolheu alterar cadastro de um veiculo no estoque,realize a busca do veiculo que deseja alterar os dados: \n");
      veiculoD = Criafiltro();
      
      // Ordenar arquivo csv
      ordenarArquivoCSV("veiculos_estoque.csv");
      
      Asermod = pesquisa(veiculoD,"veiculos_estoque.csv",5); //acha o veiculo do estoque e armarmzena a linha em asermod
      struct veiculo VeiculoA = LeVeiculo(Asermod);//coloca veiculo em uma struc
      int opcao;
      do{
        system("clear");
        printf("\nSelecione o campo que você gostaria de modificar:\n");
        printf("1. preço\n");
        printf("2. Ano\n");
        printf("3. Marca\n");
        printf("4. Modelo\n");
        printf("5. condição\n");
        printf("6. combustivel\n");
        printf("7. odometro\n");
        printf("8. status\n");
        printf("9. cambio\n");
        printf("10. tamanho\n");
        printf("11. tipo\n");
        printf("12. cor\n");
      //removerLinha("veiculos_estoque.csv",Asermod);
      
      printf("\n Opção: ");
        if (scanf("%d", &opcao) != 1) {
          // Limpa o buffer de entrada (para evitar loop infinito)
          while (getchar() != '\n');
          // Informa ao usuário que a entrada foi inválida
          printf("Entrada inválida. Por favor, digite um número.\n");
          // Reinicia o loop
          continue;
        }
      }while(opcao < 1 || opcao > 12);
      //int opcao;
      //scanf("%d", &opcao);

      switch(opcao) {//caso o usuario escolha qual campo quer alterar
         case 1:
          printf("Digite o novo preço: ");
          int precoInteiro;
          scanf("%d", &precoInteiro);
          VeiculoA.preco_base = (float)precoInteiro;
        break;
        case 2:
          printf("Digite o novo ano: ");
          scanf("%d", &VeiculoA.ano);
          fflush(stdin);
        break;
        case 3:
          printf("Digite a nova marca: ");
          scanf(" %s", VeiculoA.marca);
          fflush(stdin);
        break;
        case 4:
          printf("Digite o novo modelo: ");
          scanf(" %s", VeiculoA.modelo);
          fflush(stdin);
        break;
        case 5:
          printf("Digite a nova condição: ");
          scanf(" %s", VeiculoA.condicao);
          fflush(stdin);
        break;
        case 6:
          printf("Digite o novo tipo de combustível: ");
          scanf(" %s", VeiculoA.combustivel);
          fflush(stdin);
        break;
        case 7:
          printf("Digite a nova leitura do odômetro: ");
          scanf("%d", &VeiculoA.odometro);
          fflush(stdin);
        break;
        case 8:
          printf("Digite o novo status: ");
          scanf(" %s", VeiculoA.status);
          fflush(stdin);
        break;
        case 9:
          printf("Digite o novo tipo de câmbio: ");
          scanf(" %s", VeiculoA.cambio);
          fflush(stdin);
        break;
        case 10:
          printf("Digite o novo tamanho: ");
          scanf(" %s", VeiculoA.tamanho);
          fflush(stdin);
        break;
        case 11:
          printf("Digite o novo tipo: ");
          scanf(" %s", VeiculoA.tipo);
          fflush(stdin);
          break;
        case 12:
          printf("Digite a nova cor: ");
          scanf(" %s", VeiculoA.cor);
          fflush(stdin);
        break;
        default:
          printf("Opção inválida.\n");
        break;
      }
      adicionarLinha("veiculos_estoque.csv",VeiculoA);//adiciona o veiculo alterado no arquivo
      removerLinha("veiculos_estoque.csv",Asermod);
    break;
    
    case 3:
      
      marcaD = CriafiltroM();
      Asermod2 = pesquisaMarcaTaxa(marcaD,"Marcas.csv",1);
      struct Marca marcaA = LeMarca(Asermod2);

      int opcao2;
      do {
        system("clear");
        printf("\nSelecione o campo que você gostaria de modificar:\n");
        printf("1. marca\n");
        printf("2. taxa\n");
        if (scanf("%d", &opcao2) != 1) {
            // Limpa o buffer de entrada (para evitar loop infinito)
            while (getchar() != '\n');
            // Informa ao usuário que a entrada foi inválida
            printf("Entrada inválida. Por favor, digite um número.\n");
            // Reinicia o loop
            continue;
        }
      } while (opcao2 < 1 || opcao2 > 2);
      //int opcao2;
      //scanf("%d", &opcao2);

      switch(opcao2) {
        case 1:
          printf("Digite a marca: ");              
          scanf(" %s", marcaA.marca); 
          fflush(stdin);
          break;
        case 2:
          printf("Digite a taxa: ");
          scanf("%f", &marcaA.taxa);
          fflush(stdin);
        break;
        default:
        break;
      }
      removerLinha("Marcas.csv",Asermod2);
      adicionarLinhaM("Marcas.csv",marcaA); //adiciona a marca alterada no arquivo
      //removerLinha("Marcas.csv",Asermod2);
    break;
  }
  
}

/*****************************************************************************
                       4 - FILTRO DE BUSCAS - colsulta ao catalogo
*****************************************************************************/

//____________________________________________________________________________
/*
  Nome: [4] - Filtro de buscas / colslta ao catologo
  Entrada: 
  Saida:
  Descrição:
      Faz uma consulta ao catalogo escolhido pelo usuario
      Inclui filtros de marca, preço etc.
*/
void FiltroDeBusca(){
  
  int opcao;

  printf("\nQual arquivo você desejá ver o catalogo?");
  printf("\n[1] - Estoque de Veiculos");
  printf("\n[2] - Oferta de Veiculos");

  do{
    printf("\n\nQual sua opção: ");
    scanf("%d",&opcao);
  }while((opcao < 1) || (opcao > 2));

  struct veiculo veiculoF;
  veiculoF = Criafiltro();
  
  switch(opcao){
    case 1:
      pesquisa(veiculoF,"veiculos_estoque.csv",10);
      break;

    case 2:
      pesquisa(veiculoF,"veiculos_ofertas.csv",10);
      break;

    default:
      break;
  }
  
  printf("\nObrigado por consultar nosso catalogo\n");
  //Espera
  printf("\nPressione qualquer tecla para continuar\n");
  getchar();
  getchar( );
  fflush(stdin);
  
}
/*****************************************************************************
                             5 - Relatorio de Compra e Venda
*****************************************************************************/

void verelatorio(struct veiculo veiculo, float saldo, FILE *relatorio_file) {
  
  fprintf(relatorio_file, "Data: %s\n", veiculo.data);
  fprintf(relatorio_file, "Hora: %s\n", veiculo.hora);
  fprintf(relatorio_file, "Veículo: %s %s\n", veiculo.marca, veiculo.modelo);
  fprintf(relatorio_file, "Ano: %d\n", veiculo.ano);
  fprintf(relatorio_file, "Preço de Venda: %.2f\n", veiculo.preco_venda);
  fprintf(relatorio_file, "Saldo até agora: %.2f\n\n", saldo);
}//imprime o relatorio em um arquivo

void relatorioCv() {
  
  float saldo_final = 0;
  int op;
  do{
    system("clear");
    printf("[1] - Histórico de Compras\n");
    printf("[2] - Histórico de Vendas\n");
    printf("\nQual arquivo você deseja ver o relatório? ");
    if (scanf("%d", &op) != 1) {
        // Limpa o buffer de entrada (para evitar loop infinito)
        while (getchar() != '\n');
        // Informa ao usuário que a entrada foi inválida
        printf("Entrada inválida. Por favor, digite um número.\n");
        // Reinicia o loop
        continue;
    }
  }while(op < 1 || op > 2);
  //scanf("%d", &op);

  system("clear");
  
  FILE *file;
  if (op == 1) {
    file = fopen("historico_compras.csv", "r");
    } else if (op == 2) {
      file = fopen("historico_vendas.csv", "r");
    }

  if (file == NULL) {
     printf("Erro ao abrir o arquivo.\n");
    return;
  }

  struct veiculo veiculo;
  char linha[1024];
  char data_inicio_str[20], data_fim_str[20];

  // Solicitar ao usuário que insira as datas de início e fim
  printf("Digite a data de início (dd/mm/yyyy): ");
  scanf(" %s", data_inicio_str);
  fflush(stdin);
  printf("Digite a data de fim (dd/mm/yyyy): ");
  scanf(" %s", data_fim_str);
  fflush(stdin);

  int op_relatorio;
  do{
    system("clear");
    printf("Você deseja exibir o relatório na tela ou escrever em um arquivo?\n");
    printf("[1] - Exibir na tela\n");
    printf("[2] - Escrever em um arquivo\n");
    printf("Digite o numero da opção que deseja: ");
    if (scanf("%d", &op_relatorio) != 1) {
        // Limpa o buffer de entrada (para evitar loop infinito)
        while (getchar() != '\n');
        // Informa ao usuário que a entrada foi inválida
        printf("Entrada inválida. Por favor, digite um número.\n");
        // Reinicia o loop
        continue;
    }
  }while(op_relatorio < 1 || op_relatorio > 2);
  //scanf("%d", &op_relatorio);
  system("clear");

  FILE *relatorio_file;
  if (op_relatorio == 1) {
     relatorio_file = stdout;  // stdout é o "arquivo" da saída padrão, que é a tela
  } else {
     relatorio_file = fopen("relatorio.txt", "w");
    if (relatorio_file == NULL) {
       printf("Erro ao abrir o arquivo de relatório.\n");
       return;
    }
  }

  while (fgets(linha, sizeof(linha), file)) {
    if (op == 1) {
    sscanf(linha, "%[^,],%[^,],%f,%f,%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,]",
    veiculo.data, veiculo.hora, &veiculo.preco_venda, &veiculo.preco, &veiculo.ano, veiculo.marca, veiculo.modelo,
    veiculo.condicao, veiculo.combustivel, &veiculo.odometro, veiculo.status, veiculo.cambio,
    veiculo.tamanho, veiculo.tipo, veiculo.cor);
    } else if (op == 2) {
      sscanf(linha, "%[^,],%[^,],%[^,],%f,%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,]",
      veiculo.cliente, veiculo.data, veiculo.hora, &veiculo.preco_venda, &veiculo.ano, veiculo.marca, veiculo.modelo,
      veiculo.condicao, veiculo.combustivel, &veiculo.odometro, veiculo.status, veiculo.cambio,
      veiculo.tamanho, veiculo.tipo, veiculo.cor);
    }// Lê a linha do arquivo e armazena os dados em uma estrutura veiculo

    // Verificar se a data do veículo está dentro do intervalo de datas
    if (strcmp(veiculo.data, data_inicio_str) >= 0 && strcmp(veiculo.data, data_fim_str) <= 0) {
    // Calcular o saldo final
    if (op == 1) {
      saldo_final += veiculo.preco_venda - veiculo.preco;
    } else {
      saldo_final += veiculo.preco_venda;
    }

    // Chamar a função verelatorio para cada veículo que corresponda ao intervalo de datas
    verelatorio(veiculo, saldo_final, relatorio_file);
    }
  }

  fclose(file);
  if (op_relatorio == 2) {
    fclose(relatorio_file);
  }
  printf("Digite qualquer tecla para sair>>\n");
  getchar();
  getchar();
}

/*****************************************************************************
                             6 - Backups
*****************************************************************************/

/*____________________________________________________________________________
Nome: 7 - Backup
Entrada: -
Saida: -
Descrição:

2.8 Backup
Para proteger os dados de eventuais falhas, o programa deve efetuar um backup de todos os arquivos em formato binários quando solicitado pelos usuários, em uma subpasta chamada “backup”. O programa deverá também permitir a exclusão dos arquivos de backup.
*/
void Backup(){

  int opcao;
  
  printf("\nVocê deseja criar ou apagar o backup?");
  printf("\n[1] - Criar");
  printf("\n[2] - Apagar");

  do{
    printf("\n\nQual sua opção: ");
    scanf("%d",&opcao);
  }while((opcao < 1) || (opcao > 2));

  switch(opcao){
    case 1:
      Criabackup("veiculos_ofertas",".csv");  // Backup da oferta de veiculos
      Criabackup("veiculos_estoque",".csv"); 
      Criabackup("historico_vendas",".csv");
      Criabackup("historico_compras",".csv");  
      break;
    
    case 2:
      // funcao que remove um arquivo 
      remove("Backup/veiculos_ofertas_backup.bin");
      remove("Backup/veiculos_estoque_backup.bin");
      remove("Backup/historico_vendas_backup.bin");
      remove("Backup/historico_compras_backup.bin");
      break;

    default:
      break;
  }
}

/*______________________________________________________________________________
Nome: Cria Backup
Entrada: vetor de caracteres com o nome do arquivo e vetor com a extensão
Saida: backup do arquivo na pasta "backup"
Descrição: Cria um backup
*/
void Criabackup(char nome[50], char extensao[5]){

  //Cria pasta de backup se não existir
  //mkdir("Backup", 0777);
 
  // Cria String com nome do arquivo e nome copia
  char nome_arq[55];
  strcpy(nome_arq, nome);
  strcat(nome_arq,extensao);
  
  char nome_arq_copia[55] = "Backup/";
  strcat(nome_arq_copia, nome);
  strcat(nome_arq_copia,"_backup");
  strcat(nome_arq_copia,".bin");

  // Leitura de uma linha (variavel auxiliar)
  char linha[150];

  // arquivos
  FILE *arq = fopen(nome_arq,"r");               // Arquivo original
  FILE *arqcopia = fopen(nome_arq_copia,"w");    // backup

  // Se o arquivo tiver aberto corretamente faz o backup
  if(arq == NULL){
    printf("\nERRO AO ABRIR ARQUIVOS");
  }
  else{
    while(fgets(linha,150,arq) != NULL){
      fwrite(linha,1,strlen(linha),arqcopia);
    }
  }
  fclose(arq);
  fclose(arqcopia);

}

  
/*****************************************************************************
                          FUNÇÔES AUXILIARES
*****************************************************************************/
/*____________________________________________________________________________
  Nome: Conta linhas
  Descrição: conta as linhas de um arquivo (já aberto)
  
*/
int contalinhas(char *nome){
  FILE * arq = fopen(nome,"r");
  char linha[500];
  int cont=0;
  if(arq == NULL){
    printf("Erro ao contar linhas");
  }
  else{
    while (fgets(linha, sizeof(linha),arq) != NULL) {
      cont++;
    }
  }
  fclose(arq);
  return cont;
}
/*
  Nome: ordena csv
  Descrição:
    Ordena um arquivo csv de carros (estoque ou) 
  Sempre que uma busca é realizada no sistema, os resultados encontrados devem ser exibidos em uma ordem específica.
  No caso de compras e vendas de veículos, deve-se ter uma opção para ordenar pelo
  (a) veículo mais barato,
  (b) veículo mais caro ou 
  (c) ordenado por marca e modelo em ordem alfabética
  (ignorando maiúsculas e minúsculas), em que veículos da mesma marca são ordenados pelo modelo
*/
void ordenarArquivoCSV(const char *nomearq){

  // Escolhe opcao de ordenação
  int opcao;
  printf("\nComo você deseja ordenar essa arquivo? ");
  do{
    printf("\n\t[1] - Veiculo mais barato");
    printf("\n\t[2] - Veiculo mais caro");
    printf("\n\t[3] - Ordenar por marca");
    printf("\n\nOpção: ");
    scanf("%d",&opcao);
  }while(opcao<1 || opcao>3);

  // Conta numero de linha no arquivo
  int numlinhas = contalinhas(nomearq) - 1; // -1 do cabeçalho  
  struct veiculo veiculos[numlinhas];
  
  FILE * arq = fopen(nomearq,"r");
  FILE * arqTemp = fopen("temporario.txt", "w");
  
  if (arq == NULL || arqTemp == NULL) {
    perror("Erro ao abrir o arquivo");      // perro mostra qual foi o erro
    remove("temporario.txt");
    fclose(arqTemp);

    printf("Digite qualquer tecla para sair>>\n");
    getchar();
    getchar();
  }
  else{

    char linha[150]; 

    // Obtem cabeçalho
    fgets(linha, sizeof(linha), arq);   
    char cabecalho[150];
    strcpy(cabecalho,linha);
    
    // Lê todos as linhas e coloca na struct
    for(int i = 0; i<numlinhas; i++){
      fgets(linha, sizeof(linha), arq);
      veiculos[i] = LeVeiculo(linha); 
    }
    
    // Ordena de acordo com a opcao:
    switch(opcao){

      // [1] - Veiculo mais barato
      case 1:
        ordenabarato(numlinhas,veiculos);
        break;
          
      // [2] - Veiculo mais caro
      case 2:
        ordenacaro(numlinhas,veiculos);
        break;

      // [3] - Ordenar por marca
      case 3:
        orenaalfabetico(numlinhas,veiculos);
        break;
      
      default:
        break;
      
    }
    // Poe tudo no arquivo temporário
    fprintf(arqTemp,"%s",cabecalho);  // cabecalho
    fclose(arqTemp);
    
    for(int i = 0; i<numlinhas; i++){
      adicionarLinha("temporario.txt",veiculos[i]);
    }
    
    // Arquivo renomeado para o nome o atual + exclui o atual
    remove(nomearq);
    rename("temporario.txt", nomearq);
  }

  fclose(arq);
  
}
/*____________________________________________________________________________
  Nome: Remover linhas
  Entradas: nome de um arquivo e a linha que quer remover(*char) 
  saidas: 
  Descrição: abre um arquivo e remove uma linha
      O pricipio de funcionamento é criar um arquvio temporário e copiar pra ele tod
*/
void removerLinha(char *nomeArquivo, char *linharemover) {
  FILE *arquivoOrig = fopen(nomeArquivo, "r");
  FILE *arquivoTemp = fopen("temporario.txt", "w");

  if (arquivoOrig == NULL || arquivoTemp == NULL) {
    perror("Erro ao abrir o arquivo");      // perro mostra qual foi o erro
   }
  else{

    char linhax[150]; 
  
    // fprintf em todas as linha menos na que quer remover
    while (fgets(linhax, sizeof(linhax), arquivoOrig) != NULL) {
        if (strcmp(linhax, linharemover) != 0) {
            fprintf(arquivoTemp, "%s", linhax);
        }
    }

    // Arquivo renomeado para o nome o atual + exclui o atual
    remove(nomeArquivo);
    rename("temporario.txt", nomeArquivo);
  }

  fclose(arquivoOrig);
  fclose(arquivoTemp);

}

//____________________________________________________________________________

/*****************************************************************************
                          FUNÇÔES PARA VEICULOS  E MARCAS
*****************************************************************************/

/*____________________________________________________________________________
    Nome: Le um veiculo
    saida: Strct veiculo
    entrada: String de caracteres
    descrião: Desmembra a string em uma struct (separador -> ",")

    // preco, ano, marca, modelo, condicao, combustivel, odometro, status, cambio, tamanho, tipo, cor
  */
  struct veiculo LeVeiculo(char linha[150]){

    char linhabackup[150];
    strcpy(linhabackup,linha);
    
    struct veiculo veiculoX;

    veiculoX.preco_base = atof(strtok(linha,","));
    veiculoX.ano = atoi(strtok(NULL,","));
    strcpy(veiculoX.marca, strtok(NULL,","));
    strcpy(veiculoX.modelo, strtok(NULL,","));
    strcpy(veiculoX.condicao, strtok(NULL,","));
    strcpy(veiculoX.combustivel, strtok(NULL,","));
    veiculoX.odometro = atoi(strtok(NULL,","));
    strcpy(veiculoX.status, strtok(NULL,","));
    strcpy(veiculoX.cambio, strtok(NULL,","));
    strcpy(veiculoX.tamanho, strtok(NULL,","));
    strcpy(veiculoX.tipo, strtok(NULL,","));
    strcpy(veiculoX.cor, strtok(NULL,","));
      
  
    // Dez faz oq o strok fez (subistitui vitgula por /000)
    strcpy(linha,linhabackup);

    return veiculoX;
  }

//____________________________________________________________________________

/*____________________________________________________________________________
  Nome: Print veiculo
  Saida: Print no console 
  entrada: Struct veiculo e flag se quer cabeçalho ou não
  descrião: Printa um veiculo no console

  // preco, ano, marca, modelo, condicao, combustivel, odometro, status, cambio, tamanho, tipo, cor
*/
void printVeiculo(struct veiculo veiculoX, int cabecalho){
  
  // IMprime cabeçalho se solicitado
  if(cabecalho == 1){
    printf("\n\n");
    printf("------------------------------------------------\n");
    printf("      Marca |  Modelo |  Ano  | Preço | Cor \n");
    printf("------------------------------------------------\n\n");

  }
  // Exibir informações do veículo
  printf("[%d] - %s | %s | %d | %.2f | %s \n", cabecalho ,veiculoX.marca, veiculoX.modelo, veiculoX.ano, veiculoX.preco_base, veiculoX.cor);

}
/*____________________________________________________________________________
  Nome: Print marcas
  Saida: Print no console 
  entrada: Struct marcas e flag se quer cabeçalho ou não
  descrião: Printa uma marca no console

  // marca,taxa
*/
void printMarcas(struct Marca marcaX, int cabecalho){

  // IMprime cabeçalho se solicitado
  if(cabecalho == 1){
    printf("\n\n----------------------------------------------------------\n");
    printf("  Marca |  taxa \n");
    printf("----------------------------------------------------------\n\n");

  }
  // Exibir informações do veículo
  printf(" %s | %.4f \n", marcaX.marca, marcaX.taxa);

}

/*____________________________________________________________________________
    Nome: Pesquisa veiculo
    Entrada: Struct veiculo do filtro, nome do arquivo
    Saida: Console + retorna a ultima linha lida 
    Descrição: pesquisa uma struct veiculo em um arquivo

*/
char *pesquisa(struct veiculo veiculoF,char nome[50], int num_veiculos){


  FILE *arqC = fopen(nome, "r");
  char *linha = (char*)malloc(sizeof(char)*150);   // Linha lida (retorno)
  char linharesposta[num_veiculos][150];           // opcoes para escolher
  
  struct veiculo veiculoX;                // Linha lida em struct
  int cont = 0;                           // Contador para exibir numero de veiculos
  char continua;                          // Para ou continua (s/n)
  
  if(arqC == NULL){
      perror("Erro ao abrir o arquivo.");
  } else {
    
    fgets(linha,150,arqC);    // Pula primeira linha cabeçalho

    // Enquanto a linha não estiver vazia e não estiver no final do arquivo
    while (fgets(linha,150,arqC) != NULL ) {
              
      // Lê um veiculo
      veiculoX = LeVeiculo(linha);
      
      // Se estiver no filtro ele imprime
      if (((strcmp(veiculoF.marca ,"")  ==  0) || strcmp(veiculoF.marca, veiculoX.marca) == 0) && (veiculoF.ano == 0 || veiculoF.ano == veiculoX.ano) && (veiculoX.preco_base <= veiculoF.preco_base) && linha != NULL) {

        // Copia a linha para o vetor de opcoes para escolha
        strcpy(linharesposta[cont], linha);
        
        // Imprime um veiculo
        printVeiculo(veiculoX,cont+1);
        printf("\n");
        cont++;
      }
      if(cont >= num_veiculos){
        do{
          printf("\n\nDeseja ver mais? (s/n): ");        
          scanf(" %c",&continua);
          fflush(stdin);
        }while (continua != 's' && continua != 'n');
      
        if (continua == 's' || continua == 'S' ){
          cont = 0;
          // Limpa a tela pra não poluir
          printf("\n");
          system("clear");
        }
        else{
          break;
        }

      }
    }
  
    printf("\nFim do catalogo\n\n");
    
    printf("\n\nQual seu veiculo? ");        
    scanf("%d",&cont);
    cont--;                        // Indice do veiculo que o cliente quer
    strcpy(linha,linharesposta[cont]);  // envia o carro selecionado pra resposta
    
    
  }
  fclose(arqC);
  return linha;
}
//____________________________________________________________________________

/*____________________________________________________________________________
      Nome: Cria filtro
      Entrada: -
      Saida: Struct veiculo 
      Descrição: cria uma struct com base nas informações do usuario

*/
struct veiculo Criafiltro(){

  // Escolha (s ou n) variavei auxiliar
  char escolha;

  // veiculo filtro a ser retornada
  struct veiculo veiculoX;

  printf("\n\n");

  // Recebe valores e cria a struct
  printf("Deseja filtrar por marca? (s/n): ");
  scanf(" %c", &escolha);
  fflush(stdin);
  if (escolha == 's' || escolha == 'S') {
    printf("Digite a marca: ");
    scanf(" %[^\n]", veiculoX.marca);
    fflush(stdin);
  } else {
    strcpy(veiculoX.marca,"");    // caracter nulo
  }

  printf("Deseja filtrar por preço? (s/n): ");
  scanf(" %c", &escolha);
  fflush(stdin);
  if (escolha == 's' || escolha == 'S') {
    printf("Digite o maior valor que você que pagar: ");
    scanf("%f", &veiculoX.preco_base);
    fflush(stdin);
  } else {
    veiculoX.preco_base = 9999999;
  }

  printf("Deseja filtrar por ano? (s/n): ");
  scanf(" %c", &escolha);
  fflush(stdin);
  if (escolha == 's' || escolha == 'S') {
    printf("Digite o ano: ");
    scanf("%d", &veiculoX.ano);
    fflush(stdin);
  } else {
    veiculoX.ano = 0;
  }

  return veiculoX;
}
/*____________________________________________________________________________
    Nome: Pesquisa marca taxa
    Entrada: Struct veiculo do filtro, nome do arquivo
    Saida: Console + retorna a ultima linha lida 
    Descrição: pesquisa uma struct veiculo em um arquivo

*/
char *pesquisaMarcaTaxa(struct Marca marcas,char nome[50], int num_veiculos){

  FILE *arqC = fopen(nome, "r");
  char *linha = (char*)malloc(sizeof(char)*150);        // Linha lida (retorno)

  if(arqC == NULL){
      perror("Erro ao abrir o arquivo.");
  } else {

    struct Marca marcaX;    // Linha lida em struct
    int cont = 1;               // Contador para exibir numero de veiculos
    char continua;              // Para ou continua (s/n)

    while ((fgets(linha,150,arqC) != NULL)) {

      // Lê um veiculo
      marcaX = LeMarca(linha);

      // Se estiver no filtro ele imprime
      if (((strcmp(marcas.marca ,"")  ==  0) || strcmp(marcas.marca, marcaX.marca) == 0) && (marcaX.taxa <= marcas.taxa)) {

        // Imprime um veiculo
        printMarcas(marcaX,cont);
        printf("\n");
        cont++;
      }

      if(cont > num_veiculos){
        printf("\n\nDeseja ver mais? (s/n): ");        
        scanf(" %c",&continua);
        fflush(stdin);
        if (continua == 's'){
          cont = 1;

          // Limpa a tela pra não poluir
          printf("\n");
          system("clear");

        }
        else{
          break;
        }
      }
    }
  }
  fclose(arqC);
  return linha;
}
/*____________________________________________________________________________
      Nome: CriafiltroM
      Entrada: -
      Saida: Struct marca
      Descrição: cria uma struct com base nas informações do usuario

*/
struct Marca CriafiltroM(){

  // Escolha (s ou n) variavei auxiliar
  char escolha;

  // veiculo filtro a ser retornada
  struct Marca marcaX;

  printf("\n\n");

  // Recebe valores e cria a struct
  do{
    system("clear");
    printf("Deseja filtrar por marca? (s/n): ");
    scanf(" %c", &escolha);
    fflush(stdin);
  }while(escolha != 's' && escolha != 'S' && escolha != 'n');
  if (escolha == 's' || escolha == 'S') {
    printf("Digite a marca: ");
    scanf(" %[^\n]", marcaX.marca);
    fflush(stdin);
  } else {
    strcpy(marcaX.marca,"");    // caracter nulo
  }

  do{
    system("clear");
    printf("Deseja filtrar por taxa? (s/n): ");
    scanf(" %c", &escolha);
    fflush(stdin);
  }while(escolha != 's' && escolha != 'S' && escolha != 'n');
  if (escolha == 's' || escolha == 'S') {
    printf("Digite a maior taxa que você quer pagar: ");
    scanf("%f", &marcaX.taxa);
    fflush(stdin);
  } else {
    marcaX.taxa = 9999999;
  }
  return marcaX;
}

//____________________________________________________________________________________

/*____________________________________________________________________________
  Nome: Le uma Marca
  saida: Strct Marca
  entrada: String de caracteres
  descrião: Desmembra a string em uma struct (separador -> ",")
*/
struct Marca LeMarca(char linha[150]){


  char linhabackup[150];
  strcpy(linhabackup,linha);

  struct Marca marcaX;

  // Pega informacoes
  strcpy(marcaX.marca,strtok(linha,","));    // Marca
  marcaX.taxa = atof(strtok(NULL,","));      // Taxa

  // Dez faz oq o strok fez (subistitui virgula por /000)
  strcpy(linha,linhabackup);

  return marcaX;
}


/*____________________________________________________________________________
  Nome: Adiciona Linha structh veiculo
  Descrição: Adiciona um veiculo ao final de uma linha
*/
void adicionarLinha(char *nomeArquivo, struct veiculo veiculo) {
    FILE *arquivo = fopen(nomeArquivo, "a"); // abre o arquivo em modo de anexação

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo %s.\n", nomeArquivo);
    } else {

      // escreve as informações do veículo no arquivo
      fprintf(arquivo, "%0.4f,%d,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s", 
      veiculo.preco_base, 
      veiculo.ano, 
      veiculo.marca, 
      veiculo.modelo, 
      veiculo.condicao, 
      veiculo.combustivel, 
      veiculo.odometro, 
      veiculo.status, 
      veiculo.cambio, 
      veiculo.tamanho, 
      veiculo.tipo, 
      veiculo.cor);
    }

    fclose(arquivo); // fecha o arquivo
}
/*____________________________________________________________________________
  Nome: Adiciona Linhas Marca
  Descrição: Adiciona linha como dados da marca
*/
void adicionarLinhaM(char *nomeArquivo, struct Marca marcas){

   FILE *arquivo = fopen(nomeArquivo, "a");
  if (arquivo == NULL) {
      printf("Não foi possível abrir o arquivo %s.\n", nomeArquivo);
  } else {

    // escreve as informações do veículo no arquivo
    fprintf(arquivo, "%s,%0.4f\n", marcas.marca, marcas.taxa);
  }
  fclose(arquivo);

}

/*____________________________________________________________________________
  Nome: Algoritimo de ordenação
  Descrição: ordena uma structh veiculo do mais barato pro mais caro
*/
void ordenabarato(int numlinhas,struct veiculo veiculos[numlinhas]){
  int ordenado = 0;             // Flag ordenado
  
  while(ordenado != 1){         // Continua repetendo até que não haja nenuma alteração
    ordenado = 1;               // OK tá ordenado
    for(int i = 0;i < (numlinhas-1); i++){

      // Se o veiculo lido agora for maior que o proximo troca eles de lugar
      if (veiculos[i].preco_base > veiculos[i + 1].preco_base) {      
        // Troca os elementos se estiverem fora de ordem
        struct veiculo temp = veiculos[i];
        veiculos[i] = veiculos[i + 1];
        veiculos[i + 1] = temp;
        ordenado = 0;            // Opa, não tá ordenado
      }
    }    
  }
}

/*____________________________________________________________________________
  Nome: Algoritimo de ordenação
  Descrição: ordena uma structh veiculo do mais caro pro mais barato
*/
  
void ordenacaro(int numlinhas,struct veiculo veiculos[numlinhas]){
  int ordenado = 0;             // Flag ordenado

  while(ordenado != 1){         // Continua repetendo até que não haja nenuma alteração
    ordenado = 1;               // OK tá ordenado
    for(int i = 0;i < (numlinhas-1); i++){

      // Se o veiculo lido agora for maior que o proximo troca eles de lugar
      if (veiculos[i].preco_base < veiculos[i + 1].preco_base) {      
        // Troca os elementos se estiverem fora de ordem
        struct veiculo temp = veiculos[i];
        veiculos[i] = veiculos[i + 1];
        veiculos[i + 1] = temp;
        ordenado = 0;            // Opa, não tá ordenado
      }
    }    
  }
}
  
  /*____________________________________________________________________________
    Nome: Algoritimo de ordenação
    Descrição: ordena uma structh veiculo em ordem alfabetica
  */

void orenaalfabetico(int numlinhas,struct veiculo veiculos[numlinhas]){
  int ordenado = 0;             // Flag ordenado

  while(ordenado != 1){         // Continua repetendo até que não haja nenuma alteração
    ordenado = 1;               // OK tá ordenado
    for(int i = 0;i < (numlinhas-1); i++){

      // Se o veiculo lido agora for maior que o proximo troca eles de lugar
      if (strcmp(veiculos[i].marca,veiculos[i + 1].marca) > 0) {      
        // Troca os elementos se estiverem fora de ordem
        struct veiculo temp = veiculos[i];
        veiculos[i] = veiculos[i + 1];
        veiculos[i + 1] = temp;
        ordenado = 0;            // Opa, não tá ordenado
      }
    }    
  }
}
  