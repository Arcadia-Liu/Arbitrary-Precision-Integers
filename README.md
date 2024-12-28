# `bigint` Class Documentation

## Overview
The `bigint` class is a custom implementation for handling arbitrary-precision integers in C++. It supports most standard arithmetic operations, relational operators, and output functionality. The class is designed to work seamlessly with both positive and negative integers.

## object structure

The storage structure of a bigint object consists of two member variables: `value` and `is_negative`.

```cpp
std::vector<int64_t> value;
bool is_negative;
```

`value` is a vector type of data used to store each digit of an arbitrary-precision integer. Each element in `value` represents a numeric digit, stored in order from lowest to highest digit. For example, the number 12345 will be stored as value = {5, 4, 3, 2, 1}.

`is_negative` is a bool type of data used to store the positivity or negativity of an arbitrary-precision integer. If this bigint integer is positive, `is_negative` will be false; otherwise, if this bigint integer is negative, `is_negative` will be true.

---

### **Constructors**
1. **A Default Constructor**
This default constructor is used to initialize a `bigint` object with a value of `0`. In math, `0` is considered a neutral number, it is neither positive nor negative. For bigint, when the value is `0`, is_negative will be false.
    ```cpp
    test = bigint();
    std::cout << test;
    // output will be 0.
    ```
2. **A constructor that takes a signed 64-bit integer and converts it to an arbitrary-precision integer**
This constructor is used to initialize a `bigint` object with an `int64_t` type of data. 
    ```cpp
    int64_t num = -562;
    test = bigint(num);
    std::cout << test;
    // test.is_negative = true;
    // test.value = {2, 6, 5};
    // The output will be -562.
    ```
3. **A constructor that takes a string of digits and converts it to an arbitrary-precision integer**
This constructor is used to convert a `string` representing an integer into a `bigint` object by first checking the string for empty and illegal characters, then determining whether the first character is a sign (+ or -) to set the sign flag. Next, we check the following parts bit-by-bit if the portion of the string after the sign or the entire string (in no sign situation) is a number. Then we store it in the `bigint.value` from the lowest to the highest digit. Finally, we remove invalid leading zeros.
    ```cpp
    std::string str1 = "+46543";
    std::string str2 = "-86564";
    std::string str3 = "gk%45#^$#!";
    test1 = bigint(str1);
    test2 = bigint(str2);
    test3 = bigint(str3);
    cout << test1 << "\n";
    cout << test2 << "\n";
    cout << test3 << "\n";
    // The output will be:
    // 46543
    // -86564
    // invalid string: Please make sure there are no illegal characters in your string.
    ```

### **Mathematical Operations**
1. **Addition Operator**

    This method implements the addition operation of two bigint objects.

    When the two additions are of the same sign, the result of the addition is the same as the positivity or negativity of either addition. The digits part are then added bit by bit. Firstly, we find the maximum length `max_length` of the two numbers and adjust the storage space for the result. Starting from the lower bit, add the digits bit by bit while handling the rounding. Then we add the digits in the current bit, add the previous carry, and store the result in the current bit while calculating the new `carry`. If the `carry` is not `0` after the process, then we can append the `carry` to the highest bit of the result.

    When the two additions have different signs, we can convert this addition operation to a subtraction operation.

    ```cpp
    std::string str1 = "+46543";
    std::string str2 = "-86564";
    test1 = bigint(str1);
    test2 = bigint(str2);
    cout << test1 + test2 << "\n";
    // The output will be: -40021
    ```

2. **Plus-Equals Operator**
    This method implements the `+=` operator for the `bigint` class, enabling the addition of another bigint object to the current object and directly updating the current object with the result.

    ```cpp
    std::string str1 = "87923";
    std::string str2 = "23548";
    test1 = bigint(str1);
    test2 = bigint(str2);
    test1 += test2;
    cout << test1 << "\n";
    // The output will be: 111471  
    ```


3. **Subtraction Operator**
    
    This method implements the subtraction operation for two bigint objects.

    When the two subtracted numbers are of the same sign, we start by comparing two numbers. If the two numbers are equal, then we directly set the result as `0`. Otherwise, the method compares the length of the two numbers to determine which is longer. The subtraction is performed by iterating over the digits of the longer number and subtracting the corresponding digits of the smaller number, starting from the lower digit. Borrowing is handled where necessary: if the subtraction of a digit results in a negative value, we add `10` to the current digit, and a `borrow = 1` is propagated to the next higher digit. The result's sign will be the same as the two subtracted numbers. After the calculation, leading zeros in the result are removed to maintain a consistent representation.

    If the two numbers are of different signs, we can convert the subtraction to an addition operation.

    ```cpp
    std::string str1 = "56486";
    std::string str2 = "86564";
    test1 = bigint(str1);
    test2 = bigint(str2);
    cout << test1 - test2 << "\n";
    // The output will be: -30078
    ```

