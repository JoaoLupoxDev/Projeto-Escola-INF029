#ifndef REPOSITORIO_H
#define REPOSITORIO_H

#include "StructAluno.h"
#include "StructDisciplina.h"
#include "StructProfessor.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int indiceListaAlunos=0;//variavel global para adicionar alunos sempre em indices diferentes (evita substituição de alunos)
int indiceListaProfessores=0;//variavel global para adicionar professores sempre em indices diferentes (evita substituição de professores)
ListaAlunos listaGlobalAlunos; //lista global de alunos
ListaProfessores listaGlobalProfessores;//lista global de professores

void CadastrarAluno(){
    Aluno aluno;
    int validador;
    inicio: //label inicio para voltar aqui caso...
    //fase de cadastro
    printf("Digite o nome do aluno a ser cadastrado: ");
    fgets(aluno.NomeAluno, sizeof(aluno.NomeAluno), stdin);
    matricula:
    printf("Digite a matricula do aluno: ");
    scanf("%d", &aluno.MatriculaAluno);
    validador = verificaMatricula(aluno.MatriculaAluno);
    if (validador == 0){
        printf("Esta matricula ja esta cadastrada, digite outra matricula: ");
        goto matricula;
    }
    cpf:
    printf("Digite o CPF do aluno: ");
    fgets(aluno.CPFaluno, sizeof(aluno.CPFaluno), stdin);
    validador = verificaCPF(aluno.CPFaluno);
    if (validador == 0){
        printf("Este CPF já está cadastrado, digite outro CPF: ");
        goto cpf;
    }
    sexo:
    printf("Digite o sexo do aluno(M/F): ");
    fgets(aluno.CPFaluno, sizeof(aluno.CPFaluno), stdin);
    if (aluno.CPFaluno != 'M' || aluno.CPFaluno != 'm' || aluno.CPFaluno != 'F' || aluno.CPFaluno != 'f'){
        printf("Digite apenas M(masculino) ou F(feminino): ");
        goto sexo; //repete o cadastro do sexo para evitar que seja diferente de M,m,F,f
    }
    printf("Digite a data de nascimento do aluno (dd/mm/aaaa): ");
    fgets(aluno.DataNascimentoAluno, sizeof(aluno.DataNascimentoAluno), stdin);
    //falta verificar a data se esta correta e depois adicionar o aluno na lista

}

int verificaCPF(char cpf[]){ //verifica se há este cpf na lista de alunos e na lista de professores
    int validador=1;
    for (int i=0;i<indiceListaAlunos;i++){
        if (strcmp(listaGlobalAlunos.listaDeAlunos[i].CPFaluno, cpf) == 0){
            validador = 0;
            break;
        }
    }
    for (int i=0;i<indiceListaProfessores;i++){
        if (strcmp(listaGlobalProfessores.listaDeProfessores[i].CPFprofessor, cpf) == 0){
            validador = 0;
            break;
        }
    }
    return validador;
}

int verificaMatricula(int matricula){
    int validador=1;
    for (int i=0;i<indiceListaAlunos;i++){
        if (matricula == listaGlobalAlunos.listaDeAlunos[i].MatriculaAluno){
            validador = 0;
            break;
        }
    }
    for (int i=0;i<indiceListaProfessores;i++){
        if (matricula == listaGlobalProfessores.listaDeProfessores[i].MatriculaProfessor){
            validador = 0;
            break;
        }
    }
    return validador;
}


#endif