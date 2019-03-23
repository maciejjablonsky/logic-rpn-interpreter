#include <iostream>
#include <string>
#include <cstring>
#include "stack.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

typedef enum
{
    operation, value
} token_type;

typedef enum
{
    false_val = 'f', true_val = 't'
} value_type;

typedef enum
{
    addition = '+',
    subtraction = '-',
    multiplication = '*',
    division = '/',
    negation = 'N',
    conjunction = 'K',
    alternative = 'A'

} operation_type;

void process_input(string input, stack_t *stack);

token_type type_of_token(char ch);

bool binary_operator(char ch);

operation_type type_of_operation(char ch);

data_t count(data_t *val1, data_t *val2, char ch);

int main()
{
    cout << "Enter number of lines:" << endl;
    long long n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        string input;
        cin >> input;
        stack_t stack;
        create_stack(&stack);
        process_input(input, &stack);
        destroy_stack(&stack);
    }
    return 0;
}

void process_input(string input, stack_t *stack)
{
    for (int i = 0; i < input.length(); ++i)
    {
        switch (type_of_token(input[i]))
        {
            case operation:
            {
                data_t *val1 = nullptr, *val2 = nullptr;
                bool second_operand = false;

                pop_from_stack(&val1, stack);
                if (binary_operator(input[i]) && how_many_elements_on_stack(stack) > 0)
                {
                    pop_from_stack(&val2, stack);
                    second_operand = true;
                }
                else { val2 = val1; }

                data_t result = count(val1, val2, input[i]);
                push_on_stack(&result, stack);

                delete_returned_data(val1);
                if (second_operand) { delete_returned_data(val2); }
            }

                break;

            case value:
            {
                data_t val;
                switch (input[i])
                {
                    case false_val:val = false;
                        break;
                    case true_val:val = true;
                        break;
                }
                push_on_stack(&val, stack);
            }
                break;

            default:break;
        }
    }
    data_t *result;
    pop_from_stack(&result, stack);
    cout << (bool)*result << endl;
    delete_returned_data(result);
}


token_type type_of_token(char ch)
{
    if (strchr("tf", ch) != nullptr) { return value; }
    return operation;
}

bool binary_operator(char ch)
{
    switch (type_of_operation(ch))
    {
        case addition:
        case subtraction:
        case multiplication:
        case division:
        case conjunction:
        case alternative:return true;
    }
    return false;
}

operation_type type_of_operation(char ch)
{
    return (operation_type) ch;
}

data_t count(data_t *val1, data_t *val2, char ch)
{
    switch (type_of_operation(ch))
    {
        case addition:return *val1 + *val2;
        case subtraction:return *val1 - *val2;
        case multiplication:return *val1 * *val2;
        case division:return *val1 / *val2;
        case negation:return !*val1;
        case conjunction:return *val1 && *val2;
        case alternative:return *val1 || *val2;
        default:break;
    }
    return false;
}
