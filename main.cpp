#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Point.h"
#include "Cluster.h"
#include "Party.h"

//using namespace emp;
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

/**
 * @param argc number of arguments, need 2
 * @param argv arguments, 1st is number of K, 2nd is number of iteration
 * @return exit code
 */
int main(int argc, char **argv) {
//    char tmp[256];
//    getcwd(tmp, 256);
//    cout << "Current working directory: " << tmp << endl;

    if (argc != 3) {
        cout << "Usage: ./kmeans <k> <iteration>" << endl;
        cout << "For example: ./kemans 3 100" << endl;
        cout << "The above command will run the clustering algorithm with 3 clusters, and 100 iterations maximum"
             << endl;
        return 1;
    }

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

    int k = atoi(argv[1]);
    int iterationUpper = atoi(argv[2]);

    Party party1(0, "Alice");
    Party party2(1, "Bob");

    // Init k-points as cluster centroids
    vector<int> randomRecord;
    for (int i = 0; i < k; i++) {
        cout << i << endl;
        unsigned seed = time(nullptr);
        seed = seed + ((i + 1) * rand() % 10);
        srand(seed);
        int random = rand() % points.size();
        if (find(randomRecord.begin(), randomRecord.end(), random) !=
            randomRecord.end()) { // avoid duplicate random initial points
            i--;
            continue;
        }
        cout << random << endl;
        randomRecord.push_back(random);

        Cluster tempCluster(i, points.at(random));
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

        // UPDATE CENTROID LOCATION
        bool sameCentroid = true;
        for (auto &c : clusters) {
            unsigned int clusterId = c.getClusterId();
            vector<double> newCentroid = calculateCentroidLocation(c);
            if (newCentroid != c.getCentroid()) {
                sameCentroid = false;
                c.setCentroid(newCentroid);
                clusters.at(clusterId) = c;
            }
        }
        for (auto &c : clusters) {
            c.printCentroid();
        }
        if (sameCentroid) {
            break;
        }
    }

    cout << endl << "Clustering Done!" << endl;
    for (auto &c : clusters) {
        c.printCentroid();
    }

    return 0;
}