#pragma once

#include "fourier.hpp"
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;

const int MAX_THREADS = 16;

void check_all_functions(int n, int default_mx, const vector<Fourier>& functions) {
    printf("start checking, n = %d\n", n);

    atomic<T> global_mx{static_cast<double>(default_mx)};
    mutex print_mutex;

    auto process_chunk = [&](ULL start_i, ULL end_i, int thread_id) {
        T local_mx = default_mx;
        ULL total_iterations = end_i - start_i;
        ULL progress_step = max(1ULL, total_iterations / 10);
        ULL next_progress = start_i + progress_step;
        printf("Thread %d processing range [%llu, %llu)\n", thread_id, start_i, end_i);
        
        for (ULL i = start_i; i < end_i; ++i) {
            if (i >= next_progress) {
                ULL progress_percent = ((i - start_i) * 100) / total_iterations;
                {
                    lock_guard<mutex> lock(print_mutex);
                    printf("Thread %d: %d%% complete\n", thread_id, progress_percent);
                }
                next_progress += progress_step;
            }
            
            T mi = functions[i].measure();
            for (ULL j = i + 1; j < functions.size(); ++j) {
                T mj = functions[j].measure();
                Fourier h = functions[i].AND(functions[j]);
                T mh = h.measure();
                if (local_mx * max(mi, mj) < mh) {
                    local_mx = mh / max(mi, mj);
                    {
                        lock_guard<mutex> lock(print_mutex);
                        printf("Thread %d found new local max: i = %llu, j = %llu, mx = %.8f\n", thread_id, i, j, local_mx);
//                        printf("Нашел!\n");
//                        printf("f = %s\n", functions[i].name.c_str());
//                        functions[i].print_all_values_fourier();
//                        functions[i].print_measure();
//                        printf("g = %s\n", functions[j].name.c_str());
//                        functions[j].print_all_values_fourier();
//                        functions[j].print_measure();
//                        printf("h = %s\n", h.name.c_str());
//                        h.print_all_values_fourier();
//                        h.print_measure();
                    }
                }
            }
        }
        // Update global maximum
        T current_mx = global_mx.load();
        while (local_mx > current_mx) {
            if (global_mx.compare_exchange_weak(current_mx, local_mx)) {
                break;
            }
        }
    };

    // Create and start threads
    vector<thread> threads;
    ULL num_functions = functions.size();
    ULL chunk_size = (num_functions + MAX_THREADS - 1) / MAX_THREADS;
    
    for (int t = 0; t < MAX_THREADS; ++t) {
        ULL start_i = t * chunk_size;
        ULL end_i = min(start_i + chunk_size, num_functions);
        threads.emplace_back(process_chunk, start_i, end_i, t);
    }

    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }

    printf("END\n");
    printf("final mx = %.8f\n", global_mx.load());
}