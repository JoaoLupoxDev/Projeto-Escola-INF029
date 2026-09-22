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

// --- PROTÓTIPOS DE FUNÇÕES ---
int verificaMatricula(long matricula);
int ehCPFValido(const char cpf[]);
int verificaCPF(char cpf[]);
int verificaCPFExcluindoMatricula(char cpf[], long matriculaAtual);
int verificarData(char data[]);
int lerInteiro(void);
void limparBuffer(void);
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

// --- FUNÇÕES UTILITÁRIAS E VALIDAÇÕES ---

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int lerInteiro(void) {
    int valor;
    int resultado = scanf("%d", &valor);

    while (resultado != 1) {
        printf("Opção inválida! Digite apenas um número: ");
        limparBuffer();
        resultado = scanf("%d", &valor);
    }

    limparBuffer();
    return valor;
}

void paraMaiuscula(char *str) {
    if (str && *str >= 'a' && *str <= 'z') {
        *str -= 32;
    }
}

int verificaMatricula(long matricula) {
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (matricula == listaGlobalPessoas.listaDePessoas[i].Matricula) {
            return 0; // Matrícula já existe
        }
    }
    return 1; // Matrícula disponível
}

int ehCPFValido(const char cpf[]) {
    char apenasNumeros[12];
    int j = 0;

    for (int i = 0; cpf[i] != '\0'; i++) {
        if (isdigit((unsigned char)cpf[i])) {
            if (j < 11) {
                apenasNumeros[j++] = cpf[i];
            } else {
                return 0; 
            }
        }
    }
    apenasNumeros[j] = '\0';

    if (j != 11) return 0;

    int todosIguais = 1;
    for (int i = 1; i < 11; i++) {
        if (apenasNumeros[i] != apenasNumeros[0]) {
            todosIguais = 0;
            break;
        }
    }
    if (todosIguais) return 0;

    int soma = 0;
    for (int i = 0; i < 9; i++) {
        soma += (apenasNumeros[i] - '0') * (10 - i);
    }
    int resto = soma % 11;
    int digito1 = (resto < 2) ? 0 : (11 - resto);

    if (digito1 != (apenasNumeros[9] - '0')) return 0;

    soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += (apenasNumeros[i] - '0') * (11 - i);
    }
    resto = soma % 11;
    int digito2 = (resto < 2) ? 0 : (11 - resto);

    if (digito2 != (apenasNumeros[10] - '0')) return 0;

    return 1; 
}

// Para cadastros novos
int verificaCPF(char cpf[]) {
    if (!ehCPFValido(cpf)) {
        return -1; // Estrutura/cálculo inválido
    }

    for (int i = 0; i < indiceListaPessoas; i++) {
        if (strcmp(listaGlobalPessoas.listaDePessoas[i].CPF, cpf) == 0) {
            return 0; // Já cadastrado por outra pessoa
        }
    }

    return 1; // Válido
}

// Para atualização de cadastros existentes
int verificaCPFExcluindoMatricula(char cpf[], long matriculaAtual) {
    if (!ehCPFValido(cpf)) {
        return -1; // Estrutura/cálculo inválido
    }

    for (int i = 0; i < indiceListaPessoas; i++) {
        if (strcmp(listaGlobalPessoas.listaDePessoas[i].CPF, cpf) == 0 && 
            listaGlobalPessoas.listaDePessoas[i].Matricula != matriculaAtual) {
            return 0; // CPF pertence a OUTRA pessoa
        }
    }

    return 1; // Válido (pode ser o mesmo CPF da própria pessoa ou um novo não usado)
}

int ehBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int verificarData(char data[]) {
    // 1. Verificação do tamanho exato e dos separadores
    if (strlen(data) != 10) return 0;
    if (data[2] != '/' || data[5] != '/') return 0;

    // 2. Garantir que todos os caracteres nas posições corretas são dígitos
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit((unsigned char)data[i])) return 0;
    }

    // 3. Extração numérica de dia, mês e ano
    int dia = (data[0] - '0') * 10 + (data[1] - '0');
    int mes = (data[3] - '0') * 10 + (data[4] - '0');
    int ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + 
              (data[8] - '0') * 10 + (data[9] - '0');

    // 4. Validação básica de mês
    if (mes < 1 || mes > 12) return 0;

    // 5. Quantidade limite de dias por mês
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ajusta Fevereiro para anos bissextos
    if (mes == 2 && ehBissexto(ano)) {
        diasPorMes[2] = 29;
    }

    // Valida se o dia está no intervalo do mês
    if (dia < 1 || dia > diasPorMes[mes]) return 0;

    // 6. Validação de ano consciente do calendário atual (sem datas futuras ou anos surreais)
    time_t t = time(NULL);
    struct tm tmAtual = *localtime(&t);
    int anoAtual = tmAtual.tm_year + 1900;
    int mesAtual = tmAtual.tm_mon + 1;
    int diaAtual = tmAtual.tm_mday;

    // Limite inferior razoável (ex: pessoa com no máximo ~120 anos)
    if (ano < 1900) return 0;

    // Se o ano for futuro
    if (ano > anoAtual) return 0;

    // Se o ano for o atual, verifica se o mês ou dia são futuros
    if (ano == anoAtual) {
        if (mes > mesAtual) return 0;
        if (mes == mesAtual && dia > diaAtual) return 0;
    }

    return 1; // Data é válida e coerente
}

// --- MENUS E MÓDULOS ---

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
                            limparBuffer();
                            paraMaiuscula(&sexo);
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
                            printf("Digite um texto para buscar alunos: ");
                            fgets(texto, sizeof(texto), stdin);
                            texto[strcspn(texto, "\n")] = '\0';
                            listarPessoasPorString('A', texto);         
                            break;
                        case 0:
                            printf("Saindo do Modulo Aluno...\n");
                            break;
                        default:
                            printf("Esta opção não existe, digite um número válido.\n");
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
                            limparBuffer();
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
                            printf("Digite um texto para buscar professores: ");
                            fgets(texto, sizeof(texto), stdin);
                            texto[strcspn(texto, "\n")] = '\0';
                            listarPessoasPorString('P', texto);
                            break;
                        case 0:
                            printf("Saindo do Modulo Professor...\n");
                            break;
                        default:
                            printf("Esta opção não existe, digite um número válido.\n");
                            break;
                    }
                }
                break;
                
            case 3:
                escolhaModulo = -1;
                while (escolhaModulo != 0) {
                    printf("\n-----MODULO DISCIPLINAS-----\n");
                    printf("1 - Cadastrar disciplina\n");
                    printf("2 - Listar todas as disciplinas\n");
                    printf("3 - Listar disciplinas que passam de 40 alunos matriculados\n");
                    printf("4 - Inserir aluno em uma disciplina\n");
                    printf("0 - Sair do Modulo Disciplinas\n");
                    printf("Digite o numero referente a sua escolha: ");
                    escolhaModulo = lerInteiro();
                    
                    switch (escolhaModulo) {
                        case 1:
                            cadastrarDisciplina();
                            break;
                        case 2:
                            listarDisciplinas();
                            voltarAoMenu();
                            break;
                        case 3:
                            listarDisciplinasComMaisDe40Vagas();
                            break;
                        case 4:
                            inserirAlunoNaDisciplina();
                            break;
                        case 0:
                            printf("Saindo do Módulo Disciplinas...\n");
                            break;
                        default:
                            printf("Esta opção não existe, digite um número válido.\n");
                            break;
                    }
                }
                break;

            case 4:
                listaAniversariantesDoMes();
                break;

            case 0:
                printf("Saindo do menu... Programa encerrado.\n");
                break;
            default:
                printf("Esta opção não existe, digite um número válido.\n");
                break;
        }
    }
}

