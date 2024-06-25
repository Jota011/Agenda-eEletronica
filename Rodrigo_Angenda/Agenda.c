#include <stdio.h>
#include <stdlib.h>

//Tabela de informação do contato
typedef struct{
	char nome[50];
	int numero[12];
	int id;
} numero_contato;

//Onde os arquivos serão salvos
#define arquivo_ctt "contatos.bin"
#define contatos_maximo 100
void menu();
void addcontato();
void pesquisar_contato();
void excluir();
int proximo_id();


numero_contato contatos[contatos_maximo];
int NomeroDosContatos = 0;

int main(void){
	int opcao;
	do{ 
		menu();
		scanf("%d", &opcao);
		getchar();
		
		switch(opcao){
		case 1: //to criando os nomes das funcoes agora
			addcontato();
			break;
		case 2:
			pesquisar_contato();
			break;
		case 3:
			excluir();
			break;
		case 4:
			printf("ENCERROU O SISTEMA");
			break;
		default:
			printf("Opcao nao encontrada"); 	
		}
	}while(opcao!=4);
	return 0;
}


void menu(){
    printf("1- Adicionar Contato\n");
    printf("2- Pesquisar Contato\n");
    printf("3- Excluir Contato\n");
    printf("4- Salvar\n");
    printf("Escolha: ");

}

int proximo_id(){ //adiciona automamaticamente o id do usuario
	numero_contato contato;
	FILE *file;
	file = fopen(arquivo_ctt, "rb");//read binario
	if(file==NULL){ //busca pelo arquivo
		printf("NADA ENCONTRADO");
	exit(1);
	}
	int px_id;//proximo id;
	
	
	while(fread(&contato, sizeof(numero_contato), 1, file)==1){
	px_id=contato.id;
	}
	
	if(px_id==NULL){
		px_id=1;
	}

	px_id++;
	return px_id;
}

void addcontato(){ 
	numero_contato contato;
	FILE *file;
	file=fopen(arquivo_ctt, "ab"); ///abre o arquivo 
	if(file==NULL){ //busca pelo arquivo
		printf("NADA ENCONTRADO");
	exit(1);
	}
	
	//adiciona os dados dos usuarios
	printf("Nome:");
	scanf("%s", &contato.nome);
	printf("Numero de contato:");
	scanf("%i", contato.numero);
	
	contato.id=proximo_id();
	
	fwrite(&contato, sizeof(numero_contato), 1, file);
	fclose(file);
}

void pesquisar_contato(){
	
	numero_contato contato;
	FILE *file;
	file = fopen(arquivo_ctt, "rb");//read binario
	if(file==NULL){ //busca pelo arquivo
		printf("NADA ENCONTRADO");
	exit(1);
	}
	//basicamente mostra em tela o que tem na agenda
	while(fread(&contato, sizeof(numero_contato), 1, file)==1){
	printf("-------------------\n");
	printf("Nome: %s \n", contato.nome);
	printf("Telefone: %d \n", contato.numero);
	printf("Id do contato: %d \n", contato.id);
	}


}

void excluir(){
	int id_temp;
	int qtd_ctt = 0;	
	
	numero_contato contato;
	numero_contato contatos[100];//cria uma tabela onde vai ser listado todos os contatos
	
	FILE *file;
	file = fopen(arquivo_ctt, "rb");//read binario
	if(file==NULL){ //busca pelo arquivo
		printf("NADA ENCONTRADO");
	exit(1);
	}
	printf("Numero do id que deseja excluir: ");
	scanf("%i", &id_temp);
	
	while(fread(&contato, sizeof(numero_contato), 1, file)==1){
		contatos[qtd_ctt++] = contato;
	}
	for(int i = 0; i < qtd_ctt - 1; i++){
		if(contatos[i].id == id_temp){
			for(int j = i; j < qtd_ctt; j++){
				contatos[j] = contatos[j + 1];
			}
		printf("O contato com ID %d doi deletado", id_temp);
		printf("-------------------\n");
		}	
	}	
}