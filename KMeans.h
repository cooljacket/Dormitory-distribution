#ifndef __KMEANS__H
#define __KMEANS__H


#include <stdio.h>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;


template<typename Elem>
class KMeans
{
	size_t K, size, MaxIters;
	vector<Elem> elements, centroids;
	vector<double> dist;
	vector<size_t> my_centroids;


public:
	KMeans(const vector<Elem>& elements, size_t k, size_t MaxIters)
	: K(k), size(elements.size()), MaxIters(MaxIters), elements(elements), centroids(K), dist(size), my_centroids(size) {
		Init();
	}


	void Init() {
		vector<size_t> ranks(elements.size());
		for (int i = 0; i < elements.size(); ++i)
			ranks[i] = i;
		random_shuffle(ranks.begin(), ranks.end());
		for (int i = 0; i < K; ++i)
			centroids[i] = elements[ranks[i]];

		printf("After initialization, SSE=%lf\n", SSE());
	}


	void train() {
		for (size_t iter = 0; iter < MaxIters; ++iter) {
			for (size_t e = 0; e < size; ++e) {
				dist[e] = 1e10;
				my_centroids[e] = K;
				for (size_t c = 0; c < K; ++c) {
					double distance = elements[e].dist(centroids[c]);
					if (distance < dist[e]) {
						dist[e] = distance;
						my_centroids[e] = c;
					}
				}	
			}

			for (size_t c = 0; c < K; ++c)
				centroids.clear();

			vector<size_t> count(K, 0);
			for (size_t e = 0; e < size; ++e) {
				centroids[my_centroids[e]] += elements[e];
				++count[my_centroids[e]];
			}

			for (size_t c = 0; c < K; ++c)
				centroids[c] /= count[c];

			printf("Iteration [%d], SSE=%lf\n", int(iter), SSE());
		}
	}


	double SSE() {
		double error = 0.0;

		for (size_t e = 0; e < size; ++e) {
			// double tmp = centroids[my_centroids[e]].dist(elements[e]);
			// error += tmp * tmp;
			error += centroids[my_centroids[e]].dist(elements[e]);;
		}

		return error;
	}


	void explain() const {
		for (size_t c = 0; c < K; ++c) {
			printf("In centroids [%d], there have:\n", int(c));
			for (size_t e = 0; e < size; ++e) {
				if (my_centroids[e] == c)
					elements[e].display();
			}

			printf("-----------\n\n\n");
		}
	}
};

#endif