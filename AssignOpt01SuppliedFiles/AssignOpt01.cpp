#include "btNode.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void SeedRand();
int BoundedRandomInt(int lowerBound, int upperBound);
int RemAllOccur(int array[], int& used, int subArrSize, int target) ;
void RemDups(int array[], int& used);
void InsertSortedNonDec(int array[], int& used, int newValue) ;
void ShowArray(const int a[], int size);
bool remOne(int dataOriSorted[], int& used, int remInt);
void MilestoneBroadcast(int testCasesDone, int testCasesToDo,
                        const int dataOriUnsorted[], const int dataOriSorted[],
                        const int dataNoDupUnsorted[], const int dataNoDupSorted[],
                        int oriSize, int noDupSize, btNode* avl_root);

int main()
{
   int testCasesToDo = 1056000,
   //int testCasesToDo = 99,
       testCasesDone = 0,
       loOriSize = 1,
       //hiOriSize = 50,
       //hiOriSize = 40,
       hiOriSize = 33,
       oriSize,
       noDupSize,
       loValue = -99,
       hiValue = 99;
   int oriCount,
       numNodes,
       newInt;
   int *dataOriUnsorted = 0,
       *dataOriSorted = 0;
   int *dataNoDupUnsorted = 0,
       *dataNoDupSorted = 0;
   btNode* avl_root = 0;

   // SeedRand(); // disabled for reproducible result

   do
   {
      ++testCasesDone;
      oriSize = BoundedRandomInt(loOriSize, hiOriSize);
      dataOriUnsorted   = new int [oriSize];
      dataOriSorted     = new int [oriSize];
      dataNoDupUnsorted = new int [oriSize];
      dataNoDupSorted   = new int [oriSize];

      oriCount = 0;
      while (oriCount < oriSize)
      {
         newInt = BoundedRandomInt(loValue, hiValue);
         dataOriUnsorted[oriCount] = newInt;
         InsertSortedNonDec(dataOriSorted, oriCount, newInt);
         // NOTE: oriCount incremented by InsertSortedNonDec
         avl_insert(avl_root, newInt);
      }

      for (noDupSize = 0; noDupSize < oriSize; ++noDupSize)
      {
         dataNoDupUnsorted[noDupSize] = dataOriUnsorted[noDupSize];
         dataNoDupSorted[noDupSize]   = dataOriSorted[noDupSize];
      }

      RemDups(dataNoDupUnsorted, noDupSize);
      // NOTE: noDupSize updated by RemDups

      noDupSize = oriSize;
      RemDups(dataNoDupSorted, noDupSize);
      // NOTE: noDupSize updated by RemDups
      numNodes = tree_size(avl_root);

      if (numNodes != noDupSize)
      {
         cout << "Insert error ... bad post-insertion node count" << endl;
         cout << "expected: " << oriCount << endl;
         cout << "got this: " << numNodes << endl;
         MilestoneBroadcast(testCasesDone, testCasesToDo,
                            dataOriUnsorted, dataOriSorted,
                            dataNoDupUnsorted, dataNoDupSorted,
                            oriSize, noDupSize, avl_root);
         exit(EXIT_FAILURE);
      }

      if ( ! isAVL(avl_root) )
      {
         cout << "Error ... AVL check failed" << endl;
         MilestoneBroadcast(testCasesDone, testCasesToDo,
                            dataOriUnsorted, dataOriSorted,
                            dataNoDupUnsorted, dataNoDupSorted,
                            oriSize, noDupSize, avl_root);
         exit(EXIT_FAILURE);
      }

      if (testCasesDone == 1  ||
          testCasesDone == 3  ||
          testCasesDone == 6  ||
          testCasesDone == 10 ||
          testCasesDone % 264000 == 0)
      {
         MilestoneBroadcast(testCasesDone, testCasesToDo,
                            dataOriUnsorted, dataOriSorted,
                            dataNoDupUnsorted, dataNoDupSorted,
                            oriSize, noDupSize, avl_root);
      }

      tree_clear(avl_root);
      delete [] dataOriUnsorted;
      delete [] dataOriSorted;
      delete [] dataNoDupUnsorted;
      delete [] dataNoDupSorted;
      dataOriUnsorted = dataOriSorted = dataNoDupUnsorted = dataNoDupSorted = 0;
   }
   while (testCasesDone < testCasesToDo);
   cout << endl;
   cout << "++++++++++++++++++++++++++++++++" << endl;
   cout << "test program terminated normally" << endl;
   cout << "++++++++++++++++++++++++++++++++" << endl;

   return EXIT_SUCCESS;
}

