#pragma once

#include <iostream>
#include <numeric>
#include <cstdlib>
#include <cstdint>
#include <compare>

class Rational {
public:
    Rational() : numerator_(0), denominator_(1) {}
    
    Rational(int numerator) : numerator_(numerator), denominator_(1) {}
    
    Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        Reduction();
    }
    
    Rational(const Rational& other) = default;
    
    Rational& operator=(const Rational& other) = default;
    
    int GetNumerator() const {
        return numerator_;
    }
    
    int GetDenominator() const {
        return denominator_;
    }
    
    Rational Inv() const {
        return Rational(denominator_, numerator_);
    }
    
    Rational& operator+=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_ + denominator_ * other.numerator_;
        denominator_ = denominator_ * other.denominator_;
        Reduction();
        return *this;
    }
    
    Rational& operator-=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_ - denominator_ * other.numerator_;
        denominator_ = denominator_ * other.denominator_;
        Reduction();
        return *this;
    }
    
    Rational& operator*=(const Rational& other) {
        numerator_ = numerator_ * other.numerator_;
        denominator_ = denominator_ * other.denominator_;
        Reduction();
        return *this;
    }
    
    Rational& operator/=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_;
        denominator_ = denominator_ * other.numerator_;
        Reduction();
        return *this;
    }
    
    Rational operator+() const {
        return *this;
    }
    
    Rational operator-() const {
        return Rational(-numerator_, denominator_);
    }
    
    Rational operator+(const Rational& other) const {
        Rational result(*this);
        result += other;
        return result;
    }
    
    Rational operator-(const Rational& other) const {
        Rational result(*this);
        result -= other;
        return result;
    }
    
    Rational operator*(const Rational& other) const {
        Rational result(*this);
        result *= other;
        return result;
    }
    
    Rational operator/(const Rational& other) const {
        Rational result(*this);
        result /= other;
        return result;
    }
    
    auto operator<=>(const Rational& other) const {
        int64_t lhs = static_cast<int64_t>(numerator_) * other.denominator_;
        int64_t rhs = static_cast<int64_t>(other.numerator_) * denominator_;
        return lhs <=> rhs;
    }
    
    bool operator==(const Rational& other) const = default;
    
    friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
        if (r.denominator_ == 1) {
            os << r.numerator_;
        } else {
            os << r.numerator_ << " / " << r.denominator_;
        }
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Rational& r) {
        int numerator, denominator = 1;
        char slash = ' ';
        
        is >> numerator;
        if (!is) {
            return is;
        }
        
        if (is.peek() == ' ') {
            is >> std::ws;
        }
        
        if (is.peek() == '/') {
            is >> slash;
            if (slash != '/') {
                is.setstate(std::ios::failbit);
                return is;
            }
            is >> denominator;
            if (denominator == 0) {
                is.setstate(std::ios::failbit);
                return is;
            }
        }
        
        r = Rational(numerator, denominator);
        return is;
    }
    
private:
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }
    
private:
    int numerator_ = 0;
    int denominator_ = 1;
};
