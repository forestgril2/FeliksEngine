#include <iostream>

#include <cassert>
#include <algorithm>
#include <vector>
#include <numeric>
#include <ctime>
#include <cmath>
#include <tuple>
#include <iostream>

using namespace std;

int main ( int argc, char** argv )
{

    clock_t begin = clock();
    clock_t end = clock();
    double elapsed_microsec;

    vector<double> v = {0,0,0};
    vector<double> speed = {1, 0.5, 0.5};
    
    vector<double> sin_table;
    vector<double> cos_table;
    vector<double> acos_table;
    
    auto AreSame = [](double a, double b)
    {
        return fabs(a - b) < std::numeric_limits<double>::epsilon();
    };
    
    double sin_table_div = 100;
    
    for (double angle = 0; angle < 720; angle += 1/sin_table_div)
    {
        sin_table.push_back(sin(M_PI*angle/180));
        cos_table.push_back(cos(M_PI*angle/180));
    }
    
    double acos_table_div = 3600;
    for (double cos = -1; cos < 1 || AreSame(cos, 1); cos += 1/acos_table_div)
    {
        acos_table.push_back(acos(cos));
    }
    
//    cout << " ### sin_table.size(): " << sin_table.size() << endl;
//    cout << " ### cos_table.size(): " << cos_table.size() << endl;
//    cout << " ### acos_table.size(): " << acos_table.size() << endl;

    auto volume = [&](double angle, double l1, double l2, double area){
//        int sinCos_table_idx = round(angle*sin_table_div);
//        auto acos_table_idx = [&](double cosVal) { return ((int)round(double(acos_table.size())/2)*(1 + cosVal));};
//        auto beta = acos_table[acos_table_idx(l2*sin_table[sinCos_table_idx]/l1)];
//        auto betaAcosFun = acos(l2*sin_table[sinCos_table_idx]/l1);
//        auto y1 = l1*sin_table[round(180*beta/M_PI*sin_table_div)];

        auto y1 = l1*sin(acos(l2*sin(M_PI*angle/180)/l1));
        auto y2 = l2*cos(M_PI*angle/180);

        auto displacement = (l1+l2)-(y1+y2);

        return displacement*area;
    };

//     clock_t begin = clock();
//     for (double angle = 0; angle < 720; angle += 1/sin_table_div)
//     {
//         auto s = sin(M_PI*angle/180);
//     }
//     clock_t end = clock();

//     double elapsed_microsec = double(end - begin);
//     cout <<  "Microseconds elapsed for sin(angle): " << elapsed_microsec << endl;

//     begin = clock();
//     for (double angle = 0; angle < 720; angle += 1/sin_table_div)
//     {
//         auto s = sin_table[round(angle*sin_table_div)];
//     }
//     end = clock();

//     elapsed_microsec = double(end - begin);
//     cout <<  "Microseconds elapsed for sin_table: " << elapsed_microsec << endl;
////-------------
//     begin = clock();
//     for (double c = -1; c <= 1; c += 1/acos_table_div)
//     {
//         auto s = acos(c);
//     }
//     end = clock();

//     elapsed_microsec = double(end - begin);
//     cout <<  "Microseconds elapsed for acos(cos): " << elapsed_microsec << endl;

//     auto acos_table_idx = [&](double cosVal) { return ((int)round(double(acos_table.size())/2)*(1 + cosVal));};
//     begin = clock();
//     for (double c = -1; c <= 1; c += 1/acos_table_div)
//     {
//         auto s = acos_table[acos_table_idx(c)];
//     }
//     end = clock();

//     elapsed_microsec = double(end - begin);
//     cout <<  "Microseconds elapsed for acos_table: " << elapsed_microsec << endl;
    
    using ParamsMinMax = vector<vector<double>> ;

    ParamsMinMax angles = {{0, 135, 225},
                          {0, 135, 225}};

    ParamsMinMax areas = {{4240,3019,1320},
                         {4240,3019,1320}};

    ParamsMinMax cams1 = {{120,120,120},
                       {120,120,120}};

    ParamsMinMax cams2 = {{35,30,30},
                       {35,30,30}};

    enum Cyl : unsigned
    {
        Fast = 0,
        In = 1,
        Out = 2,
    };

    enum Extremum : unsigned
    {
        Min = 0,
        Max = 1
    };

    auto extremalParam = [](ParamsMinMax p, Extremum e, Cyl c) {
        return p[e][c];
    };

    auto paramRange = [&](ParamsMinMax p, Cyl c, int steps = 3) {
        vector<double> ret;
        auto min = extremalParam(p, Min, c);
        auto step = (extremalParam(p, Max, c) - min)/steps;
        for (int i = 0; i < steps; i++)
        {
            ret.push_back(min + i*step);
        }
        return ret;
    };

    vector<vector<double>> fullPass; //mainRotation, V, l0, l1, l
    vector<vector<double>> solutions;
    auto fullPassIt = fullPass.begin();
    pair<decltype(fullPassIt), decltype(fullPassIt)> minMax;

    begin = clock();
    for (double fastTotalAngle = 0; fastTotalAngle < 720; fastTotalAngle += 1)
    {
        for (auto angleFast: paramRange(angles, Fast))
        for (auto cam1Fast:  paramRange(cams1,  Fast))
        for (auto cam2Fast:  paramRange(cams2,  Fast))
        for (auto areaFast:  paramRange(areas,  Fast))
        {
            v[0] = volume(angleFast + fastTotalAngle*speed[0], cam1Fast, cam2Fast, areaFast);

            for (auto angleIn: paramRange(angles, In))
            for (auto cam1In:  paramRange(cams1,  In))
            for (auto cam2In:  paramRange(cams2,  In))
            for (auto areaIn:  paramRange(areas,  In))
            {
                v[1] =   volume(angleIn +   fastTotalAngle*speed[1], cam1In, cam2In, areaIn);

                for (auto angleOut: paramRange(angles, Out))
                for (auto cam1Out:  paramRange(cams1,  Out))
                for (auto cam2Out:  paramRange(cams2,  Out))
                for (auto areaOut:  paramRange(areas,  Out))
                {
                    v[2] =  volume(angleOut +  fastTotalAngle*speed[2], cam1Out, cam2Out, areaOut);

                    vector<double> pushV = {fastTotalAngle, v[0]+v[1]+v[2]};
                    fullPass.push_back({fastTotalAngle,
                                         angleFast, cam1Fast, cam2Fast, areaFast,
                                         angleIn, cam1In, cam2In, areaIn,
                                         angleOut, cam1Out, cam2Out, areaOut,
                                         v[0]+v[1]+v[2]});
                    auto test = 1;
//                    minMax = minmax_element(fullPass.begin(), fullPass.end(), [](vector<double> a, vector<double> b) {return a[1] < b[1];} );

//                    solutions.push_back({(*minMax.second)[1]/(*minMax.first)[1],
//                                         (*minMax.first)[0], (*minMax.first)[1],
//                                         (*minMax.second)[0], (*minMax.second)[1],
//                                         angleFast, cam1Fast, cam2Fast, areaFast,
//                                         angleIn, cam1In, cam2In, areaIn,
//                                         angleOut, cam1Out, cam2Out, areaOut
//                                        });

                }
            }
        }
    }
    end = clock();
    elapsed_microsec = end - begin;
    cout <<  "Microseconds elapsed: " << elapsed_microsec << endl;

    elapsed_microsec = double(end - begin);

    int minimal = 0;
    int maximal = 0;

//    for (int i = 0; i<fullPass.size(); i++)
//    {
//        if(get<1>(fullPass[i]) < get<1>(fullPass[minimal]))
//        {
//            minimal = i;
//        }

//        if(get<1>(fullPass[i]) > get<1>(fullPass[maximal]))
//        {
//            maximal = i;
//        }
//    }

//    cout <<  "Microseconds elapsed: " << elapsed_microsec << endl;

//    cout <<  "Min volume at main rotation: " << 180*get<0>(fullPass[minimal])/M_PI << ", "  << get<1>(fullPass[minimal]) << endl;
//    cout <<  "Max volume at main rotation: " << 180*get<0>(fullPass[maximal])/M_PI << ", "  << get<1>(fullPass[maximal]) << endl;
//    cout <<  "Compression ratio: " << 180*get<0>(fullPass[maximal])/M_PI << ", "  << get<1>(fullPass[maximal])/get<1>(fullPass[minimal]) << endl;

    return ( 0 );
}
