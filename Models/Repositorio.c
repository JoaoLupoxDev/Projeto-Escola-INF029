#ifndef REPOSITORIO_H
#define REPOSITORIO_H

#include "StructPessoa.h"
#include "StructDisciplina.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// --- VARIÁVEIS GLOBAIS ---
int indiceListaPessoas = 0;
ListaPessoas listaGlobalPessoas;
int quantidadeAlunos = 0;
int quantidadeProfessores = 0;
int indiceListaDisciplinas = 0;
Disciplina listaDisciplinas[MAX_DISCIPLINAS];

// --- PROTÓTIPOS DE TODAS AS FUNÇÕES ---

int verificaMatricula(long matricula);
int verificaCPF(char cpf[]);
int validaCPF(char cpf[]);
int validarFormatoCPF(const char *cpf);
int verificarData(char data[]);
int lerInteiro();
void paraMaiuscula(char *str);
void inserirAlunoNaDisciplina(void);
void menu(void);
void voltarAoMenu(void);
void cadastrarPessoa(char tipo);
void excluirPessoa(char tipo);
void atualizarPessoa(char tipo);
void listarPessoas(char tipo);
void listarPessoasPorSexo(char sexo, char tipo);
void listarPessoasPorNome(char tipo);
void listarPessoasPorIdade(char tipo);
void listarPessoasPorString(char tipo, char string[]);
void listarDisciplinas(void);
void listarDisciplinaEspecifica(char disciplina[]);
void cadastrarDisciplina(void);
int verificarProfessordisciplina(char professor[]);
void listarDisciplinasComMaisDe40Vagas(void);
void listarMenosDe3Disciplinas(void);
void listaAniversariantesDoMes(void);

// --- FUNÇÕES UTILITÁRIAS ---

int lerInteiro() {
    int valor;
    int resultado = scanf("%d", &valor);

    while (resultado != 1) {
        printf("Opção inválida! Digite apenas um número: ");
        
        // Limpa o lixo (como o "ajd[") do buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        // Tenta ler o novo número digitado pelo usuário
        resultado = scanf("%d", &valor);
    }

    // Limpa o '\n' (Enter) que sobrou após ler o número válido
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    return valor;
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

int validarFormatoCPF(const char *cpf) {
    if (strlen(cpf) != 11) {
        return 0;
    }
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            return 0;
        }
    }
    return 1;
}

