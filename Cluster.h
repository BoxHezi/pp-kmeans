#include <vector>
#include "Point.cpp"

#ifndef PP_KMEANS_CLUSTER_H
#define PP_KMEANS_CLUSTER_H

using namespace std;

class Cluster {
private:
    int clusterId;
    vector<double> centroid;
    vector<Point> points;

public:
    Cluster(int id, Point centroidPoint) {
        this->clusterId = id;
        for (double i : centroidPoint.getAttributes()) {
            this->centroid.push_back(i);
        }
    }

    void addPoint(Point point) {
        points.push_back(point);
    }

    void printPoints() {
        for (int i = 0; i < points.size(); i++) {
            cout << "Point [" << points.at(i).getPointId() << "]: ";
            for (double j : points.at(i).getAttributes()) {
                cout << j << ", ";
            }
            cout << endl;
        }
    }

    void removePoint(Point point) {
        for (int i = 0; i < points.size(); i++) {
            if (points.at(i).getPointId() == point.getPointId()) {
                points.erase(points.begin() + i);
            }
        }
    }

    int getClusterId() const {
        return clusterId;
    }

    void setClusterId(int clusterId) {
        Cluster::clusterId = clusterId;
    }

    const vector<double> &getCentroid() const {
        return centroid;
    }

    void setCentroid(const vector<double> &centroid) {
        Cluster::centroid = centroid;
    }

    const vector<Point> &getPoints() const {
        return points;
    }

    void setPoints(const vector<Point> &points) {
        Cluster::points = points;
    }

    unsigned int getSize() {
        return points.size();
    }
};


#endif //PP_KMEANS_CLUSTER_H