void voltarAoMenu(void) {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void cadastrarPessoa(char tipo) {
    Pessoa pessoa;
    memset(&pessoa, 0, sizeof(Pessoa));
    int validador;

    if (tipo == 'A' || tipo == 'P') {
        printf("Digite o nome a ser cadastrado: ");
        fgets(pessoa.Nome, sizeof(pessoa.Nome), stdin);
        pessoa.Nome[strcspn(pessoa.Nome, "\n")] = '\0';

        printf("Digite a matricula a ser cadastrada: ");
        scanf("%ld", &pessoa.Matricula);
        limparBuffer();
        
        validador = verificaMatricula(pessoa.Matricula);
        while (validador == 0) {
            printf("Esta matricula ja esta cadastrada, digite outra matricula: ");
            scanf("%ld", &pessoa.Matricula);
            limparBuffer();
            validador = verificaMatricula(pessoa.Matricula);
        }

        printf("Digite o CPF a ser cadastrado (apenas numeros): ");
        scanf("%14s", pessoa.CPF); 
        limparBuffer();

        validador = verificaCPF(pessoa.CPF);
        while (validador != 1) {
            if (validador == -1) {
                printf("CPF invalido! Digite os 11 numeros sem pontos e hifen: ");
            } else if (validador == 0) {
                printf("Este CPF ja esta cadastrado, digite outro CPF: ");
            }
            scanf("%14s", pessoa.CPF);
            limparBuffer();
            validador = verificaCPF(pessoa.CPF);
        }

        printf("Digite o sexo (M/F): ");
        scanf(" %c", &pessoa.Sexo);
        limparBuffer();
        paraMaiuscula(&pessoa.Sexo);    
        while (pessoa.Sexo != 'M' && pessoa.Sexo != 'F') {
            printf("Digite apenas M(masculino) ou F(feminino): ");
            scanf(" %c", &pessoa.Sexo);
            limparBuffer();
            paraMaiuscula(&pessoa.Sexo);
        }

        printf("Digite a data de nascimento (dd/mm/aaaa): ");
        fgets(pessoa.DataNascimento, sizeof(pessoa.DataNascimento), stdin);
        pessoa.DataNascimento[strcspn(pessoa.DataNascimento, "\n")] = '\0';
        
        validador = verificarData(pessoa.DataNascimento);
        while (validador == 0) {
            printf("Digite uma data valida (dd/mm/aaaa): ");
            fgets(pessoa.DataNascimento, sizeof(pessoa.DataNascimento), stdin);
            pessoa.DataNascimento[strcspn(pessoa.DataNascimento, "\n")] = '\0';
            validador = verificarData(pessoa.DataNascimento);
        }

        pessoa.Tipo = tipo;
        pessoa.materiasmatriculadas = 0;

        listaGlobalPessoas.listaDePessoas[indiceListaPessoas] = pessoa;
        indiceListaPessoas++;
        listaGlobalPessoas.quantidadeTotal = indiceListaPessoas;

        if (tipo == 'A') {
            printf("Aluno %s cadastrado com sucesso!\n", pessoa.Nome);
        } else {
            printf("Professor %s cadastrado com sucesso!\n", pessoa.Nome);
        }
    }
}

void excluirPessoa(char tipo) {
    int validador = 0;
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
            validador = 1;
            break;
        }
    }
    if (!validador) {
        printf("Não há %s cadastrados no momento.\n", (tipo == 'A' ? "alunos" : "professores"));
        voltarAoMenu();
        return;
    }

    long matricula;
    char nomePessoa[50];
    listarPessoas(tipo);
    printf("\nDigite a matricula de quem voce deseja excluir: ");
    scanf("%ld", &matricula);
    limparBuffer();

    for (int i = 0; i < indiceListaPessoas; i++) {
        if (matricula == listaGlobalPessoas.listaDePessoas[i].Matricula && tipo == listaGlobalPessoas.listaDePessoas[i].Tipo) {
            strcpy(nomePessoa, listaGlobalPessoas.listaDePessoas[i].Nome);
            for (int j = i; j < indiceListaPessoas - 1; j++) {
                listaGlobalPessoas.listaDePessoas[j] = listaGlobalPessoas.listaDePessoas[j + 1];
            }
            indiceListaPessoas--;
            listaGlobalPessoas.quantidadeTotal = indiceListaPessoas;
            
            printf("\n%s %s excluido(a) com sucesso.\n", (tipo == 'A' ? "Aluno" : "Professor"), nomePessoa);
            break;
        }
    }
}

