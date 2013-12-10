/*
 * cell fixed radius nearest neighbor test
 *
 */

#include <iostream>
#include <fstream>

#include "rearview/utils/fixedradnn.h"

using namespace std;

int main (int argc, char *argv[])
{
    cout << "cell fixed radius nearest neighbor test" << endl;

    double size[2] = {225.,225.};
    Cell_nn<2,3> nnbrs (size);

    // first, we'll generate a bunch of points and add to the cellnn structure 
    list<double*> points;
    for (size_t i=0;i<10000;++i) {
        double* x = new double[2];
        x[0] = rand ()%1000 - 500; 
        x[1] = rand ()%1000 - 500;
        nnbrs.add_point (x);
        points.push_back (x);
    }

    // print out all points in each cell
    ofstream fpts ("pts.txt");
    size_t id = 0;
    for (auto it=nnbrs.cells_begin ();it!=nnbrs.cells_end ();++it,++id) {
        list<const double*> pts = it->second;
        for (auto&p : pts)
            fpts << id << "\t" << p[0] << "\t" << p[1] << endl;
    }

    // query point
    double qpt[2] = {125.,-75.};
    list<pair<double,const double*> > nn = nnbrs.points_in_radius (qpt, 150);

    ofstream fnn ("nn.txt");
    for (auto& n : nn) {
        fnn <<  n.second[0] << "\t" << n.second[1] << endl;
    }

    for (auto& p : points) delete[] p;
    return EXIT_SUCCESS;
}

