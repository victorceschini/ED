#include <stdio.h>
#include <stdlib.h>  //usado system
#include <ctype.h>   //usado toupper
#include <string.h>  //usado strcmp

struct TpPedido{
    char cliente[20];      // Nome do cliente
    char produto[20];
    int quantidade;  
    float valor_original;  // Valor de compra do fornecedor
    float valor_revenda;   // Valor da revenda
    char codigo[20];       // Codigo do pedido
    int status;            // 0 se ja foi vendido, 1 caso contrario
  };

typedef struct TpPedido TpPEDIDO;

TpPEDIDO RgPedido;

FILE *ArqShip;

long int Tamanho = sizeof(RgPedido);

void Incluir() 
{
  char R;
  do
  {
    TpPEDIDO RgPedido_temp;
    system("cls");
    printf("*** inclusao ***\n\n");

    printf("Codigo do pedido a ser registrado: ");
    scanf(" %s", &RgPedido_temp.codigo);

    fseek(ArqShip,0,0);
    int Achou=0;
    do 
    {
	      fread(&RgPedido,Tamanho,1,ArqShip);
	      if (strcmp(RgPedido.codigo,RgPedido_temp.codigo) == 0 && (RgPedido.status != 0))
        {
	          Achou=1;
        }
    }
  while (!feof(ArqShip)&&(Achou==0));

  if (Achou==0)
  {
    printf("Sem problemas de repeticao!, insira os dados:\n");
    printf("Nome do Cliente: ");
    scanf(" %s", &RgPedido_temp.cliente);
    printf("Produto: ");
    scanf(" %s", &RgPedido_temp.produto);
    printf("Quantidade: ");
    scanf("%d", &RgPedido_temp.quantidade);
    printf("Valor original do produto: ");
    scanf("%f", &RgPedido_temp.valor_original);
    printf("Valor de revenda: ");
    scanf("%f", &RgPedido_temp.valor_revenda);
    RgPedido.status = 1;

    fseek(ArqShip,0,2);
    fwrite(&RgPedido_temp,Tamanho,1,ArqShip);
    printf("\nNova inclusao? S/N ");
    scanf(" %c",&R);
    R=toupper(R);
  }
  else
  {
    printf("O codigo dessa compra ja esta presente no arquivo...");
    printf("\nNova inclusao? S/N ");
    scanf(" %c",&R);
    R = toupper(R);
  }
  }
  while (R != 'N');
  return;
}

long int TArquivo()
{
	fseek(ArqShip,0,2);
	long int R = ftell(ArqShip)/Tamanho;
	return R;
}

void Excluir()
{
  if (TArquivo()!=0)
  {
    system("cls");
    fclose(ArqShip);
    ArqShip = fopen("Registro_de_vendas.dat","r+b");
    char codigo[20];
    fseek(ArqShip,0,0);

    printf("Qual o codigo do pedido? ");
    scanf(" %s",&codigo);

    int Achou = 0;

    do
    {
      fread(&RgPedido,Tamanho,1,ArqShip);
      if (strcmp(RgPedido.codigo, codigo) == 0 && (RgPedido.status != 0))
      {
        RgPedido.status = 0;
        Achou = 1;
        printf("Codigo de pedido encontrado! Excluindo...\n\n");
      }
    }
    while (!feof(ArqShip)&&(Achou==0));

    if (Achou == 0)
    {
      printf("O codigo a ser excluido nao foi encontrado no arquivo\n");
    }
    else
    {
      fseek(ArqShip,-Tamanho,1);
      fwrite(&RgPedido,Tamanho,1,ArqShip);
    }   
    system("pause");
    fclose(ArqShip);
    ArqShip = fopen("Registro_de_vendas.dat","a+b");
  }
  else
  {
    printf("Arquivo Vazio. Nao existem dados a deletar.");
    system("pause");
  }
  return;

}

