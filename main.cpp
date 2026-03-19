#include <iostream> //Declarando bibliotecas
#include <sqlite3.h> //Praticamente o express
#include <drogon/drogon.h> //Praticamente o npm

const std::string DB_PATH = "biblioteca.DB";

sqlite3* abrirBanco() { //Praticamente o getConection * ponteiro
    sqlite3 *db;
    if (sqlite3_open(DB_PATH.c_str(), &db) != SQLITE_OK) {
        std::cerr <<  "Erro ao abrir o banco!" << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }
    return db;
}

void iniciarBanco() {
    sqlite3 *db = abrirBanco();
    if (!db) return;

    const char* sql = R"(
       CREATE TABLE IF NOT EXISTS livros (
           id INTEGER PRIMARY KEY AUTOINCREMENT,
           titulo TEXT NOT NULL,
           autor TEXT NOT NULL,
           paginas INTEGER,
           lido BOOLEAN DEFAULT 0
       );
    )";

    char* erro;
    sqlite3_exec(db, sql, nullptr, nullptr, &erro);
    sqlite3_close(db);
}

int main() {}