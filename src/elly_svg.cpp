#include "elly_svg.h"

#include "elly_results.h"


bool elly::is_xml_declaration(const std::string& s){
    return s.substr(0,5) == "<?xml";}

bool elly::is_svg_start_tag(const std::string& s){
    return s.substr(0,4) == "<svg";}


bool elly::is_svg_close_tag(const std::string& s){
    return s.substr(0,6) == "</svg>";
}

bool elly::is_svg_line(const std::string& s){
    return s.substr(0,5) == "<line";
}

bool elly::is_svg(const std::vector<std::string>& svg){
    return (is_xml_declaration(svg[0]) && is_svg_start_tag(svg[1]) && is_svg_close_tag(svg.back())) ;
}

std::vector<std::string> elly::to_svg(const results&)
{
  //STUB
  return get_example_svg_1();
}





std::vector<std::string> elly::get_example_svg_1(){
return {
  "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
  "<svg width=\"200\" height=\"10\" viewBox=\"-10 0 10 1\" xmlns=\"http://www.w3.org/2000/svg\">",
  "<line x1=\"-1.2\" y1=\"1\" x2=\"3.4\" y2=\"1\" stroke=\"black\" />",
  "</svg>"};
}
