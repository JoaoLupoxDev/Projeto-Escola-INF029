#ifndef REPOSITORIO_H
#define REPOSITORIO_H

#include "StructPessoa.h"
#include "StructDisciplina.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
int verificarData(char data[]);
void paraMaiuscula(char *str);
void inserirAlunoNaDisciplina(void);
void menu(void);
void cadastrarPessoa(char tipo);
void excluirPessoa(char tipo);
void atualizarPessoa(char tipo);
void listarPessoas(char tipo);
void listarPessoasPorSexo(char sexo, char tipo);
void listarPessoasPorNome(char tipo);
void listarPessoasPorString(char tipo, char string[]);
void cadastrarDisciplina(void);
int verificarProfessordisciplina(char professor[]);

// --- FUNÇÕES UTILITÁRIAS ---

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
                printf("0 - Sair do Módulo Aluno");
                printf("\nDigite o numero referente a sua escolha: ");
                getchar();
                scanf("%d", &escolhaModulo);
                while (escolhaModulo < 0 || escolhaModulo > 9) {
                    printf("Opção inválida. Digite novamente: ");   
                    getchar();
                    scanf("%d", &escolhaModulo);
                }
                
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
                        paraMaiuscula(&sexo);
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
                getchar();
                scanf("%d", &escolhaModulo);
                while (escolhaModulo < 0 || escolhaModulo > 8) {
                    printf("Opção inválida. Digite novamente: ");
                    getchar(); // Limpa o buffer do scanf anterior
                    scanf("%d", &escolhaModulo);
                }
                
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
                printf("1 - Cadastrar disciplina\n");
                printf("2 - Listar uma disciplina e seus alunos matriculados\n");
                printf("3 - Listar disciplinas que passam de 40 alunos matriculados\n");
                printf("4 - Inserir/Excluir alunos em uma disciplina\n");
                printf("0 - Sair do Modulo Disciplinas\n");
                printf("Digite o numero referente a sua escolha: ");
                getchar();
                scanf("%d", &escolhaModulo);
                while (escolhaModulo < 0 || escolhaModulo > 4) {
                    printf("Opção inválida. Digite novamente: ");
                    getchar(); // Limpa o buffer do scanf anterior
                    scanf("%d", &escolhaModulo);
                }
                switch (escolhaModulo) {
                    case 1:
                        cadastrarDisciplina();
                        break;
                    case 2:
                    case 3:
                    case 4:
                        inserirAlunoNaDisciplina();
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
    int validador;
    char letra;
    listarPessoas(tipo);
    printf("\nDigite a matricula de quem voce deseja atualizar: ");
    scanf("%ld", &matricula);
    getchar();

    for (int i = 0; i < indiceListaPessoas; i++) {
        if (matricula == listaGlobalPessoas.listaDePessoas[i].Matricula && tipo == listaGlobalPessoas.listaDePessoas[i].Tipo){
            printf("Digite o novo nome: ");
            fgets(listaGlobalPessoas.listaDePessoas[i].Nome, sizeof(listaGlobalPessoas.listaDePessoas[i].Nome), stdin);

            printf("Digite o novo CPF: ");
            fgets(listaGlobalPessoas.listaDePessoas[i].CPF, sizeof(listaGlobalPessoas.listaDePessoas[i].CPF), stdin);

            printf("Digite o novo sexo: ");
            scanf(" %c", &listaGlobalPessoas.listaDePessoas[i].Sexo);
            while (listaGlobalPessoas.listaDePessoas[i].Sexo != 'M' && listaGlobalPessoas.listaDePessoas[i].Sexo != 'F') {
                printf("Digite apenas M(masculino) ou F(feminino): ");
                scanf(" %c", &letra);
                listaGlobalPessoas.listaDePessoas[i].Sexo = toupper(letra);   
                getchar();      
            }

            getchar();
            printf("Digite a nova data de nascimento: ");
            getchar();
            fgets(listaGlobalPessoas.listaDePessoas[i].DataNascimento, sizeof(listaGlobalPessoas.listaDePessoas[i].DataNascimento), stdin);
            validador = verificarData(listaGlobalPessoas.listaDePessoas[i].DataNascimento);
            while (validador == 0) {
                printf("Digite uma data valida (dd/mm/aaaa): ");
                fgets(listaGlobalPessoas.listaDePessoas[i].DataNascimento, sizeof(listaGlobalPessoas.listaDePessoas[i].DataNascimento), stdin);
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
        for (int i = 0; i < indiceListaPessoas; i++) {
            if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
                printf("\nNome:%s  Matricula:%ld  Sexo:%c  DataNascimento:%s\n",
                   listaGlobalPessoas.listaDePessoas[i].Nome, 
                   listaGlobalPessoas.listaDePessoas[i].Matricula, 
                   listaGlobalPessoas.listaDePessoas[i].Sexo, 
                   listaGlobalPessoas.listaDePessoas[i].DataNascimento);
            }
        }
    }else{
        if (tipo == 'A'){
            printf("\nNão ha alunos cadastrados no momento.\n");
        }else{
            printf("Não ha professores cadastrados no momento");
        }    
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
        return;
    }else if (validador == 0 && tipo == 'P'){
        printf("Não há professores cadastrados com esse sexo.\n");
        return;
    }
    while (sexo != 'M' && sexo != 'F') {
        printf("Digite apenas M(masculino) ou F(feminino): ");
        scanf(" %c", &sexo);
        paraMaiuscula(&sexo);
    }
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
    int contador=0, contadorPrints=0;
    int validador=0;
    for (int i=0;i<indiceListaPessoas;i++){
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo){
            validador = 1;
            break;
        }
    }
    if (validador == 0 && tipo == 'A'){
        printf("Não há alunos cadastrados no momento.\n");
        return;
    }else if (validador == 0 && tipo == 'P'){
        printf("Não há professores cadastrados no momento.\n");
        return;
    }
    for(int i=0;i<indiceListaPessoas;i++){ //for para navegar nos nomes da lista
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo){
            for (int c=0;c<strlen(listaGlobalPessoas.listaDePessoas[i].Nome);c++){ //for para navegar nas letras do nome
                for (int x=0;x<strlen(string);x++){ //for para navegar nas letras da string de busca
                    if (listaGlobalPessoas.listaDePessoas[i].Nome[c] == string[x]){
                        contador++;
                        c++;
                        for (int y=0;y<strlen(string);y++){
                            if (string[y] == listaGlobalPessoas.listaDePessoas[i].Nome[c]){
                                string[y] = '/';
                            }
                        }
                    }
                }
            }
            if(contador>=strlen(string)){
                printf("Nome: %s\n",listaGlobalPessoas.listaDePessoas[i].Nome);
                contador=0;
                contadorPrints++;
            }
        }
        if (i == indiceListaPessoas-1 && contadorPrints == 0){
            printf("Não foram encontrados nomes com base no texto digitado.\n");
        }
    }
}

