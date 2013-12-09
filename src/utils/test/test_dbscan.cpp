/*
 * dbscan test:
 * We generate a number of points from several normal distributions and then
 * cluster. This test outputs the point locations for each cluster. 
 *
 * The output (stored as a file) can easily be plotted with Python's
 * matplotlib:
 *      >> import numpy as np
 *      >> import matplotlib.pyplot as plt
 *      >> data = np.loadtxt (out.txt)
 *      >> for c in clusters:
 *      >>     plt.plot (data[], data[], '.')
 *      >> plt.show ()
 */

#include <iostream>
#include <random>

using namespace std;

int main (int argc, char *argv[])
{
    cout << "DBSCAN test" << endl;

    return EXIT_SUCCESS;
}