// Function to seed the random number generator
// PRE:  none
// POST: The random number generator has been seeded.
void SeedRand()
{
   srand( (unsigned) time(NULL) );
}

// Function to generate a random integer between
// lowerBound and upperBound (inclusive)
// PRE:  lowerBound is a positive integer.
//       upperBound is a positive integer.
//       upperBound is larger than lowerBound
//       The random number generator has been seeded.
// POST: A random integer between lowerBound and upperBound
//       has been returned.
int BoundedRandomInt(int lowerBound, int upperBound)
{
   return ( rand() % (upperBound - lowerBound + 1) ) + lowerBound;
}

// Pre:  (1) used >= 0
//       (2) "size of array" > used
//       (3) array's existing values (from array[0] through array[used - 1])
//           are in non-decreasing order
// Post: (1) used has been incremented by 1
//       (2) newValue has been inserted into array, keeping all its values
//           (from array[0] through array[used - 1]) in non-decreasing order
void InsertSortedNonDec(int array[], int& used, int newValue)
{
   int probeIndex = used;
   while (probeIndex > 0 && array[probeIndex - 1] > newValue)
   {
      array[probeIndex] = array[probeIndex - 1];
      --probeIndex;
   }
   array[probeIndex] = newValue;
   ++used;
}

void ShowArray(const int a[], int size)
{
   for (int i = 0; i < size; ++i)
      cout << a[i] << ' ';
   cout << endl;
}

bool remOne(int dataOriSorted[], int& used, int remInt)
{
   for (int i = 0; i < used; ++i)
      if (dataOriSorted[i] == remInt)
      {
         int j = i + 1;
         while (j < used)
            dataOriSorted[i++] = dataOriSorted[j++];
         --used;
         return true;
      }
      else if (dataOriSorted[i] > remInt)
         break;
   return false;
}

int RemAllOccur(int array[], int& used, int subArrSize, int target)
{
   int removedCount = 0;
   for (int i = 0; i < subArrSize; ++i)
      if (array[i] == target)
         ++removedCount;
      else
         array[i - removedCount] = array[i];
   used -= removedCount;
   return removedCount;
}

void RemDups(int array[], int& used)
{
   for (int i = 0; i < used - 1; ++i)
   {
      int target = array[i];
      RemAllOccur(array + i + 1, used, used - i - 1, target);
   }
}

void MilestoneBroadcast(int testCasesDone, int testCasesToDo,
                        const int dataOriUnsorted[], const int dataOriSorted[],
                        const int dataNoDupUnsorted[], const int dataNoDupSorted[],
                        int oriSize, int noDupSize, btNode* avl_root)
{
   clog << "testing case " << testCasesDone
        << " of " << testCasesToDo << endl;
   cout << endl;
   cout << "============================" << endl;
   cout << "test case " << testCasesDone
        << " of " << testCasesToDo << endl;
   cout << "============================" << endl;

   cout << "in-seq (all in): ";
   ShowArray(dataOriUnsorted, oriSize);
   cout << "sorted (all in): ";
   ShowArray(dataOriSorted, oriSize);
   cout << "in-seq (noDups): ";
   ShowArray(dataNoDupUnsorted, noDupSize);
   cout << "sorted (noDups): ";
   ShowArray(dataNoDupSorted, noDupSize);
   //cout << "\n--------------------------------------------------------------\n";
   tree_print(avl_root, 1);
   //cout << "\n--------------------------------------------------------------\n";
}