int verificarData(char data[]) {
    if (strlen(data) != 10) {   
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
        printf("\n-----MENU ESCOLA-----\n");
        printf("1 - Modulo Aluno\n");
        printf("2 - Modulo Professor\n");
        printf("3 - Modulo Disciplina\n");
        printf("4 - Aniversariantes do mes\n");
        printf("0 - Sair do Menu\n");
        printf("Digite o numero referente a sua escolha: ");
        escolhaMenu = lerInteiro();
        
        switch (escolhaMenu) {
            case 1:
                escolhaModulo = -1;
                while (escolhaModulo != 0) {
                    printf("\n-----MODULO ALUNO-----\n");
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
                    escolhaModulo = lerInteiro(); 

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
                            listarPessoasPorNome('A');
                            break;
                        case 7:
                            listarPessoasPorIdade('A');
                            break;
                        case 8:
                            listarMenosDe3Disciplinas();
                            break;
                        case 9:
                            printf("Digite um texto para buscar alunos com base no texto: ");
                            fgets(texto, sizeof(texto), stdin);
                            texto[strcspn(texto, "\n")] = '\0';
                            listarPessoasPorString('A', texto);         
                            break;
                        case 0:
                            printf("Saindo do Modulo Aluno\n");
                            break;
                        default:
                            printf("Esta opção não existe, digite um numero válido.\n");
                            break;
                    }
                }
                break;
                
            case 2:
                escolhaModulo = -1;
                while (escolhaModulo != 0) {
                    printf("\n-----MODULO PROFESSOR-----\n");
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
                    escolhaModulo = lerInteiro();               
                    
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
                            paraMaiuscula(&sexo);
                            listarPessoasPorSexo(sexo, 'P');
                            break;
                        case 6:
                            listarPessoasPorNome('P');
                            break;
                        case 7:
                            listarPessoasPorIdade('P'); 
                            break;
                        case 8:
                            printf("Digite um texto para buscar professores com base no texto: ");
                            fgets(texto, sizeof(texto), stdin);
                            texto[strcspn(texto, "\n")] = '\0';
                            listarPessoasPorString('P', texto);
                            break;
                        case 0:
                            printf("Saindo do Modulo Professor...\n");
                            break;
                        default:
                            printf("Esta opção não existe, digite um numero válido.\n");
                            break;
                    }
                }
                break;
                
            case 3:
                printf("\n-----MODULO DISCIPLINAS-----\n");
                printf("1 - Cadastrar disciplina\n");
                printf("2 - Listar uma disciplina e seus alunos matriculados\n");
                printf("3 - Listar disciplinas que passam de 40 alunos matriculados\n");
                printf("4 - Inserir/Excluir alunos em uma disciplina\n");
                printf("0 - Sair do Modulo Disciplinas\n");
                printf("Digite o numero referente a sua escolha: ");
                escolhaModulo = lerInteiro();
                
                switch (escolhaModulo) {
                    case 1:
                        cadastrarDisciplina();
                        break;
                    case 2:
                    case 3:
                        listarDisciplinasComMaisDe40Vagas();
                        break;
                    case 4:
                        inserirAlunoNaDisciplina();
                        break;
                    default:
                        printf("Esta opção não existe, digite um numero válido.\n");
                        break;
                }
                break;

            case 4:
                listaAniversariantesDoMes();

            case 0:
                printf("Saindo do menu... Programa encerrado\n");
                break;
            default:
                printf("Esta opção não existe, digite um numero válido.\n");
                break;
        }
    }
}

void voltarAoMenu(void) {
    printf("\nPressione ENTER para voltar ao menu...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarPessoa(char tipo) {
    Pessoa pessoa;
    int validador;

    if (tipo == 'A' || tipo == 'P') {

        printf("Digite o nome a ser cadastrado: ");
        fgets(pessoa.Nome, sizeof(pessoa.Nome), stdin);
        pessoa.Nome[strcspn(pessoa.Nome, "\n")] = '\0';

        printf("Digite a matricula a ser cadastrada: ");
        scanf("%ld", &pessoa.Matricula);
        validador = verificaMatricula(pessoa.Matricula);
        while (validador == 0) {
            printf("Esta matricula ja esta cadastrada, digite outra matricula: ");
            scanf("%ld", &pessoa.Matricula);
            validador = verificaMatricula(pessoa.Matricula);
        }

        printf("Digite o CPF a ser cadastrado: ");
        scanf(" %11s", pessoa.CPF); 

        validador = validarFormatoCPF(pessoa.CPF);
        while (validador == 0) {
            printf("O formato do CPF esta errado, digite os 11 numeros sem pontos e hifen: ");
            scanf("%11s", pessoa.CPF);
            validador = validarFormatoCPF(pessoa.CPF);
        }
        validador = verificaCPF(pessoa.CPF);
        while (validador == 0) {
            printf("Este CPF já está cadastrado, digite outro CPF: ");
            scanf(" %11s", pessoa.CPF);
            validador = verificaCPF(pessoa.CPF);
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
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        fgets(pessoa.DataNascimento, sizeof(pessoa.DataNascimento), stdin);
        pessoa.DataNascimento[strcspn(pessoa.DataNascimento, "\n")] = '\0';
        
        validador = verificarData(pessoa.DataNascimento);
        while (validador == 0) {
            printf("Digite uma data valida (dd/mm/aaaa): ");
            fgets(pessoa.DataNascimento, sizeof(pessoa.DataNascimento), stdin);
            pessoa.DataNascimento[strcspn(pessoa.DataNascimento, "\n")] = '\0';
            validador = verificarData(pessoa.DataNascimento);
        }

        if (tipo == 'A') {
            printf("Aluno %s cadastrado com sucesso!\n", pessoa.Nome);
        }
        else {
            printf("Professor %s cadastrado com sucesso!\n", pessoa.Nome);
        }
    }

    pessoa.Tipo = tipo;

    listaGlobalPessoas.listaDePessoas[indiceListaPessoas] = pessoa;
    indiceListaPessoas++;
    listaGlobalPessoas.quantidadeTotal = indiceListaPessoas;
}

void excluirPessoa(char tipo) {
    int validador=0;
    for (int i=0;i<indiceListaPessoas;i++){
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo){
            validador = 1;
            break;
        }
    }
    if (validador == 0 && tipo == 'A'){
        printf("Não há alunos cadastrados no momento.\n");
        voltarAoMenu();
        return;
    }else if (validador == 0 && tipo == 'P'){
        printf("Não há professores cadastrados no momento.\n");
        voltarAoMenu();
        return;
    }
    long matricula;
    char nomePessoa[50];
    listarPessoas(tipo);
    printf("\nDigite a matricula de quem voce deseja excluir: ");
    scanf("%ld", &matricula);
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (matricula == listaGlobalPessoas.listaDePessoas[i].Matricula && tipo == listaGlobalPessoas.listaDePessoas[i].Tipo) {
            strcpy(nomePessoa, listaGlobalPessoas.listaDePessoas[i].Nome);
            for (int j = i; j < indiceListaPessoas - 1; j++) {
                listaGlobalPessoas.listaDePessoas[j] = listaGlobalPessoas.listaDePessoas[j + 1];
            }
            indiceListaPessoas--;
            listaGlobalPessoas.quantidadeTotal = indiceListaPessoas;
            if (tipo == 'A'){
                printf("\nAluno %s excluido.\n", nomePessoa);
            }else if (tipo == 'P'){
                printf("\nProfessor %s excluido.\n", nomePessoa);
            }
            break;
        }
    }
}

