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

//gets x/y coords from a svg-line
float get_svg_line_x1(const std::string &svg);
float get_svg_line_y1(const std::string &svg);
float get_svg_line_x2(const std::string &svg);
float get_svg_line_y2(const std::string &svg);

//gets colour of svg-line
std::string get_svg_line_colour(const std::string &svg);

//Checks if svg has a timescale line
bool has_time_scale_line(const std::vector<std::string> &svg);


} //~namespace elly

#endif // ELLY_SVG_TEST_H
