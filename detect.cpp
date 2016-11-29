#include <stdio.h>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#define IGNORE_BELOW 10
#define MINIMUM_SPREAD 20
#define MINIMUM_INCREASE 10
#define KNOCK_INTERVAL 8

int getMax(vector<int> data, int index, int size)
{
    vector<int> slice;
    
    for (int i = index; i < index + size; ++i) {
        slice.push_back(data.at(i));
    }
    
    if (slice.size() == 0) {
        return 0;
    }
    
    sort(slice.begin(), slice.end());
    
    return abs(slice.front() - slice.back());
}

int main()
{
    vector<int> data;
    vector<int> potential_peaks;

    for (int i = 0; i < 870; ++i) {
        int temp;
        scanf("%d", &temp);
        data.push_back(temp);
    }
    
    int last_spread = 0;
    int spread = 0;
    
    for (int i = 0; i < data.size() - 4; ++i) {
	    last_spread = spread;
	    spread = getMax(data, i, 4);
	    
	    if (spread < MINIMUM_SPREAD) {
	        continue;
	    }
	    
	    if (spread - last_spread < MINIMUM_INCREASE) {
	        continue;
	    }
	    
	    if (potential_peaks.size() > 0 && i - potential_peaks.back() <= KNOCK_INTERVAL) {
	        potential_peaks.pop_back();
	    }
	    
	    //printf("%d %d %d\n", i, last_spread, spread);
	    potential_peaks.push_back(i);

        /*if (abs(node) < IGNORE_BELOW) {
            continue;
        }

        if (abs(node - previous_node) < MINIMUM_INCREASE) {
	        continue;
	    }

	    if (abs(next_node - node) < IGNORE_BELOW * 2) {
	        continue;
	    }
	    
	    int last_extreme = data.at(extremes.back());
	    if (last_extreme >= node)
	    
	    extremes.push_back(i);

        if (potential_peaks.size() == 0) {
            potential_peaks.push_back(i);
            continue;
        }

	    int last_potential_peak_id = potential_peaks.back();
        if (i - last_potential_peak_id >= KNOCK_INTERVAL) {
            potential_peaks.push_back(i);
            continue;
        }

	    if (data.at(last_potential_peak_id) <= node) {
	        potential_peaks.pop_back();
	        potential_peaks.push_back(i);
	    }*/
    }

    for (int i = 0; i < potential_peaks.size(); ++i) {
	    int potential_peak_id = potential_peaks.at(i);
	    printf("%d %d\n", potential_peak_id, data.at(potential_peak_id));
    }
}
