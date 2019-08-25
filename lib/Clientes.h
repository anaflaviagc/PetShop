//
// Created by Xx220xX on 25/08/2019.
//

#ifndef PET_CLIENTES_H
#define PET_CLIENTES_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;
#define  STRING std::string

int length(char *str) {
    int i = 0;
    for (; str[i]; i++);
    return i;
}
class EOFException : public exception {
    STRING error;
public:
    EOFException(STRING error) {
        this->error = error;
    }

    const char *what() {
        return this->error.c_str();
    }
};


STRING toStr(char *p, int begin, bool remove_endl = true) {
    int i;
    if (remove_endl) {
        if (p[length(p) - 1] == '\n') {
            p[length(p) - 1] = 0;
            if(length(p)==0){
                return "";
            }

        }

    }


    if (begin < length(p)) {

        return STRING(p + begin);
    }
    return "";
}

class BoundException : public exception {
    STRING error;
public:
    BoundException(STRING error) {
        this->error = error;
    }

    const char *what() {
        return this->error.c_str();
    }
};

class ENDERECO {
    STRING cep = "";
    STRING rua = "";
    int numero = 0;

public:
    STRING toString() {
        return STRING("RUA: ") + rua + STRING("\nnumero:") + std::to_string(this->numero) + STRING("\ncep: ") + cep +
               STRING("\n");
    }

    ENDERECO() {}

    ENDERECO(FILE *file_to_read) {
        char buff[500];
        fgets(buff, 500, file_to_read);
        this->rua = toStr(buff, 4);
        fgets(buff, 500, file_to_read);
        this->numero = atoi(toStr(buff, 7).c_str());
        fgets(buff, 500, file_to_read);
        this->cep = toStr(buff, 4);
    }

    ENDERECO(STRING cep, STRING rua, int numero) {
        this->cep = cep;
        this->rua = rua;
        this->numero = numero;
    }

};

class Cliente {
    STRING nome = "";
    STRING nome_pet = "";
    STRING pacote = "";
    STRING contato = "";
    int dia = 0;
    int mes = 0;
    int ano = 0;
    int banhos = 0;
    char dia_semana[8] = "";
    ENDERECO endereco;
public:
    Cliente() {}

    Cliente(const STRING nome, const STRING nomePet, const STRING pacote, int dia, int mes, int ano,
            const char *diaSemana, const ENDERECO end, const STRING numero = "nao informado",int banhos = 0) {
        this->nome = nome;
        this->nome_pet = nomePet;
        this->pacote = pacote;
        this->contato = numero;
        this->dia = dia;
        this->ano = ano;
        this->banhos = banhos;
        snprintf(this->dia_semana, 8, "%s", diaSemana);
    }
    static void getSTR(char *p,int size,FILE *f){
        if(!fgets(p,size,f)){
            throw EOFException("nao ha dados");
        }
      //  cout<<" aki --->"<<p<<"<----\n";
    }
    static Cliente load(FILE *font) {
        Cliente t;
        char buff[500];

        getSTR(buff, 500, font);
        t.nome = toStr(buff, 17);

        getSTR(buff, 500, font);
        t.nome_pet = toStr(buff, 13);
        getSTR(buff, 500, font);
        t.pacote = toStr(buff, 8);
        getSTR(buff, 500, font);
        t.contato = toStr(buff, 9);
        getSTR(buff, 500, font);
        t.banhos = atoi(toStr(buff, 17).c_str());
        t.endereco = ENDERECO(font);
        return t;
    }

    void save(FILE *goal) {
        fprintf(goal, "%s", this->toString().c_str());
    }

    STRING toString() {
        return STRING("Nome do cliente: ") + this->nome + STRING("\nNome do Pet: ") + this->nome_pet +
               STRING("\nPacote: ") + this->pacote + STRING("\nContato: ") +
               this->contato + STRING("\n") + STRING("Banhos Restantes: ")+to_string(this->banhos)+STRING("\n")+this->endereco.toString();
    }

    void setNome(STRING name) {
        this->nome = name;
    }

    STRING getNome() {
        return this->nome;
    }

    STRING getNomePet() {
        return this->nome_pet;
    }
};

class listClients {
    int size = 0;
    vector<Cliente> clientes;
public:

    ~listClients() {
        /**
         * Chamado quando vai destruir a variavel
         */
        clientes.clear();
    }

    STRING toString() {
        STRING a = "";
        for (int i = 0; i < size; ++i) {
            a.append(clientes[i].toString()).append("\n\n");
        }
        return a;
    }

    void add(Cliente c) {
        size++;
        clientes.push_back(c);
    }

    void remove(int index) {
        if (size > 0) {
            auto it = clientes.begin();
            std:
            advance(it, index);
            clientes.erase(it);
            size--;
        }
    }

    Cliente at(int index) {
        if (index < 0 || index >= size) {
            throw BoundException("posicao invalida");
        }
        return clientes[index];
    }

    int find(STRING nome, STRING pet) {
        for (int i = 0; i < size; i++) {
            if (nome == clientes[i].getNome() && pet == clientes[i].getNomePet()) {
                return i;
            }
        }
        return -1;
    }

    int find_next(int index_begin, STRING nome,
                  bool the_name_is_Pet = false) {// encontra o proximo cliente com o nome a partir do indice indicado;
        for (int i = index_begin; i < size; i++) {
            if (the_name_is_Pet) {
                if (nome == clientes[i].getNomePet()) {
                    return i;
                }
            } else if (nome == clientes[i].getNome()) {
                return i;
            }
        }
        return -1;//caso nao encontrar
    }

    void save(const char *fileName) {
        FILE *f = fopen(fileName, "w");
        for (int i = 0; i < size; ++i) {
            clientes[i].save(f);
        }
        fclose(f);
    }

    void load(const char *file_name) {
        FILE *f = fopen(file_name, "r");
       while (true) {
            try {
                Cliente temporario;
                temporario = Cliente::load(f);
                add(temporario);
            } catch (...) {
                break;
            }
        }
        fclose(f);
        return;

    }
};

#endif //PET_CLIENTES_H
