/*
 * EE 312 CRM in C++
 * Name: Raiyan Chowdhury
 * TA: Ka Tai
 * Section: T/Th 3:30-5:00, M 2:00-3:00 
 */

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include "String.h"
#include "Customer.h"
#include "CustomerDB.h"

using namespace std;

void readString(String&);
void readNum(int&);

CustomerDB database;

//inventory
int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;


/**********************************reset**********************************
 *clear the inventory and reset the customer database to empty 
 */
void reset(void) {
    database.clear();
    num_bottles = 0;
    num_rattles = 0;
    num_diapers = 0;
}

/**********************************selectInventItem**********************************
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the 
 * current global variable for the number of bottles in the inventory
 */
int* selectInventItem(String word) {
    if (word == "Bottles") {
        return &num_bottles;
    } else if (word == "Diapers") {
        return &num_diapers;
    } else if (word == "Rattles") {
        return &num_rattles;
    }
    
    /* NOT REACHED */
    return 0;
}

/**********************************selectInventItem**********************************
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(String word, Customer& cust) {
    if (word == "Bottles") {
        return &cust.bottles;
    } else if (word == "Diapers") {
        return &cust.diapers;
    } else if (word == "Rattles") {
        return &cust.rattles;
    }
    
    /* NOT REACHED */
    return 0;
}


/**********************************findMax**********************************
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 * 
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the 
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(String type) {
    Customer* result = 0;
    int max = 0;
    for (int k = 0; k < database.size(); k += 1) {
        Customer& cust = database[k];
        int *p = selectInventItem(type, cust); 
        if (*p > max) {
            max = *p;
            result = &cust;
        }
    }
    
    return result;
}

/**********************************processPurchase**********************************
 * This function reads the customer's name, item type, and the quantity requested
 * of said item. It then updates the customer database appropriately.
 * Prints error message if customer tries to request more than what's available.
 * INPUTS: none
 * OUTPUTS: none
 */
void processPurchase() {
    String name;
    String item;
    String bottles = String("Bottles");
    String rattles = String("Rattles");
    String diapers = String("Diapers");
    int num;

    readString(name); readString(item);
    assert(item == bottles || item == rattles || item == diapers);
    readNum(num);
    assert(num >= 0);

    if (num > 0) {//if num == 0, do nothing
        if (item == bottles) {
            if (num <= num_bottles) {//valid purchase, update accordingly
                num_bottles -= num;
                database[name].bottles += num;
            }
            else {//invalid purchase, error message
                cout << "Sorry " << name.c_str() << ", we only have " << num_bottles << " Bottles" << endl;
            }
        }

        else if (item == rattles) {
            if (num <= num_rattles) {
                num_rattles -= num;
                database[name].rattles += num;
            }
            else {
                cout << "Sorry " << name.c_str() << ", we only have " << num_rattles << " Rattles" << endl;
            }
        }

        else if (item == diapers) {
            if (num <= num_diapers) {
                num_diapers -= num;
                database[name].diapers += num;
            }
            else {
                cout << "Sorry " << name.c_str() << ", we only have " << num_diapers << " Diapers" << endl;
            }
        }
    }
}

/**********************************processSummarize**********************************
 * Prints out a summary of the inventory and purchases at the time it at which it is called.
 * First prints quantity of everything left in inventory, then number of customers who visited 
 * the store (not counting those who attempted to make an invalid purchase or bought nothing), 
 * and then it prints which customer bought the most of each item (unless no one bought a particular
 * item, in which case this is indicated instead).
 * INPUTS: none
 * OUTPUTS: none
 */
void processSummarize() {
    String bottles = String("Bottles");
    String rattles = String("Rattles");
    String diapers = String("Diapers");

    cout << "There are " << num_bottles << " Bottles, " << num_diapers << " Diapers and " << num_rattles << " Rattles in inventory" << endl; 
    cout << "we have had a total of " << database.length << " different customers" << endl;

    Customer* max = findMax(bottles);
    //nullptr means no actual max above 0 was found, so findMax's "result" pointer never changes from "0"
    if (max == nullptr) { cout << "no one has purchased any Bottles" << endl; }
    else { cout << max->name.c_str() << " has purchased the most Bottles (" << max->bottles << ")" << endl; }

    max = findMax(diapers);
    if (max == nullptr) { cout << "no one has purchased any Diapers" << endl; }
    else { cout << max->name.c_str() << " has purchased the most Diapers (" << max->diapers << ")" << endl; }

    max = findMax(rattles);
    if (max == nullptr) { cout << "no one has purchased any Rattles" << endl; }
    else { cout << max->name.c_str() << " has purchased the most Rattles (" << max->rattles << ")" << endl; }
}

/**********************************processInventory**********************************
 * This function reads the item type and quantity using readString and readNum, 
 * respectively, and updates the inventory appropriately.
 * Crashes if an incorrect item type is given.
 * INPUTS: none
 * OUTPUTS: none
 */
void processInventory() {
    String next_command;
    String bottles = String("Bottles");
    String rattles = String("Rattles");
    String diapers = String("Diapers");
    int num;

    readString(next_command);
    assert(next_command == bottles || next_command == rattles || next_command == diapers);
    readNum(num);
    assert(num > 0);
    if (num == 0) return;

    if (next_command == bottles) { num_bottles += num; }
    else if (next_command == rattles) { num_rattles += num; }
    else if (next_command == diapers) { num_diapers += num; }
}
