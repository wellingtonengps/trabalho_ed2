#ifndef TRABALHO_METRICAS_H
#define TRABALHO_METRICAS_H
#include <vector>

using namespace std;


class Metricas {
private:
    static int comparisons;
    static int swaps;
    static bool enabled;

    static double time;
    static vector<int> metricasComparison;
    static vector<double> metricasTime;
public:
    static void incrementComparisonCount(int i){ if(Metricas::enabled)Metricas::comparisons+=i;}
    static void incrementSwapCount(int i){ if(Metricas::enabled)Metricas::swaps+=i;};
    static void clearMetrics(){Metricas::swaps=0; Metricas::comparisons=0;}
    static int getComparisonCount(){return Metricas::comparisons;}
    static int getSwapCount(){return Metricas::swaps;}
    static void enable(){ Metricas::enabled=true;}
    static void disable(){ Metricas::enabled=false;}
    static void setTime(double times){Metricas::time=times;}
    static double getTime(){return Metricas::time;}
    static void incrementMedia(){metricasComparison.push_back(comparisons); metricasTime.push_back(time);}
    static void clearMedia(){metricasComparison.clear(); metricasTime.clear();};

    static int getMediaComparison(){

        int soma;

        for(int i = 0; i < metricasComparison.size(); i++){
            soma += metricasComparison[i];
        }

        return soma/metricasComparison.size();
    }

    static double getMediaTime(){

        double soma;

        for(int i = 0; i < metricasTime.size(); i++){
            soma += metricasTime[i];
        }

        return soma/metricasComparison.size();
    }
};


#endif //TRABALHO_METRICAS_H
