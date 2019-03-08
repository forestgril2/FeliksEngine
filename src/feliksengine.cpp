#include "headers/std_lib_facilities.h"
#include <cassert>
#include <algorithm>
#include <vector>
#include <numeric>
#include <ctime>

int main ( int argc, char** argv ) {
    //your code goes here
    
    auto volume = [&](double angle, double l1, double l2, double area){
        
        assert(l1>l2);
        
        auto beta = std::acos(l2*sin( angle )/l1);
        
        auto y1 = l1*sin(beta);
        auto y2 = l2*cos( angle );
        
        auto displacement = (l1+l2)-(y1+y2);

        return displacement*area;
    };
    
    std::vector<double> v = {0,0,0};
    vector<double> speed = {1, 0.5, 0.5};
    vector<double> alpha = {0, 135*M_PI/180, 225*M_PI/180};
    vector<double> area = {4200,3000,1300};
    vector<double> l1 = {120,120,120};
    vector<double> l2 = {35,30,30};
    
    vector<tuple<double, double>> fullData; //mainRotation, V
    
    for(int i = 0; i < l1.size(); i++)
    {
        assert(l1[i]>l2[i]);
    }
    
    clock_t begin = clock();

    
    for (double mainRotation = 0; mainRotation < 4*M_PI; mainRotation += 2*M_PI/360)
    {
        for(int i = 0; i < l1.size(); i++)
        {
            v[i] = volume(alpha[i] + mainRotation*speed[i], l1[i], l2[i], area[i]);
        }
        
        fullData.push_back({mainRotation, accumulate(v.begin(), v.end(), 0)});
    }
    
  clock_t end = clock();
  
    double elapsed_microsec = double(end - begin);
  
    int minimal = 0;
    int maximal = 0;
    
    double maxVal = 0;
    double minVal = 100000000000;
    
    for (int i = 0; i<fullData.size(); i++)
    {
        if(get<1>(fullData[i]) < get<1>(fullData[minimal]))
        {
            minimal = i;
        }
        
        if(get<1>(fullData[i]) > get<1>(fullData[maximal]))
        {
            maximal = i;
        }
    }

    cout <<  "Microseconds elapsed: " << elapsed_microsec << endl;
    
    cout <<  "Min volume at main rotation: " << 180*get<0>(fullData[minimal])/M_PI << ", "  << get<1>(fullData[minimal]) << endl;
    cout <<  "Max volume at main rotation: " << 180*get<0>(fullData[maximal])/M_PI << ", "  << get<1>(fullData[maximal]) << endl;

    return ( 0 );
}
