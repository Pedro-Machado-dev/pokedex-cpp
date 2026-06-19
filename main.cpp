/*
      --> Integrantes:
      Anna Livia de Souza Pereira - 794 (GES - P3)
      Joao Victor Simoes Rosa - 784 (GES - P3)
      Lara Lisandra Ferreira - 780 (GES - P3)
      Nycolle Fernanda Coutinho Pascoal - 790 (GES - P3)
      Pedro Henrique Silva Machado - 805 (GES - P3)
      Rafael Moreira Xavier - 786 (GES - P3)
*/
#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#define MAX_CIDADES 100

using namespace std;

//CONFIGURAÇÕES GLOBAIS 

struct Aresta {
    int origem, destino, peso;
};

struct Cidade {
    int codigo;
    string nome;
    bool temCentro;
    bool ativa;
};

struct Pokemon {
    string nome;
    string tipo;
    int numero;
    int x, y;
};

struct Node {
    Pokemon p;
    Node* left;
    Node* right;
};

// Nova raiz global substituindo o array
Node* rootPokemons = NULL;
Node* rootTipo = NULL; 

// Banco de dados global
Cidade listaCidades[MAX_CIDADES];
list<Aresta> listaAdj[MAX_CIDADES];   
int totalCidades = 0;

//FUNÇÕES AUXILIARES

