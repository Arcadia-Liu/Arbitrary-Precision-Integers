#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

class bigint
{
    public:
        bigint();
        bigint(int64_t input_num);
        bigint(std::string &input_digits);
        bigint operator+(const bigint &rhs) const;
        bigint &operator+=(const bigint &rhs);
        bigint operator-(const bigint &rhs) const;
        bigint &operator-=(const bigint &rhs);
        bigint operator*(const bigint &rhs) const;
        bigint &operator*=(const bigint &rhs);
        bigint operator-() const;
        bool operator==(const bigint &rhs) const;
        bool operator!=(const bigint &rhs) const;
        bool operator<(const bigint &rhs) const;
        bool operator>(const bigint &rhs) const;
        bool operator<=(const bigint &rhs) const;
        bool operator>=(const bigint &rhs) const;
        friend std::ostream &operator<<(std::ostream &os, const bigint &rhs);
        bigint &operator++();
        bigint operator++(int);
        bigint &operator--();
        bigint operator--(int);

    private:
        std::vector<int64_t> value;
        bool is_negative;
};

bigint::bigint(){
    value = {0};
    is_negative = false;
}

bigint::bigint(int64_t input_num){
    if (input_num < 0){
        is_negative = true;
    }
    else{
        is_negative = false;
    }

    if (is_negative == true) input_num = -input_num;
    
    do
    {
        value.push_back(input_num % 10);
        input_num = input_num / 10;
    } while (input_num != 0);
}

bigint::bigint(std::string &input_digits){
    if (input_digits.empty()) {
        throw std::invalid_argument("Please input a string of digits");
    }

    is_negative = false;
    bool is_symbol = false;
    if (input_digits[0] == '-'){
        is_negative = true;
        is_symbol = true;
    }
    else if (input_digits[0] == '+'){
        is_symbol = true;
    }
    
    if (is_symbol){
        if (input_digits.size() == 1){
            is_negative = false;
            value = {0};
        }
        else{
            for (char c : input_digits.substr(1)) {
                if (!std::isdigit(static_cast<unsigned char>(c))) {
                    throw std::invalid_argument("Please make sure there are no illegal characters in your string.");
                }
            }
            
            for (size_t i = input_digits.size(); i > 1; --i){
                value.push_back(input_digits[i - 1] - '0');
            }
        }
    }
    else{
        for (char c : input_digits) {
                if (!std::isdigit(static_cast<unsigned char>(c))) {
                    throw std::invalid_argument("Please make sure there are no illegal characters in your string.");
                }
            }
        
        for (size_t i = input_digits.size(); i > 0; --i){
                value.push_back(input_digits[i - 1] - '0');
        }
    }
    while (value.size() > 1 && value.back() == 0) {
        value.pop_back();
    }
}

bigint bigint::operator+(const bigint &rhs) const{
    bigint sum;
    if (is_negative == rhs.is_negative){
        sum.is_negative = is_negative;
        size_t max_length = std::max(value.size(), rhs.value.size());
        sum.value.resize(max_length);
        int64_t carry = 0;
        for (size_t i = 0; i < max_length; ++i){
            int64_t digit_l = (i < value.size()) ? value[i] : 0;
            int64_t digit_r = (i < rhs.value.size()) ? rhs.value[i] : 0;
            int64_t digit_sum = digit_l + digit_r + carry;
            sum.value[i] = digit_sum % 10;
            carry = digit_sum / 10;
        }
        if (carry > 0) {
            sum.value.push_back(carry);
        }
    }
    else{
        if (is_negative == true){
            sum = rhs - (-(*this));
        }
        else {
            sum = *this - (-rhs);
        }
    }
    return sum;
}

bigint &bigint::operator+=(const bigint &rhs)
{
    *this = *this + rhs;
    return *this;
}

