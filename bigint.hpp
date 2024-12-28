#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

/**
 *
 * @class bigint
 *
 * @brief The bigint class is a custom implementation for handling arbitrary-precision integers in C++.
 *        It supports most standard arithmetic operations (+, -, *, etc.), relational operators, and output functionality.
 *        The class is designed to work seamlessly with both positive and negative integers.
 *
 */

class bigint
{
public:
    bigint();
    bigint(int64_t input_num);
    bigint(const std::string &input_digits);
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
    /**
     *
     * @brief `value` is a vector type of data used to store each digit of an arbitrary-precision integer.
     *        Each element in `value` represents a numeric digit, stored in order from lowest to highest digit.
     *
     *        For example, the number 12345 will be stored as value = {5, 4, 3, 2, 1}.
     *
     */
    std::vector<int64_t> value;

    /**
     *
     * @brief `is_negative` is a bool type of data used to store the positivity or negativity of an arbitrary-precision integer.
     *        If this bigint integer is positive, `is_negative` will be `false`;
     *        otherwise, if this bigint integer is negative, `is_negative` will be `true`.
     *
     *        If this bigint integer is `0`, we specify the `is_negative` as `false`.
     *
     */
    bool is_negative;
};

/**
 *
 * @brief A default constructor, creating the integer 0.
 *        This default constructor is used to initialize a bigint object with a value of 0.
 *        In math, 0 is considered a neutral number, it is neither positive nor negative.
 *        For bigint, when the value is 0, is_negative will be false.
 *
 */
bigint::bigint()
{
    value = {0};
    is_negative = false;
}

/**
 *
 * @brief A constructor that takes a signed 64-bit integer and converts it to an arbitrary-precision integer.
 *        This constructor is used to initialize a bigint object with an int64_t type of data.
 *
 * @param input_num The signed 64-bit integer to initialize the `bigint` object.
 *
 */
bigint::bigint(int64_t input_num)
{
    if (input_num < 0)
    {
        is_negative = true;
    }
    else
    {
        is_negative = false;
    }

    if (is_negative == true)
        input_num = -input_num;

    do
    {
        value.push_back(input_num % 10);
        input_num = input_num / 10;
    } while (input_num != 0);
}

/**
 *
 * @brief A constructor that takes a string of digits and converts it to an arbitrary-precision integer.
 *        This constructor is used to convert a string representing an integer into a bigint object.
 *
 * @param input_digits A string representing the number.
 *
 * @throws std::invalid_argument If the string is empty, or contains non-digit characters.
 *
 */
bigint::bigint(const std::string &input_digits)
{
    if (input_digits.empty())
    {
        throw std::invalid_argument("Please input a string of digits");
    }

    is_negative = false;
    bool is_symbol = false;
    if (input_digits[0] == '-')
    {
        is_negative = true;
        is_symbol = true;
    }
    else if (input_digits[0] == '+')
    {
        is_symbol = true;
    }

    if (is_symbol)
    {
        if (input_digits.size() == 1)
        {
            is_negative = false;
            value = {0};
        }
        else
        {
            for (char c : input_digits.substr(1))
            {
                if (!std::isdigit(static_cast<unsigned char>(c)))
                {
                    throw std::invalid_argument("Please make sure there are no illegal characters in your string.");
                }
            }

            for (size_t i = input_digits.size(); i > 1; --i)
            {
                value.push_back(input_digits[i - 1] - '0');
            }
        }
    }
    else
    {
        for (char c : input_digits)
        {
            if (!std::isdigit(static_cast<unsigned char>(c)))
            {
                throw std::invalid_argument("Please make sure there are no illegal characters in your string.");
            }
        }

        for (size_t i = input_digits.size(); i > 0; --i)
        {
            value.push_back(input_digits[i - 1] - '0');
        }
    }
    while (value.size() > 1 && value.back() == 0)
    {
        value.pop_back();
    }
}

