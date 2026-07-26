#include <iostream> //Declarando bibliotecas
#include <sqlite3.h> //Banco
#include <drogon/drogon.h> //Praticamente o express - framework

const std::string DB_PATH = "biblioteca.DB";

int main() {
    std::cout << "Servidor rodando comm sucesso na porta 8080..." << std::endl;
    //Configurar o servidor pra ouvir na porta 8080
     drogon::app().addListener("0.0.0.0", 8080);
    //Rodar o seervidor
    drogon::app().run();
}