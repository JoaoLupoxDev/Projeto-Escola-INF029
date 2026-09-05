#ifndef REPOSITORIO_H
#define REPOSITORIO_H

#include "StructPessoa.h"
#include "StructDisciplina.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// --- VARIÁVEIS GLOBAIS ---
int indiceListaPessoas = 0;
ListaPessoas listaGlobalPessoas;
int quantidadeAlunos = 0;
int quantidadeProfessores = 0;
int indiceListaDisciplinas = 0;
Disciplina listaDisciplinas[MAX_DISCIPLINAS];

// --- PROTÓTIPOS DE TODAS AS FUNÇÕES ---
int lenTexto(char texto[]);
int verificaMatricula(long matricula);
int verificaCPF(char cpf[]);
int validaCPF(char cpf[]);
int verificarData(char data[]);
void paraMaiuscula(char *str);

void menu(void);
void cadastrarPessoa(char tipo);
void excluirPessoa(char tipo);
void atualizarPessoa(char tipo);
void listarPessoas(char tipo);
void listarPessoasPorSexo(char sexo, char tipo);
void listarPessoasPorNome(char tipo);
void listarPessoasPorString(char tipo, char string[]);

// --- FUNÇÕES UTILITÁRIAS ---

int lenTexto(char texto[]) {
    int i = 0;
    while (texto[i] != '\0') {
        i++;
    }
    return i;
}

void paraMaiuscula(char *str) {
    if (*str >= 'a' && *str <= 'z') {
        *str -= 32;
    }
}

int verificaMatricula(long matricula) {
    int validador = 1;
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (matricula == listaGlobalPessoas.listaDePessoas[i].Matricula) {
            validador = 0;
            break;
        }
    }
    return validador;
}

int verificaCPF(char cpf[]) {
    int validador = 1;
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (strcmp(listaGlobalPessoas.listaDePessoas[i].CPF, cpf) == 0) {
            validador = 0;
            break;
        }
    }
    return validador;
}

int validaCPF(char cpf[]) {
    (void)cpf; // Evita warning de unused parameter
    // TODO: Implementar validação lógica do CPF
    return 1;
}

int verificarData(char data[]) {
    if (lenTexto(data) != 10) {
        return 0;
    }
    if (data[2] != '/' || data[5] != '/') {
        return 0;
    }
    if (data[0] > '3' || data[0] < '0') {
        return 0;
    }
    if (data[1] < '0' || data[1] > '9') {
        return 0;
    }
    if (data[0] == '3' && data[1] > '1') {
        return 0;
    }
    if (data[0] == '0' && data[1] == '0') {
        return 0;
    }
    return 1;
}

