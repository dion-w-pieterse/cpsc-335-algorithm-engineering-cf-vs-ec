
CPP = g++ -std=c++11 -Wall

all: sort_timing run_test

run_test: sort_comparison_test
	./sort_comparison_test

headers: json.hpp rubrictest.hpp timer.hpp sort_comparison.hpp

sort_comparison_test: headers sort_comparison_test.cpp
	${CPP} sort_comparison_test.cpp -o sort_comparison_test

sort_timing: headers sort_timing.cpp
	${CPP} sort_timing.cpp -o sort_timing

clean:
	rm -f sort_comparison_test sort_timing
