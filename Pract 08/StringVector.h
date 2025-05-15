#pragma once
#include "String.h"
#include <iostream>
#include <stdexcept>
class StringVector 
{
private:
    String* _data;
    size_t _size;
    size_t _capacity;

    void freeDynamic();
    void copyDynamic(const StringVector& other);

public:
    StringVector();
    StringVector(String* data, size_t size, size_t capacity);
    StringVector(const StringVector& other);
    StringVector& operator=(const StringVector& other);
    StringVector(StringVector&& other) noexcept;
    StringVector& operator=(StringVector&& other) noexcept;
    ~StringVector();


    //setters
    void setString(String* data);
    size_t setSize(size_t size);
    size_t setCapacity(size_t capacity);



    //additional
    void push_back(const String& str);
    void resize();
    void pop_back();
    void insert(int index, const String& str);
    void erase(int index);
    void clear();
    const String& at(const int index) const;
    String& at(const int index);
    bool isEmpty() const;
    size_t getSize() const;

};