int acharIndice(int codigo) {
    for (int i = 0; i < totalCidades; i++) {
        if (listaCidades[i].ativa && listaCidades[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void menuVoltar() {
    int v;
    cout << "\n-------------------------------------------------------------" << endl;
    cout << "Digite 1 para voltar ao menu: ";
    cin >> v;
    while(cin.fail() || v != 1){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida! Digite 1 para voltar ao menu: ";
        cin >> v;
    }
}

// ==========================================
// FUNÇÕES DA ÁRVORE BINÁRIA 
// ==========================================

void insert(Node* &current, Pokemon p) {
    if (current == NULL) {
        current = new Node;
        current->p = p;
        current->left = NULL;
        current->right = NULL;
    } 
    else if (p.nome < current->p.nome) {
        insert(current->left, p);
    } 
    else {
        insert(current->right, p);
    }
}

Node* search(Node* current, string nome) {
    if (current == NULL) {
        return NULL;
    } else if (nome == current->p.nome) {
        return current;
    } else {
        if (nome < current->p.nome) {
            return search(current->left, nome);
        } else {
            return search(current->right, nome);
        }
    }
}

Node* find_less_save_right(Node* &current) {
    if (current->left != NULL) {
        return find_less_save_right(current->left);
    } else {
        Node* copy = current;
        current = current->right;
        return copy;
    }
}

bool remove(Node* &current, string nome) {
    if (current == NULL) {
        return false;
    } else if (nome == current->p.nome) {
        Node* temp = current;
        if (current->right == NULL) {
            current = current->left;
        } else if (current->left == NULL) {
            current = current->right;
        } else {
            temp = find_less_save_right(current->right);
            current->p = temp->p;
        }
        delete(temp);
        return true;
    } else {
        if (nome < current->p.nome) {
            return remove(current->left, nome);
        } else {
            return remove(current->right, nome);
        }
    }
}

void show_in_order(Node* current) {
    if (current != NULL) {
        if (current->left != NULL) {
            show_in_order(current->left);
        }
        
        cout << "Nome: " << current->p.nome
             << " | Tipo: " << current->p.tipo
             << " | Numero: " << current->p.numero
             << " | (" << current->p.x << "," << current->p.y << ")\n";
             
        if (current->right != NULL) {
            show_in_order(current->right);
        }
    }
}

void destruct(Node* &current) {
    if (current != NULL) {
        if (current->left != NULL) {
            destruct(current->left);
        }
        if (current->right != NULL) {
            destruct(current->right);
        }
        delete(current);
        current = NULL;
    }
}

// ==========================================
// FUNÇÕES DE GRAFOS E CIDADES 
// ==========================================

void mostraTime(){
    cout<<"Anna Livia de Souza Pereira - 794 (GES - P3)"<<endl;
    cout<<"Joao Victor Simoes Rosa - 784 (GES - P3)"<<endl;
    cout<<"Lara Lisandra Ferreira - 780 (GES - P3)"<<endl;
    cout<<"Nycolle Fernanda Coutinho Pascoal - 790 (GES - P3)"<<endl;
    cout<<"Pedro Henrique Silva Machado - 805 (GES - P3)"<<endl;
    cout<<"Rafael Moreira Xavier - 786 (GES - P3)"<<endl;
    system("chcp 65001 > nul");
        cout<<u8R"(
        ⠉⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
        ⠀⠀⠀⠈⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠉⠁
        ⣧⡀⠀⠀⠀⠀⠙⠿⠿⠿⠻⠿⠿⠟⠿⠛⠉⠀⠀⠀⠀⠀
        ⣿⣷⣄⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴
        ⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣴⣿⣿
        ⣿⣿⡟⠀⠀⢰⣹⡆⠀⠀⠀⠀⠀⠀⣭⣷⠀⠀⠀⠸⣿⣿
        ⣿⣿⠃⠀⠀⠈⠉⠀⠀⠤⠄⠀⠀⠀⠉⠁⠀⠀⠀⠀⢿⣿
        ⣿⣿⢾⣿⣷⠀⠀⠀⠀⡠⠤⢄⠀⠀⠀⠠⣿⣿⣷⠀⢸⣿
        ⣿⣿⡀⠉⠀⠀⠀⠀⠀⢄⠀⢀⠀⠀⠀⠀⠉⠉⠁⠀⠀⣿
        ⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹
        )"<<endl;

    menuVoltar();
}

void listarCidades() {
    cout << "\n--- CIDADES CADASTRADAS ---\n";
    bool temCidade = false;
    for (int i = 0; i < totalCidades; i++) {
        if (listaCidades[i].ativa) {
            cout << "Codigo: " << listaCidades[i].codigo
                 << " | Nome: "  << listaCidades[i].nome
                 << " | Centro Pokemon: " << (listaCidades[i].temCentro ? "Sim" : "Nao")
                 << endl;
            temCidade = true;
        }
    }
    if (!temCidade) {
        cout << "Nenhuma cidade cadastrada ainda.\n";
    }
    cout << "-----------------------------\n";
}

void mostrarConexoes(int idx) {
    cout << "\n--- CONEXOES DA CIDADE " << listaCidades[idx].nome << " ---\n";
    bool temConexao = false;

    for (list<Aresta>::iterator it = listaAdj[idx].begin();
         it != listaAdj[idx].end(); it++) {
        int vizinho = it->destino;
        cout << "Ligada a: " << listaCidades[vizinho].nome
             << " (Codigo: "  << listaCidades[vizinho].codigo << ")\n";
        temConexao = true;
    }

    if (!temConexao) {
        cout << "Essa cidade ainda nao possui estradas.\n";
    }
    cout << "---------------------------------------------\n";
}

void cadastroCidade() {
    int i = 1;
    while(i==1){   
        if (totalCidades >= MAX_CIDADES) {
            cout << "Erro: Limite de cidades atingido!" << endl;
        } else {
            Cidade nova;
            nova.codigo = totalCidades + 1; // autoincrement
            cout << "Nome da cidade: "; cin.ignore(); getline(cin, nova.nome);
            
            bool existe = false;
            for (int j = 0; j < totalCidades; j++) {
                if (listaCidades[j].ativa && listaCidades[j].nome == nova.nome) {
                    existe = true;
                    break;
                }
            }

            if (existe) {
                cout << "\nErro: Uma cidade com esse nome ja existe!\n";
            } else {
                cout << "Possui Centro Pokemon? (1-Sim / 0-Nao): "; cin >> nova.temCentro;
                while(cin.fail()){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Entrada invalida! Tente novamente: ";
                    cin >> nova.temCentro;
                }
                nova.ativa = true;
                listaCidades[totalCidades] = nova;
                totalCidades++;
                cout<< "Codigo da cidade: " << nova.codigo << endl;
                cout << "\nCidade cadastrada com sucesso! " << endl;
            }
        }
        cout << "\nDeseja cadastrar outra cidade? (1-Sim / 0-Nao): "; 
        cin >> i;
        while(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida! Tente novamente: ";
            cin >> i;
        }
        system("cls");
    }
}

void cadastroEstrada() {
    int i = 1;

    while (i == 1) {
        int cod1, cod2;

        cout << "--- CADASTRO DE ESTRADA  ---" << endl;
        listarCidades();

        cout << "Codigo da Cidade origem: ";
        cin >> cod1;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida! Tente novamente: ";
            cin >> cod1;
        }

        int i1 = acharIndice(cod1);

        if (i1 == -1) {
            cout << "\nErro: Cidade origem nao encontrada.\n";
            menuVoltar();
            return;
        }

        mostrarConexoes(i1);

        cout << "Codigo da Cidade destino: ";
        cin >> cod2;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida! Tente novamente: ";
            cin >> cod2;
        }

        int i2 = acharIndice(cod2);

        if (i2 == -1) {
            cout << "\nErro: Cidade destino nao encontrada.\n";
        } 
        else if (i1 == i2) {
            cout << "\nErro: Uma cidade nao pode ter estrada para ela mesma.\n";
        }
        else {
            bool jaExiste = false;

            for (list<Aresta>::iterator it = listaAdj[i1].begin();
                 it != listaAdj[i1].end(); it++) {
                
                if (it->destino == i2) {
                    jaExiste = true;
                    break;
                }
            }

            if (jaExiste) {
                cout << "\nErro: Estrada ja existente entre "
                     << listaCidades[i1].nome << " e "
                     << listaCidades[i2].nome << "!\n";
            } 
            else {
                listaAdj[i1].push_back({i1, i2, 0});
                listaAdj[i2].push_back({i2, i1, 0});

                cout << "\nEstrada registrada entre "
                     << listaCidades[i1].nome << " e "
                     << listaCidades[i2].nome << "!\n";
            }
        }

        cout << "\nDeseja cadastrar outra estrada? (1-Sim / 0-Nao): ";
        cin >> i;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida! Tente novamente: ";
            cin >> i;
        }

        system("cls");
    }
}

