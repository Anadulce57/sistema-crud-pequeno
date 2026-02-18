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

    std::cin.ignore();
    std::cout << "Titulo: ";
    std::getline(std::cin, novo.titulo);

    std::cout << "Autor: ";
    std::getline(std::cin, novo.autor);

    std::cout << "Paginas: ";
    std::getline(std::cin, novo.paginas);

    std:: cout << "Lido? (s/n)";
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
void listar(const std::vector<livro>& lista) {
    std::cout << "Minha biblioteca" << std::endl;
    for (int i = 0; i < lista.size(); i++) {
        std::cout << i + 1 << ". " << lista[i].titulo << "-" << lista[i].autor << "-" << lista[i].paginas << std::endl;

        if (lista[i].lido == true) {
            std::cout << "Lido" << std::endl;
        }
    }
}

//Função de UPDATE
void atualizar(std::vector<livro>& lista) {
    int indice;
    std:: cout << "Qual é o livro lido? (índice)" << std::endl;
    std:: cin >> indice;

    lista[indice].lido = true;
    std::cout << "Atualizado com sucesso!" << std::endl;
}

//Função de DELETE
void deletar(std::vector<livro>& lista) { //removendo a partir do índice
    int indice;
    std::cout << "Digite o índice: " << std::endl;
    std::cin >> indice;
    lista.erase(lista.begin() + (indice-1));

    std::cout << "Livro removido!" << std::endl;
}


int main() {
    std::vector<livro> biblioteca;
    std::cout << "Bem vindo a um pequeno sistema 'CRUD' de biblioteca!" << std::endl;
    std::cout << "Vamos comecar?" << std::endl;

    int escolha;
    do {
        std::cout << "O que voce gostaria de fazer" << std::endl;
        std::cout << "1 - Registrar\n";
        std::cout << "2 - Listar\n";
        std::cout << "3 - Deletar\n";
        std::cout << "4 - Atualizar\n";
        std::cout << "0 - Sair" << std::endl;
        std::cin >> escolha;
        switch (escolha) {
            case 1:
                adicionar(biblioteca);
                break;
            case 2:
                listar(biblioteca);
                break;
            case 3:
                deletar(biblioteca);
                break;
            case 4:
                atualizar(biblioteca);
                break;
            case 0:
                std::cout << "Saindo..." << std::endl;
                break;
            default:
                std::cout << "Erro!" << std::endl;
        }
    } while (escolha != 0);

    return 0;
}