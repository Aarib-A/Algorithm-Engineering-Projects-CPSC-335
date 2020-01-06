///////////////////////////////////////////////////////////////////////////////
// subsequence.hpp
//
// Two algorithms for solving the longest increasing subsequence problem.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <random>
#include <string>
#include <sstream>
#include <vector>

using sequence = std::vector<int>;

// Convert a sequence into a human-readable string useful for pretty-printing
// or debugging.
std::string sequence_to_string(const sequence& seq) {
	std::stringstream ss;
	ss << "[";
	bool first = true;
	for (auto& x : seq) {
		if (!first) {
			ss << ", ";
		}
		ss << x;
		first = false;
	}
	ss << "]";
	return ss.str();
}

// Generate a pseudorandom sequence of the given size, using the given
// seed, where all elements are in the range [0, max_element]. max_element
// must be non-negative.
sequence random_sequence(size_t size, unsigned seed, int max_element) {

	assert(max_element >= 0);

	sequence result;

	std::mt19937 gen(seed);
	std::uniform_int_distribution<> dist(0, max_element);

	for (size_t i = 0; i < size; ++i) {
		result.push_back(dist(gen));
	}

	return result;
}

bool is_increasing(const sequence& A) {
	for (size_t i = 1; i < A.size(); ++i) {
		// TODO
		// write the test to check if A[i-1] and A[i] are
		// in increasing order
		// if not, you need to write what needs to be done
		if (A[i - 1] >= A[i])
			return false;
	}
	return true;
}

sequence longest_increasing_end_to_beginning(const sequence& A) {

	const size_t n = A.size();

	// populate the array H with 0 values
	std::vector<size_t> H(n, 0);

	//my varirables
	//	size_t where_max_H_is_located = n - 1, max_of_H = 0;

	// calculate the values of array H
	// note that i has to be declared signed, to avoid an infinite loop, since
	// the loop condition is i >= 0
	for (size_t i = n - 2; i >= 0; i--) {
		//my code
		for (size_t j = i+1; j < n; j++)
		{
			if (A[i] < A[j] && H[i] <= H[j]) {
				H[i] = H[j] + 1;
				//break;
			}
		}

		if (i == 0) break;

	}

	// calculate in max the length of the longest subsequence
	  // by adding 1 to the maximum value in H
	auto max = *std::max_element(H.begin(), H.end()) + 1;

	// allocate space for the subsequence R
	std::vector<int> R(max);

	// add elements to R by whose H's values are in decreasing order,
	  // starting with max-1
	// store in index the H values sought
	size_t r = 0, less = max - 1;
	for (size_t i = 0; i < n ; i++) {
		
		// TODO
		// write the statements to add A[i] to the sequene R by
		// storing it into R[j], decrement index and increment j
		if (H[i] == less && r != max && less >= 0)
		{
			R[r] = A[i];
			r++;
			less--;
		}
	}


	
	return sequence(R.begin(), R.begin() + max);
}

sequence longest_increasing_powerset(const sequence& A) {
	const size_t n = A.size();
	sequence best;
	std::vector<size_t> stack(n + 1, 0);
	size_t k = 0;
	while (true) {

		if (stack[k] < n) {
			stack[k + 1] = stack[k] + 1;
			++k;
		}
		else {
			stack[k - 1]++;
			k--;
		}

		if (k == 0) {
			break;
		}

		sequence candidate;
		for (size_t i = 1; i <= k; ++i) {
			candidate.push_back(A[stack[i] - 1]);
		}
		// TODO
		   // write the if statement to test whether candidate determines
		   // an increasing sequence AND has a size larger than the size
		   // of the current best
		   // if both conditions are satisfied, then stored candidate in best
		if (is_increasing(candidate) && candidate.size() > best.size())
		{
			//for (int i = 0; i < candidate.size(); i++)
			//{
			//	//best[i] = candidate[i];
			//	best.push_back(candidate[i]);
			//}
			best = candidate;
		}
	}
	return best;
}