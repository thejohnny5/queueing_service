#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdint.h"

#define KEY_SIZE 50
// We want a hashtable that has a key which is a char of up to 50 characters
// The value can be either an int32 float32 char of up to 50 characters
// Uses chaining to handle merge conflicts
typedef enum ValueType {
    INT_TYPE,
    STRING_TYPE,
    FLOAT_TYPE
} ValueType;

typedef struct node{
    char key[KEY_SIZE];
    ValueType value_type; // Need some way to specify the value in the union
    union Value
    {
        int32_t num;
        char string[KEY_SIZE];
        _Float32 decimal;
    } value;
    struct node* next;
    
} node;

typedef struct hashtable
{
    size_t capacity;
    size_t size;
    struct node** array;
} hashtable;

hashtable* create_hash_table(size_t capacity);
void add(hashtable* hasht);


#endif