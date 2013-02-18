/**
 * Carmen St. Jean - CS 515, Assignment 11
 * December 11, 2009
 *
 * Assignment 11 uses a greedy algorithm to find the
 * shortest paths between vertices.  The input requires
 * that there be first a value indicating the number of
 * vertices, say n.  Then there must be n^2 values
 * to represent an adjacency matrix.  For any entry [i][j]
 * of this matrix, the value is the cost to get from vertex
 * i to vertex j.  A negative value represents infinity.
 * Finally, the input must indicate a starting vertex.
 * The program uses this starting vertex to find the cost
 * to visit all other vertices and then reports the paths.
 */

#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;
#include "Weight.h"
#include "PathList.h"

    // constants
    const int maxSize = 100;

// inputs values into the adjacency matrix
void inputMatrix(Weight matrix[][maxSize], int &size, int &start);
// prints the adjacency matrix
void printMatrix(Weight matrix[][maxSize], int &size);
// prints the resulting costs and paths
void printResults(PathList p, Weight cost[], int &size, int &start);

int main()
{
   int size, start;

   cin >> size;

   if (size < 0)
   {
      cerr << "error: negative number of vertices\n";
      exit(1);
   }

   Weight adjmatrix[maxSize][maxSize];
   inputMatrix(adjmatrix, size, start);
   printMatrix(adjmatrix, size);

   PathList pathlist;

   cerr << "\nstart vertex: " << start;

   bool used[size];
   Weight cost[maxSize];

   for (int i = 0; i < size; i++)
   {
      used[i] = false;
      cost[i] = adjmatrix[start][i]; // copy adjmatrix into cost

      if (cost[i] != Weight::infinity() && i != start)
      {
         pathlist.insert(start, i);
      }
   }

   used[start] = true;
   bool allused = false;
   int current = start;

   while (!allused)
   {
      Weight smallest = Weight::infinity();
      int smallestIndex;

      for (int i = 0; i < size; i++)
      {
         if (!used[i] && cost[i] < smallest)
         {
            smallestIndex = i;
            smallest = cost[i];
         }
      }

      if (smallest == Weight::infinity())
      {
         break;
      }

      used[smallestIndex] = true;
      Weight tmp[size];

      for (int i = 0; i < size; i++)
      {
         tmp[i] = adjmatrix[smallestIndex][i] + smallest;

         if (!used[i] && tmp[i] < cost[i])
         {
            cost[i] = tmp[i];
            pathlist.insert(smallestIndex, i);
         }
      }

      allused = true;

      for (int i = 0; i < size; i++)
      {
         if (!used[i])
           allused = false;
      }

      current = smallestIndex;
   }

   printResults(pathlist, cost, size, start);

   return 0;
}

// inputs values into the adjacency matrix
void inputMatrix(Weight matrix[][maxSize], int &size, int &start)
{
   for (int i = 0; i < size; i++)
   {
      for (int j = 0; j < size; j++)
      {
         if (!(cin >> matrix[i][j]))
         {
            cerr << "not enough values\n";
            exit(1);
         }
      }
   }

   if (!(cin >> start))
   {
     cerr << "not enough values\n";
     exit(1);
   }
}

// prints the adjacency matrix
void printMatrix(Weight matrix[][maxSize], int &size)
{
   cerr << "adjacency matrix\n";
   cerr << "----------------\n\n";

   if (size == 0)
   {
      cerr << "no vertices\n";
      return;
   }

   string dashes = "        ";
   cerr << dashes;

   for (int i = 0; i < size; i++)
   {
      cerr << i;

      if (i < 10)
         cerr << " ";

      cerr << "      ";
      dashes += "----    ";
   }

   cerr << "\n" << dashes << "\n";

   for (int i = 0; i < size; i++)
   {
      cerr << i;

      if (i < 10)
         cerr << "     | ";
      else if (i < 100)
         cerr << "    | ";

      for (int j = 0; j < size; j++)
      {
         cerr << matrix[i][j] << " ";
      }
      cerr << "\n";
   }
}

// prints the resulting costs and paths
void printResults(PathList p, Weight cost[], int &size, int &start)
{
   cerr << "\n";
   for (int i = 0; i < size; i++)
   {
      if (i != start)
      {
         cerr << "\n" << start << " -> " << i << "  cost: ";
         cerr << cost[i] << "edges:";
         p.findpath(start, i);
      }
   }
   cerr << "\n";
}