void atualizarPessoa(char tipo) {
    long matricula;
    int validador = 0;
    int indiceEncontrado = -1;

    // 1. Verifica se existem pessoas do tipo solicitado
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
            validador = 1;
            break;
        }
    }

    if (!validador) {
        printf("Não há %s cadastrados no momento.\n", (tipo == 'A' ? "alunos" : "professores"));
        voltarAoMenu();
        return;
    }

    // 2. Exibe os cadastros atuais e solicita a matrícula
    listarPessoas(tipo);
    printf("\nDigite a matricula de quem voce deseja atualizar: ");
    scanf("%ld", &matricula);
    limparBuffer();

    // 3. Procura o índice correspondente
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Matricula == matricula && 
            listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1) {
        printf("Matrícula não encontrada.\n");
        voltarAoMenu();
        return;
    }

    // Usamos uma variável auxiliar temporária para evitar corromper o registro caso o usuário digite algo errado
    Pessoa temp = listaGlobalPessoas.listaDePessoas[indiceEncontrado];

    // --- LEITURA DO NOVO NOME ---
    printf("Digite o novo nome: ");
    fgets(temp.Nome, sizeof(temp.Nome), stdin);
    temp.Nome[strcspn(temp.Nome, "\n")] = '\0';
    
    // --- LEITURA DO NOVO CPF ---
    printf("Digite o novo CPF: ");
    scanf("%14s", temp.CPF);
    limparBuffer();

    validador = verificaCPFExcluindoMatricula(temp.CPF, temp.Matricula);
    while (validador != 1) {
        if (validador == -1) {
            printf("CPF invalido! Digite os 11 numeros sem pontos e hifen: ");
        } else if (validador == 0) {
            printf("Este CPF ja esta cadastrado para outra pessoa, digite outro CPF: ");
        }
        scanf("%14s", temp.CPF);
        limparBuffer();
        validador = verificaCPFExcluindoMatricula(temp.CPF, temp.Matricula);
    }

    // --- LEITURA DO SEXO ---
    printf("Digite o novo sexo (M/F): ");
    scanf(" %c", &temp.Sexo);
    limparBuffer();
    paraMaiuscula(&temp.Sexo);
    while (temp.Sexo != 'M' && temp.Sexo != 'F') {
        printf("Digite apenas M(masculino) ou F(feminino): ");
        scanf(" %c", &temp.Sexo);
        limparBuffer();
        paraMaiuscula(&temp.Sexo);
    }

    // --- LEITURA DA DATA DE NASCIMENTO ---
    printf("Digite a nova data de nascimento (dd/mm/aaaa): ");
    fgets(temp.DataNascimento, sizeof(temp.DataNascimento), stdin);
    temp.DataNascimento[strcspn(temp.DataNascimento, "\n")] = '\0';
    
    validador = verificarData(temp.DataNascimento);
    while (validador == 0) {
        printf("Digite uma data valida (dd/mm/aaaa): ");
        fgets(temp.DataNascimento, sizeof(temp.DataNascimento), stdin);
        temp.DataNascimento[strcspn(temp.DataNascimento, "\n")] = '\0';
        validador = verificarData(temp.DataNascimento);
    }

    // Preserva intactos o Tipo, a Matrícula original e as matérias matriculadas
    temp.Tipo = tipo;
    temp.Matricula = matricula;

    // Aplica as alterações no registro global com segurança
    listaGlobalPessoas.listaDePessoas[indiceEncontrado] = temp;

    printf("\nDados atualizados com sucesso.\n");
    voltarAoMenu();
}

void listarPessoas(char tipo) {
    int validador = 0;
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
            validador = 1;
            break;
        }
    }

    if (validador) {
        printf("\n=== LISTA DE %s ===\n", (tipo == 'A' || tipo == 'a') ? "ALUNOS" : "PROFESSORES");
        for (int i = 0; i < indiceListaPessoas; i++) {
            if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
                printf("Nome: %-20s | Matricula: %-8ld | CPF: %-11s | Sexo: %c | DataNasc: %s\n",
                   listaGlobalPessoas.listaDePessoas[i].Nome, 
                   listaGlobalPessoas.listaDePessoas[i].Matricula, 
                   listaGlobalPessoas.listaDePessoas[i].CPF,
                   listaGlobalPessoas.listaDePessoas[i].Sexo, 
                   listaGlobalPessoas.listaDePessoas[i].DataNascimento);
            }
        }
    } else {
        printf("\nNão há %s cadastrados no momento.\n", (tipo == 'A' ? "alunos" : "professores"));
    }
}

void listarPessoasPorSexo(char sexo, char tipo) {
    int encontrou = 0;
    while (sexo != 'M' && sexo != 'F') {
        printf("Digite apenas M(masculino) ou F(feminino): ");
        scanf(" %c", &sexo);
        limparBuffer();
        paraMaiuscula(&sexo);
    }

    printf("\n=== LISTA POR SEXO (%c) ===\n", sexo);
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo && listaGlobalPessoas.listaDePessoas[i].Sexo == sexo) {
            printf("Nome: %-20s | Matricula: %-8ld | DataNasc: %s\n",
                   listaGlobalPessoas.listaDePessoas[i].Nome, 
                   listaGlobalPessoas.listaDePessoas[i].Matricula, 
                   listaGlobalPessoas.listaDePessoas[i].DataNascimento);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum cadastro do tipo selecionado com este sexo.\n");
    }
    voltarAoMenu();
}

