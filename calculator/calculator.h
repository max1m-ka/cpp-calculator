#pragma once

#include <string>
#include <optional>
#include <cmath>
#include <type_traits>
#include "rational.h"
#include "pow.h"

using Error = std::string;

template<class Number>
Number Pow(Number lhs, Number rhs) {
    if constexpr (std::is_floating_point_v<Number>) {
        return std::pow(lhs, rhs);
    } else if constexpr (std::is_same_v<Number, Rational>) {
        return ::Pow(lhs, rhs);
    } else {
        return IntegerPow(lhs, rhs);
    }
}

template<class Number>
class Calculator {
public:
    Calculator() = default;

    void Set(Number n) {
        current_ = n;
    }

    Number GetNumber() const {
        return current_;
    }

    void Save() {
        mem_ = current_;
    }

    void Load() {
        if (mem_.has_value()) {
            current_ = mem_.value();
        }
    }

    bool GetHasMem() const {
        return mem_.has_value();
    }

    std::optional<Error> Add(Number n) {
        current_ += n;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number n) {
        current_ -= n;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number n) {
        current_ *= n;
        return std::nullopt;
    }

    std::optional<Error> Div(Number n) {
        if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
            if (n == Number{0}) {
                return "Division by zero";
            }
        }
        current_ /= n;
        return std::nullopt;
    }

    std::optional<Error> Pow(Number n) {
        if (current_ == Number{0} && n == Number{0}) {
            return "Zero power to zero";
        }
        
        if constexpr (std::is_integral_v<Number>) {
            if (n < Number{0}) {
                return "Integer negative power";
            }
        }
        
        if constexpr (std::is_same_v<Number, Rational>) {
            if (n.GetDenominator() != 1) {
                return "Fractional power is not supported";
            }
        }
        
        current_ = ::Pow(current_, n);
        return std::nullopt;
    }

private:
    Number current_{};
    std::optional<Number> mem_{};
};
