#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define timeNow() high_resolution_clock::now()
#define iters pow(2,8)

int main()
{
    char c;
    printf("Size    Time\n");
    ofstream trash ("trash.txt", ofstream::out);

    for(int_fast32_t i = pow(2,10); i <= pow(2,26); i *= 2)
    {
        // Create a buffer of size i and fill with random numbers
        vector<char> buffer(i);
        generate(buffer.begin(), buffer.end(), rand);

        // Create a vector of indices from 0 to i-1 and shuffle the indices at random
        vector<int_fast32_t> idxs(i);
        iota (begin(idxs), end(idxs), 0);
        random_shuffle(idxs.begin(),idxs.end());

        vector<float> times(iters);

        for(int_fast32_t j=0; j<iters;j++)
        {
            // Get random index to read from buffer
            int_fast32_t idx = idxs[j];
            // Time single byte read from buffer
            auto t1 = timeNow();
            c = buffer[idx];
            auto t2 = timeNow();
            
            // Durations in nanoseconds
            double duration = duration_cast<nanoseconds>( t2 - t1 ).count();
            times[j] = duration;
        }
        trash << c;
        double min_time = *min_element(times.begin(),times.end());

        printf("%ld  %f ns\n",i,min_time);
    }
    trash.close();
    return 0;
}