/*
 * cell fixed radius nearest neighbor test
 *
 */

#include <iostream>

#include "rearview/utils/fixedradnn.h"

using namespace std;

int main (int argc, char *argv[])
{
    cout << "cell fixed radius nearest neighbor test" << endl;

    double size[2] = {125.,125.};
    Cell_nn<2,20> cell (size);

    // first, we'll generate a bunch of points and add to the cellnn structure 
    //cout << "adding points" << endl;
    std::list<double*> points;
    for (size_t i=0;i<10000;++i) {
        double* x = new double ();
        x[0] = rand ()%1000 - 500; 
        x[1] = rand ()%1000 - 500;
        cell.add_point (x);
        points.push_back (x);
        //cout << x[0] << "\t" << x[1] << endl;
    }

    // print out all points in each cell
    //cout << "iding points" << endl;
    size_t id = 0;
    for (auto it=cell.cells_begin ();it!=cell.cells_end ();++it,++id) {
        std::list<double*> pts = it->second;
        for (auto&p : pts)
            cout << id << "\t" << p[0] << "\t" << p[1] << endl;
    }

    for (auto& p : points) delete p;
    return EXIT_SUCCESS;
}

