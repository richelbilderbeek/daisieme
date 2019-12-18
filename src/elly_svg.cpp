#include "elly_svg.h"

#include "elly_results.h"

#include <regex>
#include <iostream>

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

int elly::get_svg_width(const std::vector<std::string>& svg){
    std::regex rgx(".*width=\"(.*?)\".*");
    std::smatch width;
    std::regex_search(svg[1], width , rgx);
    return stoi(width[1]);
}

int elly::get_svg_height(const std::vector<std::string>& svg){
    std::regex rgx(".*height=\"(.*?)\".*");
    std::smatch height;
    std::regex_search(svg[1], height , rgx);
    return stoi(height[1]);
}


float elly::get_svg_viewbox_x1(const std::vector<std::string> &svg)
{
    std::regex rgx(".*viewBox=\"(.*?) (.*?) (.*?) (.*?)\".*");
    std::smatch viewbox;
    std::regex_search(svg[1], viewbox, rgx);

    return stof(viewbox[1]);
}

float elly::get_svg_viewbox_y1(const std::vector<std::string> &svg)
{
    std::regex rgx(".*viewBox=\"(.*?) (.*?) (.*?) (.*?)\".*");
    std::smatch viewbox;
    std::regex_search(svg[1], viewbox, rgx);

    return stof(viewbox[2]);
}

float elly::get_svg_viewbox_x2(const std::vector<std::string> &svg)
{
    std::regex rgx(".*viewBox=\"(.*?) (.*?) (.*?) (.*?)\".*");
    std::smatch viewbox;
    std::regex_search(svg[1], viewbox, rgx);

    return stof(viewbox[3]);
}

float elly::get_svg_viewbox_y2(const std::vector<std::string> &svg)
{
    std::regex rgx(".*viewBox=\"(.*?) (.*?) (.*?) (.*?)\".*");
    std::smatch viewbox;
    std::regex_search(svg[1], viewbox, rgx);

    return stof(viewbox[4]);
}

float elly::get_svg_line_x1(const std::string &svg)
{
    std::regex rgx(".*x1=\"(.*?)\".*");
    std::smatch x1;
    for (unsigned int i = 0; i < svg.size(); i++)
    {
        if (is_svg_line(svg))
        {
            std::regex_search(svg, x1, rgx);
        }
    }
    return stof(x1[1]);
}

float elly::get_svg_line_y1(const std::string &svg)
{
    std::regex rgx(".*y1=\"(.*?)\".*");
    std::smatch y1;
    for (unsigned int i = 0; i < svg.size(); i++)
    {
        if (is_svg_line(svg))
        {
            std::regex_search(svg, y1, rgx);
        }
    }

    return stof(y1[1]);
}

float elly::get_svg_line_x2(const std::string &svg)
{
    std::regex rgx(".*x2=\"(.*?)\".*");
    std::smatch x2;
    for (unsigned int i = 0; i < svg.size(); i++)
    {
        if (is_svg_line(svg))
        {
            std::regex_search(svg, x2, rgx);
        }
    }

    return stof(x2[1]);
}

float elly::get_svg_line_y2(const std::string &svg)
{
    std::regex rgx(".*y2=\"(.*?)\".*");
    std::smatch y2;
    for (unsigned int i = 0; i < svg.size(); i++)
    {
        if (is_svg_line(svg))
        {
            std::regex_search(svg, y2, rgx);
        }
    }

    return stof(y2[1]);
}

std::string elly::get_svg_line_colour(const std::string &svg)
{
    std::regex rgx(".*stroke=\"(.*?)\".*");
    std::smatch colour;
    for (unsigned int i = 0; i < svg.size(); i++)
    {
        if (is_svg_line(svg))
        {
            std::regex_search(svg, colour, rgx);
        }
    }

    return colour[1];
}



bool elly::has_time_scale_line(const std::vector<std::string> &svg){
    for(unsigned int i = 0; i < svg.size(); ++i){
        if(is_svg_line(svg[i]) &&
                get_svg_line_x1(svg[i]) == 0.0 &&
                get_svg_line_y1(svg[i]) == 1.0 &&
                get_svg_line_x2(svg[i]) == 1.0 &&     // can also add input to function (crown age variable?)
                get_svg_line_y2(svg[i]) == 1.0 &&
                get_svg_line_colour(svg[i]) == "black"){
           return is_svg_line(svg[i]);
        }
    }
  return false;
}





std::vector<std::string> elly::get_example_svg_1(){
return {
  "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
  "<svg width=\"200\" height=\"10\" viewBox=\"-10 0 10 1\" xmlns=\"http://www.w3.org/2000/svg\">",
  "<line x1=\"-1.2\" y1=\"1\" x2=\"3.4\" y2=\"1\" stroke=\"black\" />",
  "<line x1=\"0\" y1=\"1\" x2=\"1\" y2=\"1\" stroke=\"black\" />",
  "</svg>"};
}
