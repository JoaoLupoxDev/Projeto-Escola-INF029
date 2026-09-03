#ifndef STRUCT_PESSOA_H
#define STRUCT_PESSOA_H
#define MAX_PESSOAS 100

typedef struct
{
    long Matricula;
    char Nome[50];
    char Sexo; //pega apenas M ou F
    char DataNascimento[11];   
    char CPF[15];
    char Tipo;
}Pessoa;

typedef struct{
    Pessoa listaDePessoas[MAX_PESSOAS];
    int quantidadeTotal;
}ListaPessoas;

typedef struct{
    int dia;
    int mes;
    int ano;
}Data;

extern ListaPessoas listaGlobalPessoas;
extern int indiceListaPessoas;

#endif