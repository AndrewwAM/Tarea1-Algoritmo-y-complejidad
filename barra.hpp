#include <iostream>
#include <string>
#include <bits/stdc++.h>

//writes a progress bar to the console
void progressBar(int max, int progress, int barWidth = 70) {
    float percentage = (float)progress / max;
    int pos = barWidth * percentage;

    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(percentage * 100.0) << " %\r";
    std::cout.flush();
}
