/*
 * dbscan test:
 * We generate a number of points from several normal distributions and then
 * cluster. This test outputs the point locations for each cluster. 
 *
 * The output (stored as a file) can easily be plotted with Python's
 * matplotlib:
 *      >> import numpy as np
 *      >> import matplotlib.pyplot as plt
 *      >> d = np.loadtxt ('clustsers.txt')
 *      >> plt.scatter (d[:,0],d[:,1],c=d[:,0],cmap=plt.cm.jet,edgecolor='none')
 *      >> plt.show ()
 */

#include <cmath>
#include <iostream>
#include <fstream>
#include <random>

#include "rearview/utils/dbscan.h"

using namespace std;

int main (int argc, char *argv[])
{
    cout << "DBSCAN test" << endl;

    // random pt parameters
    default_random_engine gen;
    normal_distribution<double> p_x0 (0.,5.);
    normal_distribution<double> p_y0 (0.,10.);
    normal_distribution<double> p_r1 (50.,3.);
    normal_distribution<double> p_t1 (0.,M_PI);

    double eps = 5.;
    size_t minpts = 5;
    rearview::DBSCAN<2,15> db (eps, minpts);

    // add points
    list<double*> points;
    ofstream fpts ("pts.txt");
    for (size_t i=0;i<1000;++i) {
        double* x0 = new double[2];
        x0[0] = p_x0 (gen);
        x0[1] = p_y0 (gen);
        db.add_point (x0);
        fpts << x0[0] << "\t" << x0[1] << endl;

        double* x1 = new double[2];
        double r = p_r1 (gen), t = p_t1 (gen);
        x1[0] = r*cos (t);
        x1[1] = r*sin (t);
        db.add_point (x1);
        fpts << x1[0] << "\t" << x1[1] << endl;
    }

    // cluster
    db.cluster ();

    ofstream fcl ("cluster.txt");
    size_t id=0;
    for (auto it=db.clusters_begin ();it!=db.clusters_end ();++it,++id) {
        for (auto&p : *it)
            fcl << id << "\t" << p[0] << "\t" << p[1] << endl;
    }

    for (auto& p : points) delete[] p;
    return EXIT_SUCCESS;
}