/**
 *
 * @brief This method implements the addition operation of two bigint objects.
 *
 * @param rhs The right-hand side `bigint` object.
 *
 * @return A new `bigint` representing the result of adding.
 *
 */
bigint bigint::operator+(const bigint &rhs) const
{
    bigint sum;
    if (is_negative == rhs.is_negative)
    {
        sum.is_negative = is_negative;
        size_t max_length = std::max(value.size(), rhs.value.size());
        sum.value.resize(max_length);
        int64_t carry = 0;
        for (size_t i = 0; i < max_length; ++i)
        {
            int64_t digit_l = (i < value.size()) ? value[i] : 0;
            int64_t digit_r = (i < rhs.value.size()) ? rhs.value[i] : 0;
            int64_t digit_sum = digit_l + digit_r + carry;
            sum.value[i] = digit_sum % 10;
            carry = digit_sum / 10;
        }
        if (carry > 0)
        {
            sum.value.push_back(carry);
        }
    }
    else
    {
        if (is_negative == true)
        {
            sum = rhs - (-(*this));
        }
        else
        {
            sum = *this - (-rhs);
        }
    }
    return sum;
}

/**
 *
 * @brief This method implements the += operator for the bigint class,
 *        enabling the addition of another bigint object to the current object
 *        and directly updating the current object with the result.
 *
 * @param rhs The right-hand side `bigint` object.
 *
 * @return The left-hand side `bigint` object's reference after the addition.
 *
 */
bigint &bigint::operator+=(const bigint &rhs)
{
    *this = *this + rhs;
    return *this;
}

/**
 *
 * @brief This method implements the subtraction operation for two bigint objects.
 *
 * @param rhs The right-hand side `bigint` object.
 *
 * @return A new `bigint` representing the result of subtracting.
 *
 */
bigint bigint::operator-(const bigint &rhs) const
{
    bigint subtract;
    if (is_negative == rhs.is_negative)
    {
        if (*this == rhs)
        {
            subtract.is_negative = false;
            subtract.value = {0};
        }
        else
        {
            const bigint &larger_num = (*this < rhs) ? rhs : *this;
            const bigint &smaller_num = (*this > rhs) ? rhs : *this;
            if (!is_negative)
            {
                subtract.is_negative = (*this < rhs) ? !is_negative : is_negative;
                size_t max_length = larger_num.value.size();
                subtract.value.resize(max_length);
                int64_t borrow = 0;
                for (size_t i = 0; i < max_length; ++i)
                {
                    int64_t digit_l = larger_num.value[i];
                    int64_t digit_r = (i < smaller_num.value.size()) ? smaller_num.value[i] : 0;
                    int64_t sub_digit = digit_l - digit_r - borrow;
                    if (sub_digit < 0)
                    {
                        borrow = 1;
                        sub_digit += 10;
                    }
                    else
                    {
                        borrow = 0;
                    }
                    subtract.value[i] = sub_digit;
                }
            }
            else
            {
                subtract.is_negative = (*this < rhs) ? is_negative : !is_negative;
                size_t max_length = smaller_num.value.size();
                subtract.value.resize(max_length);
                int64_t borrow = 0;
                for (size_t i = 0; i < max_length; ++i)
                {
                    int64_t digit_l = smaller_num.value[i];
                    int64_t digit_r = (i < larger_num.value.size()) ? larger_num.value[i] : 0;
                    int64_t sub_digit = digit_l - digit_r - borrow;
                    if (sub_digit < 0)
                    {
                        borrow = 1;
                        sub_digit += 10;
                    }
                    else
                    {
                        borrow = 0;
                    }
                    subtract.value[i] = sub_digit;
                }
            }
            while (subtract.value.size() > 1 && subtract.value.back() == 0)
            {
                subtract.value.pop_back();
            }
        }
    }
    else
    {
        subtract = *this + (-rhs);
    }
    return subtract;
}