int compararNomesSeguro(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        char c1 = tolower((unsigned char)s1[i]);
        char c2 = tolower((unsigned char)s2[i]);

        if (c1 != c2) {
            return c1 - c2;
        }
        i++;
    }
    return s1[i] - s2[i];
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
        printf("\nNenhum cadastro encontrado.\n");
        voltarAoMenu();
        return;
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
        printf("Nome: %-20s | Matricula: %-8ld | Sexo: %c | DataNasc: %s\n",
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
    if (ano1 != ano2) return ano1 - ano2;

    int mes1 = ((d1[3]-'0')*10 + (d1[4]-'0')); 
    int mes2 = ((d2[3]-'0')*10 + (d2[4]-'0')); 
    if (mes1 != mes2) return mes1 - mes2;

    int dia1 = ((d1[0]-'0')*10 + (d1[1]-'0')); 
    int dia2 = ((d2[0]-'0')*10 + (d2[1]-'0'));
    return dia1 - dia2; 
}

void listaAniversariantesDoMes(void) {
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
    int qtdAlunos = 0, qtdProfessores = 0;

    printf("\n=== LISTA ANIVERSARIANTES DESTE MES (%d) ===\n", mesAtual);
    
    for (int i = 0; i < indiceListaPessoas; i++) {
        int mesNascimento = ((listaGlobalPessoas.listaDePessoas[i].DataNascimento[3] - '0') * 10) + 
                            (listaGlobalPessoas.listaDePessoas[i].DataNascimento[4] - '0');

        if (mesAtual == mesNascimento) {
            if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'A') {
                alunosAniversariantes[qtdAlunos++] = listaGlobalPessoas.listaDePessoas[i];
            } else if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'P') {
                professoresAniversariantes[qtdProfessores++] = listaGlobalPessoas.listaDePessoas[i];
            }
        }
    }

    if (qtdAlunos == 0 && qtdProfessores == 0) {
        printf("Nenhum aniversariante no mes.\n");
        voltarAoMenu();
        return;
    }

    printf("\n--- ALUNOS ---\n");
    if (qtdAlunos == 0) {
        printf("Nenhum aluno aniversariante este mes.\n");
    } else {
        for (int i = 0; i < qtdAlunos; i++) {
            printf("Nome: %-20s | Aniversario: %s | Matricula: %ld\n",
                   alunosAniversariantes[i].Nome,
                   alunosAniversariantes[i].DataNascimento,
                   alunosAniversariantes[i].Matricula);
        }
    }

    printf("\n--- PROFESSORES ---\n");
    if (qtdProfessores == 0) {
        printf("Nenhum professor aniversariante este mes.\n");
    } else {
        for (int i = 0; i < qtdProfessores; i++) {
            printf("Nome: %-20s | Aniversario: %s | Matricula: %ld\n",
                   professoresAniversariantes[i].Nome,
                   professoresAniversariantes[i].DataNascimento,
                   professoresAniversariantes[i].Matricula);
        }
    }
    voltarAoMenu();    
}

