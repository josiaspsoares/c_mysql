#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <C:\conectorC\include/mysql.h>

MYSQL *__stdcall obterConexao()
{
    char *servidor = "127.0.0.1";
    char *usuario = "root";
    char *senha = "";
    char *nomeBanco = "bancoC";

    MYSQL *conexao = mysql_init(NULL);

    if (!mysql_real_connect(conexao, servidor, usuario, senha, nomeBanco, 0, NULL, 0))
    {
        fprintf(stderr, "\n%s\n", mysql_error(conexao));
        mysql_close(conexao);
        exit(1);
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
    sprintf(query, "INSERT INTO CLIENTES(nome, saldo) VALUES('%s', '%f');", nome, saldo);

    if (mysql_query(conexao, query))
    {
        fprintf(stderr, "\n%s\n", mysql_error(conexao));
        exit(1);
    }
    else
    {
        printf("\nDados inseridos com sucesso!\n");
    }
}

int main()
{
    MYSQL *conexao = obterConexao();

    mysql_close(conexao);
    return 0;
}