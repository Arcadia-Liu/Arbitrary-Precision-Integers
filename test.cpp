#include "bigint.hpp"

int main()
{
    try
    {
        // Test the Default Constructor
        bigint test_default;
        std::cout << "Test the Default Constructor: " << test_default << " (should be 0 if correct)" << "\n";

        // Test the Interger Constructor
        int64_t num_positive = 5647431;
        bigint test_interger_positive(num_positive);
        std::cout << "Test the Interger Constructor (positive): " << test_interger_positive << " (should be 5647431 if correct)" << "\n";
        int64_t num_negative = -86132;
        bigint test_interger_negative(num_negative);
        std::cout << "Test the Interger Constructor (negative): " << test_interger_negative << " (should be -86132 if correct)" << "\n";

        // Test the String Constructor
        std::string str_positive = "+100000000000000000000";
        bigint test_str_positive(str_positive);
        std::cout << "Test the String Constructor (positive): " << test_str_positive << " (should be 100000000000000000000 if correct)" << "\n";

        std::string str_negatvive = "-000100000000000000000000";
        bigint test_str_negatvive(str_negatvive);
        std::cout << "Test the String Constructor (negative): " << test_str_negatvive << " (should be -100000000000000000000 if correct)" << "\n";

        // Test if illegal input throws an exception
        std::cout << "\n"
                  << "Test if illegal input throws an exception:" << "\n";
        try
        {
            std::string str_invalid = "gk%45#^$#!";
            bigint test_str_invalid(str_invalid);
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "invalid string: " << e.what() << "\n";
        }

        std::string str_1 = "86435927";
        bigint num_1(str_1);
        std::string str_2 = "265496872654";
        bigint num_2(str_2);
        std::string str_3 = "-75648";
        bigint num_3(str_3);
        std::string str_4 = "-3694449856";
        bigint num_4(str_4);
        std::string str_5 = "86360279";
        bigint num_5(str_5);
        std::string str_6 = "86865279";
        bigint num_6(str_6);

        // Test Addition Operations
        std::cout << "\n"
                  << "Test Addition Operations:" << "\n";
        std::cout << "Add two positive bigint numbers:" << "\n";
        std::cout << "86435927 + 265496872654 = " << num_1 + num_2 << " (should be 265583308581 if correct)" << "\n";

        std::cout << "Add a positive bigint number and a negative one:" << "\n";
        std::cout << "86435927 + -3694449856 = " << num_1 + num_4 << " (should be -3608019929 if correct)" << "\n";

        std::cout << "Add two negative bigint numbers:" << "\n";
        std::cout << "-75648 + -3694449856 = " << num_3 + num_4 << " (should be -3694525504 if correct)" << "\n";

        // Test Plus-Equals Operator
        std::cout << "\n"
                  << "Test Plus-Equals Operator:" << "\n";
        num_1 += num_3;
        std::cout << "(86435927 += -75648), then left side variable becomes " << num_1 << " (should be 86360279 if correct)" << "\n";

        // Test Subtraction Operator
        std::cout << "\n"
                  << "Test Subtraction Operator:" << "\n";
        std::cout << "A positive bigint number minus a positvie one:" << "\n";
        std::cout << "86360279 - 265496872654 = " << num_1 - num_2 << " (should be -265410512375 if correct)" << "\n";
        std::cout << "A positive bigint number minus a negative one:" << "\n";
        std::cout << "86360279 - -75648 = " << num_1 - num_3 << " (should be 86435927 if correct)" << "\n";
        std::cout << "A negative bigint number minus a positvie one:" << "\n";
        std::cout << "-3694449856 - 265496872654 = " << num_4 - num_2 << " (should be -269191322510 if correct)" << "\n";
        std::cout << "A negative bigint number minus a negative one:" << "\n";
        std::cout << "-3694449856 - -75648 = " << num_4 - num_3 << " (should be -3694374208 if correct)" << "\n";

        // Test Minus-Equals Operator
        std::cout << "\n"
                  << "Test Minus-Equals Operator:" << "\n";
        num_2 -= num_1;
        std::cout << "(265496872654 -= 86360279), then left side variable becomes " << num_2 << " (should be 265410512375 if correct)" << "\n";

        // Test Multiplication Operator
        std::cout << "\n"
                  << "Test Multiplication Operator:" << "\n";
        std::cout << "A positive bigint number multiplied by a positvie one:" << "\n";
        std::cout << "86360279 * 265410512375 = " << num_1 * num_2 << " (should be 22920925898237952625 if correct)" << "\n";
        std::cout << "A positive bigint number multiplied by a negative one:" << "\n";
        std::cout << "86360279 * -75648 = " << num_1 * num_3 << " (should be -6532982385792 if correct)" << "\n";
        std::cout << "A negative bigint number multiplied by a negative one:" << "\n";
        std::cout << "-75648 * -3694449856 = " << num_3 * num_4 << " (should be 279477742706688 if correct)" << "\n";

        // Test Multiply-Equals Operator
        std::cout << "\n"
                  << "Test Multiply-Equals Operator:" << "\n";
        num_3 *= num_1;
        std::cout << "(86360279 *= -75648), then left side variable becomes " << num_3 << " (should be -6532982385792 if correct)" << "\n";

        // Test Unary Minus Operator
        std::cout << "\n"
                  << "Test Unary Minus Operator" << "\n";
        std::cout << "-(86360279) = " << -num_1 << " (should be -86360279 if correct)" << "\n";
        std::cout << "-(-6532982385792) = " << -num_3 << " (should be 6532982385792 if correct)" << "\n";

        // Test Relational Operators
        std::cout << std::boolalpha;
        std::cout << "\n"
                  << "Test Relational Operators" << "\n";
        std::cout << "(86360279 == 86360279) ? The answer is " << (num_1 == num_5) << " (should be true if correct)" << "\n";
        std::cout << "(86360279 == -6532982385792) ? The answer is " << (num_1 == num_3) << " (should be false if correct)" << "\n";
        std::cout << "(86360279 == -86360279) ? The answer is " << (num_1 == -num_3) << " (should be false if correct)" << "\n";

        std::cout << "\n";
        std::cout << "(86360279 < 86360279) ? The answer is " << (num_1 < num_5) << " (should be false if correct)" << "\n";
        std::cout << "(86360279 < 6532982385792) ? The answer is " << (num_1 < -num_3) << " (should be true if correct)" << "\n";
        std::cout << "(-6532982385792 < 86360279) ? The answer is " << (num_3 < num_1) << " (should be true if correct)" << "\n";
        std::cout << "(86865279 < 86360279) ? The answer is " << (num_6 < num_5) << " (should be false if correct)" << "\n";

        std::cout << "\n";
        std::cout << "(86360279 <= 86360279) ? The answer is " << (num_1 <= num_5) << " (should be true if correct)" << "\n";
        std::cout << "(86360279 <= -6532982385792) ? The answer is " << (num_1 <= num_3) << " (should be false if correct)" << "\n";
        std::cout << "(-6532982385792 <= 86360279) ? The answer is " << (num_3 <= num_1) << " (should be true if correct)" << "\n";
        std::cout << "(86865279 <= 86360279) ? The answer is " << (num_6 <= num_5) << " (should be false if correct)" << "\n";

        std::cout << "\n";
        std::cout << "(86360279 > 86360279) ? The answer is " << (num_1 > num_5) << " (should be false if correct)" << "\n";
        std::cout << "(86360279 > -6532982385792) ? The answer is " << (num_1 > num_3) << " (should be true if correct)" << "\n";
        std::cout << "(-6532982385792 > 86360279) ? The answer is " << (num_3 > num_1) << " (should be false if correct)" << "\n";
        std::cout << "(86865279 > 86360279) ? The answer is " << (num_6 > num_5) << " (should be true if correct)" << "\n";

        std::cout << "\n";
        std::cout << "(86360279 >= 86360279) ? The answer is " << (num_1 >= num_5) << " (should be true if correct)" << "\n";
        std::cout << "(86360279 >= -6532982385792) ? The answer is " << (num_1 >= num_3) << " (should be true if correct)" << "\n";
        std::cout << "(-6532982385792 >= 86360279) ? The answer is " << (num_3 >= num_1) << " (should be false if correct)" << "\n";
        std::cout << "(86865279 >= 86360279) ? The answer is " << (num_6 >= num_5) << " (should be true if correct)" << "\n";

        std::string str_a = "10";
        bigint a(str_a);
        std::string str_b = "-10";
        bigint b(str_b);

        std::cout << "\n"
                  << "Test Increment Operator" << "\n";
        bigint c_1 = a++;
        bigint c_2 = b++;
        std::cout << "When a = 10 and b = -10," << "\n";
        std::cout << "if c = a++, then c = " << c_1 << " (should be 10 if correct), a = " << a << " (should be 11 if correct)" << "\n";
        std::cout << "if c = b++, then c = " << c_2 << " (should be -10 if correct), b = " << b << " (should be -9 if correct)" << "\n";

        bigint d_1 = ++a;
        bigint d_2 = ++b;
        std::cout << "Now a = 11 and b = -9," << "\n";
        std::cout << "if c = ++a, then c = " << d_1 << " (should be 12 if correct), a = " << a << " (should be 12 if correct)" << "\n";
        std::cout << "if c = ++b, then c = " << d_2 << " (should be -8 if correct), b = " << b << " (should be -8 if correct)" << "\n";

        std::cout << "\n"
                  << "Test Decrement Operator" << "\n";
        bigint e_1 = a--;
        bigint e_2 = b--;
        std::cout << "Now a = 12 and b = -8," << "\n";
        std::cout << "if c = a--, then c = " << e_1 << " (should be 12 if correct), a = " << a << " (should be 11 if correct)" << "\n";
        std::cout << "if c = b--, then c = " << e_2 << " (should be -8 if correct), b = " << b << " (should be -9 if correct)" << "\n";

        bigint h_1 = --a;
        bigint h_2 = --b;
        std::cout << "Now a = 11 and b = -9," << "\n";
        std::cout << "if c = --a, then c = " << h_1 << " (should be 10 if correct), a = " << a << " (should be 10 if correct)" << "\n";
        std::cout << "if c = --b, then c = " << h_2 << " (should be -10 if correct), b = " << b << " (should be -10 if correct)" << "\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "An exception is threw:" << e.what() << "\n";
    }
}