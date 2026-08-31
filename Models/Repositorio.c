#ifndef REPOSITORIO_H
#define REPOSITORIO_H

#include "StructPessoa.h"
#include "StructDisciplina.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int indiceListaPessoas=0;//variavel global para adicionar professores e alunos sempre em indices diferentes (evita substituição de professores)
ListaPessoas listaGlobalPessoas;
int indiceListaDisciplinas=0;//variavel global para adicionar disciplinas sempre em indices diferentes (evita substituição de disciplinas)
ListaDisciplinas listaGlobalDisciplinas;


void CadastrarAluno(){
    Pessoa pessoa;
    Data data;
    int validador;
    char transformador;

    //fase de cadastro
    printf("Digite o tipo da pessoa a ser cadastrada (A/aluno ou P/professor): ");
    fgets(pessoa.Tipo, sizeof(pessoa.Tipo), stdin);
    paraMaiuscula(&pessoa.Tipo); //função para tratar letras minusculas
    while(pessoa.Tipo != 'A' || pessoa.Tipo != 'P'){
        printf("Digite apenas A (aluno) ou P(professor): ");
        fgets(pessoa.Tipo, lenTexto(pessoa.Tipo), stdin);
        paraMaiuscula(&pessoa.Tipo);
    }

    if (pessoa.Tipo == 'A'){
        printf("Digite o nome do aluno a ser cadastrado: ");
    }else{
        printf("Digite o nome do professor a ser cadastrado: ");
    }
    fgets(pessoa.Nome, lenTexto(pessoa.Nome), stdin);

    if (pessoa.Tipo == 'A'){
        printf("Digite a matricula do aluno a ser cadastrado: ");
    }else{
        printf("Digite a matricula do professor a ser cadastrado: ");
    }
    scanf("%d", &pessoa.Matricula);
    validador = verificaMatricula(pessoa.Matricula);
    while (validador == 0){
        printf("Esta matricula ja esta cadastrada, digite outra matricula: ");
        scanf("%d", &pessoa.Matricula);    
    }   

    if (pessoa.Tipo == 'A'){
        printf("Digite o CPF do aluno a ser cadastrado: ");
    }else{
        printf("Digite o CPF do professor a ser cadastrado: ");
    }
    fgets(pessoa.CPF, lenTexto(pessoa.CPF), stdin);
    validador = verificaCPF(pessoa.CPF);
    while (validador == 0){
        printf("Este CPF já está cadastrado, digite outro CPF: ");
        fgets(pessoa.CPF, lenTexto(pessoa.CPF), stdin);
    }

    if (pessoa.Tipo == 'A'){
        printf("Digite o sexo do aluno a ser cadastrado (M/F): ");
    }else{
        printf("Digite o sexo do professor a ser cadastrado (M/F): ");
    }
    fgets(pessoa.CPF, sizeof(pessoa.CPF), stdin);
    paraMaiuscula(&pessoa.CPF);
    if (pessoa.CPF != 'M' || pessoa.CPF != 'F'){
        printf("Digite apenas M(masculino) ou F(feminino): ");
    }
    if (pessoa.Tipo == 'A'){
        printf("Digite a data de nascimento do aluno a ser cadastrado (dd/mm/aaaa): ");
    }else{
        printf("Digite a data de nascimento do professor a ser cadastrado (dd/mm/aaaa): ");
    }
    fgets(pessoa.DataNascimento, lenTexto(pessoa.DataNascimento), stdin); //trocar a data para vetor
    //falta verificar a data se esta correta AQUI!!!!!!!

    listaGlobalPessoas.listaDePessoas[indiceListaPessoas] = pessoa;
    indiceListaPessoas++;
}

void excluirPessoa(long matricula, char tipo){
    for (int i = 0; i < indiceListaPessoas; i++){
        if (matricula == listaGlobalPessoas.listaDePessoas[i].Matricula && tipo == listaGlobalPessoas.listaDePessoas[i].Tipo){
            // Move os elementos posteriores uma posição para trás
            for (int j = i; j < indiceListaPessoas - 1; j++){
                listaGlobalPessoas.listaDePessoas[j] = listaGlobalPessoas.listaDePessoas[j+1];
            }
            indiceListaPessoas--; // Reduz a contagem de pessoas
            break; 
        }
    }
}

void atualizarPessoa(long matricula, char tipo){ //falta verificar a data de nascimento se está correta
    for (int i = 0; i < indiceListaPessoas; i++){
        if (matricula == listaGlobalPessoas.listaDePessoas[i].Matricula && tipo == listaGlobalPessoas.listaDePessoas[i].Tipo){
            printf("Digite o novo nome: ");
            fgets(listaGlobalPessoas.listaDePessoas[i].Nome, lenTexto(listaGlobalPessoas.listaDePessoas[i].Nome), stdin);
            printf("Digite o novo CPF: ");
            fgets(listaGlobalPessoas.listaDePessoas[i].CPF, lenTexto(listaGlobalPessoas.listaDePessoas[i].CPF), stdin);
            printf("Digite o novo sexo: ");
            fgets(listaGlobalPessoas.listaDePessoas[i].Sexo, lenTexto(listaGlobalPessoas.listaDePessoas[i].Sexo), stdin);
            printf("Digite a nova data de nascimento: "); //verificar a data de nascimento aqui!!!
            fgets(listaGlobalPessoas.listaDePessoas[i].DataNascimento, lenTexto(listaGlobalPessoas.listaDePessoas[i].DataNascimento), stdin);
            break;
        }
    }
}

