#ifndef STRUCT_DISCIPLINA_H
#define STRUCT_DISCIPLINA_H
#define MAX_DISCIPLINAS 100
#define MAX_ALUNOS_MATRICULADOS 50
#include "StructPessoa.h"

typedef struct{
    char NomeDisciplina[50];
    long CodigoDisciplina;
    char SemestreDisciplina[6];
    Pessoa ProfessorDisciplina;
    Pessoa AlunosMatriculados[MAX_ALUNOS_MATRICULADOS];
    int indiceAlunosMatriculados;
}Disciplina;


#endif
