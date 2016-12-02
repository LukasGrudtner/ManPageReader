#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <stdexcept>

using namespace std;

class LinkedList
{
    public:
        LinkedList();
        virtual ~LinkedList();
        void clear();
        void push_back(const string& data);
        void push_back_register(const string& data, std::size_t quantidade_);
        void push_front(const string& data);
        void insert(const string& data, std::size_t index);
        void insert_sorted(const string& data);
        string& at(std::size_t index);
        string pop(std::size_t index);
        string pop_back();
        string pop_front();
        void remove(const string& data);
        bool empty() const;
        bool contains(const string& data) const;
        string find(const string& data) const;
        std::size_t getQuantidadeNode(const string& data) const;
        void incQuantidadeNode(const string& data);
        std::size_t size() const;

    protected:

    private:
        class Node { // Elemento
         public:

            //! Construtor
            /*! Método construtor da classe Node com um parâmetro de dados.
                /param data dado a ser inserido no Node.
            */
            Node(){};

            Node(const string& data):
                data_{data}
            {}

            //! Data
            /*! Método getter de um Node.
                /return o dado do elemento.
            */
            string& data() {
                return data_;
            }

            //! Data Const
            /*! Método getter de um Node, onde o dado retornado não será alterado.
                /return o dado do elemento.
            */
            const string& data() const {
                return data_;
            }

            //! Next
            /*! Método getter de um Node.
                /return o ponteiro para o próximo elemento.
            */
            Node* next() { // getter: próximo
                return next_;
            }

            //! Next
            /*! Método getter de um Node, onde o ponteiro retornado não será alterado.
                /return o ponteiro para o próximo elemento.
            */
            const Node* next() const {
                return next_;
            }

            //! Next
            /*! Método setter de um Node.
                /param um ponteiro, que será o indicador do próximo elemento.
            */
            void next(Node* node) { // setter: próximo
                next_ = node;
            }

            void incQuantidade() {
                quantidade_++;
            }

            void setQuantidade(std::size_t quantidade) {
                quantidade_ = quantidade;
            }

            std::size_t getQuantidade() {
                return quantidade_;
            }

         private:
            string data_; /**< Declaração do dado, do tipo T. */
            std::size_t quantidade_ = 0;
            Node* next_{nullptr}; /**< Declaração do ponteiro para o próximo Node. */
    };

    Node* head{nullptr}; /**< Declaração da cabeça da lista. */
    std::size_t size_{0u}; /**< Declaração do tamanho da lista. */

};

#endif // LINKEDLIST_H
