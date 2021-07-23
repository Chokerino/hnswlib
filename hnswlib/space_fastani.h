#pragma once
#include "hnswlib.h"
#include <stdio.h>
#include <stdlib.h>
#include "cgi/calDist.hpp"

namespace hnswlib {

    static float
    FastANIDist(const void *pVect1v, const void *pVect2v, const void *qty_ptr) {
        char *pVect1 = (char *) pVect1v;
        char *pVect2 = (char *) pVect2v;


        char* command[] = {"./fastANI", "-q", pVect1, "-r" , pVect2};
        float result = dist::getDistance(command);
        return 100.0 - result;
    }

    class FastANISpace : public SpaceInterface<float> {

        DISTFUNC<float> fstdistfunc_;
        size_t data_size_;
        size_t dim_;
    public:
        FastANISpace(size_t dim) {
            fstdistfunc_ = FastANIDist;
            dim_ = dim;
            data_size_ = dim * sizeof(std::array<char, 500>);
        }

        size_t get_data_size() {
            return data_size_;
        }

        DISTFUNC<float> get_dist_func() {
            return fstdistfunc_;
        }

        void *get_dist_func_param() {
            return &dim_;
        }

        ~FastANISpace() {}
    };

}