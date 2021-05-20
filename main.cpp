#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <cmath>
#include "Point.h"
#include "Cluster.h"

using namespace std;

/**
 * find the closet cluster
 * @param point point
 * @param clusters all clusters
 * @return cluster id of the closet cluster
 */
int findClosetCluster(const Point &point, const vector<Cluster> &clusters) {
    unsigned int dimensionCount = point.getAttributes().size();
    vector<double> distances;
    double distance;
    for (auto &cluster : clusters) {
        distance = 0;
        for (int j = 0; j < dimensionCount; j++) {
            distance += pow(point.getAttributes().at(j) - cluster.getCentroid().at(j), 2);
        }
        distances.push_back(distance);
    }

    int closetClusterId = 0;
    for (int i = 1; i < distances.size(); i++) {
        if (distances.at(i) < distances.at(closetClusterId)) {
            closetClusterId = i;
        }
    }

    return closetClusterId;
}

vector<double> calculateCentroidLocation(Cluster &cluster) {
    vector<double> newCentroid;

    unsigned int dimensionCount = cluster.getCentroid().size();
    vector<Point> tempPoints = cluster.getPoints();

    double sum;
    for (int i = 0; i < dimensionCount; i++) {
        sum = 0;
        for (auto &tempPoint : tempPoints) {
            sum += tempPoint.getAttributes().at(i);
        }
        double average = sum / (double) tempPoints.size();
        newCentroid.push_back(average);
    }

    return newCentroid;
}

int main() {
//    char tmp[256];
//    getcwd(tmp, 256);
//    cout << "Current working directory: " << tmp << endl;

    std::cout << "k-means clustering" << std::endl;

    vector<Point> points;
    vector<Cluster> clusters;

    // load csv
    ifstream inputFile;
    inputFile.open("hungary_chickenpox.csv", ios::in);
    string line;
    getline(inputFile, line); // skip the first row

    int id = 0;
    while (getline(inputFile, line)) {
        Point tempPoint(id, line);
        points.push_back(tempPoint);
        id++;
    }
    // end load csv

    int k = 3;
    int iterationUpper = 10;

//    // TODO: randomly select k initial points as centroid
//    Cluster cluster1(0, points.at(500));
//    Cluster cluster2(1, points.at(120));
//    Cluster cluster3(2, points.at(360));
//
//    clusters.push_back(cluster1);
//    clusters.push_back(cluster2);
//    clusters.push_back(cluster3);

    for (int i = 0; i < k; i++) {
        Cluster tempCluster(i, points.at(points.size() / (i + 1) - 1));
        clusters.push_back(tempCluster);
    }

    unsigned int dimensionCount = points.at(0).getAttributes().size();
    cout << "Dimension: " << dimensionCount << endl;

    for (int i = 0; i < iterationUpper; i++) {
        cout << "Iteration " << i + 1 << ": " << endl;
        for (auto &p : points) {
            int closetId = findClosetCluster(p, clusters);

            if (p.getClusterId() == -1) {
                p.setClusterId(closetId);
                Cluster newCluster = clusters.at(closetId);
                newCluster.addPoint(p);
                clusters.at(closetId) = newCluster;
            } else {
                if (p.getClusterId() != closetId) {
                    // REMOVE FROM A CLUSTER
                    Cluster oldCluster = clusters.at(p.getClusterId());
                    oldCluster.removePoint(p);
                    clusters.at(p.getClusterId()) = oldCluster;

                    p.setClusterId(closetId);

                    // ADD TO A NEW CLUSTER
                    Cluster newCluster = clusters.at(closetId);
                    newCluster.addPoint(p);
                    clusters.at(closetId) = newCluster;
                }
            }
        }
//        for (auto &c : clusters) {
//            cout << c.getClusterId() << ": " << c.getSize() << endl;
//        }

        // TODO: FIX UPDATE CENTROID LOCATION BUG
        for (auto &c : clusters) {
            unsigned int clusterId = c.getClusterId();
            vector<double> newCentroid = calculateCentroidLocation(c);
            c.setCentroid(newCentroid);
            clusters.at(clusterId) = c;
        }
    }

    for (auto &c : clusters) {
        cout << c.getSize() << endl;
    }

    return 0;
}