#ifndef ELLY_SVG_TEST_H
#define ELLY_SVG_TEST_H

#include <string>
#include <vector>

namespace elly {

///The tests for the daisieme project by Damian and Dave.
void svg_test();


//gives the width of the SVG
int get_svg_width(const std::vector<std::string>& svg);

//gives the height of the SVG
int get_svg_height(const std::vector<std::string>& svg);

//give viewbox coordinates
float get_svg_viewbox_x1(const std::vector<std::string> &svg);
float get_svg_viewbox_x2(const std::vector<std::string> &svg);
float get_svg_viewbox_y1(const std::vector<std::string> &svg);
float get_svg_viewbox_y2(const std::vector<std::string> &svg);



} //~namespace elly

#endif // ELLY_SVG_TEST_H
