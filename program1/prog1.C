/*
 * Carmen St. Jean
 * CS 515, Assignment 1
 * September 11, 2009
 *
 * Assignment 1 calculates mileage by reading input in triples.
 * A complete triple set (float, float, char) contains the
 * odometer reading at a fill-up, the quantity of gasoline at
 * the fill-up, and the unit for the quantity of gas (gallons or
 * (liters).  Input is processed until a sentinel triple is
 * reached (ex: -1 0 G).
 *
 */

#include <iostream>
using namespace std;

int main()
{
    float miles = 0, totalMiles = 0, prevMile = 0;
    float gallons = 0, totalGallons = 0;
    char unit = 'G';

    cin >> miles >> gallons >> unit;
    cout << "\ndata input\n";

    while (miles > prevMile)
    {
        cout << miles << " " << gallons << " " << unit <<"\n";

        // converts liters to gallons if necessary
        if (unit == 'l' || unit == 'L')
        {
            gallons = gallons / 3.785;
        }

        // adds to total sums if current fill-up was not first fill-up
        if (prevMile != 0)
        {
            totalMiles += miles - prevMile;
            totalGallons += gallons;
        }

        // sets new sentinel to the current mileage for best comparison
        prevMile = miles;

        cin >> miles >> gallons >> unit;
    }

    // checks to see if any values were added before sentinel reached
    if (totalMiles > 0)
    {
        cout << "\ntotal miles: " << totalMiles << "\n";
        cout << "total gallons: " << totalGallons << "\n";
        cout << "mileage: " << totalMiles/totalGallons;
        cout << " Miles Per Gallon\n\n";
    }
    else
    {
        cout << "\nNo more data or error.\n\n";
    }

    return 0;
}