4. **Minus-Equals Operator**
    This method implements the `-=` operator for the `bigint` class, enabling the subtraction of another `bigint` object to the current object and directly updating the current object with the result.

    ```cpp
    std::string str1 = "87923";
    std::string str2 = "23548";
    test1 = bigint(str1); 
    test2 = bigint(str2);
    test1 -= test2;
    cout << test1 << "\n";
    // The output will be: 64375 
    ```

5. **Multiply Operator**
    This method implements the `*` operator for the `bigint` class, enabling the multiplication of two `bigint` objects and returning the resulting product.

    When the two subtracted numbers are of the same sign, the result will be positive. When the two subtracted numbers are of different signs, the result will be negative.

    When calculating, each digit of the left-hand side number `value[i]` is multiplied by every digit of the right-hand side number `rhs.value[j]`, starting from the least significant digit. For every such multiplication, the partial product is added to the corresponding position in the `product.value` array, accounting for the positional offset `(i + j)`. If there is a carry generated during this step, it is propagated to the next higher position. Finally, we remove the leading zeros in the result to make sure the format is correct.


    ```cpp
    std::string str1 = "87923";
    std::string str2 = "23548";
    test1 = bigint(str1); 
    test2 = bigint(str2);
    test3 = test1 * test2;
    cout << test3 << "\n";
    // The output will be: 2,070,410,804
    ```

6. **Multiply-Equals Operator**
    This method implements the `*=` operator for the `bigint` class, enabling the multiplication of another `bigint` object to the current object and directly updating the current object with the result.

    ```cpp
    std::string str1 = "23";
    std::string str2 = "75";
    test1 = bigint(str1); 
    test2 = bigint(str2);
    test1 *= test2;
    cout << test1 << "\n";
    // The output will be: 1725
    ```

7. **Unary Minus Operator**
    This method implements the unary minus operator for the `bigint` class, which returns a new `bigint` object that have the opposite sign of the current `bigint` object.

    ```cpp
    std::string str1 = "23";
    test1 = bigint(str1); 
    cout << - (test1) << "\n";
    // The output will be: -23
    ```

### **Relational Operations**

1. **Equality and Inequality Operator**
    The equality method implements the `==` operator for the `bigint` class, which compares two `bigint` objects and returns `true` if they are equal and `false` otherwise.

    Firstly, we check if the signs of the two bigint objects are the same. If `is_negative` of the left-hand side object is different from `is_negative` of the right hand side object, the method returns `false`, indicating the objects are not equal.

    Then we check if the number of digits of the two `bigint` objects are equal. If the sizes are different, the method returns false, as objects with different numbers of digits cannot be equal.

    If the signs and sizes are both the same, the method proceeds to compare the digits of the two bigint objects. It iterates over the digits and compares each corresponding digit in both objects. If any digit differs, the method returns `false`.

    If all the above checks pass, the method returns `true`, indicating that the two bigint objects are equal.

    The inequality method is the opposite of the equality method. This method implements the `!=` operator for the bigint class, which returns `true` if two bigint objects are not equal and `false` if they are equal.

    ```cpp
    std::cout << std::boolalpha;
    std::string str1 = "23";
    std::string str2 = "100";
    std::string str3 = "23";
    test1 = bigint(str1); 
    test2 = bigint(str2); 
    test3 = bigint(str3); 
    cout << test1 == test2 << "\n";     // The output will be: false
    cout << test1 == test3 << "\n";     // The output will be: true
    cout << test1 != test2 << "\n";     // The output will be: true
    cout << test1 != test3 << "\n";     // The output will be: false
    ```

