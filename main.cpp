#include <iostream>

struct livro { //Iniciando estrutura -> como se fosse um objeto com key values
    std::string titulo;
    std::string autor;
    std::string paginas;
    bool lido;
};

int main() {
    livro meuLivro; //Chamando o objeto e definindo um caso pra ele
    meuLivro.titulo = "Silmarilion";
    meuLivro.autor = "John R. R. Tolkien";
    meuLivro.paginas = "494";
    meuLivro.lido = true;

    std::cout << meuLivro.titulo << std::endl;
    return 0;
}