void Alterar()
{
  if (TArquivo()!=0)
{
  fclose(ArqShip);
  ArqShip = fopen("Registro_de_vendas.dat","r+b");
  system("cls");
  printf("*** alterar ***\n\n");  
  fseek(ArqShip,0,0);
  char codigo[20];

  printf("Qual o codigo de venda? ");  
  scanf(" %s", &codigo);
  int Achou=0;
  do 
  {
	fread(&RgPedido,Tamanho,1,ArqShip);
	if (strcmp(RgPedido.codigo,codigo)==0 && RgPedido.status != 0)
    {
	    Achou=1;	
	    printf("\nNome do Cliente: %s\n",RgPedido.cliente);
      printf("Produto: %s\n",RgPedido.produto);
      printf("Quantidade: %d\n",RgPedido.quantidade);
      printf("Valor original do produto: %.2f\n",RgPedido.valor_original);
      printf("Valor de revenda: %.2f\n",RgPedido.valor_revenda);
      printf("Codigo de venda: %s\n\n", RgPedido.codigo);
    }
  }
  while (!feof(ArqShip)&&(Achou==0));

  if (Achou==0)
    printf("Registro inexistente!\n"); 

  else
  {
    char Resposta;
    do
    {
      printf("O que gostaria de alterar?\n\n");
      printf("C - Nome do Cliente \n");  
      printf("P - Produto \n");
      printf("Q - Quantidade \n");
      printf("O - Valor Original do produto \n");
      printf("R - Valor de Revenda \n");
      printf("S - Sair \n\n");
      scanf(" %c", &Resposta);
      Resposta = toupper(Resposta);
      switch(Resposta)
      {
        case 'C':
          printf("Qual o novo nome do Cliente? \n");
          scanf(" %s", &RgPedido.cliente);
          fseek(ArqShip,-Tamanho,1);
          fwrite(&RgPedido,Tamanho,1,ArqShip);
          printf(">>> Alteracao efetuada com sucesso! <<<\n");
          break;

        case 'P':
          printf("Qual o novo Produto? \n");
          scanf(" %s", &RgPedido.produto);
          fseek(ArqShip,-Tamanho,1);
          fwrite(&RgPedido,Tamanho,1,ArqShip);
          printf(">>> Alteracao efetuada com sucesso! <<<\n");
          break;

        case 'Q':
          printf("Qual a nova quantidade? \n");
          scanf("%d", &RgPedido.quantidade);
          fseek(ArqShip,-Tamanho,1);
          fwrite(&RgPedido,Tamanho,1,ArqShip);
          printf(">>> Alteracao efetuada com sucesso! <<<\n");
          break;

        case 'O':
          printf("Qual o novo valor original? \n");
          scanf("%f", &RgPedido.valor_original);
          fseek(ArqShip,-Tamanho,1);
          fwrite(&RgPedido,Tamanho,1,ArqShip);
          printf(">>> Alteracao efetuada com sucesso! <<<\n");
          break;

        case 'R':
          printf("Qual o novo valor de revenda? \n");
          scanf("%f", &RgPedido.valor_revenda);
          fseek(ArqShip,-Tamanho,1);
          fwrite(&RgPedido,Tamanho,1,ArqShip);
          printf(">>> Alteracao efetuada com sucesso! <<<\n");
          break;
      }
    }
    while (Resposta != 'S');
  }
  system("pause");
  fclose(ArqShip);
  ArqShip = fopen("Registro_de_vendas.dat","a+b");
}
  else
  {
    printf("Arquivo Vazio.  Nao existem dados a alterar.");
    system("pause");
  }
  return;
}

void Consultar() 
{
  system("cls");
  printf("*** consulta ***\n\n");  
  fseek(ArqShip,0,0);
  char codigo[20];

  printf("Qual o codigo de venda? ");
  scanf(" %s", &codigo);

  int Achou=0;
  do 
  {
	fread(&RgPedido,Tamanho,1,ArqShip);
	if (strcmp(RgPedido.codigo,codigo)==0 && (RgPedido.status != 0))
    {
	    Achou=1;
	    printf("\nCliente: %s\n",RgPedido.cliente);
      printf("Produto: %s\n",RgPedido.produto);
      printf("Quantidade: %d\n",RgPedido.quantidade);
      printf("Valor original do produto: R$%.2f\n",RgPedido.valor_original);
      printf("Valor de revenda: R$%.2f\n",RgPedido.valor_revenda);
      printf("Codigo de venda: %s\n\n", RgPedido.codigo);
    }
  }
  while (!feof(ArqShip)&&(Achou==0));

  if (Achou==0)
    printf("Registro inexistente!\n");  
  
  system("pause");
  return;
}

void ListarTodos()
{
  system("cls");
  printf("*** lista todos ***\n\n");  
  fseek(ArqShip,0,0);

  do 
  {
	fread(&RgPedido,Tamanho,1,ArqShip);
	if (!feof(ArqShip) && RgPedido.status != 0)
    {
	    printf("Cliente: %s\n",RgPedido.cliente);
      printf("Produto: %s\n",RgPedido.produto);
      printf("Quantidade: %d\n",RgPedido.quantidade);
      printf("Valor original do produto: R$%.2f\n",RgPedido.valor_original);
      printf("Valor de revenda: R$%.2f\n",RgPedido.valor_revenda);
      printf("Codigo de venda: %s\n", RgPedido.codigo);
      printf("---------------\n");
    }
  }
  while (!feof(ArqShip));

  system("pause");
  return;
}

void Historico()
{
  system("cls");
  printf("*** Historico ***\n\n");  
  fseek(ArqShip,0,0);

  do 
  {
	fread(&RgPedido,Tamanho,1,ArqShip);
	if (!feof(ArqShip) && RgPedido.status == 0)
    {
	    printf("Cliente: %s\n",RgPedido.cliente);
      printf("Produto: %s\n",RgPedido.produto);
      printf("Quantidade: %d\n",RgPedido.quantidade);
      printf("Valor original do produto: R$%.2f\n",RgPedido.valor_original);
      printf("Valor de revenda: R$%.2f\n",RgPedido.valor_revenda);
      printf("Codigo de venda: %s\n", RgPedido.codigo);
      printf("---------------\n");
    }
  }
  while (!feof(ArqShip));

  system("pause");
  return;
}

int main()
{
  ArqShip = fopen("Registro_de_vendas.dat","a+b");
  char Opcao;
  do
  {
	  system("cls");
    printf("\n\n> > > Dropshipping < < <\n\n");
    printf("O que deseja fazer? \n\n");
    printf("I - Incluir \n");  
    printf("E - Excluir \n");
    printf("A - Alterar \n");
    printf("C - Consultar \n");
    printf("T - Listar Todos \n");
    printf("H - Historico\n");
    printf("S - Sair \n\n");
    scanf(" %c", &Opcao);
    Opcao = toupper(Opcao);
    switch (Opcao)
    {
      case 'I': Incluir(); break;
      case 'E': Excluir(); break;
      case 'A': Alterar(); break;
      case 'C': Consultar(); break;
      case 'T': ListarTodos(); break;
      case 'H' : Historico(); break;

    }
  }
  while (Opcao != 'S');
  fclose(ArqShip);
  return 0;
}