#include <iostream>
#include <vector>
#include <string>

struct livro { //Iniciando estrutura -> como se fosse um objeto com key values
    std::string titulo;
    std::string autor;
    std::string paginas;
    bool lido;
};

//Função de CREATE
void adicionar(std::vector<livro>& listaLivros) {
    livro novo;
    char resposta;

    std::cout << "Titulo: ";
    std::getline(std::cin, novo.titulo);

    std::cout << "Autor: ";
    std::getline(std::cin, novo.autor);

    std::cout << "Paginas: ";
    std::getline(std::cin, novo.paginas);

    std:: cout << "Lido? (s/n) ";
    std:: cin >> resposta;

    if (resposta == 's'||resposta == 'S') {
        novo.lido = true;
    }else{
        novo.lido = false;
    }

    listaLivros.push_back(novo);
    std::cout << "Cadastrado com sucesso!"<< std::endl;
}

//Função de READ
void listar(std::vector<livro>& lista) {
    std::cout << "Minha biblioteca" << std::endl;
    for (int i = 0; i < lista.size(); i++) {
        std::cout << i + 1 << ". " << lista[i].titulo << "-" << lista[i].autor << "-" << lista[i].paginas << std::endl;

        if (lista[i].lido == true) {
            std::cout << "Lido" << std::endl;
        }
    }
}

//Função de UPDATE

//Função de DELETE



int main() {
    std::vector<livro> biblioteca;


    adicionar(biblioteca);
    listar(biblioteca);
    return 0;
}