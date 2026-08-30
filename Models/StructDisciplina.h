#ifndef STRUCT_DISCIPLINA_H
#define SRTUCT_DISCIPLINA_H
#define MAX_DISCIPLINAS 100
#include "StructPessoa.h"

typedef struct{
    char NomeDisciplina[50];
    long CodigoDisciplina;
    char SemestreDisciplina;
    Pessoa ProfessorDisciplina; 
}Disciplina;

typedef struct{
    Disciplina listaDeDisciplinas[MAX_DISCIPLINAS];
    int quantidadeDisciplinas;
}ListaDisciplinas;

#endif