void atualizarPessoa(char tipo) {
    long matricula;
    int validador=0;
    for (int i=0;i<indiceListaPessoas;i++){
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo){
            validador = 1;
            break;
        }
    }
    if (validador == 0 && tipo == 'A'){
        printf("Não há alunos cadastrados no momento.\n");
        voltarAoMenu();
        return;
    }else if (validador == 0 && tipo == 'P'){
        printf("Não há professores cadastrados no momento.\n");
        voltarAoMenu();
        return;
    }
    listarPessoas(tipo);
    printf("\nDigite a matricula de quem voce deseja atualizar: ");
    scanf("%ld", &matricula);

    for (int i = 0; i < indiceListaPessoas; i++) {
        if (matricula == listaGlobalPessoas.listaDePessoas[i].Matricula && tipo == listaGlobalPessoas.listaDePessoas[i].Tipo) {
            printf("Digite o novo nome: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            fgets(listaGlobalPessoas.listaDePessoas[i].Nome, sizeof(listaGlobalPessoas.listaDePessoas[i].Nome), stdin);
            listaGlobalPessoas.listaDePessoas[i].Nome[strcspn(listaGlobalPessoas.listaDePessoas[i].Nome, "\n")] = '\0';
            
            printf("Digite o novo CPF: ");
            fgets(listaGlobalPessoas.listaDePessoas[i].CPF, sizeof(listaGlobalPessoas.listaDePessoas[i].CPF), stdin);
            listaGlobalPessoas.listaDePessoas[i].CPF[strcspn(listaGlobalPessoas.listaDePessoas[i].CPF, "\n")] = '\0';

            printf("Digite o novo sexo: ");
            scanf(" %c", &listaGlobalPessoas.listaDePessoas[i].Sexo);
            
            printf("Digite a nova data de nascimento: ");
            while ((c = getchar()) != '\n' && c != EOF);
            fgets(listaGlobalPessoas.listaDePessoas[i].DataNascimento, sizeof(listaGlobalPessoas.listaDePessoas[i].DataNascimento), stdin);
            listaGlobalPessoas.listaDePessoas[i].DataNascimento[strcspn(listaGlobalPessoas.listaDePessoas[i].DataNascimento, "\n")] = '\0';
            
            validador = verificarData(listaGlobalPessoas.listaDePessoas[i].DataNascimento);
            while (validador == 0) {
                printf("Digite uma data valida (dd/mm/aaaa): ");
                fgets(listaGlobalPessoas.listaDePessoas[i].DataNascimento, sizeof(listaGlobalPessoas.listaDePessoas[i].DataNascimento), stdin);
                listaGlobalPessoas.listaDePessoas[i].DataNascimento[strcspn(listaGlobalPessoas.listaDePessoas[i].DataNascimento, "\n")] = '\0';
                validador = verificarData(listaGlobalPessoas.listaDePessoas[i].DataNascimento);
            }

            printf("\nDados atualizados com sucesso.\n");
            break;
        }
    }
}