void listarDisciplinas(void){
    for (int i=0;i<indiceListaDisciplinas;i++){
        printf("Nome: %s Codigo: %ld\n  Semestre: %s Professor: %s\n",
            listaDisciplinas[i].NomeDisciplina,
            listaDisciplinas[i].CodigoDisciplina, 
            listaDisciplinas[i].SemestreDisciplina, 
            listaDisciplinas[i].ProfessorDisciplina.Nome);
    }
}

void listarDisciplinaEspecifica(char disciplina[]) {
    for (int i = 0; i < indiceListaDisciplinas; i++){
        if (strcmp(listaDisciplinas[i].NomeDisciplina, disciplina) == 0) {
            printf("Nome: %s Codigo: %ld Semestre: %s Professor: %s\n",
                listaDisciplinas[i].NomeDisciplina,
                listaDisciplinas[i].CodigoDisciplina,
                listaDisciplinas[i].SemestreDisciplina,
                listaDisciplinas[i].ProfessorDisciplina.Nome); // Acessa a propriedade .Nome da struct

            for (int j = 0; j < 10; j++) { 
                // navegação nos alunos
            }
            return;
        }
    }
}

int verificarProfessordisciplina(char professor[]){
    for(int i=0;i<indiceListaPessoas;i++){
        if(listaGlobalPessoas.listaDePessoas[i].Tipo=='P'){
            if(strcmp(listaGlobalPessoas.listaDePessoas[i].Nome,professor)==0){
                return 1;
            }
        }

      }
    return 0;
}


