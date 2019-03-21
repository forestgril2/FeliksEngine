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
    vector<double> v = {0,0,0};
    vector<double> speed = {1, 0.5, 0.5};

    auto volume = [&](vector<double> paramsPerCyl) {
        double angle = paramsPerCyl[0];
        double l1 =    paramsPerCyl[1];
        double l2 =    paramsPerCyl[2];
        double area =  paramsPerCyl[3];

        auto y1 = l1*sin(acos(l2*sin(M_PI*angle/180)/l1));
        auto y2 = l2*cos(M_PI*angle/180);

        auto displacement = (l1+l2)-(y1+y2);

        return displacement*area;
    };
    
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

    auto paramRange = [&](ParamsMinMax p, Cyl c, int steps = 2) {
        vector<double> ret;
        auto min = extremalParam(p, Min, c);
        auto step = (extremalParam(p, Max, c) - min)/steps;
        for (int i = 0; i < steps; i++)
        {
            ret.push_back(min + i*step);
        }
        return ret;
    };

    auto getRandomParamForRange = [](double& param, vector<double> range) {
        param = range[0] + (range[range.size()-1] - range[0])*(static_cast<double>(random())/static_cast<double>(RAND_MAX));
        return param;
    };

    vector<double> solution;
    vector<vector<double>> fullPass, solutions; //({fastTotalAngle, v[0]+v[1]+v[2]});
    auto fullPassIt = fullPass.begin();
    pair<decltype(fullPassIt), decltype(fullPassIt)> minMax;

    random();


    double angleFast = getRandomParamForRange(angleFast, paramRange(angles, Fast));
    double cam1Fast =  getRandomParamForRange(cam1Fast,  paramRange(cams1,  Fast));
    double cam2Fast =  getRandomParamForRange(cam2Fast,  paramRange(cams2,  Fast));
    double areaFast =  getRandomParamForRange(areaFast,  paramRange(areas,  Fast));
    double angleIn =   getRandomParamForRange(angleIn, paramRange(angles, In));
    double cam1In =    getRandomParamForRange(cam1In,  paramRange(cams1,  In));
    double cam2In =    getRandomParamForRange(cam2In,  paramRange(cams2,  In));
    double areaIn =    getRandomParamForRange(areaIn,  paramRange(areas,  In));
    double angleOut =  getRandomParamForRange(angleOut, paramRange(angles, Out));
    double cam1Out =   getRandomParamForRange(cam1Out,  paramRange(cams1,  Out));
    double cam2Out =   getRandomParamForRange(cam2Out,  paramRange(cams2,  Out));
    double areaOut =   getRandomParamForRange(areaOut,  paramRange(areas,  Out));

    double compressRat = 100;
    double compressRatPrev = 1000;
    double compressRatDeltaMin = 0.0001;

    long passes = 0;
    long maxPasses = 100;

    auto bestCompressionRatioForParamSet = [&](vector<vector<double>> paramsAllCyls){
        auto begin = clock();
        for (double fastTotalAngle = 0; fastTotalAngle < 720; fastTotalAngle += 1)
        {
            auto paramsCylFast = paramsAllCyls[0];
            auto paramsCylIn =   paramsAllCyls[1];
            auto paramsCylOut =  paramsAllCyls[2];

            paramsCylFast[0] = angleFast + fastTotalAngle*speed[0];
            paramsCylIn[0] =   angleIn +   fastTotalAngle*speed[1];
            paramsCylOut[0] =  angleOut +  fastTotalAngle*speed[2];

            v[0] = volume(paramsCylFast);
            v[1] = volume(paramsCylIn);
            v[2] = volume(paramsCylOut);

            vector<double> pushV = {fastTotalAngle, v[0]+v[1]+v[2]};
            fullPass.push_back(pushV);
        }

        minMax = minmax_element(fullPass.begin(),
                                fullPass.end(),
                                [](vector<double> a, vector<double> b) {return a[1] < b[1];} );


        auto end = clock();
        auto elapsed_microsec = end - begin;
        cout <<  "Microseconds elapsed: " << elapsed_microsec << endl;
        auto compressionRatio = (*minMax.second)[1]/(*minMax.first)[1];
        cout <<  "CompressionRatio : " << compressionRatio  << endl;
        return compressionRatio;
    };

    auto getCompressionRatioDifferentialForParam = [&](vector<vector<double>> allCylParams, ulong cyl, ulong param) {
        auto relative_epsilon = 0.00001;
        allCylParams[cyl][param] *= (1 + relative_epsilon);
        return (bestCompressionRatioForParamSet(allCylParams) - compressRat)/relative_epsilon;
    };

    do
    {
//        auto solution = {compressRat,
//                (*minMax.first)[0], (*minMax.first)[1],
//                (*minMax.second)[0], (*minMax.second)[1],
//                angleFast, cam1Fast, cam2Fast, areaFast,
//                angleIn, cam1In, cam2In, areaIn,
//                angleOut, cam1Out, cam2Out, areaOut
//               };

        auto paramsCylFast = {angleFast, cam1Fast, cam2Fast, areaFast};
        auto paramsCylIn =   {angleIn, cam1In, cam2In, areaIn};
        auto paramsCylOut =  {angleOut, cam1Out, cam2Out, areaOut};

        vector<vector<double>> allCylParams = {paramsCylFast, paramsCylIn, paramsCylOut};

        compressRat = bestCompressionRatioForParamSet(allCylParams);

        vector<vector<double>> compressionRatioPartialDifferentials;
        compressionRatioPartialDifferentials.resize(allCylParams.size());

        for (ulong cyl = 0; cyl < compressionRatioPartialDifferentials.size(); ++cyl)
        {
            compressionRatioPartialDifferentials[cyl].resize(allCylParams[cyl].size());

            for (ulong param = 0; param < compressionRatioPartialDifferentials[cyl].size(); ++param)
            {
                compressionRatioPartialDifferentials[cyl][param] = getCompressionRatioDifferentialForParam(allCylParams, cyl,param);
            }
        }

        fullPass.clear();

        passes++;
        cout <<  "passes: " << passes << endl;
    }
    while (abs((compressRat - compressRatPrev)/compressRat) >= compressRatDeltaMin && passes <= maxPasses);


//    cout <<  "Min volume at main rotation: " << 180*get<0>(fullPass[minimal])/M_PI << ", "  << get<1>(fullPass[minimal]) << endl;
//    cout <<  "Max volume at main rotation: " << 180*get<0>(fullPass[maximal])/M_PI << ", "  << get<1>(fullPass[maximal]) << endl;
//    cout <<  "Compression ratio: " << 180*get<0>(fullPass[maximal])/M_PI << ", "  << get<1>(fullPass[maximal])/get<1>(fullPass[minimal]) << endl;

    return ( 0 );
}
