#ifndef STRUCT_ALUNO_H
#define STRUCT_ALUNO_H
#define MAX_ALUNOS 100

typedef struct
{
    long MatriculaAluno;
    char NomeAluno[50];
    char SexoAluno[1]; //pega apenas M ou F
    char DataNascimentoAluno[11];   
    char CPFaluno[15];
}Aluno;

typedef struct{
    Aluno listaDeAlunos[MAX_ALUNOS];
    int quantidadeTotal;
}ListaAlunos;

extern ListaAlunos listaGlobalAlunos[];
extern int indiceListaAlunos=0;

#endif