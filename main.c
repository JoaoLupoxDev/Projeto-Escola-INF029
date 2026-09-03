#include "Models/StructPessoa.h"
#include "Models/StructDisciplina.h"
#include "Models/Repositorio.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//redeclarar aqui todas as funcoes para evitar erros
void listarPessoas(char tipo);
void listarPessoasPorNome(char tipo);
void listarPessoasPorString(char tipo, char string[]);
void listarPessoasPorSexo(char tipo, char sexo);
void listarPessoasPorData(char tipo, char data[]);
void listarPessoasPorMatricula(char tipo, long matricula);
void cadastrarPessoa(char tipo);
void excluirPessoa(char tipo);
void atualizarPessoa(char tipo);
int verificaMatricula(long matricula);
int verificaCPF(char cpf[]);
int lenTexto(char texto[]);
void paraMaiuscula(char *str);
void menu();


//execução do codigo principal aqui:
int main() {
    menu();
    return 0;
}