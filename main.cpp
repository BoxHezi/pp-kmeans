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
    vector<double> distances;
    double distance;
    for (int i = 0; i < clusters.size(); i++) {
        Cluster cluster = clusters.at(i);
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

//    unsigned int dimensionCount = point.getAttributes().size();
//    double minDistance = 0;
//    double distance = 0;
//    for (int i = 0; i < dimensionCount; i++) {
//        minDistance += pow(point.getAttributes().at(i) - clusters.at(0).getCentroid().at(i), 2);
//    }
//    int closetId = clusters.at(0).getClusterId();
//
//    for (int i = 1; i < clusters.size(); i++) {
//        distance = 0;
//        for (int j = 0; j < dimensionCount; j++) {
//            distance += pow(point.getAttributes().at(j) - clusters.at(i).getCentroid().at(j), 2);
//            if (distance < minDistance) {
//                minDistance = distance;
//                closetId = clusters.at(i).getClusterId();
//            }
//        }
//    }
//    return closetId;
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
    Cluster cluster1(0, points.at(500));
    Cluster cluster2(1, points.at(120));
    Cluster cluster3(2, points.at(360));

    clusters.push_back(cluster1);
    clusters.push_back(cluster2);
    clusters.push_back(cluster3);

    unsigned int dimensionCount = points.at(0).getAttributes().size();
    cout << "Dimension: " << dimensionCount << endl;

    for (int i = 0; i < iterationUpper; i++) {
        cout << "Iteration " << i + 1 << ": " << endl;
        for (int j = 0; j < points.size(); j++) {
            Point point = points.at(j);
            int closetId = findClosetCluster(point, clusters);

            if (point.getClusterId() == -1) {
                point.setClusterId(closetId);
                points.at(j) = point;
                Cluster newCluster = clusters.at(closetId);
                newCluster.addPoint(point);
                clusters.at(closetId) = newCluster;
            } else {
                if (point.getClusterId() != closetId) {
                    // TODO: REMOVE FROM A CLUSTER
                    unsigned int oldId = point.getClusterId();
                    Cluster oldCluster = clusters.at(oldId);
                    vector<Point> newPoints = oldCluster.removePoint(point);
                    oldCluster.setPoints(newPoints);
                    clusters.at(oldId) = oldCluster;

                    // TODO: ADD TO A NEW CLUSTER
                    Cluster newCluster = clusters.at(closetId);
                    newCluster.addPoint(point);
                    clusters.at(closetId) = newCluster;
                }
            }
        }

        // TODO: update centroid location
        for (int j = 0; j < k; j++) {
            vector<double> newCentroid = calculateCentroidLocation(clusters.at(j));
            clusters.at(j).setCentroid(newCentroid);
        }

//        for (int j = 0; j < k; j++) {
//            for (int l = 0; l < clusters.at(j).getCentroid().size(); l++) {
//                cout << clusters.at(j).getCentroid().at(l);
//            }
//            cout << endl;
//        }
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