#include "calculator.h"

using namespace std;

bool ReadNumber(Number& result) {
    if (cin >> result) {
        return true;
    }
    return false;
}

bool RunCalculatorCycle() {
    Number num;
    Number memory;

    if (!(cin >> num)) {
        cerr << "Error: Numeric operand expected " << endl;
        return 0;
    }

    string commond;
    bool memory_initialized = false;

    while (true) {
        if (!(cin >> commond)) {
        break;
        }
        if (commond == "+") {
            Number operand;
            if (!(cin >> operand)) {
                cerr << "Error: Numeric operand expected" << endl;
                break;
            }
            num += operand;
        }
        else if (commond == "-") {
            Number operand;
            if (!(cin >> operand)) {
                cerr << "Error: Numeric operand expected" << endl;
                break;
            }
            num -= operand;
        }
        else if (commond == "/") {
            Number operand;
            if (!(cin >> operand)) {
                cerr << "Error: Numeric operand expected" << endl;
                break;
            }
            num /= operand;
        }
        else if (commond == "*") {
            Number operand;
            if (!(cin >> operand)) {
                cerr << "Error: Numeric operand expected" << endl;
                break;
            }
            num *= operand;
        }
        else if (commond == "**") {
            Number operand;
            if (!(cin >> operand)) {
                cerr << "Error: Numeric operand expected" << endl;
                break;
            }
            num = pow(num,operand);
        }
        else if (commond == "=") {
            cout << num << endl;
        }
        else if (commond == "q") {
            break;
        }
        else if (commond == "c") {
            num = 0;
        }
        else if (commond == ":") {
            Number operand;
            if (!(cin >> operand)) {
                cerr << "Error: Numeric operand expected" << endl;
            }
            num = operand;
        }
        else if (commond == "s" || commond == "l") {
            if (commond == "s"){
            memory = num;
            memory_initialized = true;
           }
            else {
                if (!(memory_initialized)) {
                    cerr << "Error: Memory is empty" << endl;
                }
                else {
                    num = memory;
                }
            }
        }
        else {
            cerr << "Error: Unknown token " << commond << endl;
            break;
        }
    }
    return 0;
}
