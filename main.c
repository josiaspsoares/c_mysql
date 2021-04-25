#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <C:\conectorC\include/mysql.h>

void erro(MYSQL *conexao)
{
    fprintf(stderr, "\n%s\n", mysql_error(conexao));
    mysql_close(conexao);
    exit(1);
}

MYSQL *__stdcall obterConexao()
{
    char *servidor = "127.0.0.1";
    char *usuario = "root";
    char *senha = "";
    char *nomeBanco = "bancoC";

    MYSQL *conexao = mysql_init(NULL);

    if (!mysql_real_connect(conexao, servidor, usuario, senha, nomeBanco, 0, NULL, 0))
    {
        erro(conexao);
    }
    else
    {
        printf("\nConexao realizada com sucesso!\n");
        return conexao;
    }
}

void inserir(MYSQL *conexao, char *nome, float saldo)
{
    char query[100];
    sprintf(query, "INSERT INTO clientes(nome, saldo) VALUES('%s', '%f');", nome, saldo);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados inseridos com sucesso!\n");
    }
}

void ler(MYSQL *conexao)
{
    MYSQL_RES *resultado;
    MYSQL_ROW row;

    if (mysql_query(conexao, "SELECT * FROM clientes"))
    {
        erro(conexao);
    }

    resultado = mysql_store_result(conexao);
    if (resultado == NULL)
    {
        erro(conexao);
    }

    while ((row = mysql_fetch_row(resultado)) != NULL)
    {
        printf("\nNome: %s\n", row[0]);
        printf("Conta: %s\n", row[1]);
        printf("Saldo: %s\n", row[2]);
    }

    mysql_free_result(resultado);
}

void atualizar(MYSQL *conexao, int numeroConta, float saldo)
{
    char query[100];
    sprintf(query, "UPDATE clientes SET saldo = %f WHERE numero_conta = %d;", saldo, numeroConta);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados atualizados com sucesso!\n");
    }
}

void apagar(MYSQL *conexao, int numeroConta)
{
    char query[100];
    sprintf(query, "DELETE FROM clientes WHERE numero_conta = %d;", numeroConta);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados apagados com sucesso!\n");
    }
}

int main()
{
    MYSQL *conexao = obterConexao();
    char nome[100];
    float saldo;
    int i;

    printf("\n*** CADASTRO DE CLIENTES ***\n");
    for (i = 0; i < 3; i++)
    {
        printf("\n%d - Nome: ", i);
        fflush(stdin);
        gets(nome);
        printf("%d - Saldo: ", i);
        scanf("%f", &saldo);
        inserir(conexao, nome, saldo);
    }

    printf("\n*** CLIENTES CADASTRADOS ***\n");
    ler(conexao);

    // // atualizar(conexao, 9, 300.49);

    // printf("\n*** CLIENTES CADASTRADOS ***\n");
    // ler(conexao);

    // apagar(conexao, 11);

    // printf("\n*** CLIENTES CADASTRADOS ***\n");
    // ler(conexao);

    mysql_close(conexao);
    return 0;
}