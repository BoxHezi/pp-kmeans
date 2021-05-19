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
int findClosetCluster(Point point, vector<Cluster> clusters) {
    unsigned int dimensionCount = point.getAttributes().size();
    double minDistance = 0;
    double distance = 0;
    for (int i = 0; i < dimensionCount; i++) {
        minDistance += pow(point.getAttributes().at(i) - clusters.at(0).getCentroid().at(i), 2);
    }
    int closetId = clusters.at(0).getClusterId();

    for (int i = 1; i < clusters.size(); i++) {
        distance = 0;
        for (int j = 0; j < dimensionCount; j++) {
            distance += pow(point.getAttributes().at(j) - clusters.at(i).getCentroid().at(j), 2);
            if (distance < minDistance) {
                minDistance = distance;
                closetId = clusters.at(i).getClusterId();
            }
        }
    }
    return closetId;
}

vector<double> calculateCentroidLocation(Cluster cluster) {
    vector<double> newCentroid;

    unsigned int dimensionCount = cluster.getCentroid().size();
    vector<Point> tempPoints = cluster.getPoints();

    double sum = 0;
    for (int i = 0; i < dimensionCount; i++) {
        sum = 0;
        for (auto &tempPoint : tempPoints) {
            sum += tempPoint.getAttributes().at(i);
        }
        newCentroid.push_back(sum / dimensionCount);
    }

    return newCentroid;
}

Cluster findClusterById(unsigned int id, vector<Cluster> clusters) {
    for (auto &cluster : clusters) {
        if (cluster.getClusterId() == id) {
            return cluster;
        }
    }
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

    // TODO: randomly select k initial points as centroid
    Cluster cluster1(1, points.at(0));
    Cluster cluster2(2, points.at(120));
    Cluster cluster3(3, points.at(360));

    clusters.push_back(cluster1);
    clusters.push_back(cluster2);
    clusters.push_back(cluster3);

    unsigned int dimensionCount = points.at(0).getAttributes().size();
    cout << "Dimension: " << dimensionCount << endl;

    for (int i = 0; i < iterationUpper; i++) {
        cout << "Iteration " << i + 1 << ": " << endl;
        for (auto &point : points) {
            int closetId = findClosetCluster(point, clusters);
            if (point.getClusterId() != closetId) {
                Cluster oldCluster = clusters.at(closetId - 1);
                oldCluster.removePoint(point);
                clusters.at(closetId - 1) = oldCluster;

                point.setClusterId(closetId);

                Cluster newCluster = clusters.at(closetId - 1);
                newCluster.addPoint(point);
                clusters.at(closetId - 1) = newCluster;
            }
        }

        // TODO: update centroid location
        for (int j = 0; j < k; j++) {
            vector<double> newCentroid = calculateCentroidLocation(clusters.at(j));
            clusters.at(j).setCentroid(newCentroid);
        }
    }

    for (int i = 0; i < k; i++) {
        cout << clusters.at(i).getSize() << endl;
    }

//    for (int i = 0; i < k; i++) {
//        cout << "Cluster " << i + 1 << ": " << endl;
//        clusters.at(i).printPoints();
//    }

    return 0;
}