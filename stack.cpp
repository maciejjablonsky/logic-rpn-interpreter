//
// Created by maciek on 22.03.19.
//

#include <cstdlib>
#include "stack.h"

static bool assign_new_stack(stack_t *stack);

static bool rewrite_stack(stack_t *old_stack);

static bool copy_stack(stack_t *new_stack, stack_t *old_stack);

static bool copy_stack_data(data_t *dst, const data_t *const src);

static bool delete_stack_data(data_t *data);


bool create_stack(stack_t *stack)
{
    stack->elements_on_stack = 0;
    stack->size = default_init_stack_size;
    stack->stack = nullptr;

    return (bool) assign_new_stack(stack);
}

static bool assign_new_stack(stack_t *stack)
{
    if (stack->stack != nullptr) { destroy_stack(stack); }
    stack->stack = new data_t[stack->size];

    return (bool) stack->stack;
}

bool push_on_stack(const data_t *const value, stack_t *stack)
{
    if (stack->elements_on_stack == stack->size)
    {
        rewrite_stack(stack);
    }
    if (copy_stack_data(stack->stack + stack->elements_on_stack, value))
    {
        ++stack->elements_on_stack;
        return true;
    }
    return false;
}

static bool rewrite_stack(stack_t *old_stack)
{
    stack_t new_stack;

    if (create_stack(&new_stack))
    {
        new_stack.size = 2 * old_stack->size;
        copy_stack(&new_stack, old_stack);
    }
    destroy_stack(old_stack);
    *old_stack = new_stack;
    return true;
}

static bool copy_stack(stack_t *new_stack, stack_t *old_stack)
{
    for (int i = 0; i < old_stack->size; ++i)
    {
        push_on_stack(&old_stack->stack[i], new_stack);
    }
    return new_stack->elements_on_stack == old_stack->elements_on_stack;
}

static bool copy_stack_data(data_t *dst, const data_t *const src)
{
    *dst = *src;
    return true;
}

bool pop_from_stack(data_t **data, stack_t *stack)
{
    if (*data) { delete_returned_data(*data); }

    *data = new data_t;
    if (*data)
    {
        copy_stack_data(*data, &stack->stack[stack->elements_on_stack - 1]);
        if (delete_stack_data(&stack->stack[stack->elements_on_stack - 1]))
        {
            --stack->elements_on_stack;
            return true;
        }
    }
    return false;
}

static bool delete_stack_data(data_t *data)
{
    *data = 0;
    return true;
}

bool delete_returned_data(data_t *data)
{
    delete data;
}

void destroy_stack(stack_t *stack)
{
    if (stack->stack != nullptr) { delete stack->stack; }
    stack->stack = nullptr;
}

stack_size_t how_many_elements_on_stack(stack_t *stack)
{
    return stack->elements_on_stack;
}