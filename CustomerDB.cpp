#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(String name) { // done, please do not edit
    this->bottles = 0;
    this->rattles = 0;
    this->diapers = 0;
    this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

int CustomerDB::size(void) {
    return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
    delete[] this->data;
}

void CustomerDB::clear(void) { // done, please do not edit
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
    assert(k >= 0 && k < this->length);
    return this->data[k];
}

/* This member function simply checks to see if a particular customer's name is
 * located in the CustomerDB struct database, returns true if so and false otherwise. */
bool CustomerDB::isMember(String name) { 
    for (int i = 0; i < this->length; i++) {
        if (this->data[i].name == name) return true;
        else return false;
    }
}

/* Operator overload--customers can access database locations using the customer's name directly,
 * e.g. "database[name]," where "name" is a String variable of someone's name,
 * would be the equivalent of accessing the kth element in the array of Customer structs,
 * where "k" is the location of the customer requested in the array. If the customer requested isn't present, 
 * their name is added to the array and their data is returned. */
Customer& CustomerDB::operator[](String name) {
    for (int i = 0; i < this->length; i++) {
        if (this->data[i].name == name) {
            return this->data[i];
        }
    }

    //amortized doubling for when a greater capacity is required to add a new customer
    if (this->length == this->capacity) {
        this->capacity *= 2;
        Customer* new_data = new Customer[this->capacity];

        for (int i = 0; i < this->length; i++) {
            new_data[i].name = this->data[i].name;
            new_data[i].bottles = this->data[i].bottles;
            new_data[i].rattles = this->data[i].rattles;
            new_data[i].diapers = this->data[i].diapers;
        }

        delete[] this->data;
        this->data = new_data;
    }

    this->data[length].name = name;
    this->data[length].bottles = this->data[length].rattles = this->data[length].diapers = 0;
    this->length += 1;
    return this->data[length-1];
}


