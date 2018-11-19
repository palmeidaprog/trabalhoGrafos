#ifndef CENTROID_H
#define CENTROID_H

namespace grafos { namespace kmeans {
template <typename T = float>
class Centroid {
    T data;
public:
    Centroid(T data) : data(data) { }
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
