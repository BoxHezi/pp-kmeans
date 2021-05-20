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
    Cluster(int id, const Point& centroidPoint) {
        this->clusterId = id;
        for (double i : centroidPoint.getAttributes()) {
            this->centroid.push_back(i);
        }
    }

    void addPoint(const Point& point) {
        points.push_back(point);
    }

    void printPoints() {
        for (auto & point : points) {
            cout << "Point [" << point.getPointId() << "]: ";
            for (double j : point.getAttributes()) {
                cout << j << ", ";
            }
            cout << endl;
        }
    }

    void removePoint(const Point& point) {
        for (int i = 0; i < points.size(); i++) {
            if (points.at(i).getPointId() == point.getPointId()) {
                points.erase(points.begin() + i);
                break;
            }
        }
    }

    void printCentroid() {
        cout << "[";
        for (vector<double>::const_iterator i = centroid.begin(); i != centroid.end(); i++) {
            cout << *i;
            if (i != centroid.end() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }

    int getClusterId() const {
        return clusterId;
    }

    void setClusterId(int newClusterId) {
        Cluster::clusterId = newClusterId;
    }

    vector<double> getCentroid() const {
        return centroid;
    }

    void setCentroid(const vector<double> &newCentroid) {
        Cluster::centroid = newCentroid;
    }

    const vector<Point> &getPoints() const {
        return points;
    }

    void setPoints(const vector<Point> &newPoints) {
        Cluster::points = newPoints;
    }

    unsigned int getSize() {
        return points.size();
    }
};


#endif //PP_KMEANS_CLUSTER_H
