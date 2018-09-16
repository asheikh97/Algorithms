/**********************************************************************
 *
 * CISC 4080 (Computer Algorithms)
 * Project 2: Comparing Polynomial Multiplication Algorithms
 *
 * Author: A. G. Werschulz
 * Date:   12 Feb 2018
 *
 * This is the header file for a (fairly minimal) polynomial class.
 * 
 **********************************************************************/

#pragma once

#include <iostream>
#include <vector>

// Templates are a pain with friend functions, so change this if you
// want polynomials with (say) complex coefficients
using T = double;

class Polynomial
{
public:
   int degree() const;

   T& operator[](size_t index);
   const T operator[](size_t index) const;
   
   friend bool operator==(const Polynomial& a, const Polynomial& b);
   friend bool operator!=(const Polynomial& a, const Polynomial& b);
   friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
   friend Polynomial add(const Polynomial& a, const Polynomial& b);
   friend Polynomial subtract(const Polynomial& a, const Polynomial& b);
   friend Polynomial naive_mult(const Polynomial& a, const Polynomial& b);
   friend Polynomial karatsuba(const Polynomial& a, const Polynomial& b);
   friend Polynomial monomial_mult(const Polynomial& a, int n);

private:
   std::vector<T> data;
   void split(Polynomial& p_left, Polynomial& p_right) const;
};

// the zero polynomial is useful to have around
static Polynomial zero;