/**
 *
 * @brief This method implements the -= operator for the bigint class,
 *        enabling the subtraction of another bigint object to the current object
 *        and directly updating the current object with the result.
 *
 * @param rhs The right-hand side `bigint` object.
 *
 * @return The left-hand side `bigint` object's reference after the subtraction.
 *
 */
bigint &bigint::operator-=(const bigint &rhs)
{
    *this = *this - rhs;
    return *this;
}

/**
 *
 * @brief This method implements the multiplication operation for two bigint objects.
 *
 * @param rhs The right-hand side `bigint` object.
 *
 * @return A new `bigint` representing the result of multiplication.
 *
 */
bigint bigint::operator*(const bigint &rhs) const
{
    bigint product;
    product.is_negative = (is_negative == rhs.is_negative) ? false : true;
    product.value.resize(value.size() + rhs.value.size());
    for (size_t i = 0; i < value.size(); ++i)
    {
        int64_t carry = 0;
        for (size_t j = 0; j < rhs.value.size(); ++j)
        {
            int64_t product_digit = product.value[i + j] + value[i] * rhs.value[j] + carry;
            product.value[i + j] = product_digit % 10;
            carry = product_digit / 10;
        }
        product.value[rhs.value.size() + i] += carry;
    }
    while (product.value.size() > 1 && product.value.back() == 0)
    {
        product.value.pop_back();
    }

    return product;
}

/**
 *
 * @brief This method implements the *= operator for the bigint class,
 *        enabling the multiplication of two bigint objects and returning the resulting product.
 *
 * @param rhs The right-hand side `bigint` object.
 *
 * @return The left-hand side `bigint` object's reference after the multiplication.
 *
 */
bigint &bigint::operator*=(const bigint &rhs)
{
    *this = *this * rhs;
    return *this;
}

/**
 *
 * @brief This method implements the unary minus operator for the bigint class.
 *
 * @return a new bigint object that have the opposite sign of the current bigint object.
 *
 */
bigint bigint::operator-() const
{
    bigint negated;
    negated.value = value;
    negated.is_negative = is_negative;
    if ((negated.value.size() != 1) || (negated.value[0] != 0))
    {
        negated.is_negative = !negated.is_negative;
    }
    return negated;
}

/**
 *
 * @brief Compares two `bigint` objects for equality.
 *        The equality method implements the `==` operator for the bigint class,
 *        which compares two bigint objects and returns true if they are equal and false otherwise.
 *
 * @param rhs The right-hand side `bigint` object.
 *
 * @return `true` if `bigint` objects are equal, otherwise `false`.
 *
 */
bool bigint::operator==(const bigint &rhs) const
{
    if (is_negative != rhs.is_negative)
    {
        return false;
    }
    if (value.size() != rhs.value.size())
    {
        return false;
    }
    for (size_t i = value.size(); i > 0; --i)
    {
        if (value[i - 1] != rhs.value[i - 1])
        {
            return false;
        }
    }
    return true;
}

/**
 *
 * @brief Compares two `bigint` objects for inequality.
 *        The inequality method implements the `!=` operator for the bigint class,
 *        which compares two bigint objects and returns false if they are equal and true otherwise.
 *
 * @param rhs The right-hand side `bigint` object.
 *
 * @return `false` if `bigint` objects are equal, otherwise `true`.
 *
 */
bool bigint::operator!=(const bigint &rhs) const
{
    if (*this == rhs)
    {
        return false;
    }
    return true;
}

/**
 *
 * @brief The less than operation method implements the < operator for the bigint class,
 *        which checks whether one bigint is smaller than another.
 *
 * @param rhs The right-hand side `bigint` object.
 *
 * @return  If the left-hand side number is less than the right-side number, then it will return `true`.
 *          If they are equal or the left-hand side number is greater than the right-side number, then it will return `false`
 *
 */
