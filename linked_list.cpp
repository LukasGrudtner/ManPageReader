#include "linked_list.h"
#include <iostream>

LinkedList::LinkedList()
{
    size_ = 0;
    head = new Node();
}

LinkedList::~LinkedList()
{
    clear();
    delete(head);
}

void LinkedList::clear()
{
    while (!empty()) {
        pop_front();
    }
}

void LinkedList::push_back(const string& data)
{
    insert(data, size());
}

void LinkedList::push_back_register(const string& data, size_t quantidade_)
{
    Node* atual;
    Node* novo;

    if (novo == NULL) {
        throw std::out_of_range("Erro Lista Cheia!");
    } else {
        if(size() == 0) {
            novo = new Node(data);
            novo->setQuantidade(quantidade_);
            head->next(novo);
            size_++;
        } else {
            atual = head->next();
            while (atual->data() != data && atual->next() != nullptr) {
                atual = atual->next();
            }
            if (atual->data() == data) {
                atual->setQuantidade(quantidade_);
            } else {
                novo = new Node(data);
                novo->setQuantidade(quantidade_);
                atual->next(novo);
            }
        }
    }
}

void LinkedList::push_front(const string& data)
{
    Node* novo;
    novo = new Node(data);

    if (novo == NULL) {
        throw std::out_of_range("Erro Lista Cheia!");
    } else {
        if(size() == 0) {
            head->next(novo);
            size_++;
            novo->incQuantidade();
        } else {
            novo->next(head->next());
            head->next(novo);
            novo->incQuantidade();
            size_++;
        }
    }
}

void LinkedList::insert(const string& data, std::size_t index)
{
    Node *novo;
    Node *anterior;

    if (index < 0 || index > size_) {
        throw std::out_of_range("Erro Posição!");
    } else {

        if (index == 0) {
            push_front(data);
        } else {
            novo = new Node(data);

            if (novo == NULL) {
                throw std::out_of_range("Erro Lista Cheia!");

            } else {
                anterior = head->next();

                for (auto i = 0u; i < index - 1; ++i) {
                    anterior = anterior->next();
                }

                novo->next(anterior->next());
                anterior->next(novo);
                novo->incQuantidade();
                size_++;
            }
        }
    }
}

void LinkedList::insert_sorted(const string& data)
{
    Node* atual;
    auto posicao = 0;

    if (empty()) {
        push_front(data);
    } else {
        atual = head->next();

        while (atual->next() != NULL && data > atual->data()) {
            atual = atual->next();
            posicao++;
        }

        if (data > atual->data()) {
            insert(data, posicao+1);
        } else {
            insert(data, posicao);
        }
    }
}

string& LinkedList::at(std::size_t index)
{
    Node* anterior = head;

    if (empty()) {
        throw std::out_of_range("Erro Lista Vazia!");
    } else {
        if (index < 0 || index > size_) {
            throw std::out_of_range("ERRO");
        } else {

            anterior = head->next();

            for (auto i = 0; i < index; ++i) {
                anterior = anterior->next();
            }

            return anterior->data();
        }
    }
}

string LinkedList::pop(std::size_t index)
{
    Node *atual;
    Node *eliminar;
    string volta = 0;

    if (index < 0 || index > size_ -1) {
        throw std::out_of_range("Erro Posição!");
    } else {
        if (index == 0) {
            pop_front();
        } else {
            atual = head->next();

            for (auto i = 0u; i < index - 1; ++i) {
                atual = atual->next();
            }

            eliminar = atual->next();
            volta = eliminar->data();

            if (index < size() - 1) {
                atual->next(eliminar->next());
            }

            size_--;
            delete(eliminar);
            return volta;
        }
    }

    return volta;
}

string LinkedList::pop_back()
{
    if (empty()) {
        throw std::out_of_range("Erro Lista Vazia!");
    }
    return pop(size()-1);
}

string LinkedList::pop_front()
{
    Node* saiu;
    string volta;

    if (empty()) {
        throw std::out_of_range("Erro Lista Vazia!");
    } else {
        saiu = head->next();
        volta = saiu->data();
        if (size_ > 0) {
            head->next(saiu->next());
        }
        size_--;
        delete(saiu);
        return volta;
    }
}

void LinkedList::remove(const string& data)
{
    Node *atual = head->next();
    Node *anterior = head;

    while (atual->data() != data) {
        anterior = anterior->next();
        atual = atual->next();
    }

    anterior->next(atual->next());
    delete(atual);
    size_--;
}

bool LinkedList::empty() const
{
    return (size_ == 0);
}

bool LinkedList::contains(const string& data) const
{
    Node *anterior = head;

    for (auto i = 0u; i < size_; ++i) {
        anterior = anterior->next();
        if (anterior->data() == data) {
            return true;
        }
    }

    return false;
}

string LinkedList::find(const string& data) const
{
    auto i = 0u;
    Node* anterior = head->next();

    while (anterior->data() != data && i < size()) {
        ++i;

        if (i < size())
            anterior = anterior->next();
    }
    return anterior->data();
}

std::size_t LinkedList::size() const
{
    return size_;
}

std::size_t LinkedList::getQuantidadeNode(const string& data) const
{
    auto i = 0u;
    Node* anterior = head->next();

    while (anterior->data() != data && i < size()) {
        ++i;
        anterior = anterior->next();
    }
    return anterior->getQuantidade();
}

void LinkedList::incQuantidadeNode(const string& data)
{
    auto i = 0u;
    Node* anterior = head->next();

    while (anterior->data() != data && i < size()) {
        ++i;
        anterior = anterior->next();
    }
    anterior->incQuantidade();
}
