#include <iostream>
#include <fstream>

using namespace std;

class Node{
    double info;
    Node *prev;
    Node *urm;
public:
    Node(double info = 0){
        this->info = info;
        this->urm = NULL;
        this->prev = NULL;
    }

    double getinfo();
    Node*& getNext();
    Node*& getPrev();
    void setInfo(double val);
    void setNext(Node* n);
    void setPrev(Node* n);
    friend class List;
};

double Node::getinfo()
{
    return this->info;
}

void Node::setInfo(double val){
    this->info = val;
}

Node*& Node::getNext(){
    return this->urm;
}

Node*& Node::getPrev(){
    return this->prev;
}

void Node::setNext(Node* n){
    this->urm  = n;
}

void Node::setPrev(Node* n){
    this->prev = n;
}

class List{
private:
    int nrElem;
    Node *prim;
    Node *ultim;

public:

     List(int nrElem = 0){
        this->nrElem = nrElem;
        this-> prim = NULL;
        this->ultim = NULL;
    }
  /*  ~List(){
        Node *p, *s = prim;
        while(s->urm != NULL){
            s = s->urm;
            p = s->prev;
            delete p;
    }*/

     Node*& getPrim() {
        return prim;
    }

    Node*& getUltim() {
        return ultim;
    }

    int getnrElem();
    void setnrElem(int nrElem);
    void addLast(double val);
    void deleteLast();

    static void concatenate(Node *a,Node *b)
    {
        if( a != NULL && b!= NULL )
        {
            if (a->getNext() == NULL)
              {
                a->setNext(b);
                b->setPrev(a);
              }
            else
                concatenate(a->getNext(),b);

        }
        else
        {
            cout << "Either a or b is NULL\n";
        }
    }

    friend istream &operator >> (istream & f, List &lista);
    friend ostream &operator << (ostream & g, List &lista);
    List& operator + ( List& lista1);

};

int List::getnrElem()
{
    return nrElem;
}

void List::setnrElem(int nrElem){
    this->nrElem = nrElem;
}

void List::addLast(double val){
    Node *p = new Node;
    p->setInfo(val);
    p->setNext(NULL);

    if(prim == NULL){
        prim = p;
        prim->setPrev(NULL);
        ultim = prim;
    }
    else{
        ultim->setNext(p);
        p->setPrev(ultim);
        ultim = p;
    }
}

void List::deleteLast(){
    Node *p = new Node;
    p = ultim;
    ultim = ultim->getPrev();
    ultim->setNext(NULL);
    delete p;
}

istream &operator >> (istream& f, List &lista){
    double val;
    int i;

    for(i=0; i<lista.getnrElem(); i++){
        cout<<"x = ";
        f>>val;
        lista.addLast(val);
    }

    cout<<endl;
}

ostream &operator << (ostream& g, List &lista){
    Node *s = new Node;
    s = lista.getPrim();
    g<<"Afisarea listei in ordinea introducerii elementelor: "<<endl;
    while(s != NULL)
    {
        g<<s->getinfo()<<" ";
        s = s->getNext();
    }

    cout<<endl;

    s = lista.getUltim();
    g<<"Afisarea listei in ordine inversa"<<endl;
    while(s != NULL){
        g<<s->getinfo()<<" ";
        s = s->getPrev();
    }
    cout<<endl;
}


List& List::operator+(List &lista1){

    List *p = new List(this->getnrElem() + lista1.getnrElem());
    Node *s = this->getPrim();
    Node *k = lista1.getPrim();
    concatenate(s, k);
    p->getPrim() = s;
    p->getUltim() = lista1.getUltim();

    return *p;
}

int main()
{
    int nr1, t, nr2, ok;
    cout<<"Numarul de elemente pentru prima lista este: ";cin>>nr1;
    cout<<"Numarul de elemente pentru cea de-a doua lista este: "; cin>>nr2;

    List L1(nr1);
    List L2(nr2);

    cin>>L1;
    cin>>L2;

    cout<<"Afisarea listei L1 (in ordinea introducerii elementelor si in ordinea inversa)"<<endl;
    cout<<L1;
    cout<<endl;

    cout<<"Afisarea listei L2 (in ordinea introducerii elementelor si in ordinea inversa)"<<endl;
    cout<<L2;
    cout<<endl;

    cout<<"Doriti sa stergeti un element de la final? 1 - Da ; 0 - Nu"<<endl;
    cin>>ok;
    if(ok == 1){
        int ok1;
        cout<<"Stergeti din L1 sau L2? 1 - L1 ; 0 - L2"<<endl;
        cin>>ok1;
        if(ok1 == 0){
            L2.deleteLast();
            cout<<L2;
        }
        else{
            L1.deleteLast();
            cout<<L1;
        }
    }

    cout<<"Cele doua liste dupa concatenare: "<<endl;
    cout<<L1 + L2;
    cout<<endl;


    return 0;
}
