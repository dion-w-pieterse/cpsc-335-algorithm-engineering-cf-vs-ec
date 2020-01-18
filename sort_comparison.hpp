///////////////////////////////////////////////////////////////////////////////
// sort_comparison.hpp
//
// Four sorting algorithms:
//
// - the builtin C/C++ sort
// - in-place selection sort
// - merge sort on linked lists
// - merge sort on vectors
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

// standard library headers
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

// user libraries
#include "json.hpp"

using namespace std;

// aliases for a vector or list of strings
using StringVector = std::vector<std::string>;
using StringList = std::list<std::string>;

// Load strings from the JSON file at json_path. The JSON file must
// contain precisely one array object, where each element of the array
// is a string. Returns nullptr on I/O error or parse error.
std::unique_ptr<StringVector> load_json_string_array(const std::string& json_path) {
    
    // Null object to return in the event of error.
    std::unique_ptr<StringVector> io_failure(nullptr);
    
    // First, try to load a JSON file, whatever it might contain, into
    // root.
    nlohmann::json root;
    {
        // Open file.
        std::ifstream f(json_path);
        if (!f) {
            // file not found
            return io_failure;
        }
        
        // Parse JSON.
        f >> root;
        if (!f) {
            // JSON parse error
            f.close();
            return io_failure;
        }
        
        f.close();
        // We're done with the file, so don't need to worry about closing
        // it from now on.
    }
    
    // Check that the json object is actually an array of strings.
    if (!(root.is_array() &&
          std::all_of(root.begin(),
                      root.end(),
                      [&](const nlohmann::json& element) {
                          return element.is_string();
                      }))) {
                          // We got a JSON object, but not the right type of JSON object.
                          return io_failure;
                      }
    
    // Now copy the strings out of root and into a StringVector.
    std::unique_ptr<StringVector> result(new StringVector());
    for (auto&& element : root) {
        result->push_back(element);
    }
    return result;
}

// Sort unsorted in-place, using std::sort or qsort.
void builtin_sort(StringVector& unsorted) {
    
    //run built in std sort method
    sort(unsorted.begin(), unsorted.end());
}

// Sort unsorted in-place, using selection sort.
void selection_sort(StringVector& unsorted) {
    
    //define the size of the unsorted string vector passed as argument
    const long long SIZE = unsorted.size();
    
    for(long long k = 0; k < SIZE; ++k) {
        long long least_index = k;
        //find the least string
        for(long long i = k + 1; i < SIZE; ++i) {
            //if a smaller string value is found...
            if(unsorted[i] < unsorted[least_index]) {
                //update the least index to the new index value
                least_index = i;
            }
        }
        //switch positions of strings to update sorted zone
        swap(unsorted[least_index], unsorted[k]);
    }
}

/******************************************************
 *** helper fucntion: merge (for merge_sort_vector) ***
 *****************************************************/

std::unique_ptr<StringVector> merge(unique_ptr<StringVector> L, unique_ptr<StringVector> R) {
    
    //create an empty result string vector
    unique_ptr<StringVector> S(new StringVector());
    
    //define and initialize the left and right counters for the left and right halves
    unsigned long long li = 0;
    unsigned long long ri = 0;
    
    //while the counters for left and right are less than size of L and R...
    //Notes: if either li or ri reach size then it breaks out of while
    while(li < (*L).size() && ri < (*R).size()) {
        
        //if left half value  <= right half value then add left half value to result string vector
        if((*L)[li] <= (*R)[ri]) {
            (*S).push_back((*L)[li]);
            //increment left counter
            li += 1;
        }
        else {
            //otherwise add right half value to result string vector
            (*S).push_back((*R)[ri]);
            //increment right half counter
            ri += 1;
        }
    }
    //collect up straggler values from left half string vector after right half ri counter reaches R.size()
    for(unsigned long long i = li; i < (*L).size(); ++i) {
        (*S).push_back((*L)[i]);
    }
    //collect up straggler values from right half string vector after left half li counter reaches L.size()
    for(unsigned long long i = ri; i < (*R).size(); ++i) {
        (*S).push_back((*R)[i]);
    }
    
    return S;
}

