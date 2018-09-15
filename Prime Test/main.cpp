/**********************************************************************
 *
 * CISC 4080, Project 1:  Testing For Primes
 *
 * 
 *
 * Author: Abadali Sheikh
 *
 **********************************************************************/

// system includes
#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <libgen.h>

// Walter Brown's library
#include "random.h"

// be lazy
using namespace std;
using namespace std::chrono;

// function prototypes
void usage(string progname);
void check_prime(long int number);
bool is_prime_exact(long int number);
bool is_prime_prob(long int number);
long int pow_mod(long int a, long int b, long int n);

// usual main function
int main(int argc, char** argv)
{
    // command-line parameter processing
    string progname{basename(argv[0])};
    if (argc != 2) {
        usage(progname);
        return 1;
    }
    ifstream data_stream{argv[1]};
    if (!data_stream) {
        cerr << progname << ": couldn't open " << argv[1] << endl;
        return 2;
    }
    
    // comment this out if debugging
    randomize();
    
    // print "false" and "true" for bool values
    cout << boolalpha;
    
    // finally:check primality of each number in the file
    for (long int number; data_stream >> number; ) {
        if (number <= 1)
            cout << number <<" <= 2: ignored\n";
        else
            check_prime(number);
    }
}

// print usage msg (for error msgs)
void usage(string progname)
{
    cerr << "Say something useful here \n";
    exit(2);
}

// precondition: number >= 2
// checks whether number is prime, printing the result (as well as how
// long the calculation took), using both the exact and the
// probabilistic algorithms
void check_prime(long int number)
{
    cout << "checking " << number << ":\n";
    // exact algorithm
    auto start = system_clock::now();
    bool prime_result = is_prime_exact(number);
    auto end = system_clock::now();
    duration<double> elapsed_seconds = end - start;
    cout << "  exact says " << prime_result
    << " (" << elapsed_seconds.count() << " seconds),\n";
    
    // probabilistic algorithm
    start = system_clock::now();
    prime_result = is_prime_prob(number);
    end = system_clock::now();
    elapsed_seconds = end - start;
    cout << "  probabilistic says " << prime_result
    << " (" << elapsed_seconds.count() << " seconds)\n";
}

// Exact Algorithm for testing Primes O(n)
bool is_prime_exact(long int number)
{
    for(long i = 2; i*i <= number; i++)
    {
        if(number % i == 0)
        {
            return false;
            break;
        }
    }
    return true; 
}

//Probab
bool is_prime_prob(long int number)
{
    long int num;
    for(int i = 0; i < 10; i++)
    {
        num = pick_a_number(int(number), int(number - 1));
        if (pow_mod(num, number - 1, number) !=1)
            return false;
    }
    return true;
}

//Modular exponentaiton
long int pow_mod(long int a, long int b, long int n)
{
    long z;
    if (b == 0)
        return 1;
    z = pow_mod(a, b/2, n);
    if (b % 2 == 0)
        return ((z * z) % n);
    else
        return (a * ((z * z) % n));
}
