#include <cassert>
#include <algorithm>
#include <vector>
#include <numeric>
#include <ctime>
#include <cmath>
#include <tuple>
#include <iostream>

using namespace std;

int main ( int argc, char** argv ) {
    
    auto volume = [&](double angle, double l1, double l2, double area){
        
        assert(l1>l2);
        
        auto beta = std::acos(l2*sin( angle )/l1);
        
        auto y1 = l1*sin(beta);
        auto y2 = l2*cos( angle );
        
        auto displacement = (l1+l2)-(y1+y2);

        return displacement*area;
    };
    
    vector<double> v = {0,0,0};
    vector<double> speed = {1, 0.5, 0.5};
    
    using ParamsMinMax = vector<vector<double>> ;
    
    ParamsMinMax angles = {{0, 110*M_PI/180, 200*M_PI/180},
                          {0, 160*M_PI/180, 250*M_PI/180}};
                                    
    ParamsMinMax areas = {{3200,1500,700},
                         {5200,4500,2300}};
                                   
    ParamsMinMax cams1 = {{80,80,80},
                       {160,160,160}};
                                 
    ParamsMinMax cams2 = {{15,15,15}, 
                       {65,65,65}};
                       
    enum Cyl : unsigned
    {
        Main = 0,
        Aux1 = 1,
        Aux2 = 2,
    };
    
    enum Extremum : unsigned
    {
        Min = 0,
        Max = 1
    };
    
    auto extremalParam = [](ParamsMinMax p, Extremum e, Cyl c) {
        return p[e][c];
    };
    
    auto paramRange = [&](ParamsMinMax p, Cyl c, int steps = 1) {
        vector<double> ret;
        auto min = extremalParam(p, Min, c);
        auto step = (extremalParam(p, Max, c) - min)/steps; 
        for (int i = 0; i < steps; i++)
        {
            ret.push_back(min + i*step);
        }
        return ret;
    };
    
    vector<tuple<double, double>> fullData; //mainRotation, V, l0, l1, l
    
    clock_t begin = clock();


    for (auto angle: paramRange(angles, static_cast<Cyl>(0)))
    for (auto cam1:  paramRange(cams1,  static_cast<Cyl>(0)))
    for (auto cam2:  paramRange(cams2,  static_cast<Cyl>(0)))
    for (auto area:  paramRange(areas,  static_cast<Cyl>(0)))    
        
    for (double mainRotation = 0; mainRotation < 4*M_PI; mainRotation += 2*M_PI/360)
    {
        for (double mainRotation = 0; mainRotation < 4*M_PI; mainRotation += 2*M_PI/360)
        {
            
                    v[i] = volume(angle + mainRotation*speed[i], cam1, cam2, area);
            fullData.push_back({mainRotation, accumulate(v.begin(), v.end(), 0)});
        }
    }
    
  clock_t end = clock();
  
    double elapsed_microsec = double(end - begin);
  
    int minimal = 0;
    int maximal = 0;
    
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
    cout <<  "Compression ratio: " << 180*get<0>(fullData[maximal])/M_PI << ", "  << get<1>(fullData[maximal])/get<1>(fullData[minimal]) << endl;

    return ( 0 );
}
