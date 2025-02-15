#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <omp.h>

using namespace std;
typedef uint8_t datatype;
// #define DEBUG

float Hxy(std::vector<datatype> &y_true, std::vector<datatype> &y_pred)
{
    // std::map<std::pair<datatype, datatype>, float> pxy;
    // std::map<datatype, float> px;
    // std::map<datatype, float> py;
    // uint32_t countxy = y_true.size();


    /**
     if uncomment this line will parallelise the contingency matrix calucation
    be carful to change pxy to pxy[0] and px to px[0] and py to py[0] in the rest of the code
    **/
    std::map<std::pair<datatype, datatype>, float> pxy[16];
    std::map<datatype, float> px[16];
    std::map<datatype, float> py[16];
    uint32_t countxy = y_true.size();
    #pragma omp parallel
    {
        uint16_t nthreads = omp_get_num_threads();
        uint16_t chunk_size = countxy / (nthreads + 1);
        uint8_t thread_id = omp_get_thread_num();
        size_t start = thread_id * chunk_size;
        size_t end = (thread_id + 1) * chunk_size;
        for (size_t i = start; i < end; i++)
        {
            #ifdef DEBUG
            #pragma omp critical
            {
                cout << "Thread " << static_cast<int>(thread_id) << " range: " << start << "..." << end << " " << countxy << " " << static_cast<float>(y_true[i])<<" "<< static_cast<float>(y_pred[i]) << endl;
            }
            #endif
            pxy[omp_get_thread_num()][{y_true[i], y_pred[i]}] += 1./countxy;
            px[omp_get_thread_num()][y_true[i]] += 1./countxy;
            py[omp_get_thread_num()][y_pred[i]] += 1./countxy;
        }
    }

    #pragma omp master
    {
        uint16_t nthreads = omp_get_max_threads();
        uint16_t chunk_size = countxy / (nthreads + 1);

        for (size_t i = chunk_size*nthreads; i < countxy; i++)
        {
            #ifdef DEBUG
            cout << "Thread " << nthreads+1 << " range: " << chunk_size * nthreads << "..." << countxy << " " << countxy << " " << static_cast<float>(y_true[i]) << " " << static_cast<float>(y_pred[i]) << endl;
            #endif
            pxy[nthreads+1][{y_true[i], y_pred[i]}] += 1. / countxy;
            px[nthreads+1][y_true[i]] += 1. / countxy;
            py[nthreads+1][y_pred[i]] += 1. / countxy;
        }

        for (int i = 1; i < nthreads+2; i++)
        {
         #ifdef DEBUG
            cout<<"Merging thread "<<i<<endl;
            cout<<"pxy size: "<<pxy[0].size()<<endl;
         #endif
            std::for_each(pxy[i].begin(), pxy[i].end(), [&](auto &p) {
                pxy[0][p.first] += p.second;
            });

            std::for_each(px[i].begin(), px[i].end(), [&](auto &p) {
                px[0][p.first] += p.second;
            });

            std::for_each(py[i].begin(), py[i].end(), [&](auto &p) {
                py[0][p.first] += p.second;
            });
        }
    }
    

    // for (size_t i = 0; i < countxy; i++) {
    //     pxy[{y_true[i], y_pred[i]}]+=1./countxy;
    //     px[y_true[i]]+=1./countxy;
    //     py[y_pred[i]]+=1./countxy;
    // }

    float H = 0;
    #pragma omp parallel for reduction(+:H)
    for (size_t i = 0; i < pxy[0].size(); i++)
    {
        auto pxx_iterator = std::next(pxy[0].begin(),i);
        datatype x = pxx_iterator->first.first;
        datatype y = pxx_iterator->first.second;
        float h = static_cast<float>(pxy[0][{x, y}]) * log(pxy[0][{x, y}] / (px[0][x] * py[0][y])); // cambio base log in ln /log(exp(1))
    #pragma omp critical
        {
            H+= h;
            #ifdef DEBUG
            std::cout<< "(" << static_cast<int>(x)<<"  " << static_cast<int>(y) << ") ";
            std::cout << "[" << static_cast<float>(pxy[0][{x, y}] ) <<" "<<px[0][x]  << "  " << py[0][y]  << "] " << std::endl;
            #endif
        }
    }
    return H;
}

    int main(int argc, char const *argv[])
{

    std::vector<std::vector<datatype>> data;

    int ncells = 0;
    if (argc > 1)
        ncells = std::stoi(argv[1]);

    if(argc > 2){
        omp_set_num_threads(std::stoi(argv[2]));
        #pragma omp parallel master
        std::cout<<"Using threads: "<<omp_get_num_threads()<<std::endl;
    }
    //random data
    // for(int i =0;i<40;i++){
    //     auto a = std::vector<int>(1000);
    //     for (int j = 0; j < ncells; j++)
    //         a.push_back(rand() % 10);
    //     data.push_back(a);
    // }


    //easy data
    // data.push_back({1,1,2,3,1});
    // data.push_back({0,1,0,3,0});


    auto file = std::ifstream("data.csv");
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<datatype> row;
        std::string value;
        std::stringstream lineStream(line);
        while (std::getline(lineStream, value, ','))
        {
            row.push_back(std::stoi(value));
        }
        data.push_back(row);
    }
    ncells=data[0].size();
    
    auto start = std::chrono::high_resolution_clock::now();

    float result = Hxy(data[0], data[1]);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    std::cout << "Elapsed time: " << duration.count() << " seconds H=" <<result <<" cells="<<ncells<< std::endl;

    return 0;
}