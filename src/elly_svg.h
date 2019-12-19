#ifndef ELLY_SVG_H
#define ELLY_SVG_H

#include <string>
#include <vector>

namespace elly {

struct results;

//tests if line is SVG close tag
bool is_svg_close_tag(const std::string& s);

// tests if string is an XML declaration
bool is_xml_declaration(const std::string& s);

//tests if line is SVG line
bool is_svg_line(const std::string& s);

//test if line is text element
bool is_svg_text(const std::string& s);

//tests if line is SVG start tag
bool is_svg_start_tag(const std::string& s);

//Test if svg follows the svg conventions
bool is_svg(const std::vector<std::string>& svg);


//gives the width of the SVG
int get_svg_width(const std::vector<std::string>& svg);

//gives the height of the SVG
int get_svg_height(const std::vector<std::string>& svg);

//give viewbox coordinates
float get_svg_viewbox_xmin(const std::vector<std::string> &svg);
float get_svg_viewbox_ymin(const std::vector<std::string> &svg);
float get_svg_viewbox_width(const std::vector<std::string> &svg);
float get_svg_viewbox_height(const std::vector<std::string> &svg);

//gets x/y coords from a svg-line
float get_svg_line_x1(const std::string &svg);
float get_svg_line_y1(const std::string &svg);
float get_svg_line_x2(const std::string &svg);
float get_svg_line_y2(const std::string &svg);

//gets colour of svg-line
std::string get_svg_line_colour(const std::string &svg);

//Checks if svg has a timescale line
bool has_time_scale_line(const std::vector<std::string> &svg);

//Gives an example svg
std::vector<std::string> get_example_svg_1();

///Functions to create an SVG of a list of DAISIE events
std::vector<std::string> create_svg_object(const results&);

///Convert the results to the text of an SVG,
///each element being a line of text.
///First line will be the XML declarator
std::vector<std::string> to_svg(const results& r);



} //~namespace elly

#endif // ELLY_SVG_H
