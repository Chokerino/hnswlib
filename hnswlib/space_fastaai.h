#pragma once
#include "hnswlib.h"
#include <stdio.h>
#include <stdlib.h>

namespace hnswlib {

    static float
    FastAAIDist(const void *pVect1v, const void *pVect2v, const void *qty_ptr) {
    char *x = (char *) pVect1v;
    char *y = (char *) pVect2v;

    std :: string filename = ".aai_filenames_hnswlib.txt";
    std :: ofstream outputfile;

    outputfile.open(filename);
    outputfile << x << "\n" << y;
    outputfile.close();

    system("comparem aai_wf aai_filenames_hnswlib.txt aai_outputs_hnswlib");
    const char * AAI_File = "aai_outputs_hnswlib/aai/aai_summary.tsv";
    std :: ifstream  fileP(AAI_File);

    std :: string labels, genomeA, genesA, genomeB, genesB, orthogenes, aai;
    std :: getline(fileP, labels, '\n'); //Header File

    std :: getline(fileP, genomeA, '\t'); //Genome A
    std :: getline(fileP, genesA, '\t'); //Genes in A
    std :: getline(fileP, genomeB, '\t'); //Genome B
    std :: getline(fileP, genesB, '\t'); //Genes in B
    std :: getline(fileP, orthogenes, '\t'); //Orthogonal Genes
    std :: getline(fileP, aai, '\t'); //AAI Score

    double result = ::atof(aai.c_str());
    system("rm -rf aai_outputs_hnswlib/");
    system("rm -f .aai_filenames_hnswlib.txt");
    return 100.0 - result;
    }

    class FastAAISpace : public SpaceInterface<float> {

        DISTFUNC<float> fstdistfunc_;
        size_t data_size_;
        size_t dim_;
    public:
        FastAAISpace(size_t dim) {
            fstdistfunc_ = FastAAIDist;
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

        ~FastAAISpace() {}
    };

}