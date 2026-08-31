#include <iostream> //Declarando bibliotecas
#include <sqlite3.h> //Banco
#include <drogon/drogon.h> //Praticamente o express - framework

const std::string DB_PATH = "biblioteca.DB";

//Função 1 - Abrir conexão com banco (O getConnection() do Node - ou seja toda rota vai chamar ela pra falar com o banco de dados)
sqlite3* abrirBanco() { // Padrão
    sqlite3* db;
    if (sqlite3_open(DB_PATH.c_str(), &db) != SQLITE_OK) {
        std::cerr <<"Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }
    return db;
}

//Função 2 - Criar umma tabela se não existir - como o db.sync() do Sequelize: roda uma vez só quando o servidor liga, garante que a tabela existe.
sqlite3* iniciarBanco(){
    sqlite3* db = abrirBanco();
    if (!db) return db;

    const  char* sql = R"(
        CREATE TABLE IF NOT EXISTS livros(
          id INTEGER PRIMARY KEY AUTOINCREMENT,
          titulo TEXT NOT NULL,
          autor TEXT NOT NULL,
          paginas INTEGER,
          lido BOOLEAN DEFAULT 0
       )
    )";

    char* erro; //Declara uma variável para guardar a mensagem de erro caso o SQL falhe. É como fazer let erro no JS
    if (sqlite3_exec(db, sql, nullptr, nullptr, &erro) != SQLITE_OK) {
        std::cerr << "Error creating database" << erro << std::endl;
        sqlite3_free(erro);
    }
    sqlite3_close(db); //Fecha a conexão com o banco

}

int main() {
    std::cout << "Servidor rodando comm sucesso na porta 8080..." << std::endl; //Iniciar o servidor
    //Configurar o servidor pra ouvir na porta 8080
     drogon::app().addListener("0.0.0.0", 8080);
    //Rodar o seervidor
    drogon::app().run();
}

