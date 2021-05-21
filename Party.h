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
    vector<double> centroids;

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
    vector<double> calPartialEuDist() {
        vector<double> results;
        unsigned int dimensionCount = points.at(0).getAttributes().size();
        double distance;
        for (auto &point : points) {
            for (auto &c : centroids) {
                distance = 0;
                for (int i = 0; i < dimensionCount; i++) {
                    if (partyId == 0) {
                        distance += pow(point.getAttributes().at(i) - centroids.at(i), 2);
                    } else {
                        distance += pow(
                                point.getAttributes().at(i) - centroids.at(centroids.size() - dimensionCount + i), 2);
                    }
                }
            }
            results.push_back(distance);
        }
        return results;
    }

    void addPoint(const Point &point) {
        points.push_back(point);
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

    const vector<double> &getCentroid() const {
        return centroids;
    }

    void setCentroid(const vector<double> &pCentroid) {
        Party::centroids = pCentroid;
    }


};


#endif //PP_KMEANS_PARTY_H