void listarPessoas(char tipo) {
    int validador=0;
    for (int i=0;i<indiceListaPessoas;i++){
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo){
            validador = 1;
            break;
        }
    }
    if (validador == 1){
        if(tipo == 'A' || tipo == 'a'){
            printf("\n=== LISTA DE ALUNOS ===\n");
        }
        if(tipo == 'P' || tipo == 'p'){
            printf("\n=== LISTA DE PROFESSORES ===\n");
        }

        for (int i = 0; i < indiceListaPessoas; i++) {
            if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
                printf("\nNome:%s  Matricula:%ld  Sexo:%c  DataNascimento:%s\n",
                   listaGlobalPessoas.listaDePessoas[i].Nome, 
                   listaGlobalPessoas.listaDePessoas[i].Matricula, 
                   listaGlobalPessoas.listaDePessoas[i].Sexo, 
                   listaGlobalPessoas.listaDePessoas[i].DataNascimento);
            }
        }
        voltarAoMenu();

    }else{
        if (tipo == 'A'){
            printf("\nNão ha alunos cadastrados no momento.\n");
        }else if (tipo == 'P'){
            printf("Não ha professores cadastrados no momento.\n");
        }
        voltarAoMenu();
    }
}

void listarPessoasPorSexo(char sexo, char tipo) {
    int validador=0;
    for (int i=0;i<indiceListaPessoas;i++){
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo){
            validador = 1;
            break;
        }
    }
    if (validador == 0 && tipo == 'A'){
        printf("Não há alunos cadastrados com esse sexo.\n");
        voltarAoMenu();
        return;
    }else if (validador == 0 && tipo == 'P'){
        printf("Não há professores cadastrados com esse sexo.\n");
        voltarAoMenu();
        return;
    }
    while (sexo != 'M' && sexo != 'F') {
        printf("Digite apenas M(masculino) ou F(feminino): ");
        scanf(" %c", &sexo);
        paraMaiuscula(&sexo);
    }
    printf("\n=== LISTA POR SEXO ===\n");
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo && listaGlobalPessoas.listaDePessoas[i].Sexo == sexo) {
            printf("Nome:%s  Matricula:%ld  Sexo:%c  DataNascimento:%s \n",
                   listaGlobalPessoas.listaDePessoas[i].Nome, 
                   listaGlobalPessoas.listaDePessoas[i].Matricula, 
                   listaGlobalPessoas.listaDePessoas[i].Sexo, 
                   listaGlobalPessoas.listaDePessoas[i].DataNascimento);
        }
    }
    voltarAoMenu();
}

int compararNomesSeguro(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        char c1 = s1[i];
        char c2 = s2[i];

        if (c1 == '\n' || c1 == '\r') c1 = '\0';
        if (c2 == '\n' || c2 == '\r') c2 = '\0';

        if (c1 == '\0' || c2 == '\0') break;

        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

        if (c1 != c2) {
            return c1 - c2;
        }
        i++;
    }
    return 0;
}

