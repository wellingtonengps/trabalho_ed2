#ifndef TRABALHO_METRICAS_H
#define TRABALHO_METRICAS_H


class Metricas {
private:
    static int comparisons;
    static int swaps;

public:
    static void incrementComparisonCount(int i){ Metricas::comparisons+=i;}
    static void incrementSwapCount(int i){ Metricas::swaps+=i;};
    static void clearMetrics(){Metricas::swaps=0; Metricas::comparisons=0;}
    static int getComparisonCount(){return Metricas::comparisons;}
    static int getSwapCount(){return Metricas::swaps;}
};


#endif //TRABALHO_METRICAS_H