// Sort an unsorted vector using merge sort. Returns a vector
// containing the same elements as unsorted, but in nondecreasing
// order.
std::unique_ptr<StringVector> merge_sort_vector(const StringVector& unsorted) {
    
    //if the size of the string vector is 1 or less, return it as is.
    if(unsorted.size() <= 1) {
        unique_ptr<StringVector> ptr_unsorted_cpy(new StringVector(unsorted));
        return ptr_unsorted_cpy;
    }
    else {
        //define midway point of string vector
        long long HALF_LENGTH = unsorted.size() / 2;
        
        //define and initialize iterators
        StringVector::const_iterator start = unsorted.begin();
        StringVector::const_iterator half_way = unsorted.begin() + HALF_LENGTH;
        StringVector::const_iterator end_of = unsorted.end();
        
        //split the copied vector in halves (left and right)
        StringVector left_half(start, half_way);
        StringVector right_half(half_way, end_of);
        
        return merge(merge_sort_vector(left_half), merge_sort_vector(right_half));
    }
}

/***************************************
 *** helper fucntion: merge for list ***
 **************************************/

std::unique_ptr<StringList> merge_l(unique_ptr<StringList> L, unique_ptr<StringList> R) {
    
    //create an empty string list
    unique_ptr<StringList> S(new StringList());
    
    //define and initialize variables for left and right halves string lists
    unsigned long long li = 0;
    unsigned long long ri = 0;
    
    //define and initialize iterators used in left and right halves of the string list
    StringList::iterator li_it = (*L).begin();
    StringList::iterator ri_it = (*R).begin();
    
    //while counters for left and right halves are less than size of either left and right...
    while(li < (*L).size() && ri < (*R).size()) {
        
        //if value at iterator li_it is <= values at iterator ri_it
        if(*li_it <= *ri_it) {
            //add it to the result (S)
            (*S).push_back(*li_it);
            //increment li counter value
            advance(li_it, 1);
            li += 1;
        }
        else {
            //otherwise add the right iterator value to the result string list
            (*S).push_back(*ri_it);
            //increment the right counter value
            advance(ri_it, 1);
            ri += 1;
        }
    }
    //Collect up straggler values from left string list once right string list ri counter has reached R.size()
    for(unsigned long long i = li; i < (*L).size(); ++i) {
        (*S).push_back(*li_it);
        //advance left iterator, otherwise it keeps adding the same char value
        advance(li_it, 1);
    }
    //Collect up straggler values from the right string list once left string list li counter has reached L.size()
    for(unsigned long long i = ri; i < (*R).size(); ++i) {
        (*S).push_back(*ri_it);
        //advance the right iterator, otherwise it keeps adding the same char value
        advance(ri_it, 1);
    }
    //return the result string list
    return S;
}


// Sort an unsorted linked list using merge sort. Returns a linked
// list containing the same elements as unsorted, but in nondecreasing
// order.
std::unique_ptr<StringList> merge_sort_list(const StringList& unsorted) {
    
    //if size of string list is 1 or less return it
    if(unsorted.size() <= 1) {
        unique_ptr<StringList> ptr_unsorted_cpy(new StringList(unsorted));
        return ptr_unsorted_cpy;
    }
    else {
        //define half way point of main string list
        long long HALF_LENGTH = unsorted.size() / 2;
        
        //create iterator for start of string list
        StringList::const_iterator begin_it = unsorted.begin();
        
        //create half way iterator and advance to half way point
        StringList::const_iterator half_way_it = unsorted.begin();
        advance(half_way_it, HALF_LENGTH);
        
        //create iterator for end position
        StringList::const_iterator end_it = unsorted.end();
        
        //create two sub lists for left and right halves of main string list
        StringList left_half;
        StringList right_half;
        
        //set the beginning iterator for both left and right halves
        StringList::iterator begin_it_l = left_half.begin();
        StringList::iterator begin_it_r = right_half.begin();
        
        //populate left and right sublists
        left_half.insert(begin_it_l, begin_it, half_way_it);
        right_half.insert(begin_it_r, half_way_it, end_it);
        
        return merge_l(merge_sort_list(left_half), merge_sort_list(right_half));
    }
}

