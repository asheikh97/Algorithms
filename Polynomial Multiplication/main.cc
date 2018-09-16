/*
**********************************************************************
*
* CISC 4080 (Computer Algorithms)
* Project 2: Comparing Polynomial Multiplication Algorithms
*
* Author: Abadali Sheikh
* Date: 02/16/2018
*
* Collection of functions for multiplication of Polynomials
* Former function multiplies polynomials using naive algorithm
* Latter function multiplies polynomials using Karatsuba algorithm
* (implementation file).
*
**********************************************************************/
#include "Polynomial.h"
using namespace std;

/*
 * Returns the Degree of the Polynomial
 */
int Polynomial::degree() const
{
    return data.size()-1;
}

/*
 * p[i] is the i-th coefficient of the Polynomial p
 * this is the rvalue version
 */
const double Polynomial::operator[](size_t index) const
{
    return (index <= degree()) ? data[index] : 0;
    return data[index];
}

/*
 * p[i] is the i-th coefficient of the Polynomial p
 * this is the lvalue version
 */
double& Polynomial::operator[](size_t index)
{
    for (int i = data.size(); i <= index; i++) data.push_back(0.0);
    return data[index];
}

/*
 * equality operator for Polynomials
 */
bool operator==(const Polynomial& a, const Polynomial& b)
{
    // two doubles will be considered nearly equal if their relative
    // distance is at most epsilon
    const double epsilon {1.0e-10};
    if (a.degree() != b.degree()) return false;
    for (int i = 0; i <= a.degree(); i++)
        if (abs(a[i] - b[i]) > epsilon) return false;
    return true;
}

/*
 * inequality operator for Polynomials
 * returns the negation of the equality operator
 */
bool operator!=(const Polynomial& a, const Polynomial& b)
{
    return !(a==b);
}

/*
 * Output a Polynomial
 */
ostream& operator<<(ostream& os, const Polynomial& p)
{
    if (p.degree() == -1 || (p.degree() == 0 && p[0] == 0)) {
        cout << 0;
        return os;
    }
    for (int i = 0; i <= p.degree(); i++) {
        if (p[i] != 0) {
            if (i == 0) os << p[0];
            else if (i == 1) os << p[1] << "x";
            else os << p[i] << "x^" << i;
            if (i < p.degree()) cout << " + ";
        }
    }
    return os;
}

/*
 * Addition operator for Polynomials
 */
Polynomial add(const Polynomial& a, const Polynomial& b)
{
    if (a == zero) return b;
    if (b == zero) return a;
    
    Polynomial sum;
    int deg = max(a.degree(), b.degree());
    for (int i = 0; i <= deg; i++)
        sum.data.push_back(a[i] + b[i]);
    return sum;
}

/*
 * Subtraction operator for polynomials
 */
Polynomial subtract(const Polynomial& a, const Polynomial& b)
{
    if (b == zero) return a;
    Polynomial diff;
    int deg = max(a.degree(), b.degree());
    for (int i = 0; i <= deg; i++)
        diff.data.push_back(a[i] - b[i]);
    return diff;
}


/*
 * Naive Multiplication for Polynomials
 * Input: Two polynomials of same degree
 * Output: Product of the two Polynomials using naive method
 */
Polynomial naive_mult(const Polynomial& a, const Polynomial& b)
{
    Polynomial prod;
    int deg = max(a.degree(), b.degree());
    
    for(int i = 0; i <= deg; i++)
        for (int j = 0; j<= deg ; j++)
            prod[i+j] += a[i] * b[j];
    return prod;
}

/*
 * Karatsuba multiplication for Polynomials
 * Input: Two polynomials of same degree
 * Output: Product of the two Polynomials using karatsuba method
 */
Polynomial karatsuba(const Polynomial& a, const Polynomial& b)
{
    Polynomial prod;
    int size = max(a.data.size(), b.data.size());
    int half = size/2;
    
    if(size == 1){
        prod[0] = a[0] * b[0];
        return prod;
    }
    Polynomial a_left, a_right, b_left, b_right;
    a.split(a_left, a_right); // Splits polynomial 'a' into halves of roughly equal degree
    b.split(b_left, b_right); // Splits polynmial  'b' into halves of roughly equal degree
    Polynomial prod_1 = karatsuba(a_left, b_left);   // a_left  * b_left
    Polynomial prod_2 = karatsuba(a_right, b_right); // a_right * b_right
    Polynomial prod_3 = karatsuba(add(a_left, a_right), add(b_left, b_right)); // (a_left + b_left) * (a_right + b_right)
    Polynomial prod_4 = subtract(subtract(prod_3, prod_1), prod_2); // prod_3 - prod_1 - prod_2
    
    // Check if odd number of terms. Use Ceiling LHS & floor RHS
    if (size % 2 == 1) {
        size++;
        half++;
    }
    Polynomial mid_term = monomial_mult(prod_4, half);
    Polynomial last_term = monomial_mult(prod_2, size);
    prod = add(add(prod_1, mid_term), last_term);
    return prod;
}

/*
 * Multiply a Polynomial by x^n
 */
Polynomial monomial_mult(const Polynomial& a, int n)
{
    Polynomial result;
    for(int i = 0; i <= a.degree(); i++)
        result[i+n] = a[i];
    return result;
}

/*
 * Split a Poylynomial into two pieces of roughly equal degree
 * after
 *      p.split(p_left, p_right)
 * we have
 *      p(x) = p_left(x) + x^n p_right(x)
 * where n is roughly p.degree()/2.  YMMV.
 */
void Polynomial::split(Polynomial& p_left, Polynomial& p_right) const
{
    int deg = int (data.size() - 1);
    for(int i = 0; i <= deg; ++i){
        if (i <= deg / 2)
            p_left[i] = data[i];
        else
            p_right[(i-p_left.degree()-1)] = data[i];
    }
}