void buscaCentro() {
    int codInicio;
    listarCidades();
    cout<<endl;
    cout << "Onde voce esta agora? (Digite o codigo da cidade): "; cin >> codInicio;
    while(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida! Tente novamente: ";
        cin >> codInicio;
    }

    int idxInicio = acharIndice(codInicio);
    if (idxInicio == -1) {
        cout << "Cidade nao cadastrada!" << endl;
        menuVoltar();
        return;
    }

    bool temVinculo = !listaAdj[idxInicio].empty();

    if (!temVinculo && !listaCidades[idxInicio].temCentro) {
        cout << "\nEsta cidade nao tem vinculos com outras cidades" << endl;
        menuVoltar();
        return;
    }

    bool visitado[MAX_CIDADES];
    int  predecessor[MAX_CIDADES];
    list<Aresta>::iterator it;

    for (int i = 0; i < MAX_CIDADES; i++) {
        visitado[i]    = false;
        predecessor[i] = -1;
    }

    list<int> fila_visitacao;          
    fila_visitacao.push_back(idxInicio);
    visitado[idxInicio] = true;

    int idxDestino = -1;

    while (!fila_visitacao.empty()) {
        int u = fila_visitacao.front();
        fila_visitacao.pop_front();   

        if (listaCidades[u].temCentro) {
            idxDestino = u;
            break;
        }

        for (it = listaAdj[u].begin(); it != listaAdj[u].end(); it++) {
            int v = it->destino;
            if (!visitado[v]) {
                visitado[v]    = true;
                predecessor[v] = u;
                fila_visitacao.push_back(v);
            }
        }
    }

    if (idxDestino != -1) {
        cout << "\n>>> CENTRO POKEMON ENCONTRADO! <<<" << endl;
        cout << "Cidade Destino: " << listaCidades[idxDestino].nome << endl;
        cout << "Rota recomendada: ";

        list<int> caminho;
        int temp = idxDestino;
        while (temp != -1) {
            caminho.push_front(temp);
            temp = predecessor[temp];
        }

        for (list<int>::iterator it = caminho.begin(); it != caminho.end(); it++) {
            if (it != caminho.begin()) cout << " --> ";
            cout << listaCidades[*it].nome;
        }
        cout << endl;
    } 
    else {
        cout << "\nNenhum Centro Pokemon encontrado no mapa conectado." << endl;
    }

    menuVoltar();
}

// ==========================================
// FUNÇÕES DOS POKÉMONS NO MENU
// ==========================================

void insertTipo(Node* &current, Pokemon p) {
    if (current == NULL) {
        current = new Node;
        current->p = p;
        current->left = NULL;
        current->right = NULL;
    } 
    else if (p.tipo < current->p.tipo || (p.tipo == current->p.tipo && p.nome < current->p.nome)) {
        insertTipo(current->left, p);
    } 
    else {
        insertTipo(current->right, p);
    }
}

bool removeTipo(Node* &current, string tipo, string nome) {
    if (current == NULL) {
        return false;
    } else if (tipo == current->p.tipo && nome == current->p.nome) {
        Node* temp = current;
        if (current->right == NULL) {
            current = current->left;
        } else if (current->left == NULL) {
            current = current->right;
        } else {
            temp = find_less_save_right(current->right);
            current->p = temp->p;
        }
        delete(temp);
        return true;
    } else {
        if (tipo < current->p.tipo || (tipo == current->p.tipo && nome < current->p.nome)) {
            return removeTipo(current->left, tipo, nome);
        } else {
            return removeTipo(current->right, tipo, nome);
        }
    }
}

