#include <utility>
#include <vector>
#include <string>
#include <cmath>
#include "Point.h"

#ifndef PP_KMEANS_PARTY_H
#define PP_KMEANS_PARTY_H

using namespace std;

class Party {
private:
    int partyId;
    string name;
    vector<Point> points;
    vector<vector<double>> centroids; // 2-D vector to represent centroids for different clusters.

public:
    Party(int pId, string pName, vector<Point> pPoints) {
        this->partyId = pId;
        this->name = move(pName);
        this->points = move(pPoints);
    }

    Party(int pId, string pName) {
        this->partyId = pId;
        this->name = std::move(pName);
    }

    /**
     * calculate partial Euclidean distance based on known info
     * results need to be exchange after
     * @return Euclidean Distance for different dimension
     */
    vector<double> calPartialEuDist(const Point &point) {
        vector<double> results;
        unsigned int dimensionCount = points.at(0).getAttributes().size();
        unsigned int counter = 0;
        double distance;
        for (auto &c : centroids) {
            distance = 0;
            for (int i = 0; i < dimensionCount; i++) {
                if (partyId == 0) { // alice
                    distance += pow(point.getAttributes().at(i) - c.at(i), 2);
                } else {
                    distance += pow(point.getAttributes().at(i) - c.at(c.size() - dimensionCount + i), 2);
                }
            }
            results.push_back(distance);
            counter++;
            if (counter >= dimensionCount) {
                break;
            }
        }

        return results;
    }

    void addPoint(const Point &point) {
        points.push_back(point);
    }

    void addCentroid(const vector<double> &centroid) {
        centroids.push_back(centroid);
    }

    int getPartyId() const {
        return partyId;
    }

    void setPartyId(int pId) {
        Party::partyId = pId;
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &pName) {
        Party::name = pName;
    }

    const vector<Point> &getPoints() const {
        return points;
    }

    void setPoints(const vector<Point> &pPoints) {
        Party::points = pPoints;
    }

    const vector<vector<double>> &getCentroids() const {
        return centroids;
    }

    void setCentroids(const vector<vector<double>> &centroids) {
        Party::centroids = centroids;
    }


};


#endif //PP_KMEANS_PARTY_H