void listarPessoasPorNome(char tipo) {
    if (indiceListaPessoas == 0) {
        printf("\nNenhum cadastro encontrado.\n");
        voltarAoMenu();
        return;
    }
    Pessoa nomesOrdenados[indiceListaPessoas]; 
    int qtd = 0;

    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
            nomesOrdenados[qtd] = listaGlobalPessoas.listaDePessoas[i];
            qtd++;
        }
    }

    if (qtd == 0) {
        if (tipo == 'A') {
            printf("\nNenhum aluno cadastrado.\n");
            voltarAoMenu();
            return;
        } else if (tipo == 'P') {
            printf("\nNenhum professor cadastrado.\n");
            voltarAoMenu();
            return;
        }
    }

    for (int i = 0; i < qtd - 1; i++) {
        for (int k = i + 1; k < qtd; k++) {
            if (compararNomesSeguro(nomesOrdenados[i].Nome, nomesOrdenados[k].Nome) > 0) {
                Pessoa temp = nomesOrdenados[i];
                nomesOrdenados[i] = nomesOrdenados[k];
                nomesOrdenados[k] = temp;
            }
        }
    }

    printf("\n=== LISTA EM ORDEM ALFABETICA ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("Nome: %s | Matricula: %ld | Sexo: %c | DataNasc: %s\n",
               nomesOrdenados[i].Nome,
               nomesOrdenados[i].Matricula,
               nomesOrdenados[i].Sexo,
               nomesOrdenados[i].DataNascimento);
    }
    voltarAoMenu();
}

int compararIdade(char d1[], char d2[]){
    int ano1 = ((d1[6]-'0')*1000 + (d1[7]-'0')*100 + (d1[8]-'0')*10 + (d1[9]-'0')); 
    int ano2 = ((d2[6]-'0')*1000 + (d2[7]-'0')*100 + (d2[8]-'0')*10 + (d2[9]-'0'));
    if(ano1 != ano2){
        return ano1 - ano2;
    }

    int mes1 = ((d1[3]-'0')*10 + (d1[4]-'0')); 
    int mes2 = ((d2[3]-'0')*10 + (d2[4]-'0')); 
    if(mes1 != mes2){
        return mes1 - mes2;
    }

    int dia1 = ((d1[0]-'0')*10 + (d1[1]-'0')); 
    int dia2 = ((d2[0]-'0')*10 + (d2[1]-'0'));
    return dia1 - dia2; 
}

