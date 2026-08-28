#ifndef STRUCT_PROFESSOR_H
#define STRUCT_PROFESSOR_H
#define MAX_PROFESSORES 100

typedef struct{
    long MatriculaProfessor;
    char NomeProfessor[50];
    char SexoProfessor;
    char DataNascimentoProfessor[11];    
    char CPFprofessor[15];
}Professor;

typedef struct{
    Professor listaDeProfessores[MAX_PROFESSORES];
    int quantidadeProfessores;
}ListaProfessores;

#endif