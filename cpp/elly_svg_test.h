#ifndef ELLY_SVG_TEST_H
#define ELLY_SVG_TEST_H

#include <string>
#include <vector>

namespace elly {

///The tests for the daisieme project by Damian and Dave.
void svg_test();

int get_svg_width(const std::vector<std::string>& svg);

int get_svg_height(const std::vector<std::string>& svg);

} //~namespace elly

#endif // ELLY_SVG_TEST_H
