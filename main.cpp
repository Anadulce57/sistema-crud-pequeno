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
    //GET livros - app.get('/livros', (req, res) => { ... }) : para confirmar que aparece na lista
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

    //POST /livros — equivalente ao app.post('/livros', (req, res) => { ... }) : para adicionar um livro
    drogon::app().registerHandler("/livros",
        [](const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& __callback) {

                // Lê o body JSON — equivalente ao "req.body" do Express (com express.json())
                auto body = req->getJsonObject();
                Json::Value resposta;

            // Verificação — equivalente ao "if (!req.body.titulo) return res.status(400)..."
                if (!body || !(*body).isMember("titulo") || !(*body).isMember("autor")) {
                    resposta["erro"] = "Campos 'título' e 'autor' são obrigatórios";
                    auto resp = drogon::HttpResponse::newHttpJsonResponse(resposta);
                    resp-> setStatusCode(drogon::k400BadRequest); //res.status(400)
                    __callback(resp);
                    return; // para a execução — equivalente ao "return res.status(400).json()"
                }
            // Extrai os valores do body — equivalente ao "const { titulo, autor } = req.body"
            std::string titulo = (*body)["titulo"].asString();
            std::string autor = (*body)["autor"].asString();
            int paginas = (*body).get("paginas",0).asInt();

            sqlite3* db = abrirBanco();
            if (db) {
                sqlite3_stmt* stmt;
                //? como se fosse o placeholder
                const char* sql = "INSERT INTO livros (titulo, autor, paginas, lido) VALUES (?, ?, ?, 0);";

                if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
                    // Bind: preenche os "?" em ordem — equivalente ao array de params do pg
                    sqlite3_bind_text(stmt, 1, titulo.c_str(), -1, SQLITE_STATIC);
                    sqlite3_bind_text(stmt, 2, autor.c_str(), -1, SQLITE_STATIC);
                    sqlite3_bind_int(stmt, 3, paginas);
                    sqlite3_step(stmt); //executar insert
                    sqlite3_finalize(stmt); //liberar memória
                }
                sqlite3_close(db);
            }
            resposta["mensagem"] = "Livro cadastrado com sucesso!";
            auto resp = drogon::HttpResponse::newHttpJsonResponse(resposta);
            resp->setStatusCode(drogon::k201Created); //res.status(201)
            __callback(resp);
    },
    {drogon::Post}
);

    std::cout << "Servidor rodando em http://localhost:8080" << std::endl;

    // Equivalente ao "app.listen(8080)" do Express — bloqueia e mantém o servidor vivo
    drogon::app().addListener("0.0.0.0", 8080).run();

    return 0;
}