void menu(void) {
    int escolhaMenu = -1, escolhaModulo;
    char sexo, texto[50];
    while (escolhaMenu != 0) {
        printf("-----MENU ESCOLA-----\n");
        printf("1 - Modulo Aluno\n");
        printf("2 - Modulo Professor\n");
        printf("3 - Modulo Disciplina\n");
        printf("0 - Sair do Menu\n");
        printf("Digite o numero referente a sua escolha: ");
        scanf("%d", &escolhaMenu);
        
        switch (escolhaMenu) {
            case 1:
                printf("-----MODULO ALUNO-----\n");
                printf("1 - Cadastrar aluno\n");
                printf("2 - Excluir aluno\n");
                printf("3 - Atualizar aluno\n");
                printf("4 - Listar alunos\n");
                printf("5 - Listar alunos por sexo\n");
                printf("6 - Listar alunos por ordem alfabetica\n");
                printf("7 - Listar alunos por data de nascimento\n");
                printf("8 - Lista de alunos matriculados em menos de 3 disciplinas\n");
                printf("9 - Buscar alunos por texto\n");
                printf("0 - Sair do Módulo Aluno\n");
                printf("Digite o numero referente a sua escolha: ");
                scanf("%d", &escolhaModulo);
                
                switch (escolhaModulo) {
                    case 1:
                        cadastrarPessoa('A');
                        break;
                    case 2:
                        excluirPessoa('A');
                        break;
                    case 3:
                        atualizarPessoa('A');
                        break;
                    case 4:
                        listarPessoas('A');
                        break;
                    case 5:
                        printf("Digite o sexo (M - Masculino | F - Feminino): ");
                        scanf(" %c", &sexo);
                        listarPessoasPorSexo(sexo, 'A');
                        break;
                    case 6:
                        listarPessoasPorNome('A'); //esta incompleto
                        break;
                    case 7:
                        // falta implementar
                        break;
                    case 8:
                        
                        break;
                    case 9:
                        printf("Digite um texto para buscar alunos com base no texto: ");
                        getchar(); // limpa buffer antes de ler string
                        fgets(texto, sizeof(texto), stdin);
                        listarPessoasPorString('A', texto);         
                        break;
                    case 0:
                        printf("Saindo do Modulo Aluno\n");
                        break;
                    default:
                        printf("Esta opção não existe, digite um numero válido.\n");
                        break;
                }
                break;
                
            case 2:
                printf("-----MODULO PROFESSOR-----\n");
                printf("1 - Cadastrar professor\n");
                printf("2 - Excluir professor\n");
                printf("3 - Atualizar professor\n");
                printf("4 - Listar professores\n");
                printf("5 - Listar professores por sexo\n");
                printf("6 - Listar professores por ordem alfabetica\n");
                printf("7 - Listar professores por data de nascimento\n");
                printf("8 - Buscar professores por texto\n");
                printf("0 - Sair do Módulo Professor\n");
                printf("Digite o numero referente a sua escolha: ");
                scanf("%d", &escolhaModulo);
                
                switch (escolhaModulo) {
                    case 1:
                        cadastrarPessoa('P');
                        break;
                    case 2:
                        excluirPessoa('P');
                        break;
                    case 3:
                        atualizarPessoa('P');
                        break;
                    case 4:
                        listarPessoas('P');
                        break;
                    case 5:
                        printf("Digite o sexo (M - Masculino | F - Feminino): ");
                        scanf(" %c", &sexo);
                        listarPessoasPorSexo(sexo, 'P');
                        break;
                    case 6:
                        listarPessoasPorNome('P');
                        break;
                    case 7: 
                        break;
                    case 8:
                        printf("Digite um texto para buscar professores com base no texto: ");
                        fgets(texto, sizeof(texto), stdin);
                        listarPessoasPorString('P', texto);
                        break;
                    case 0:
                        printf("Saindo do Modulo Professor...\n");
                        break;
                    default:
                        printf("Esta opção não existe, digite um numero válido.\n");
                        break;
                }
                break;
                
            case 3:
                printf("-----MODULO DISCIPLINAS-----\n");
                printf("1 - Listar todas as disciplinas\n");
                printf("2 - Listar uma disciplina e seus alunos matriculados\n");
                printf("3 - Listar disciplinas que passam de 40 alunos matriculados\n");
                printf("4 - Inserir/Excluir alunos de uma disciplina\n");
                printf("0 - Sair do Modulo Disciplinas");
                scanf("%d", &escolhaModulo);
                switch (escolhaModulo) {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                        break;
                    default:
                        printf("Esta opção não existe, digite um numero válido.\n");
                        break;
                }
                break;
                
            case 0:
                printf("Saindo do menu... Programa encerrado\n");
                break;
            default:
                printf("Esta opção não existe, digite um numero válido.\n");
                break;
        }
    }
}

void cadastrarPessoa(char tipo) {
    Pessoa pessoa;
    int validador;

    if (tipo == 'A' || tipo == 'P') {
        pessoa.Tipo = tipo;

        printf("Digite o nome a ser cadastrado: ");
        getchar(); // Limpa o buffer do scanf anterior
        fgets(pessoa.Nome, sizeof(pessoa.Nome), stdin);

        printf("Digite a matricula a ser cadastrada: ");
        scanf("%ld", &pessoa.Matricula);
        validador = verificaMatricula(pessoa.Matricula);
        while (validador == 0) {
            printf("Esta matricula ja esta cadastrada, digite outra matricula: ");
            scanf("%ld", &pessoa.Matricula);
        }

        printf("Digite o CPF a ser cadastrado: ");
        getchar();
        fgets(pessoa.CPF, sizeof(pessoa.CPF), stdin);
        validador = verificaCPF(pessoa.CPF);
        while (validador == 0) {
            printf("Este CPF já está cadastrado, digite outro CPF: ");
            fgets(pessoa.CPF, sizeof(pessoa.CPF), stdin);
        }

        printf("Digite o sexo (M/F): ");
        scanf(" %c", &pessoa.Sexo);
        paraMaiuscula(&pessoa.Sexo);
        while (pessoa.Sexo != 'M' && pessoa.Sexo != 'F') {
            printf("Digite apenas M(masculino) ou F(feminino): ");
            scanf(" %c", &pessoa.Sexo);
            paraMaiuscula(&pessoa.Sexo);
        }

        printf("Digite a data de nascimento (dd/mm/aaaa): ");
        getchar();
        fgets(pessoa.DataNascimento, sizeof(pessoa.DataNascimento), stdin);
        validador = verificarData(pessoa.DataNascimento);
        while (validador == 0) {
            printf("Digite uma data valida (dd/mm/aaaa): ");
            fgets(pessoa.DataNascimento, sizeof(pessoa.DataNascimento), stdin);
            validador = verificarData(pessoa.DataNascimento);
        }
        if (tipo == 'A') {
            printf("Aluno %s cadastrado com sucesso!\n", pessoa.Nome);
        }
        else{
            printf("Professor %s cadastrado com sucesso!\n", pessoa.Nome);
        }
    }
    listaGlobalPessoas.listaDePessoas[indiceListaPessoas] = pessoa;
    indiceListaPessoas++;
    listaGlobalPessoas.quantidadeTotal = indiceListaPessoas;
}