bigint bigint::operator-(const bigint &rhs) const {
    bigint subtract;
    if (is_negative == rhs.is_negative) {
        if (*this == rhs){
            subtract.is_negative = false;
            subtract.value = {0};
        }
        else {
            const bigint &larger_num = (*this < rhs) ? rhs : *this;
            const bigint &smaller_num = (*this > rhs) ? rhs : *this;
            if (!is_negative){
                subtract.is_negative = (*this < rhs) ? !is_negative : is_negative;
                size_t max_length = larger_num.value.size();
                subtract.value.resize(max_length);
                int64_t borrow = 0;
                for (size_t i = 0; i < max_length; ++i) {
                    int64_t digit_l = larger_num.value[i];
                    int64_t digit_r = (i < smaller_num.value.size()) ? smaller_num.value[i] : 0;
                    int64_t sub_digit = digit_l - digit_r - borrow;
                    if (sub_digit < 0){
                        borrow = 1;
                        sub_digit += 10;
                    }
                    else {
                        borrow = 0;
                    }
                    subtract.value[i] = sub_digit;
                }
            }
            else {
                subtract.is_negative = (*this < rhs) ? is_negative : !is_negative;
                size_t max_length = smaller_num.value.size();
                subtract.value.resize(max_length);
                int64_t borrow = 0;
                for (size_t i = 0; i < max_length; ++i) {
                    int64_t digit_l = smaller_num.value[i];
                    int64_t digit_r = (i < larger_num.value.size()) ? larger_num.value[i] : 0;
                    int64_t sub_digit = digit_l - digit_r - borrow;
                    if (sub_digit < 0){
                        borrow = 1;
                        sub_digit += 10;
                    }
                    else {
                        borrow = 0;
                    }
                    subtract.value[i] = sub_digit;
                }
            }
            while (subtract.value.size() > 1 && subtract.value.back() == 0) {
                subtract.value.pop_back();
            }
        }
    }
    else {
        subtract = *this + (-rhs);
    }
    return subtract;
}

bigint &bigint::operator-=(const bigint &rhs)
{
    *this = *this - rhs;
    return *this;
}

bigint bigint::operator*(const bigint &rhs) const {
    bigint product;
    product.is_negative = (is_negative == rhs.is_negative) ? false : true;
    product.value.resize(value.size() + rhs.value.size());
    for (size_t i = 0; i < value.size(); ++i) {
        int64_t carry = 0;
        for (size_t j = 0; j < rhs.value.size(); ++j)
        {
            int64_t product_digit = product.value[i + j] + value[i] * rhs.value[j] + carry;
            product.value[i + j] = product_digit % 10;
            carry = product_digit / 10;
        }
        product.value[rhs.value.size() + i] += carry;
    }
    while (product.value.size() > 1 && product.value.back() == 0) {
        product.value.pop_back();
    }

    return product;
}

bigint &bigint::operator*=(const bigint &rhs) {
    *this = *this * rhs;
    return *this;
}

bigint bigint::operator-() const{
    bigint reversed;
    reversed.value = value;
    reversed.is_negative = is_negative;
    if ((reversed.value.size() != 1) || (reversed.value[0] != 0)) {
        reversed.is_negative = !reversed.is_negative;
    }
    return reversed;
}

bool bigint::operator==(const bigint &rhs) const {
    if (is_negative != rhs.is_negative) {
        return false;
    }
    if (value.size() != rhs.value.size()) {
        return false;
    }
    for (size_t i = value.size(); i > 0; --i) {
        if (value[i - 1] != rhs.value[i - 1]) {
            return false;
        }
    }
    return true;
}

bool bigint::operator!=(const bigint &rhs) const {
    if (*this == rhs) {
        return false;
    }
    return true;
}

bool bigint::operator<(const bigint &rhs) const {
    if (is_negative != rhs.is_negative) {
        return is_negative;
    }
    if (value.size() != rhs.value.size()) {
        if (is_negative) {
            return value.size() > rhs.value.size();
        }
        else {
            return value.size() < rhs.value.size();
        }
    }
    for (size_t i = value.size(); i > 0; --i) {
        if (value[i - 1] != rhs.value[i - 1]) {
            if (is_negative) {
                return value[i - 1] > rhs.value[i - 1];
            }
            else {
                return value[i - 1] < rhs.value[i - 1];
            }
        }
    }
    return false;
}

bool bigint::operator>(const bigint &rhs) const {
    if ((*this == rhs) || (*this < rhs)) {
        return false;
    }
    return true;
}

bool bigint::operator<=(const bigint &rhs) const {
    if ((*this == rhs) || (*this < rhs)) {
        return true;
    }
    return false;
}

bool bigint::operator>=(const bigint &rhs) const {
    if (!(*this < rhs)) {
        return true;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, const bigint &rhs) {
    if (rhs.is_negative) {
        os << '-';
    }
    for(size_t i = rhs.value.size(); i > 0; --i) {
        os << static_cast<char>(rhs.value[i - 1] + '0');
    }
    return os;
}

bigint &bigint::operator++() {
    bigint one;
    one.is_negative = false;
    one.value = {1};
    *this += one;
    return *this;
}

bigint bigint::operator++(int) {
    bigint current_num = *this;
    ++(*this);
    return current_num;
}

bigint &bigint::operator--() {
    bigint one;
    one.is_negative = true;
    one.value = {1};
    *this += one;
    return *this;
}

bigint bigint::operator--(int) {
    bigint current_num = *this;
    --(*this);
    return current_num;
}