2. **Less Than Operator, Less Than and Equal to Operator**

    The less than operation method implements the `<` operator for the `bigint` class, which compares whether one `bigint` is smaller than another. If the left-hand side number is less than the right-side number, then it will return `true`. If the same or larger, then it will return `false`.

    First, we compare the `is_negative` flags of both bigint objects. If the signs are different, then we immediately returns whether the left-hand side object is negative. If `*this` is negative, it is smaller than any positive number at the right hand side.

    If the signs are the same, then we compares the sizes of the value vectors of these two `bigint` numbers. If these two numbers are positive, then the smaller vector size indicates a smaller number. If these two `bigint` numbers are negative, the result is reversed because a larger number with more digits is actually smaller in the negative number space.

    If both the size and signs match, then we compare the digits of both `bigint` objects starting from the higher digit to the lower. The digits are compared one by one, considering the sign.

    For less than and equal to operation, we check if the left-hand side bigint object satisfies the less than or equal to operation. If so, it returns true. If not satisfied, then it returns false.

    ```cpp
    std::cout << std::boolalpha;
    std::string str1 = "233";
    std::string str2 = "100";
    std::string str3 = "233";
    test1 = bigint(str1); 
    test2 = bigint(str2); 
    test3 = bigint(str3); 
    cout << (test1 < test2) << "\n";     // The output will be: false
    cout << (test2 < test1) << "\n";     // The output will be: true
    cout << (test1 < test3) << "\n";     // The output will be: false
    cout << (test1 <= test3) << "\n";    // The output will be: true
    ```

3. **Greater Than Operator, Greater Than and Equal to Operator**

    The greater than operation method implements the `>` operator for the `bigint` class, which compares whether one `bigint` is greater than another. It is the opposite of less than and equal to operation.

    For greater than and equal to operation, we check if the left-hand side bigint object satisfies the greater than or equal to operation. If so, it returns true. If not satisfied, then it returns false.

     ```cpp
    std::cout << std::boolalpha;
    std::string str1 = "233";
    std::string str2 = "100";
    std::string str3 = "233";
    test1 = bigint(str1); 
    test2 = bigint(str2); 
    test3 = bigint(str3); 
    cout << (test1 > test2) << "\n";     // The output will be: true
    cout << (test2 > test1) << "\n";     // The output will be: false
    cout << (test1 > test3) << "\n";     // The output will be: false
    cout << (test1 >= test3) << "\n";    // The output will be: true
    ```

### **Increment and Decrement Operator**
1. Prefix Increment Operator

    The prefix increment operator `++` is used to increment the `bigint` object by 1. We implement this by creating a bigint number, with is_negative = false and value = {1}. We add the created bigint object to the original one, and then return the updated bigint.
    
    ```cpp
    std::string str1 = "233";
    test1 = bigint(str1); 
    test2 = ++test1;
    cout << test1 << "\n";     // The output will be: 234
    cout << test2 << "\n";     // The output will be: 234
    ```

2. Postfix Increment Operator

    The postfix increment operator `++` is used to increment the `bigint` object by 1, but it returns the object before the increment. We implement this by first storing the original bigint object. Then we use the prefix increment operator to add 1 to the original bigint object, but then returns the bigint before updating.
    
    ```cpp
    std::string str1 = "233";
    test1 = bigint(str1); 
    test2 = test1++;
    cout << test1 << "\n";     // The output will be: 234
    cout << test2 << "\n";     // The output will be: 233
    ```

3. Prefix Decrement Operator

    The prefix decrement operator `--` is used to decrease the `bigint` object by 1. We implement this by creating a bigint number, with is_negative = true and value = {1}. We add the created bigint object to the original one, and then return the updated bigint.
    
    ```cpp
    std::string str1 = "233";
    test1 = bigint(str1); 
    test2 = --test1;
    cout << test1 << "\n";     // The output will be: 232
    cout << test2 << "\n";     // The output will be: 232
    ```

4. Postfix Decrement Operator

    The postfix decrement operator `--` is used to decrementing the `bigint` object by 1, but it returns the object before the decrementing. We implement this by first storing the original bigint object. Then we use the prefix decrement operator to add -1 to the original bigint object, but then returns the bigint before updating.
    
    ```cpp
    std::string str1 = "233";
    test1 = bigint(str1); 
    test2 = test1--;
    cout << test1 << "\n";     // The output will be: 232
    cout << test2 << "\n";     // The output will be: 233
    ```

### **Output Stream Insertion Operator**

The output stream insertion operator `<<` is used to output the bigint object to an output stream.

If the bigint object is negative, we first insert a minus sign to indicate that the number is negative. Then we process the digits part. The digits of the bigint are stored in a vector with the least significant digit at the first position, so we iterate through the vector in reverse order to display the number in a readable format.

```cpp
    std::string str1 = "123";
    std::string str2 = "-123";
    test1 = bigint(str1); 
    test2 = bigint(str2); 
    cout << test1 << "\n";     // The output will be: 123
    cout << test2 << "\n";     // The output will be: -123
```