// VolEsti (volume computation and sampling library)

// Copyright (c) 20012-2018 Vissarion Fisikopoulos
// Copyright (c) 2018 Apostolos Chalkis

// Licensed under GNU LGPL.3, see LICENCE file

#ifndef ZONOTOPE_EXACT_VOL_H
#define ZONOTOPE_EXACT_VOL_H

#include <algorithm>
#include <iostream>
#include <string>

// From rosetta code at http://rosettacode.org/wiki/Combinations#C.2B.2B
// We made some adjustments to vectorize the output
std::vector< std::vector<int> > comb(int N, int K)
{
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's
    std::vector<int> iter_comb(K,0);
    std::vector<std::vector<int> > combs;
    int count;

    // print integers and permute bitmask
    do {
        count = 0;
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i]){
                std::cout << " " << i;
                iter_comb[count] = i;
                count++;
            }
        }
        combs.push_back(iter_comb);
        std::cout << std::endl;
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    return combs;
}


template <typename NT, class Polytope>
NT exact_zonotope_vol(Polytope ZP){

    typedef typename Polytope::MT 	MT;
    typedef typename Polytope::VT 	VT;

    int n = ZP.dimension();
    int k = ZP.num_of_generators();
    MT V = ZP.get_mat().transpose();
    std::cout<<V<<"\n"<<std::endl;
    NT vol = 0.0;

    std::vector< std::vector<int> > combs = comb(k, n);
    std::vector< std::vector<int> >::iterator iter_combs;
    std::vector<int>::iterator it;

    int col;
    MT SubV(n,n);

    iter_combs = combs.begin();
    for ( ;  iter_combs!=combs.end(); ++iter_combs) {
        it = (*iter_combs).begin();
        col = 0;
        for ( ;  it!=(*iter_combs).end(); ++it, ++col) {
            SubV.col(col) = V.col(*it);
        }
        std::cout<<"\n"<<SubV<<std::endl;
        vol += std::abs(SubV.determinant());
    }
    return vol;
}

#endif
