/**********************************************************************
 *
 * CISC 4080: Computer Algorithms <br/>
 * Project 4: Dynamic Programming <br/>
 * Spring 2018 <br/>
 *
 * @author Abadali Sheikh
 * @date 3/15/2018
 * @file proj4.cc
 * A dynamic programming algorithm to determine the minimal number
 * of multiplications needed to compute the product, in O(n^3).
 *
 **********************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include "Matrix.h"
#include "MatrixIO.h"
#include <limits.h>

using namespace Numeric_lib;
using namespace std;
/*
 * Function declarations
 */ 

/**
 * Create a vector of ints, whose content comes from an istream
 *
 * @param source the input stream
 * @return the vector
 */
vector<int> fill(istream& source);

/**
 * Calculates optimal number of multiplications
 * for chain of matrices
 */
int opt_mult(const vector<int>& m);

/**
 * The usual main() function
 */
int main(int argc, char** argv)
{
   string progname{argv[0]};           // for msgs

   // command-line arg processing
   if (argc > 2) {
      cerr << "Usage: " << progname << " [mfile]\n";
      return 1;
   }

   // get the data
   vector<int> m;
   if (argc == 1) 
      m = fill(cin);
   else {
      ifstream source(argv[1]);
      if (!source) {
         cerr << progname << ": can't open " << argv[1] << endl;
         return 2;
      }
      m = fill(source);
   }
    
   // solve the problem and report results
   int mults = opt_mult(m);
   cout << mults << " multiplications\n";
};

/*
 * Function definitions
 */

vector<int> fill(istream& source)
{
   vector<int> m;
   int datum;
   while (source >> datum)
      m.push_back(datum);
   return m;
}

/*
    Using Dynamic Algorithm with underlyin DAG approach
    to calcualte minimum number of multiplications required
*/
int opt_mult(const vector<int>& m)
{
    int num_matrices = m.size()-1;              //Number of matrices
    Matrix<int,2> C(num_matrices,num_matrices); //Matrix to store # of multiplications
    
    for (int i = 0; i < num_matrices; i++)
        C(i,i) = 0;                             //Cost is 0 when multiplying a single matrix
    
    for (int s = 1; s < num_matrices; s++) {    //Here s denotes chain length
        for (int i = 0; i < num_matrices - s; i++) {
            int j = i + s;
            C(i,j) = INT_MAX;
            // Calculate min. multiplications & store in q
            for (int k = i; k < j; k++) {
                int q = C(i,k) + C(k+1,j) + m[i] * m[k+1] * m[j+1];
                if (q < C(i,j))
                    C(i,j) = q;
            }
        }
    }
    return C(0,num_matrices-1);					// return min. # of multiplications
}
