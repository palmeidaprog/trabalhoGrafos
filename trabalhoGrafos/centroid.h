#ifndef CENTROID_H
#define CENTROID_H

namespace grafos { namespace kmeans {
template <typename T = float>
class Centroid {
    T data;
    float x, y;
public:
    Centroid(T data) : data(data), x(0), y(0) { }
    Centroid(T data, float x, float y) : data(data), x(x), y(y) { }
    ~Centroid() { }

    T getData() const {
        return data;
    }

    void setData(T data) {
        Centroid::data = data;
    }


};
}}

#endif // CENTROID_H
