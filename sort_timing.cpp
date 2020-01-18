///////////////////////////////////////////////////////////////////////////////
// sort_timing.cpp
//
// Example code showing how to run each algorithm while measuring
// elapsed times precisely. You should modify this program to gather
// all of your experimental data.
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "sort_comparison.hpp"
#include "timer.hpp"

using namespace std;

void print_bar() {
    cout << string(79, '-') << endl;
}

int main() {
    
    ofstream small_n_results;
    small_n_results.open("small_value_n_170_results.txt");
    
    
    
    
    const int MAX_SELECTION_SORT_SIZE = 20*1000;
    const int MAX_SELECTION_SORT_SIZE_MEDIUM = 50000;
    
    auto all_words = load_json_string_array("warandpeace.json");
    assert( all_words );
    
    double elapsed;
    Timer timer;
    
    
    //*** n = 2 -> n = 100
    
    //start of loop to generate values
    for(unsigned long long n = 1; n < 170; n++) {
        
        assert( n <= all_words->size() );
        
        const StringVector word_vector(all_words->begin(), all_words->begin() + n);
        assert( word_vector.size() == n );
        
        const StringList word_list(word_vector.begin(), word_vector.end());
        assert( word_list.size() == n );
        
        print_bar();
        cout << "n=" << n << endl << endl;
        
        StringVector selection_sort_solution;
        bool do_selection_sort = (n <= MAX_SELECTION_SORT_SIZE);
        if (!do_selection_sort) {
            cout << "(n too large for selection sort)" << endl;
        } else {
            selection_sort_solution = word_vector;
            timer.reset();
            selection_sort(selection_sort_solution);
            elapsed = timer.elapsed();
            cout << "selection sort elapsed time=" << elapsed << " seconds" << endl;
            small_n_results << "sel.sort: " << "\t" << elapsed << "\t";
        }
        
        timer.reset();
        auto merge_sort_list_solution = merge_sort_list(word_list);
        elapsed = timer.elapsed();
        cout << "merge sort list elapsed time=" << elapsed << " seconds" << endl;
        small_n_results << "merge sort list: " << "\t" << elapsed << "\t";
        
        timer.reset();
        auto merge_sort_vector_solution = merge_sort_vector(word_vector);
        elapsed = timer.elapsed();
        cout << "merge sort vector elapsed time=" << elapsed << " seconds" << endl;
        small_n_results << "merge sort vector: " << "\t" << elapsed << "\t";
        
        StringVector builtin_sort_solution = word_vector;
        timer.reset();
        builtin_sort(builtin_sort_solution);
        elapsed = timer.elapsed();
        cout << "builtin sort elapsed time=" << elapsed << " seconds" << endl;
        small_n_results << "builtin sort: " << "\t" << elapsed << "\t";
        small_n_results << "\n";
        
        if (do_selection_sort) {
            assert(std::equal(builtin_sort_solution.begin(),
                              builtin_sort_solution.end(),
                              selection_sort_solution.begin()));
        }
        
        assert(std::equal(builtin_sort_solution.begin(),
                          builtin_sort_solution.end(),
                          merge_sort_list_solution->begin()));
        
        assert(std::equal(builtin_sort_solution.begin(),
                          builtin_sort_solution.end(),
                          merge_sort_vector_solution->begin()));
        
        if (n >= 10) {
            print_bar();
            cout << "first 10 words alphabetically:" << endl;
            for (int i = 0; i < 10; ++i) {
                cout << builtin_sort_solution[i] << ' ';
            }
            cout << endl;
        }
        
        print_bar();
        
    }//end for loop to collect small input n = 2 -> n = 99
    small_n_results.close();
    
    
    //*** Medium values of n = 1000 -> 50 000
    
    ofstream medium_n_results;
    medium_n_results.open("medium_value_n_results.txt");
    
    //start of loop to generate values
    for(unsigned long long n = 1000; n < 50000; n+=1000) {
        
        assert( n <= all_words->size() );
        
        const StringVector word_vector(all_words->begin(), all_words->begin() + n);
        assert( word_vector.size() == n );
        
        const StringList word_list(word_vector.begin(), word_vector.end());
        assert( word_list.size() == n );
        
        print_bar();
        cout << "n=" << n << endl << endl;
        
        StringVector selection_sort_solution;
        bool do_selection_sort = (n <= MAX_SELECTION_SORT_SIZE_MEDIUM);
        if (!do_selection_sort) {
            cout << "(n too large for selection sort)" << endl;
        } else {
            selection_sort_solution = word_vector;
            timer.reset();
            selection_sort(selection_sort_solution);
            elapsed = timer.elapsed();
            cout << "selection sort elapsed time=" << elapsed << " seconds" << endl;
            medium_n_results << "sel.sort: " << "\t" << elapsed << "\t";
        }
        
        timer.reset();
        auto merge_sort_list_solution = merge_sort_list(word_list);
        elapsed = timer.elapsed();
        cout << "merge sort list elapsed time=" << elapsed << " seconds" << endl;
        medium_n_results << "merge sort list: " << "\t" << elapsed << "\t";
        
        timer.reset();
        auto merge_sort_vector_solution = merge_sort_vector(word_vector);
        elapsed = timer.elapsed();
        cout << "merge sort vector elapsed time=" << elapsed << " seconds" << endl;
        medium_n_results << "merge sort vector: " << "\t" << elapsed << "\t";
        
        StringVector builtin_sort_solution = word_vector;
        timer.reset();
        builtin_sort(builtin_sort_solution);
        elapsed = timer.elapsed();
        cout << "builtin sort elapsed time=" << elapsed << " seconds" << endl;
        medium_n_results << "builtin sort: " << "\t" << elapsed << "\t";
        medium_n_results << "\n";
        
        if (do_selection_sort) {
            assert(std::equal(builtin_sort_solution.begin(),
                              builtin_sort_solution.end(),
                              selection_sort_solution.begin()));
        }
        
        assert(std::equal(builtin_sort_solution.begin(),
                          builtin_sort_solution.end(),
                          merge_sort_list_solution->begin()));
        
        assert(std::equal(builtin_sort_solution.begin(),
                          builtin_sort_solution.end(),
                          merge_sort_vector_solution->begin()));
        
        if (n >= 10) {
            print_bar();
            cout << "first 10 words alphabetically:" << endl;
            for (int i = 0; i < 10; ++i) {
                cout << builtin_sort_solution[i] << ' ';
            }
            cout << endl;
        }
        
        print_bar();
        
    }//end for loop to collect medium input n = 1000  -> n = 50 000
    medium_n_results.close();//close the file.
    
    
    
    //*** Larger values of n = 25000 -> 550 000
    
    ofstream large_n_results;
    large_n_results.open("large_value_n_results.txt");
    
    //start of loop to generate values
    for(unsigned long long n = 25000; n < 560000; n+=25000) {
        
        assert( n <= all_words->size() );
        
        const StringVector word_vector(all_words->begin(), all_words->begin() + n);
        assert( word_vector.size() == n );
        
        const StringList word_list(word_vector.begin(), word_vector.end());
        assert( word_list.size() == n );
        
        print_bar();
        cout << "n=" << n << endl << endl;
        
        StringVector selection_sort_solution;
        bool do_selection_sort = (n <= MAX_SELECTION_SORT_SIZE);
        if (!do_selection_sort) {
            cout << "(n too large for selection sort)" << endl;
        } else {
            selection_sort_solution = word_vector;
            timer.reset();
            selection_sort(selection_sort_solution);
            elapsed = timer.elapsed();
            cout << "selection sort elapsed time=" << elapsed << " seconds" << endl;
            large_n_results << "sel.sort: " << "\t" << elapsed << "\t";
        }
        
        timer.reset();
        auto merge_sort_list_solution = merge_sort_list(word_list);
        elapsed = timer.elapsed();
        cout << "merge sort list elapsed time=" << elapsed << " seconds" << endl;
        large_n_results << "merge sort list: " << "\t" << elapsed << "\t";
        
        timer.reset();
        auto merge_sort_vector_solution = merge_sort_vector(word_vector);
        elapsed = timer.elapsed();
        cout << "merge sort vector elapsed time=" << elapsed << " seconds" << endl;
        large_n_results << "merge sort vector: " << "\t" << elapsed << "\t";
        
        StringVector builtin_sort_solution = word_vector;
        timer.reset();
        builtin_sort(builtin_sort_solution);
        elapsed = timer.elapsed();
        cout << "builtin sort elapsed time=" << elapsed << " seconds" << endl;
        large_n_results << "builtin sort: " << "\t" << elapsed << "\t";
        large_n_results << "\n";
        
        if (do_selection_sort) {
            assert(std::equal(builtin_sort_solution.begin(),
                              builtin_sort_solution.end(),
                              selection_sort_solution.begin()));
        }
        
        assert(std::equal(builtin_sort_solution.begin(),
                          builtin_sort_solution.end(),
                          merge_sort_list_solution->begin()));
        
        assert(std::equal(builtin_sort_solution.begin(),
                          builtin_sort_solution.end(),
                          merge_sort_vector_solution->begin()));
        
        if (n >= 10) {
            print_bar();
            cout << "first 10 words alphabetically:" << endl;
            for (int i = 0; i < 10; ++i) {
                cout << builtin_sort_solution[i] << ' ';
            }
            cout << endl;
        }
        
        print_bar();
        
    }//end for loop to collect large input n = 10000 -> n = 550000
    large_n_results.close();//close the file.
    
    return 0;
}