void listarPessoasPorIdade(char tipo) {
    if (indiceListaPessoas == 0) {
        printf("\nNenhum cadastro encontrado.\n");
        voltarAoMenu();
        return;
    }
    Pessoa IdadesOrdenadas[indiceListaPessoas]; 
    int qtd = 0;

    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
            IdadesOrdenadas[qtd++] = listaGlobalPessoas.listaDePessoas[i];
        }
    }

    if (qtd == 0) {
        printf("\nNenhum cadastro do tipo selecionado.\n");
        voltarAoMenu();
        return;
    }

    for (int i = 0; i < qtd - 1; i++) {
        for (int k = i + 1; k < qtd; k++) {
            if (compararIdade(IdadesOrdenadas[i].DataNascimento, IdadesOrdenadas[k].DataNascimento) > 0) {
                Pessoa temp = IdadesOrdenadas[k];
                IdadesOrdenadas[k] = IdadesOrdenadas[i];
                IdadesOrdenadas[i] = temp;            
            }
        }
    }

    printf("\n=== LISTA POR DATA DE NASCIMENTO (CRONOLOGICA) ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("Data Nasc: %s | Nome: %-20s | Matricula: %-8ld | Sexo: %c\n",
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

    if (!validador) {
        printf("Não há %s cadastrados no momento.\n", (tipo == 'A' ? "alunos" : "professores"));
        voltarAoMenu();
        return;
    }

    int contadorPrints = 0;

    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == tipo) {
            if (strstr(listaGlobalPessoas.listaDePessoas[i].Nome, string) != NULL) {
                printf("Nome: %s | Matricula: %ld\n", 
                       listaGlobalPessoas.listaDePessoas[i].Nome,
                       listaGlobalPessoas.listaDePessoas[i].Matricula);
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
    if (indiceListaDisciplinas == 0) {
        printf("\nNenhuma disciplina cadastrada.\n");
        return;
    }

    printf("\n=== LISTA DE DISCIPLINAS ===\n");
    for (int i = 0; i < indiceListaDisciplinas; i++) {
        printf("Nome: %-15s | Codigo: %-6ld | Semestre: %d | Professor: %s | Matriculados: %d\n",
            listaDisciplinas[i].NomeDisciplina,
            listaDisciplinas[i].CodigoDisciplina, 
            listaDisciplinas[i].SemestreDisciplina, 
            listaDisciplinas[i].ProfessorDisciplina.Nome,
            listaDisciplinas[i].indiceAlunosMatriculados);
    }
}

void listarDisciplinaEspecifica(char disciplina[]) {
    for (int i = 0; i < indiceListaDisciplinas; i++) {
        if (strcmp(listaDisciplinas[i].NomeDisciplina, disciplina) == 0) {
            printf("Nome: %s | Codigo: %ld | Semestre: %d | Professor: %s\n",
                listaDisciplinas[i].NomeDisciplina,
                listaDisciplinas[i].CodigoDisciplina,
                listaDisciplinas[i].SemestreDisciplina,
                listaDisciplinas[i].ProfessorDisciplina.Nome);
            return;
        }
    }
    printf("Disciplina não encontrada.\n");
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
    int validador = 0;
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'P') {
            validador = 1;
            break;
        }
    }

    if (validador) {
        Disciplina disciplina;
        memset(&disciplina, 0, sizeof(Disciplina));

        printf("Digite o nome da disciplina: ");
        fgets(disciplina.NomeDisciplina, sizeof(disciplina.NomeDisciplina), stdin);
        disciplina.NomeDisciplina[strcspn(disciplina.NomeDisciplina, "\n")] = '\0';

        printf("Digite o codigo da disciplina: ");
        scanf("%ld", &disciplina.CodigoDisciplina);

        printf("Digite o semestre da disciplina: ");
        scanf("%d", &disciplina.SemestreDisciplina);

        while (disciplina.SemestreDisciplina != 1 && disciplina.SemestreDisciplina != 2) {
            printf("Digite apenas 1 (Primeiro semestre) ou 2 (Segundo semestre): ");
            scanf("%d", &disciplina.SemestreDisciplina);
        }

        limparBuffer();

        printf("\nLista de professores cadastrados:\n");
        listarPessoas('P');
        
        printf("\nAtribua um professor a disciplina: ");
        fgets(disciplina.ProfessorDisciplina.Nome, sizeof(disciplina.ProfessorDisciplina.Nome), stdin);
        disciplina.ProfessorDisciplina.Nome[strcspn(disciplina.ProfessorDisciplina.Nome, "\n")] = '\0';

        while (verificarProfessordisciplina(disciplina.ProfessorDisciplina.Nome) == 0) {
            printf("Professor não encontrado, Digite um professor válido: ");
            fgets(disciplina.ProfessorDisciplina.Nome, sizeof(disciplina.ProfessorDisciplina.Nome), stdin);
            disciplina.ProfessorDisciplina.Nome[strcspn(disciplina.ProfessorDisciplina.Nome, "\n")] = '\0';
        }

        disciplina.indiceAlunosMatriculados = 0;
        listaDisciplinas[indiceListaDisciplinas] = disciplina;
        indiceListaDisciplinas++;
        
        printf("Disciplina %s cadastrada com sucesso!\n", disciplina.NomeDisciplina);
    } else {
        printf("É preciso cadastrar professores antes de cadastrar uma disciplina.\n");
    }
    voltarAoMenu();
}

