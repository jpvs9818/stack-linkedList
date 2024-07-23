#include <iostream>

using namespace std;

class celula{
    private:

    char conteudo = '\0';
    celula *prox = nullptr;

    public:         // gets e sets da classe celula
    void setConteudo(const char conteudo){
        this->conteudo = conteudo;
    }
    void setProx(celula *prox){
        this->prox = prox;
    }
    char getConteudo(){
        return this->conteudo;
    }
    celula* getProx(){
        return this->prox;
    }
    explicit celula(const char c){      //evitar conversões implicitas por acidente sendo necessario chamar o método
        setConteudo(c);
    }
};

class lista{
    private:

    celula *cabeca = nullptr;

    public:

        void empilha(const char c){
            celula *temp = cabeca;
            if(temp == nullptr) {
                cabeca = new celula(c);
            }
            else {
                while(temp->getProx() != nullptr) {
                    temp = temp->getProx();
                }
                temp->setProx(new celula(c));
            }
        }

        void desempilha(){
           celula *temp = cabeca;
            if(temp == nullptr) {   //evitar segmentation faults
                cout << "Nao existe valor para remover.\n";
            }
            else {
                    if(temp->getProx() == nullptr) {
                    delete cabeca;
                    cabeca = nullptr;
                }
                else {
                    celula *temp2 = nullptr;
                    while(temp->getProx() != nullptr) {         //temp2 para evitar dangling pointer
                        temp2 = temp;
                        temp = temp->getProx();
                    }
                    delete temp;
                    temp2->setProx(nullptr);
                }
            }

        }

        void desempilhaTudo() {         //desalocar todos os espaços de memória
            while(cabeca != nullptr)
                desempilha();
        }

        void mostraListaPilha(){
            celula *temp = cabeca;
            int contador = 1;
            while(temp != nullptr){
                cout << "Conteudo da celula " << contador  << ": " << temp->getConteudo() << '\n';
                contador++;
                temp = temp->getProx();
            }
        }
};

int menu(){
    int i = 0;
    cout << "Insira a operacao desejada"<<'\n' << '\n'
         << "1.Add valor (empilha)" << '\n'
         << "2.Rem valor (desempilha)" << '\n'
         << "3.Mostrar valores da lista" << '\n'
         << "4.Sair" << '\n';
    cin >> i;
    return i;
}

void opcao1(lista &pilha){  //feito para organizar o case 1 no main
    char conteudo = '\0';
    cout << "Insira um caractere"<<"\n\n";
    cin >> conteudo;
    pilha.empilha(conteudo);
}

int main(){
    lista pilha;
    int i;
    do{
        i = menu();

        switch(i){
            case 1:
                opcao1(pilha);
                break;
            case 2:
                pilha.desempilha();
                break;
            case 3:
                pilha.mostraListaPilha();
                break;
            case 4:
                cout << "Saindo";
                break;
            default:
                cout << "Insira um valor valido\n";
                break;
        }
    }while(i != 4);

    pilha.desempilhaTudo();
    return 0;
}