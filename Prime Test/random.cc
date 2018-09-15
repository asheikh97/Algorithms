 /**********************************************************************
 *
 * Random number toolkit
 *
 * Author: Walter E. Brown <webrown.cpp@gmail.com>
 * Date: 12 Mar 2013
 *
 * Collection of functions to simplify random-number generation
 * (implementation file).
 * 
 **********************************************************************/

#include "random.h"

// Shares a single URNG with the other functions in this toolkit.
std::default_random_engine & global_urng()
{
   static std::default_random_engine u{};
   return u;
}

// Sets the shared URNG to an unpredictable state.
void randomize()
{
   static std::random_device rd{};
   global_urng().seed(rd());
}

//Returns an int variate uniformly distributed in [from, thru].
int pick_a_number(int from, int thru)
{
   static std::uniform_int_distribution<> d{};
   using parm_t = decltype(d)::param_type;
   return d(global_urng(), parm_t{from, thru});
}

// Returns a double variate uniformly distributed in [from, upto).
double pick_a_number(double from, double upto)
{
   static std::uniform_real_distribution<> d{};
   using parm_t = decltype(d)::param_type;
   return d(global_urng(), parm_t{from, upto});
}
