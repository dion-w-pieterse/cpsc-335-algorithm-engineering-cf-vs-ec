///////////////////////////////////////////////////////////////////////////////
// sort_comparison_test.cpp
//
// Unit tests for sort_comparison.hpp
//
///////////////////////////////////////////////////////////////////////////////

// standard library headers
#include <algorithm>
#include <cassert>

// user libraries
#include "rubrictest.hpp"

// code being tested
#include "sort_comparison.hpp"

int main() {
  
  Rubric rubric;

  const std::string a("a"), b("b"), c("c"), d("d"), e("e"), f("f"), g("g"), h("h");

  StringVector empty,
               a_only{a},
               abcdefgh{a, b, c, d, e, f, g, h},
               abc{a, b, c},
               acb{a, c, b},
	       bac{b, a, c},
	       bca{b, c, a},
	       cab{c, a, b},
	       cba{c, b, a};

  auto war_and_peace = load_json_string_array("warandpeace.json");

  StringVector war_and_peace_sorted = *war_and_peace;
  std::sort(war_and_peace_sorted.begin(), war_and_peace_sorted.end());

  rubric.criterion("load_json_string_array still works", 2,
		   [&]() {
		     TEST_TRUE("non-null", war_and_peace);
		     TEST_EQUAL("size", 566283, war_and_peace->size());
		     TEST_EQUAL("war_and_peace->at(0)", "The", war_and_peace->at(0));
		     TEST_EQUAL("war_and_peace->at(1)", "Project", war_and_peace->at(1));
		     TEST_EQUAL("war_and_peace->at(2)", "Gutenberg", war_and_peace->at(2));
		     TEST_EQUAL("war_and_peace->at(566232)", "eBooks.", war_and_peace->at(566282));
		   });

  rubric.criterion("selection_sort", 4,
		   [&]() {
		     StringVector input;

		     input = empty;
		     selection_sort(input);
		     TEST_EQUAL("empty", empty, input);

		     input = a_only;
		     selection_sort(input);
		     TEST_EQUAL("a", a_only, input);

		     input = abc;
		     selection_sort(input);
		     TEST_EQUAL("abc", abc, input);
		     input = acb;
		     selection_sort(input);
		     TEST_EQUAL("acb", abc, input);
		     input = bac;
		     selection_sort(input);
		     TEST_EQUAL("bac", abc, input);
		     input = bca;
		     selection_sort(input);
		     TEST_EQUAL("bca", abc, input);
		     input = cab;
		     selection_sort(input);
		     TEST_EQUAL("cab", abc, input);
		     input = cba;
		     selection_sort(input);
		     TEST_EQUAL("cba", abc, input);

		     StringVector perm = abcdefgh;
		     do {
		       input = perm;
		       selection_sort(input);
		       TEST_EQUAL("exhaustive permutations", abcdefgh, input);
		     } while (std::next_permutation(perm.begin(), perm.end()));

		     StringVector prefix(war_and_peace->begin(),
					 war_and_peace->begin() + 10000);

		     StringVector prefix_sorted = prefix;
		     std::sort(prefix_sorted.begin(), prefix_sorted.end());
		     
		     selection_sort(prefix);
		     TEST_EQUAL("war and peace (first 10,000 elements only)", prefix_sorted, prefix);
		   });

  rubric.criterion("merge_sort_vector", 4,
		   [&]() {
		     TEST_EQUAL("empty",
				empty,
				*merge_sort_vector(empty));

		     TEST_EQUAL("a",
				a_only,
				*merge_sort_vector(a_only));

		     TEST_EQUAL("abc", abc, *merge_sort_vector(abc));
		     TEST_EQUAL("acb", abc, *merge_sort_vector(acb));
		     TEST_EQUAL("bac", abc, *merge_sort_vector(bac));
		     TEST_EQUAL("bca", abc, *merge_sort_vector(bca));
		     TEST_EQUAL("cab", abc, *merge_sort_vector(cab));
		     TEST_EQUAL("cba", abc, *merge_sort_vector(cba));
		     
		     StringVector perm = abcdefgh;
		     do {
		       TEST_EQUAL("exhaustive permutations",
				  abcdefgh,
				  *merge_sort_vector(perm));
		     } while (std::next_permutation(perm.begin(), perm.end()));
		     
		     TEST_EQUAL("war and peace",
				war_and_peace_sorted,
				*merge_sort_vector(*war_and_peace));
		   });

  rubric.criterion("merge_sort_list", 4,
		   [&]() {
		     TEST_EQUAL("empty",
				StringList(),
				*merge_sort_list({}));

		     TEST_EQUAL("a",
				StringList({a}),
				*merge_sort_list({a}));

		     StringList abc_list{a, b, c};
		     TEST_EQUAL("abc", abc_list, *merge_sort_list({a, b, c}));
		     TEST_EQUAL("acb", abc_list, *merge_sort_list({a, c, b}));
		     TEST_EQUAL("bac", abc_list, *merge_sort_list({b, a, c}));
		     TEST_EQUAL("bca", abc_list, *merge_sort_list({b, c, a}));
		     TEST_EQUAL("cab", abc_list, *merge_sort_list({c, a, b}));
		     TEST_EQUAL("cba", abc_list, *merge_sort_list({c, b, a}));

		     StringList abcdefgh_list(abcdefgh.begin(), abcdefgh.end()),
		       perm = abcdefgh_list;
		     do {
		       TEST_EQUAL("exhaustive permutations",
				  abcdefgh_list,
				  *merge_sort_list(perm));
		     } while (std::next_permutation(perm.begin(), perm.end()));
		     
		     TEST_EQUAL("war and peace",
				StringList(war_and_peace_sorted.begin(),
					   war_and_peace_sorted.end()),
				*merge_sort_list(StringList(war_and_peace->begin(),
							    war_and_peace->end())));
		   });

  return rubric.run();
}
