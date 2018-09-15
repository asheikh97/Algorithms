/**********************************************************************
 *
 * Random number toolkit
 *
 * Author: Walter E. Brown <webrown.cpp@gmail.com>
 * Date: 12 Mar 2013
 *
 * Collection of functions to simplify random-number generation
 * (header file).
 * 
 **********************************************************************/

#pragma once

#include <random>

// Shares a single URNG with the other functions in this toolkit.
std::default_random_engine & global_urng();

// Sets the shared URNG to an unpredictable state.
void randomize();

//Returns an int variate uniformly distributed in [from, thru].
int pick_a_number(int from, int thru);

// Returns a double variate uniformly distributed in [from, upto).
double pick_a_number(double from, double upto);