void cadastroPokemon() {
    int i = 1;
    while(i==1){
        Pokemon p;

        cout << "--- CADASTRO DE POKEMON ---\n";

        cout << "Nome: ";
        cin.ignore();
        getline(cin, p.nome);

        cout << "Tipo: ";
        getline(cin, p.tipo);

        cout << "Numero da Pokedex: ";
        cin >> p.numero;
        while(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida! Tente novamente: ";
            cin >> p.numero;
        }

        cout << "Localizacao no mapa (x y): ";
        cin >> p.x >> p.y;
        while(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida! Tente novamente: ";
            cin >> p.x >> p.y;
        }

        if (search(rootPokemons, p.nome) != NULL) {
            cout << "\nErro: O Pokemon '" << p.nome << "' ja esta cadastrado!\n";
        } else {
            insert(rootPokemons, p);
            insertTipo(rootTipo, p);
            cout << "\nPokemon cadastrado com sucesso!\n";
        }

        cout << "\nDeseja cadastrar outro Pokemon? (1-Sim / 0-Nao): ";
        cin >> i; 
        while(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida! Tente novamente: ";
            cin >> i;
        }
        system("cls");
    }
}

void listaNome() {
    cout << "\n--- POKEMONS ORDENADOS POR NOME ---\n";
    show_in_order(rootPokemons);
}

void removePokemon() {
    listaNome(); // Exibe a lista por ordem alfabetica antes de remover

    string nome;
    cout << "\nDigite o nome do Pokemon a remover: ";
    cin.ignore();
    getline(cin, nome);

    Node* alvo = search(rootPokemons, nome);

    if (alvo != NULL) {
        string tipoAlvo = alvo->p.tipo;
        remove(rootPokemons, nome);
        removeTipo(rootTipo, tipoAlvo, nome);
        cout << "\nPokemon removido com sucesso!\n";
    } else {
        cout << "\nPokemon nao encontrado!\n";
    }

    menuVoltar();
}

void listaTipo() {
    cout << "\n--- POKEMONS ORDENADOS POR TIPO ---\n";
    show_in_order(rootTipo);
    menuVoltar();
}

void countTree(Node* current, string tipo, int &count) {
    if (current != NULL) {
        if (current->p.tipo == tipo) count++;
        countTree(current->left, tipo, count);
        countTree(current->right, tipo, count);
    }
}

void contaPokemon() {
    string tipoBusca;
    cout << "Digite o tipo: ";
    cin.ignore();
    getline(cin, tipoBusca);
    
    int count = 0;
    countTree(rootPokemons, tipoBusca, count);
    
    cout << "\nQuantidade: " << count << "\n";
    menuVoltar();
}

void countDist(Node* current, int x, int y, int &count) {
    if (current != NULL) {
        int dx = current->p.x - x;
        int dy = current->p.y - y;
        if ((dx * dx + dy * dy) <= 10000) {
            count++;
        }
        countDist(current->left, x, y, count);
        countDist(current->right, x, y, count);
    }
}

void encontraPokemon() {
    int px, py;
    cout << "Localizacao (x y): ";
    cin >> px >> py;
    while(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida! Tente novamente: ";
        cin >> px >> py;
    }
    
    int count = 0;
    countDist(rootPokemons, px, py, count);
    
    cout << "\nPokemons proximos: " << count << "\n";
    menuVoltar();
}

void preCadastrarDados() {
    // Pré-cadastro de Cidades
    listaCidades[totalCidades] = {totalCidades + 1, "Pallet Town", false, true};
    totalCidades++;
    
    listaCidades[totalCidades] = {totalCidades + 1, "Viridian City", true, true};
    totalCidades++;

    // Pré-cadastro de Pokémons
    Pokemon p1 = {"Pikachu", "Eletrico", 25, 67, 100};
    insert(rootPokemons, p1);
    insertTipo(rootTipo, p1);

    Pokemon p2 = {"Charmander", "Fogo", 4, 15, 27};
    insert(rootPokemons, p2);
    insertTipo(rootTipo, p2);

    Pokemon p3 = {"Squirtle", "Agua", 7, 4, 14};
    insert(rootPokemons, p3);
    insertTipo(rootTipo, p3);

    Pokemon p4 = {"Bulbassauro", "Planta", 1, 78, 91};
    insert(rootPokemons, p4);
    insertTipo(rootTipo, p4);
}