void inserirAlunoNaDisciplina(void) {
    if (indiceListaDisciplinas <= 0) {
        printf("Não existem disciplinas cadastradas.\n");
        voltarAoMenu();
        return;
    }
    if (indiceListaPessoas <= 0) {
        printf("Não existem alunos cadastrados.\n");
        voltarAoMenu();
        return;
    }

    int opcao = -1, idxDisciplina = -1, validaAluno = 0;
    char nome[50];
    
    listarDisciplinas();
    
    while (1) {
        printf("\nDigite o nome da disciplina em que deseja inserir o(s) aluno(s): ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';

        for (int i = 0; i < indiceListaDisciplinas; i++) {
            if (strcmp(listaDisciplinas[i].NomeDisciplina, nome) == 0) {
                idxDisciplina = i;
                break;
            }
        }
        if (idxDisciplina != -1) {
            printf("\nDisciplina \"%s\" selecionada com sucesso!\n", nome);
            break;
        } else {
            printf("Disciplina não encontrada. Digite novamente.\n");
        }
    }

    printf("\nLista de alunos cadastrados:\n");
    listarPessoas('A');

    while (opcao != 0) {
        printf("\nDigite o nome do aluno que deseja inserir na disciplina: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';

        validaAluno = 0;
        for (int i = 0; i < indiceListaPessoas; i++) {
            if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'A') {
                if (strcmp(listaGlobalPessoas.listaDePessoas[i].Nome, nome) == 0) {
                    validaAluno = 1;
                    int idxMat = listaDisciplinas[idxDisciplina].indiceAlunosMatriculados;
                    
                    listaDisciplinas[idxDisciplina].AlunosMatriculados[idxMat] = listaGlobalPessoas.listaDePessoas[i];
                    listaDisciplinas[idxDisciplina].indiceAlunosMatriculados++;
                    listaGlobalPessoas.listaDePessoas[i].materiasmatriculadas++;
                    break;
                }
            }
        } 
        if (validaAluno == 1) {
            printf("Aluno %s inserido com sucesso.\n", nome);
            printf("Deseja inserir outro aluno nesta disciplina? (1 - Sim | 0 - Não): ");
            scanf("%d", &opcao);
            limparBuffer();
            if (opcao == 0) break;
        } else {
            printf("Aluno não encontrado na base de cadastros.\n");
        }
    }
    voltarAoMenu();
}

void listarDisciplinasComMaisDe40Vagas(void) {
    if (indiceListaDisciplinas > 0) {
        int cont = 0;
        for (int i = 0; i < indiceListaDisciplinas; i++) {
            if (listaDisciplinas[i].indiceAlunosMatriculados > 40) {
                printf("Disciplina: %s | Professor: %s | Codigo: %ld | Semestre: %d\n", 
                    listaDisciplinas[i].NomeDisciplina,
                    listaDisciplinas[i].ProfessorDisciplina.Nome,
                    listaDisciplinas[i].CodigoDisciplina,
                    listaDisciplinas[i].SemestreDisciplina);
                cont++;
            }
        }
        if (cont == 0) {
            printf("Não existem disciplinas com mais de 40 alunos matriculados.\n");
        }
    } else {
        printf("Não existem disciplinas cadastradas.\n");
    }
    voltarAoMenu();
}

void listarMenosDe3Disciplinas(void) {
    int possuiAlunos = 0;
    int alunosEncontrados = 0;
    
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'A') {
            possuiAlunos = 1;
            break;
        }
    }
    if (!possuiAlunos) {
        printf("Não existem alunos cadastrados no momento.\n");
        voltarAoMenu();
        return;
    }

    printf("\n=== ALUNOS COM MENOS DE 3 DISCIPLINAS ===\n");
    for (int i = 0; i < indiceListaPessoas; i++) {
        if (listaGlobalPessoas.listaDePessoas[i].Tipo == 'A' && listaGlobalPessoas.listaDePessoas[i].materiasmatriculadas < 3) {
            printf("Aluno: %-20s | Matricula: %-8ld | Qtd Disciplinas: %d\n",
                   listaGlobalPessoas.listaDePessoas[i].Nome,
                   listaGlobalPessoas.listaDePessoas[i].Matricula, 
                   listaGlobalPessoas.listaDePessoas[i].materiasmatriculadas);
            alunosEncontrados++;
        }
    }
    if (alunosEncontrados == 0) {
        printf("Não existem alunos matriculados em menos de 3 disciplinas.\n");
    }
    voltarAoMenu();
}

#endif 