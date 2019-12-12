#ifndef ELLY_SVG_TEST_H
#define ELLY_SVG_TEST_H

#include <string>
#include <vector>

namespace elly {

///The tests for the daisieme project by Damian and Dave.
void svg_test();

bool is_xml_declaration(const std::string& s){
    return s.substr(0,4) == "<?xml";}

bool is_svg_start_tag(const std::string& s){
    return s.substr(0,3) == "<svg";
}

bool is_svg_close_tag(const std::string& s){
    return s.substr(0,5) == "</svg>";
}

bool is_svg_line(const std::string& s){
    return s.substr(0,4) == "<line";
}

} //~namespace elly

#endif // ELLY_SVG_TEST_H