bool bigint::operator<(const bigint &rhs) const
{
    if (is_negative != rhs.is_negative)
    {
        return is_negative;
    }
    if (value.size() != rhs.value.size())
    {
        if (is_negative)
        {
            return value.size() > rhs.value.size();
        }
        else
        {
            return value.size() < rhs.value.size();
        }
    }
    for (size_t i = value.size(); i > 0; --i)
    {
        if (value[i - 1] != rhs.value[i - 1])
        {
            if (is_negative)
            {
                return value[i - 1] > rhs.value[i - 1];
            }
            else
            {
                return value[i - 1] < rhs.value[i - 1];
            }
        }
    }
    return false;
}

/**
 *
 * @brief The greater than operation method implements the > operator for the bigint class,
 *        which checks whether one bigint is greater than another.
 *
 * @param rhs The right-hand side `bigint` object.
 *
 * @return  If the left-hand side number is greater than the right-side number, then it will return `true`.
 *          If they are equal or the left-hand side number is less than the right-side number, then it will return `false`
 *
 */
bool bigint::operator>(const bigint &rhs) const
{
    if ((*this == rhs) || (*this < rhs))
    {
        return false;
    }
    return true;
}

/**
 *
 * @brief The less than or equal to operation method implements the <= operator for the bigint class,
 *        which checks whether one bigint is less than or equal to another.
 *
 * @param rhs The right-hand side `bigint` object.
 *
 * @return  If the left-hand side number is less than or equal to the right-side number, then it will return `true`.
 *          If the left-hand side number is greater than the right-side number, then it will return `false`
 *
 */
bool bigint::operator<=(const bigint &rhs) const
{
    if ((*this == rhs) || (*this < rhs))
    {
        return true;
    }
    return false;
}

/**
 *
 * @brief The greater than or equal to operation method implements the >= operator for the bigint class,
 *        which checks whether one bigint is greater than or equal to another.
 *
 * @param rhs The right-hand side `bigint` object.
 *
 * @return  If the left-hand side number is greater than or equal to the right-side number, then it will return `true`.
 *          If the left-hand side number is less than the right-side number, then it will return `false`
 *
 */
bool bigint::operator>=(const bigint &rhs) const
{
    if (!(*this < rhs))
    {
        return true;
    }
    return false;
}

/**
 *
 * @brief The output stream insertion operator << is used to output the bigint object to an output stream.
 *
 * @param os The output stream.
 * @param rhs The right-hand side `bigint` object which should be output.
 *
 * @return A reference to the output stream.
 *
 */
std::ostream &operator<<(std::ostream &os, const bigint &rhs)
{
    if (rhs.is_negative)
    {
        os << '-';
    }
    for (size_t i = rhs.value.size(); i > 0; --i)
    {
        os << static_cast<char>(rhs.value[i - 1] + '0');
    }
    return os;
}

/**
 *
 * @brief The prefix increment operator `++` is used to increment the `bigint` object by 1.
 *
 * @return A reference to the `bigint` after incrementing.
 *
 */
bigint &bigint::operator++()
{
    bigint one;
    one.is_negative = false;
    one.value = {1};
    *this += one;
    return *this;
}

/**
 *
 * @brief The postfix increment operator `++` is used to increment the `bigint` object by 1.
 *
 * @return A reference to the `bigint` before incrementing.
 *
 */
bigint bigint::operator++(int)
{
    bigint current_num = *this;
    ++(*this);
    return current_num;
}

/**
 *
 * @brief The prefix decrement operator `--` is used to decrement the `bigint` object by 1.
 *
 * @return A reference to the `bigint` after decrementing.
 *
 */
bigint &bigint::operator--()
{
    bigint one;
    one.is_negative = true;
    one.value = {1};
    *this += one;
    return *this;
}

/**
 *
 * @brief The postfix decrement operator `--` is used to decrement the `bigint` object by 1.
 *
 * @return A reference to the `bigint` before decrementing.
 *
 */
bigint bigint::operator--(int)
{
    bigint current_num = *this;
    --(*this);
    return current_num;
}