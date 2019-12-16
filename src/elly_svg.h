#ifndef ELLY_SVG_H
#define ELLY_SVG_H

#include <string>
#include <vector>

namespace elly {

struct results;

///Functions to create an SVG of a list of DAISIE events

///Convert the results to the text of an SVG,
///each element being a line of text.
///First line will be the XML declarator
std::vector<std::string> to_svg(const results& r);

} //~namespace elly

#endif // ELLY_SVG_H
