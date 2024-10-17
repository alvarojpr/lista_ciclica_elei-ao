#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct node{
    int id;
    int chave; // maior chave deve ser eleita
    bool eleito; 
    node* proximo;
    node* anterior;
};

void novo_no(node* head, int id, int chave_aleatoria){
    node* novo = new node;
    novo->id = id;
    novo->chave = chave_aleatoria;
    novo->eleito = false;

    if(head->proximo == head){ // se tiver só um nó
        novo->proximo = head;
        novo->anterior = head;
        head->proximo = novo;
        head->anterior = novo;
    } else { // se tiver mais de um nó
        node* ultimo = head->anterior;
        novo->proximo = head;      // O próximo do novo nó será sempre head
        novo->anterior = ultimo;   // O anterior será o antigo último nó
        ultimo->proximo = novo;    // O próximo do antigo último agora é o novo
        head->anterior = novo;     // O anterior do head é o novo nó
    }
}

void listar(node* head){
    node* atual = head;
    do{
        if(atual->eleito == false){
            cout << "Nó " << atual->id << " tem chave " << atual->chave << " e não foi o eleito.\n";
        } else {
            cout << "Nó " << atual->id << " tem chave " << atual->chave << " e FOI ELEITO.\n";
        }
        atual = atual->proximo;
    } while(atual != head);
}

void enviar_mensagem(node* head, string mensagem) {
    node* atual = head;
    do {
        cout << "Nó " << atual->id << " recebeu a mensagem: " << mensagem << "\n";
        atual = atual->proximo; // passa de nó em nó
    } while (atual != head);
}

void eleicao(node* head){
    node* atual = head;
    int maior_chave = atual->chave;
    node* eleito = atual;

    do {
        cout << "Nó " << atual->id << " participa da eleição com chave " << atual->chave << "\n";
        if (atual->chave > maior_chave) {
            maior_chave = atual->chave;
            eleito = atual;
        }
        atual = atual->proximo;
    } while (atual != head);

    eleito->eleito = true;
    cout << "Nó " << eleito->id << " com chave " << eleito->chave << " foi eleito como coordenador.\n";
}

void chamar_eleicao(node* head, int id){
    node* atual = head;
    do {
        if(atual->id == id){
            cout << "Nó de id: " << atual->id << " com chave " << atual->chave << " convoca eleicao.\n";
            eleicao(head);
            break;
        }
        atual = atual->proximo;
    } while(atual != head);
}

void liberar_memoria(node* head) {
    node* atual = head;
    do {
        node* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    } while (atual != head);
}

int main() {
    srand(time(0)); // Inicializa a semente, fazendo com que cada vez que eu rode o programa os números sejam diferentes
    int chave_aleatoria = rand() % 19 + 2; // Gera número entre 2 e 20

    // Cria o primeiro nó da lista, cabeça
    node* head = new node{1, chave_aleatoria, false, nullptr, nullptr}; //nullpts é o mesmo que NULL
    head->proximo = head;
    head->anterior = head;

    int id;

    // Criando + 9 nós, totalizando 10
    for(id = 2; id <= 10; id++){
        chave_aleatoria = rand() % 19 + 2; // Gera um número entre 2 e 20
        novo_no(head, id, chave_aleatoria);
    }

    int choice;
    string mensagem;

    do {
        cout << "Escolha uma opção:\n";
        cout << "1 - Listar nós\n";
        cout << "2 - Fazer eleição\n";
        cout << "3 - Enviar mensagem\n>>";
        cin >> choice;

        switch (choice) {
            case 1:
                listar(head);
                break;
            case 2:
                cout << "Digite o id do nó que deseja enviar a mensagem de eleição: ";
                cin >> id;
                chamar_eleicao(head, id);
                break;
            case 3:
                cout << "Digite a mensagem a ser enviada: ";
                cin >> mensagem;
                enviar_mensagem(head, mensagem);
                break;
            default:
                liberar_memoria(head);
                return 0;
        }
    } while(choice >= 1 && choice <= 3);

    liberar_memoria(head);
    return 0;
}
