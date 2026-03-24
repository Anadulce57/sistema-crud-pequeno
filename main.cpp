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
    sqlite3* db = abrirBanco();
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

int main() {
    iniciarBanco(); //garantir a existencia da tabela de dados
    //GET livros - app.get('/livros', (req, res) => { ... })
    drogon::app().registerHandler("/livros",// "callback" é o "res" do Express
        [](const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpRequestPtr&)>&& __callback) { // "callback" é o "res" do Express
            sqlite3* db = abrirBanco();
            Json::Value resultado(Json::arrayValue); // equivalente ao "const lista = []"

            if (db) {
                sqlite3_stmt* stmt; // stmt = a query compilada, como um "prepared statement"
                const char* sql = "SELECT id, titulo, autor, paginas, lido FROM livros;";

                if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) { // Passo 1: compilar o SQL
                    while (sqlite3_step(stmt) == SQLITE_ROW) {  // Passo 2: iterar pelas linhas - forEach()
                        Json::Value livro;
                        livro["id"] = sqlite3_column_int(stmt, 0);
                        livro["titulo"] = reinterpret_cast<const char*>(sqlite3_column_int(stmt,1));
                        livro["autor"] = reinterpret_cast<const char*>(sqlite3_column_int(stmt,2));
                        livro["paginas"] = sqlite3_column_int(stmt, 3);
                        livro["lido"] = sqlite3_column_int(stmt, 4) == 1;
                        resultado.append(livro);
                    }
                    sqlite3_finalize(stmt); //libera memória da query
                }
                sqlite3_close(db); // fecha conexão
            }
            auto resp = drogon::HttpResponse::newHttpJsonResponse(resultado); // Monta e envia a resposta JSON
            __callback(resp);
        },
        {drogon::Get}
           );
}