int main(){
    for (int i = 0; i < MAX_CIDADES; i++) {
        listaCidades[i].ativa = false;
    }

    preCadastrarDados();

    int opcao;
    while (true){
        system("cls");
        system("chcp 65001 > nul");
        cout<<u8R"(
⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛🟥🟥🟥🟥🟥🟥⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛🟥🟥🟥🟥🟥🟥🟥🟥🟥🟥⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛🟥🟥🟥🟥🟥🟥🟥🟥🟥🟥🟥🟥⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛🟥🟥🟥🟥🟥🟥🟥🟥🟥🟥🟥🟥⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬛🟥🟥🟥🟥🟥🟥⬛⬛🟥🟥🟥🟥🟥🟥⬛⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬛🟥🟥🟥🟥🟥⬛⬜⬜⬛🟥🟥🟥🟥🟥⬛⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬜⬜⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬛⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬛⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜
⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜
        )"<<endl;

        cout<<"|-------------------------- POKEDEX --------------------------|"<<endl;
        cout<<"|                                                             |"<<endl;
        cout<<"|----------------------- BEM VINDO(A)!!-----------------------|"<<endl;
        cout<<"|-------------------------------------------------------------|"<<endl;
        cout<<"|  |                                                       |  | "<<endl;
        cout<<"|  |                 | |    MENU      | |                  |  | "<<endl;
        cout<<"|  |                                                       |  | "<<endl;
        cout<<"|  |                                                       |  | "<<endl;
        cout<<"|  |             >>  1. Cadastrar Cidade  <<               |  | "<<endl;
        cout<<"|  |                                                       |  | "<<endl;
        cout<<"|  |            >>  2. Cadastrar Estrada  <<               |  |"<<endl;
        cout<<"|  |                                                       |  | "<<endl;
        cout<<"|  |     >>  3. Buscar Centro Pokemon Mais Proximo  <<     |  |"<<endl;
        cout<<"|  |                                                       |  | "<<endl;
        cout<<"|  |             >>  4. Cadastrar Pokemon  <<              |  |"<<endl;
        cout<<"|  |                                                       |  | "<<endl;
        cout<<"|  |              >>  5. Remover Pokemon  <<               |  |"<<endl;
        cout<<"|  |                                                       |  | "<<endl;
        cout<<"|  |           >>  6. Listar Pokemons (Nome) <<            |  |"<<endl;
        cout<<"|  |                                                       |  | "<<endl;
        cout<<"|  |         >>  7.  Listar Pokemons (Tipo)  <<            |  |"<<endl;
        cout<<"|  |                                                       |  | "<<endl;
        cout<<"|  |       >>  8.  Contar Pokemons de Cada Tipo  <<        |  |"<<endl;
        cout<<"|  |                                                       |  | "<<endl;
        cout<<"|  |        >>  9.  Encontrar Pokemons Proximos  <<        |  |"<<endl;
        cout<<"|  |                                                       |  | "<<endl;
        cout<<"|  |                   >>  10.  Sair  <<                   |  |"<<endl;
        cout<<"|  |                                                       |  | "<<endl;
        cout<<"|-------------------------------------------------------------|"<<endl;
        cout<<"|                      |   z(^.w.^)   |                       |"<<endl;
        cout<<"|-------------------------------------------------------------|"<<endl;
        cout<<"\n";
        cout<<"|-------------------------------------------------------------|"<<endl;
        cout<<"|--------| Para saber mais sobre o time, pressione 0 |--------|"<<endl;
        cout<<"|-------------------------------------------------------------|"<<endl;
        cout<<"\n";
        cout<<"                 >>   Escolha uma opcao:   <<                  "<<endl;
        cout<<"                             ...                                "<<endl;
        
        cin >> opcao;
        while(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida! Tente novamente: ";
            cin >> opcao;
        }

        system("cls");

        switch(opcao){
            case 0:  mostraTime();      break;
            case 1:  cadastroCidade();  break;
            case 2:  cadastroEstrada(); break;
            case 3:  buscaCentro();     break;
            case 4:  cadastroPokemon(); break;
            case 5:  removePokemon();   break;
            case 6:  
                listaNome();       
                menuVoltar();
                break;
            case 7:  listaTipo();       break;
            case 8:  contaPokemon();    break;
            case 9:  encontraPokemon(); break;
            case 10: 
                destruct(rootPokemons);
                destruct(rootTipo);
                return 0;
            default:
                cout << "Opcao invalida!" << endl;
                menuVoltar();
        }
    }

    return 0;
}