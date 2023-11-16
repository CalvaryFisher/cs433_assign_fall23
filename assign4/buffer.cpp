/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Reece Harris & Calvary Fisher 
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include "buffer.h"
#include <iostream>

using namespace std;

// TODO: Add your implementation of the buffer class here

Buffer::Buffer(int size) {
    this->size = size;
    this->num_elements = 0;
}

Buffer::~Buffer() {
    
}

bool Buffer::insert_item(buffer_item item) {
    if (this->is_full() == true) {
        cout << "Buffer full. Insertion failed." << endl;
        return false;
    }
    else {
        this->buffer.push_back(item);
        this->num_elements++;
        return true;
    }
}


bool Buffer::remove_item(buffer_item item) {
    if (this->is_empty() == true) {
        cout << "Buffer empty. Removal failed." << endl;
        return false;
    }
    else {
        this->buffer.erase(buffer.begin());
        this->num_elements--;
        return true;
    }
}

int Buffer::get_size() {
    return this->size;
}

int Buffer::get_count() {
    return this->num_elements;
}

bool Buffer::is_empty() {
    if (this->num_elements == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Buffer::is_full() {
    if (num_elements == size) {
        return true;
    }
    else {
        return false;
    }
}

void Buffer::print_buffer() {
    cout << "Buffer: [";  
    if (this->num_elements > 0) {
        for (int i = 0; i < this->num_elements - 1; i++) {
        cout << buffer[i] << ", ";
        }
        cout << buffer[this->num_elements - 1];
    }  
    

    cout << "]\n";
}



