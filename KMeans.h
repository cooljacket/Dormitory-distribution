#ifndef __KMEANS__H
#define __KMEANS__H


#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <set>
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
	map<size_t, size_t> my_centroids_map;
	map<size_t, set<size_t> > my_points_map;


public:
	KMeans(const vector<Elem>& elements, size_t k, size_t MaxIters)
	: K(k), size(elements.size()), MaxIters(MaxIters), elements(elements), centroids(K), dist(size), my_centroids(size) {
		Init();
	}


	void Init() {
		srand(time(0));
		vector<size_t> ranks(size);
		for (int i = 0; i < size; ++i) {
			ranks[i] = i;
		}
		random_shuffle(ranks.begin(), ranks.end());
		for (int i = 0; i < size; ++i) {
			if (i < K) {
				my_centroids[ranks[i]] = i;
				centroids[i] = elements[ranks[i]];
				my_points_map[i].insert(ranks[i]);
				my_centroids_map[ranks[i]] = i;
				dist[ranks[i]] = 0.0;
				// printf("At first, i=%d, ranks[i]=%d\n", i, int(ranks[i]));
				// centroids[i].output();
			} else {
				// default centroid is 0
				my_centroids[ranks[i]] = 0;
				my_centroids_map[ranks[i]] = 0;
				my_points_map[0].insert(ranks[i]);
				dist[ranks[i]] = centroids[0].dist(elements[ranks[i]]);
			}
		}

		printf("After initialization, SSE=%lf\n", SSE());
	}


	void train() {
		for (size_t iter = 0; iter < MaxIters; ++iter) {
			for (size_t e = 0; e < size; ++e) {
				for (size_t c = 0; c < K; ++c) {
					double distance = elements[e].dist(centroids[c]);
					if (distance < dist[e]) {
						dist[e] = distance;
						my_centroids[e] = c;
					}
				}
			}

			for (size_t c = 0; c < K; ++c)
				centroids[c].clear();

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


	void train_inc() {
		for (size_t iter = 0; iter < MaxIters; ++iter) {
			for (size_t e = 0; e < size; ++e) {
				for (size_t c = 0; c < K; ++c) {
					double distance = elements[e].dist(centroids[c]);
					if (distance < dist[e]) {
						dist[e] = distance;
						my_centroids[e] = c;
					}
				}
				if (my_centroids[e] != my_centroids_map[e]) {
					size_t oldC = my_centroids_map[e], newC = my_centroids[e];
					// printf("hehe, change c=%d, for e=%d, oldC=%d\n", int(newC), int(e), int(oldC));

					my_centroids_map[e] = newC;
					my_points_map[oldC].erase(e);
					my_points_map[newC].insert(e);
					update_centroid(oldC);
					update_centroid(newC);
				}
			}

			printf("Iteration [%d], SSE=%lf\n", int(iter), SSE());
		}
	}


	void update_centroid(size_t c) {
		set<size_t>& points = my_points_map[c];
		set<size_t>::iterator it = points.begin();
		centroids[c].clear();
		while (it != points.end()) {
			centroids[c] += elements[*it];
			++it;
		}
		if (points.size() > 1)
			centroids[c] /= points.size();
		// printf("heheheh size=%d, c=%d\n", int(points.size()), int(c));
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
					elements[e].output(cout);
			}

			printf("-----------\n\n\n");
		}
	}

	vector<size_t> getSortedRepresentative() {
		vector<size_t> rep(K);
		for (size_t i = 0; i < K; ++i) {
			rep[i] = getBestPointInCluster(i);
		}
		sort(rep.begin(), rep.end());
		return rep;
	}


	size_t getBestPointInCluster(size_t c) {
		set<size_t>& points = my_points_map[c];
		set<size_t>::iterator it = points.begin();

		double d = 1e10, tmpD;
		size_t ans = size;
		while (it != points.end()) {
			if ((tmpD = centroids[c].dist(elements[*it])) < d) {
				d = tmpD;
				ans = *it;
			}
			++it;
		}

		return ans;
	}
};

#endif