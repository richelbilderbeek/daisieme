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

//tests if line is SVG start tag
bool is_svg_start_tag(const std::string& s);


///Functions to create an SVG of a list of DAISIE events

///Convert the results to the text of an SVG,
///each element being a line of text.
///First line will be the XML declarator
std::vector<std::string> to_svg(const results& r);

} //~namespace elly

#endif // ELLY_SVG_H
