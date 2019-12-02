/**********************************************************************
 *
 * CISC 4080 (Computer Algorithms)
 * Project 2: Comparing Polynomial Multiplication Algorithms
 *
 * Author: A. G. Werschulz
 * Date:   12 Feb 2018
 *
 * This program generates two polynomials, whose degree is given as a
 * command-line parameter.  It then runs the naive and the Karatsuba
 * polynomial multiplication algorithms, reporting the amount of time
 * used by each, and declaring the winner.  It also double-checks that
 * the two algorithms give the same result.
 *
 **********************************************************************/

// includes and usings
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>

#include <libgen.h>
#include <unistd.h>

#include "Polynomial.h"
#include "random.h"

// be lazy
using namespace std;
using namespace std::chrono;

// function declarations
void usage(const string& progname);
void parse_cmd_line(const string& progname, int argc, char** argv,
                    bool& debug, int& degree);

int main(int argc, char** argv)
{
    string progname {basename(argv[0])};
    
    // get command-line parameters
    bool debug;
    int degree;
    parse_cmd_line(progname, argc, argv, debug, degree);
    
    // two polynomials of given degree, with randomly chosen coefficents
    randomize();
    Polynomial a, b;
    for (int i = 0; i <= degree; i++) {
        a[i] = pick_a_number(-1.0, 1.0);
        b[i] = pick_a_number(-1.0, 1.0);
    }
    
    // debugging output, if requested
    if (debug) {
        cout << "Debugging:\n"
        << "    a = " << a << endl
        << "    b = " << b << endl;
    }
    
    // run the naive algorithm
    auto start = system_clock::now();
    Polynomial c1 = naive_mult(a, b);
    auto end = system_clock::now();
    duration<double> naive_seconds = end - start;
    if (debug)
        cout << "    Naive product = " << c1 << endl;
    
    // run Karatsuba's algorithm
    start = system_clock::now();
    Polynomial c2 = karatsuba(a, b);
    end = system_clock::now();
    duration<double> karatsuba_seconds = end - start;
    if (debug)
        cout << "    Karatsuba product = " << c2 << endl << endl;
    // do the two algorithms give the same result?
    if (c1 == c2) cout << "Results match.\n";
    else {
        cout << "results don't match:\n";
        if (debug) {
            cout << "  Naive     = " << c1 << endl;
            cout << "  Karatsuba = " << c2 << endl;
        }
        return 3;
    }
    
    // and finally, report our results
    cout << "\nTiming: \n"
    << "    Naive algorithm: "<< naive_seconds.count() << " seconds\n"
    << "    Karatsuba algorithm: " << karatsuba_seconds.count()
    << " seconds\n";
    if (naive_seconds < karatsuba_seconds)
        cout << "Naive algorithm wins!\n";
    else if (naive_seconds == karatsuba_seconds)
        cout << "Tie!\n";
    else  // naive_seconds > karatsuba_seconds
        cout << "Karatsuba algorithm wins!\n";
}

/*
 * print a usage message
 */
void usage(const string& progname)
{
    cerr << "Usage: " << progname << " [-d] deg\n"
    << "  where -d means debugging mode\n"
    << "        deg is the degree of the polynomials to be multiplied\n";
}

/*
 * check command line
 * valid flags are
 *    -d: some debugging output
 *    -h: help message
 */
void parse_cmd_line(const string& progname, int argc, char** argv,
                    bool& debug, int& degree)
{
    int opt;
    debug = false;
    while ((opt = getopt(argc, argv, "d")) != -1) {
        switch (opt) {
            case 'd':
                debug = true;
                break;
            default:
                usage(progname);
                exit(1);
        }
    }
    if (optind >= argc || argc - optind > 1) {
        cerr << "Wrong number of command line arguments\n";
        usage(progname);
        exit(2);
    }
    degree = atoi(argv[optind]);
}

