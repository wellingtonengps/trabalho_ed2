#ifndef TRABALHO_METRICAS_H
#define TRABALHO_METRICAS_H


class Metricas {
private:
    static int comparisons;
    static int swaps;
    static bool enabled;

public:
    static void incrementComparisonCount(int i){ if(Metricas::enabled)Metricas::comparisons+=i;}
    static void incrementSwapCount(int i){ if(Metricas::enabled)Metricas::swaps+=i;};
    static void clearMetrics(){Metricas::swaps=0; Metricas::comparisons=0;}
    static int getComparisonCount(){return Metricas::comparisons;}
    static int getSwapCount(){return Metricas::swaps;}
    static void enableMetrics(){Metricas::enabled=true;}
    static void disableMetrics(){Metricas::enabled=false;}
};


#endif //TRABALHO_METRICAS_H