void listaAniversariantesDoMes(void) {
    // define o mes atual
    time_t t = time(NULL);           
    struct tm tm = *localtime(&t);   
    int mesAtual = tm.tm_mon + 1; 

    if (indiceListaPessoas == 0) {
        printf("\nNao ha pessoas cadastradas no momento.\n");
        voltarAoMenu();
        return;
    }

    Pessoa alunosAniversariantes[indiceListaPessoas];  
    Pessoa professoresAniversariantes[indiceListaPessoas];  
    int qtdAlunos = 0;
    int qtdProfessores = 0;

    printf("\n=== LISTA ANIVERSARIANTES DESSE MES (%d) ===\n", mesAtual);
    
    for (int i = 0; i < indiceListaPessoas; i++) {
        int mesNascimento = ((listaGlobalPessoas.listaDePessoas[i].DataNascimento[3] - '0') * 10) + 
                            (listaGlobalPessoas.listaDePessoas[i].DataNascimento[4] - '0');

        if (mesAtual == mesNascimento) {
            if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'A') {
                alunosAniversariantes[qtdAlunos] = listaGlobalPessoas.listaDePessoas[i];
                qtdAlunos++;
            } else if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'P') {
                professoresAniversariantes[qtdProfessores] = listaGlobalPessoas.listaDePessoas[i];
                qtdProfessores++;
            }
        }
    }

    if (qtdAlunos == 0 && qtdProfessores == 0) {
        printf("Nenhum aniversariante no mes.\n");
        voltarAoMenu();
        return;
    }

    for (int i = 0; i < qtdAlunos - 1; i++) {
        for (int k = i + 1; k < qtdAlunos; k++) {
            int dia1 = (alunosAniversariantes[i].DataNascimento[0]-'0')*10 + (alunosAniversariantes[i].DataNascimento[1]-'0');
            int dia2 = (alunosAniversariantes[k].DataNascimento[0]-'0')*10 + (alunosAniversariantes[k].DataNascimento[1]-'0');
            if (dia1 > dia2) {
                Pessoa temp = alunosAniversariantes[i];
                alunosAniversariantes[i] = alunosAniversariantes[k];
                alunosAniversariantes[k] = temp;
            }
        }   
    }

    for (int i = 0; i < qtdProfessores - 1; i++) {
        for (int k = i + 1; k < qtdProfessores; k++) {
            int dia1 = (professoresAniversariantes[i].DataNascimento[0]-'0')*10 + (professoresAniversariantes[i].DataNascimento[1]-'0');
            int dia2 = (professoresAniversariantes[k].DataNascimento[0]-'0')*10 + (professoresAniversariantes[k].DataNascimento[1]-'0');
            if (dia1 > dia2) {
                Pessoa temp = professoresAniversariantes[i];
                professoresAniversariantes[i] = professoresAniversariantes[k];
                professoresAniversariantes[k] = temp;
            }
        }   
    }

    printf("\n   ALUNOS   \n");
    if (qtdAlunos == 0) {
        printf("Nenhum aluno aniversariante este mes.\n");
    } else {
        for (int i = 0; i < qtdAlunos; i++) {
            printf("Nome: %s | Aniversario: %s | Matricula: %ld\n",
                   alunosAniversariantes[i].Nome,
                   alunosAniversariantes[i].DataNascimento,
                   alunosAniversariantes[i].Matricula);
        }
    }

    printf("\n   PROFESSORES   \n");
    if (qtdProfessores == 0) {
        printf("Nenhum professor aniversariante este mes.\n");
    } else {
        for (int i = 0; i < qtdProfessores; i++) {
            printf("Nome: %s | Aniversario: %s | Matricula: %ld\n",
                   professoresAniversariantes[i].Nome,
                   professoresAniversariantes[i].DataNascimento,
                   professoresAniversariantes[i].Matricula);
        }
    }
    voltarAoMenu();    
}


void listarPessoasPorIdade(char tipo){
    if (indiceListaPessoas == 0) {
        printf("\nNenhum cadastro encontrado.\n");
        return;
    }
    Pessoa IdadesOrdenadas[indiceListaPessoas]; 
    int qtd = 0;

    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
            IdadesOrdenadas[qtd] = listaGlobalPessoas.listaDePessoas[i];
            qtd++;
        }
    }

    if (qtd == 0) {
        printf("\nNenhum cadastro do tipo selecionado.\n");
        return;
    }

    for(int i = 0; i < qtd-1; i++){
        for(int k = i+1; k<qtd; k++){
            if(compararIdade(IdadesOrdenadas[i].DataNascimento, IdadesOrdenadas[k].DataNascimento) > 0){
                Pessoa temp;
                temp = IdadesOrdenadas[k];
                IdadesOrdenadas[k] = IdadesOrdenadas[i];
                IdadesOrdenadas[i] = temp;            
            }
        }
    }

    printf("\n=== LISTA POR DATA DE NASCIMENTO (CRONOLOGICA) ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("Data Nasc: %s | Nome: %s | Matricula: %ld | Sexo: %c\n",
               IdadesOrdenadas[i].DataNascimento,
               IdadesOrdenadas[i].Nome,
               IdadesOrdenadas[i].Matricula,
               IdadesOrdenadas[i].Sexo);
    }
    voltarAoMenu();
}

void listarPessoasPorString(char tipo, char string[]) {
    int validador = 0;

    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
            validador = 1;
            break;
        }
    }

    if (validador == 0) {
        if (tipo == 'A') {
            printf("Não há alunos cadastrados no momento.\n");
        } else if (tipo == 'P') {
            printf("Não há professores cadastrados no momento.\n");
        }
        voltarAoMenu();
        return;
    }

    int contadorPrints = 0;

    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
            if (strstr(listaGlobalPessoas.listaDePessoas[i].Nome, string) != NULL) {
                printf("Nome: %s\n", listaGlobalPessoas.listaDePessoas[i].Nome);
                contadorPrints++;
            }
        }
    }

    if (contadorPrints == 0) {
        printf("Não foram encontrados nomes com base no texto digitado.\n");
    }

    voltarAoMenu();
}

