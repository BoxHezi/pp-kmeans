#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>


#ifndef PP_KMEANS_POINT_H
#define PP_KMEANS_POINT_H

using namespace std;

class Point {
private:
    int pointId;
    int clusterId = 0;
    vector<double> attributes;

public:
    Point(int id, string &data) {
        this->pointId = id;
        const char *delimiter = ",";

        stringstream is(data);

        char *value;

        int count = 0;

        do {
            char *dataChar = const_cast<char *>(data.c_str());
            value = strtok(dataChar, delimiter);

            if (data.empty()) {
                break;
            }

            // skip the first attribute as it is date
            if (count != 0) {
                // convert char pointer to double
                stringstream ss;
                ss << value;
                double d;
                ss >> d;
                attributes.push_back(d);
            }

            data = data.erase(0, strlen(value) + 1);
            count++;
        } while (value != nullptr);
    }

    int getPointId() const {
        return pointId;
    }

    void setPointId(int pointId) {
        Point::pointId = pointId;
    }

    int getClusterId() const {
        return clusterId;
    }

    void setClusterId(int clusterId) {
        Point::clusterId = clusterId;
    }

    const vector<double> &getAttributes() const {
        return attributes;
    }

    void setAttributes(const vector<double> &attributes) {
        Point::attributes = attributes;
    }


};


#endif //PP_KMEANS_POINT_H
