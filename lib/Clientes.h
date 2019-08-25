//
// Created by Xx220xX on 25/08/2019.
//

#ifndef PET_CLIENTES_H
#define PET_CLIENTES_H

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;
#define  STRING std::string
class Endereco {
    STRING cep = "";
    STRING rua = "";
    int numero = 0;

public:
    STRING toString() {
        return STRING("RUA: ") + rua + STRING("\nnumero:") + std::to_string(this->numero) + STRING("\ncep: ") + cep;
    }

    Endereco() {}

    Endereco(STRING cep, STRING rua, int numero) {
        this->cep = cep;
        this->rua = rua;
        this->numero = numero;
    }

};

class Cliente {
    int id;
    STRING nome;
    STRING nome_pet;
    STRING pacote;
    int dia;
    int mes;
    int ano;
    char dia_semana[8];
    Endereco endereco;
public:
    Cliente() {}

    Cliente(const STRING nome, const STRING nomePet, const STRING pacote, int dia, int mes, int ano,
            const char *diaSemana, const Endereco end) {
        this->nome = nome;
        this->nome_pet = nomePet;
        this->pacote = pacote;
        this->dia = dia;
        this->ano = ano;
        snprintf(this->dia_semana, 8, "%s", diaSemana);
    }

    STRING toString() {
        return STRING("Nome do cliente: ") + this->nome + STRING("\nNome do Pet: ") + this->nome_pet +
               STRING("\nPacote: ") + this->pacote + STRING("\n") + this->endereco.toString();
    }

    void setNome(STRING name) {
        this->nome = name;
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
            a.append("\n").append(clientes[i].toString()).append("\n");
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
};

#endif //PET_CLIENTES_H