int verificaCPF(char cpf[]){ //verifica se há este cpf na lista de pessoas
    int validador=1;
    for (int i=0;i<indiceListaPessoas;i++){
        if (strcmp(listaGlobalPessoas.listaDePessoas[i].CPF, cpf) == 0){
            validador = 0;
            break;
        }
    }
    return validador;
}
int verificaMatricula(long matricula){ //verifica se há esta matricula na lista de pessoas
    int validador=1;
    for (int i=0;i<indiceListaPessoas;i++){
        if (matricula == listaGlobalPessoas.listaDePessoas[i].Matricula){
            validador = 0;
            break;
        }
    }
    return validador;
}

void paraMaiuscula(char *str){
    if (*str >= 97 && *str <= 122){
        *str -= 32;
    }
}

void listarPessoas(char tipo){
    if (tipo == 'A'){
        for (int i=0;i<indiceListaPessoas;i++){
            if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'A'){
                printf("Nome:%s Matricula:%ld Sexo:%c DataNascimento:%s \n",listaGlobalPessoas.listaDePessoas[i].Nome, listaGlobalPessoas.listaDePessoas[i].Matricula, listaGlobalPessoas.listaDePessoas[i].Sexo, listaGlobalPessoas.listaDePessoas[i].DataNascimento);
            }            
        }
    }else{
        for (int i=0;i<indiceListaPessoas;i++){
            if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'P'){
                printf("Nome:%s Matricula:%ld Sexo:%c DataNascimento:%s \n",listaGlobalPessoas.listaDePessoas[i].Nome, listaGlobalPessoas.listaDePessoas[i].Matricula, listaGlobalPessoas.listaDePessoas[i].Sexo, listaGlobalPessoas.listaDePessoas[i].DataNascimento);
            }              
        }
    }   
}

void listarPessoasPorSexo(char sexo, char tipo){
    if (sexo == 'M' && tipo == 'A'){
        for (int i=0;i<indiceListaPessoas;i++){
            if (listaGlobalPessoas.listaDePessoas[i].Sexo == 'M' && listaGlobalPessoas.listaDePessoas[i].Tipo == 'A'){
                printf("Nome:%s Matricula:%ld Sexo:%c DataNascimento:%s \n",listaGlobalPessoas.listaDePessoas[i].Nome, listaGlobalPessoas.listaDePessoas[i].Matricula, listaGlobalPessoas.listaDePessoas[i].Sexo, listaGlobalPessoas.listaDePessoas[i].DataNascimento);
            }
        }
    }else if (sexo == 'F' && tipo == 'A'){
        for (int i=0;i<indiceListaPessoas;i++){
            if (listaGlobalPessoas.listaDePessoas[i].Sexo == 'F' && listaGlobalPessoas.listaDePessoas[i].Tipo == 'A'){
                printf("Nome:%s Matricula:%ld Sexo:%c DataNascimento:%s \n",listaGlobalPessoas.listaDePessoas[i].Nome, listaGlobalPessoas.listaDePessoas[i].Matricula, listaGlobalPessoas.listaDePessoas[i].Sexo, listaGlobalPessoas.listaDePessoas[i].DataNascimento);
            }
        }
    }else if (sexo == 'M' && tipo == 'P'){
        for (int i=0;i<indiceListaPessoas;i++){
            if (listaGlobalPessoas.listaDePessoas[i].Sexo == 'M' && listaGlobalPessoas.listaDePessoas[i].Tipo == 'P'){
                printf("Nome:%s Matricula:%ld Sexo:%c DataNascimento:%s \n",listaGlobalPessoas.listaDePessoas[i].Nome, listaGlobalPessoas.listaDePessoas[i].Matricula, listaGlobalPessoas.listaDePessoas[i].Sexo, listaGlobalPessoas.listaDePessoas[i].DataNascimento);
            }
        }
    }else if (sexo == 'F' && tipo == 'P'){
        for (int i=0;i<indiceListaPessoas;i++){
            if (listaGlobalPessoas.listaDePessoas[i].Sexo == 'F' && listaGlobalPessoas.listaDePessoas[i].Tipo == 'P'){
                printf("Nome:%s Matricula:%ld Sexo:%c DataNascimento:%s \n",listaGlobalPessoas.listaDePessoas[i].Nome, listaGlobalPessoas.listaDePessoas[i].Matricula, listaGlobalPessoas.listaDePessoas[i].Sexo, listaGlobalPessoas.listaDePessoas[i].DataNascimento);
            }
        }
    }
}

int lenTexto(char texto[]){ //funcao que retorna o tamanho de um texto
    int i=0;
    while (texto[i] != '\0'){
        i++;
    }
    return i;
}


int verificaData(char data[]){ //verifica se o molde escrito da data esta correto e se a data escrita é valida (dd/mm/aaaa) 
    int validador=1; //falta verificar se o ano é bissexto
    int contadorBarra=0;
    int contadorNum=0;
    if (len0Texto(data) != 10){
        validador=0;
        return validador;
    }
    if (data[2] != '/' || data[5] != '/'){
        validador=0;
        return validador;
    }
    if (data[0] > '3' || data[0] < '0'){
        validador=0;
        return validador;
    }
    if (data[1] < '0' || data[1] > '9'){
        validador=0;
        return validador;
    }
    if (data[0] == '3' && data[1] > '1'){
        validador=0;
        return validador;
    }
    if (data[0] == '0' && data[1] == '0'){
        validador=0;
        return validador;
    }
}
void listarAlunosPorNome(){

}

#endif