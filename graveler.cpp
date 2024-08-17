#include <iostream>
#include <random>

#include <omp.h>

int main(void)
{
    const int seed = 42;  // fixed seed to ensure reproducibility
    
    const int nSuccesses = 177;
    const int nRepeats = 1000000000;
    const int nRolls = 231;
    
    int maxSuccesses = -1;
    
    std::cout << "Number of rolls: " << nRolls << '\n';
    std::cout << "Number of repeats: " << nRepeats << '\n';
    
    const int maxThreads = omp_get_max_threads();
    std::cout << "Using " << maxThreads << " threads.\n\n";
    
    const double start = omp_get_wtime();
    #pragma omp parallel num_threads(maxThreads)
    {
        // Initialize random number generator differently for each thread
        std::mt19937 gen(seed + omp_get_thread_num());
        std::uniform_int_distribution<int> dist(1, 4);
        
        #pragma omp for reduction(max:maxSuccesses)
        for (int i = 0; i < nRepeats; ++i)
        {
            int successes = 0;
            for (int j = 0; j < nRolls; ++j)
            {
                // Branchless: Add 1 success if we roll the digit 1
                #ifndef BRANCH
                    successes += dist(gen) == 1;
                #else
                    if (dist(gen) == 1)
                    {
                        ++successes;
                    }
                #endif
            }
            
            if (successes > maxSuccesses)
            {
                maxSuccesses = successes;
            }
        }
    }
    const double duration = omp_get_wtime() - start;
     
    std::cout << "Highest 1 roll: " << maxSuccesses <<  " / " << nSuccesses << '\n';
    std::cout << "Time taken: " << duration << " s\n";
    
    return EXIT_SUCCESS;
}