void excluirPessoa(char tipo) {
    long matricula;
    listarPessoas(tipo);
    printf("\nDigite a matricula de quem voce deseja excluir: ");
    scanf("%ld", &matricula);
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (matricula == listaGlobalPessoas.listaDePessoas[i].Matricula && tipo == listaGlobalPessoas.listaDePessoas[i].Tipo) {
            for (int j = i; j < indiceListaPessoas - 1; j++) {
                listaGlobalPessoas.listaDePessoas[j] = listaGlobalPessoas.listaDePessoas[j + 1];
            }
            indiceListaPessoas--;
            listaGlobalPessoas.quantidadeTotal = indiceListaPessoas;
            break;
        }
    }
}

void atualizarPessoa(char tipo) {
    long matricula;
    listarPessoas(tipo);
    printf("\nDigite a matricula de quem voce deseja atualizar: ");
    scanf("%ld", &matricula);
    getchar();

    for (int i = 0; i < indiceListaPessoas; i++) {
        if (matricula == listaGlobalPessoas.listaDePessoas[i].Matricula && tipo == listaGlobalPessoas.listaDePessoas[i].Tipo){
            printf("Digite o novo nome: ");
            fgets(listaGlobalPessoas.listaDePessoas[i].Nome, lenTexto(listaGlobalPessoas.listaDePessoas[i].Nome), stdin);
            printf("Digite o novo CPF: ");
            fgets(listaGlobalPessoas.listaDePessoas[i].CPF, lenTexto(listaGlobalPessoas.listaDePessoas[i].CPF), stdin);
            printf("Digite o novo sexo: ");
            scanf(" %c", &listaGlobalPessoas.listaDePessoas[i].Sexo);
            printf("Digite a nova data de nascimento: ");
            fgets(listaGlobalPessoas.listaDePessoas[i].DataNascimento, lenTexto(listaGlobalPessoas.listaDePessoas[i].DataNascimento), stdin);
            break;
        }
    }
}

void listarPessoas(char tipo) {
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
            printf("Nome:%s  Matricula:%ld  Sexo:%c  DataNascimento:%s \n",
                   listaGlobalPessoas.listaDePessoas[i].Nome, 
                   listaGlobalPessoas.listaDePessoas[i].Matricula, 
                   listaGlobalPessoas.listaDePessoas[i].Sexo, 
                   listaGlobalPessoas.listaDePessoas[i].DataNascimento);
        }
    }
}

void listarPessoasPorSexo(char sexo, char tipo) {
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Sexo == sexo && listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
            printf("Nome:%s Matricula:%ld Sexo:%c DataNascimento:%s \n",
                   listaGlobalPessoas.listaDePessoas[i].Nome, 
                   listaGlobalPessoas.listaDePessoas[i].Matricula, 
                   listaGlobalPessoas.listaDePessoas[i].Sexo, 
                   listaGlobalPessoas.listaDePessoas[i].DataNascimento);
        }
    }
}

void listarPessoasPorNome(char tipo) {
    (void)tipo;
}

void listarPessoasPorString(char tipo, char string[]) {
    int contador=0;
    for(int i=0;i<indiceListaPessoas;i++){ //for para navegar nos nomes da lista
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo){
            for (int c=0;c<lenTexto(listaGlobalPessoas.listaDePessoas[i].Nome);c++){ //for para navegar nas letras do nome
                for (int x=0;x<lenTexto(string);x++){ //for para navegar nas letras da string de busca
                    if (listaGlobalPessoas.listaDePessoas[i].Nome[c] == string[x]){
                        contador++;
                        c++;
                        for (int y=0;y<lenTexto(string);y++){
                            if (string[y] == listaGlobalPessoas.listaDePessoas[i].Nome[c]){
                                string[y] = '/';
                            }
                        }
                    }
                }
            }
            if(contador>=lenTexto(string)){
                printf("Nome: %s\n",listaGlobalPessoas.listaDePessoas[i].Nome);
                contador=0;
            }
        }
    }
}

void listarDisciplinas(void){
    for (int i=0;i<indiceListaDisciplinas;i++){
        printf("Nome: %s Codigo: %ld\n  Semestre: %s Professor: %s\n",
            listaDisciplinas[i].NomeDisciplina,
            listaDisciplinas[i].CodigoDisciplina, 
            listaDisciplinas[i].SemestreDisciplina, 
            listaDisciplinas[i].ProfessorDisciplina);
    }
}

void listarDisciplinaEspecifica(char disciplina){
    for (int i=0;i<indiceListaDisciplinas;i++){
        if (listaDisciplinas[i].NomeDisciplina == disciplina){
            printf("Nome: %s Codigo: %ld Semestre: %s Professor: %s\n",
                listaDisciplinas[i].NomeDisciplina,
                listaDisciplinas[i].CodigoDisciplina,
                listaDisciplinas[i].SemestreDisciplina,
                listaDisciplinas[i].ProfessorDisciplina);
                for (int j=0;j<10;j++){ //falta navegar nos alunos da respectiva disciplina para printar todos
                    
                }       
        }
    }
}



#endif