void listarDisciplinas(void) {
    for (int i = 0; i < indiceListaDisciplinas; i++) {
        printf("Nome: %s Codigo: %ld\n  Semestre: %d Professor: %s\n",
            listaDisciplinas[i].NomeDisciplina,
            listaDisciplinas[i].CodigoDisciplina, 
            listaDisciplinas[i].SemestreDisciplina, 
            listaDisciplinas[i].ProfessorDisciplina.Nome);
    }
}

void listarDisciplinaEspecifica(char disciplina[]) {
    for (int i = 0; i < indiceListaDisciplinas; i++) {
        if (strcmp(listaDisciplinas[i].NomeDisciplina, disciplina) == 0) {
            printf("Nome: %s Codigo: %ld Semestre: %d Professor: %s\n",
                listaDisciplinas[i].NomeDisciplina,
                listaDisciplinas[i].CodigoDisciplina,
                listaDisciplinas[i].SemestreDisciplina,
                listaDisciplinas[i].ProfessorDisciplina.Nome);

            return;
        }
    }
    voltarAoMenu();
}

int verificarProfessordisciplina(char professor[]) {
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'P') {
            if (strcmp(listaGlobalPessoas.listaDePessoas[i].Nome, professor) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void cadastrarDisciplina(void) {
    int validador=0;
    for (int i = 0; i < indiceListaPessoas; i++){
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'P'){
            validador = 1;
            break;
        }
    }
    if (validador == 1){
        Disciplina disciplina;
        printf("Digite o nome da disciplina: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        fgets(disciplina.NomeDisciplina, sizeof(disciplina.NomeDisciplina), stdin);
        disciplina.NomeDisciplina[strcspn(disciplina.NomeDisciplina, "\n")] = '\0';

        printf("Digite o codigo da disciplina: ");
        scanf("%ld", &disciplina.CodigoDisciplina);

        printf("Digite o semestre da disciplina: ");
        scanf("%d", &disciplina.SemestreDisciplina);

        while (disciplina.SemestreDisciplina != 1 && disciplina.SemestreDisciplina != 2){
            printf("Digite apenas 1 (Primeiro semestre) ou 2 (Segundo semestre): ");
            scanf("%d", &disciplina.SemestreDisciplina);
        }

        printf("Lista de professores cadastrados:\n");
        listarPessoas('P');
        printf("Atribua um professor a disciplina: ");
        while ((c = getchar()) != '\n' && c != EOF);
        fgets(disciplina.ProfessorDisciplina.Nome, sizeof(disciplina.ProfessorDisciplina.Nome), stdin);
        disciplina.ProfessorDisciplina.Nome[strcspn(disciplina.ProfessorDisciplina.Nome, "\n")] = '\0';

        while (verificarProfessordisciplina(disciplina.ProfessorDisciplina.Nome) == 0) {
            printf("Professor não encontrado ou cadastrado, Digite um professor válido: ");
            fgets(disciplina.ProfessorDisciplina.Nome, sizeof(disciplina.ProfessorDisciplina.Nome), stdin);
            disciplina.ProfessorDisciplina.Nome[strcspn(disciplina.ProfessorDisciplina.Nome, "\n")] = '\0';
        }
        listaDisciplinas[indiceListaDisciplinas] = disciplina;
        indiceListaDisciplinas++;
        printf("Disciplina %s cadastrada com sucesso!\n", disciplina.NomeDisciplina);
    }else{
        printf("É preciso cadastrar professores antes de cadastrar uma disciplina.");
        voltarAoMenu();
    }
}

void inserirAlunoNaDisciplina(){
    if (indiceListaDisciplinas <= 0){
        printf("Não existem disciplinas cadastradas.");
        return;
    }
    if (indiceListaPessoas <= 0){
        printf("Não existem alunos cadastrados.");
        return;
    }

    int opcao = -1, validaDisciplina = 0, validaAluno = 0;
    char nome[50];
    listarDisciplinas();
    
    while (opcao != 0){
        printf("\nDigite o nome da disciplina que deseja inserir o(s) aluno(s): ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';

        for (int i = 0; i < indiceListaDisciplinas; i++){
            if (strcmp(listaDisciplinas[i].NomeDisciplina, nome) == 0){
                validaDisciplina = 1;
                break;
            }
        }
        if (validaDisciplina == 1){
            printf("\nDisciplina %s selecionada\n", nome);
            break;
        } else {
            printf("\nDigite corretamente o nome da disciplina.\n");
        }
    }

    printf("\nLista de alunos cadastrados:\n");
    listarPessoas('A');

    while (opcao != 0){
        printf("Digite o nome do aluno que deseja inserir na disciplina: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';

        for (int i = 0; i < indiceListaPessoas; i++){
            if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'A'){
                if (strcmp(listaGlobalPessoas.listaDePessoas[i].Nome, nome) == 0){
                    validaAluno = 1;
                    listaDisciplinas[indiceListaDisciplinas-1].AlunosMatriculados[listaDisciplinas[indiceListaDisciplinas-1].indiceAlunosMatriculados] = listaGlobalPessoas.listaDePessoas[i];
                    listaDisciplinas[indiceListaDisciplinas-1].indiceAlunosMatriculados++;
                    listaGlobalPessoas.listaDePessoas[i].materiasmatriculadas++;
                    break;
                }
            }
        } 
        if (validaAluno == 1){
            printf("Aluno %s inserido.", nome);
            printf("Deseja inserir outro aluno? (1 - Sim | 0 - Não): ");
            scanf("%d", &opcao);
            if (opcao == 0){
                break;
            } else if (opcao != 1){
                printf("Opção inválida, digite 1 para sim ou 0 para não.");
            }
        } else {
            printf("Digite corretamente o nome do aluno.");
        }
    }
}

void listarDisciplinasComMaisDe40Vagas(void){
    if (indiceListaDisciplinas > 0){
        int cont=0;
        for (int i=0;i<indiceListaDisciplinas;i++){
            if (listaDisciplinas[i].indiceAlunosMatriculados > 40){
                    printf("Disciplina: %s Professor: %s Codigo: %ld Semestre: %d\n", 
                    listaDisciplinas[i].NomeDisciplina,
                    listaDisciplinas[i].ProfessorDisciplina.Nome,
                    listaDisciplinas[i].CodigoDisciplina,
                    listaDisciplinas[i].SemestreDisciplina);
                    cont++;
            }
        }
        if (cont == 0){
            printf("Não existem disciplinas com mais de 40 vagas.");
        }
    }else{
        printf("Não existem disciplinas cadastradas.");
    }
    voltarAoMenu();
}

void listarMenosDe3Disciplinas(void){
    int possuiAlunos = 0;
    int alunosEncontrados = 0;
     for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'A') {
            possuiAlunos = 1;
            break;
        }
       
    }
     if(possuiAlunos == 0){
            printf("Não existem alunos cadastrados no momento.\n");
            voltarAoMenu();
            return;
        }

    printf("\n=== ALUNOS COM MENOS DE 3 DISCIPLINAS ===\n");
     for(int i=0;i<indiceListaPessoas;i++){
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'A' && listaGlobalPessoas.listaDePessoas[i].materiasmatriculadas < 3){
            printf("\nAluno: %s Matricula: %ld Quantidade de disciplinas: %d",listaGlobalPessoas.listaDePessoas[i].Nome,listaGlobalPessoas.listaDePessoas[i].Matricula, listaGlobalPessoas.listaDePessoas[i].materiasmatriculadas );
        
            alunosEncontrados++;
        }
     
    }
    if(alunosEncontrados == 0){
        printf("Não existem alunos matriculados em menos de 3 disciplinas.\n");
     }
    voltarAoMenu();
    
   
}

#endif