#include "calculator.h"

void Calculator::Set(Number n) {
    number_ = n;
}

Number Calculator::GetNumber() const {
    return number_;
}

void Calculator::Add(Number n) {
    number_ += n;
}

void Calculator::Sub(Number n) {
    number_ -= n;
}

void Calculator::Div(Number n) {
    if (n != 0.0) {
        number_ = number_ / n;
    }
}

void Calculator::Mul(Number n) {
    number_ *= n;
}

void Calculator::Pow(Number n) {
    number_ = std::pow(number_, n);
}

void Calculator::Save() {
    memory_ = number_;
    has_memory_ = true;
}

void Calculator::Load() {
    number_ = memory_;
}

bool Calculator::HasMem() const {
    return has_memory_;
}

std::string Calculator::GetNumberRepr() const {
    return std::to_string(number_);
}

void Calculator::ClearMemory() {
    has_memory_ = false;
}