void cadastrarDisciplina(void){

    Disciplina disciplina;
    printf("Digite o nome da disciplina: ");
    getchar();
    fgets(disciplina.NomeDisciplina,sizeof(disciplina.NomeDisciplina),stdin);

    printf("Digite o codigo da disciplina: ");
    getchar();
    scanf("%ld",&disciplina.CodigoDisciplina);

    printf("Digite o semestre da disciplina: ");
    getchar();
    fgets(disciplina.SemestreDisciplina,sizeof(disciplina.SemestreDisciplina),stdin);

    printf("Lista de professores cadastrados:\n");
    listarPessoas('P');
    printf("Atribua um professor a disciplina: ");
    fgets(disciplina.ProfessorDisciplina.Nome, sizeof(disciplina.ProfessorDisciplina.Nome), stdin);
    while(verificarProfessordisciplina(disciplina.ProfessorDisciplina.Nome)==0){
        printf("Professor não encontrado ou cadastrado, Digite um professor válido: ");
        fgets(disciplina.ProfessorDisciplina.Nome, sizeof(disciplina.ProfessorDisciplina.Nome),stdin);
    }
    listaDisciplinas[indiceListaDisciplinas] = disciplina;
    indiceListaDisciplinas++;
    printf("Disciplina %s cadastrada com sucesso!\n", disciplina.NomeDisciplina);

}


void inserirAlunoNaDisciplina(){
    if (indiceListaDisciplinas < 0){
        printf("Não existem disciplinas cadastradas.");
        return;
    }
    else if (indiceListaPessoas < 0){
        printf("Não existem alunos cadastrados.");
        return;
    }else{
        int opcao, validaDisciplina=0, validaAluno=0;
        char nome[50];
        listarDisciplinas();
        while (opcao != 0){
            printf("\nDigite o nome da disciplina que deseja inserir o(s) aluno(s): ");
            getchar();
            fgets(nome, 50, stdin);
            for (int i=0;i<indiceListaDisciplinas;i++){
                if (strcmp(listaDisciplinas[i].NomeDisciplina, nome) == 0){
                    validaDisciplina=1;
                }
            }
            if (validaDisciplina == 1){
                printf("\nDisciplina %s selecionada\n", nome);
                break;
            }else{
                printf("\nDigite corretamente o nome da disciplina.\n");
            }
        }
        printf("\nLista de alunos cadastrados:\n");
        listarPessoas('A');
        while (opcao != 0){
            printf("Digite o nome do aluno que deseja inserir na disciplina: ");
            getchar();
            fgets(nome, 50, stdin);
            for (int i=0;i<indiceListaPessoas;i++){
                if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'A'){
                    if (strcmp(listaGlobalPessoas.listaDePessoas[i].Nome, nome) == 0){
                        validaAluno=1;
                        listaDisciplinas[indiceListaDisciplinas-1].AlunosMatriculados[listaDisciplinas[indiceListaDisciplinas-1].indiceAlunosMatriculados] = listaGlobalPessoas.listaDePessoas[i];
                        listaDisciplinas[indiceListaDisciplinas-1].indiceAlunosMatriculados++;
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
                }else if (opcao != 1){
                    printf("Opção inválida, digite 1 para sim ou 0 para não.");
                }
            }else{
                printf("Digite corretamente o nome do aluno.");
            }
        }
    }
}

#endif