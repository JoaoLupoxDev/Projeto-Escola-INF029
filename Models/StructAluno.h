#ifndef STRUCT_ALUNO_H
#define STRUCT_ALUNO_H
#define MAX_ALUNOS 100

typedef struct
{
    long MatriculaAluno;
    char NomeAluno[50];
    char SexoAluno;
    char DataNascimentoAluno[11];   
    char CPFaluno[15];
}Aluno;

typedef struct{
    Aluno listaDeAlunos[MAX_ALUNOS];
    int quantidadeTotal;
}ListaAlunos;

#endif