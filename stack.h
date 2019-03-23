//
// Created by maciek on 22.03.19.
//

#ifndef LOGIC_STACK_H
#define LOGIC_STACK_H

constexpr unsigned int default_init_stack_size = 2;
typedef unsigned int stack_size_t;

typedef bool data_t;

typedef struct stack_t
{
    data_t *stack;
    stack_size_t size;
    stack_size_t elements_on_stack;
} stack_t;

bool create_stack(stack_t *stack);

void destroy_stack(stack_t *stack);

bool push_on_stack(const data_t * const value, stack_t * stack);

bool pop_from_stack(data_t ** data, stack_t *stack);

bool delete_returned_data(data_t * data); // must be used on data returned by pop_from_stack()

stack_size_t how_many_elements_on_stack(stack_t * stack);

#endif //LOGIC_STACK_H
