#include "elly_svg.h"

#include "elly_results.h"

#include <regex>
#include <iostream>
#include <sstream>

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

bool elly::is_svg_text(const std::string& s){
    return s.substr(0,5) == "<text";
}

bool elly::is_svg(const std::vector<std::string>& svg){
    return (is_xml_declaration(svg[0]) && is_svg_start_tag(svg[1]) && is_svg_close_tag(svg.back())) ;
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

float elly::get_svg_viewbox_xmin(const std::vector<std::string> &svg)
{
    std::regex rgx(".*viewBox=\"(.*?) (.*?) (.*?) (.*?)\".*");
    std::smatch viewbox;
    std::regex_search(svg[1], viewbox, rgx);

    return stof(viewbox[1]);
}

float elly::get_svg_viewbox_ymin(const std::vector<std::string> &svg)
{
    std::regex rgx(".*viewBox=\"(.*?) (.*?) (.*?) (.*?)\".*");
    std::smatch viewbox;
    std::regex_search(svg[1], viewbox, rgx);

    return stof(viewbox[2]);
}

float elly::get_svg_viewbox_width(const std::vector<std::string> &svg)
{
    std::regex rgx(".*viewBox=\"(.*?) (.*?) (.*?) (.*?)\".*");
    std::smatch viewbox;
    std::regex_search(svg[1], viewbox, rgx);

    return stof(viewbox[3]);
}

float elly::get_svg_viewbox_height(const std::vector<std::string> &svg)
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

int elly::get_svg_line_ID(const std::string &svg){
    std::regex rgx(".*id=\"(.*?)\".*");
    std::smatch ID;
    for (unsigned int i = 0; i < svg.size(); i++)
    {
        if (is_svg_line(svg))
        {
            std::regex_search(svg, ID, rgx);
        }
    }
    return stoi(ID[1]);
}



bool elly::has_time_scale_line(const std::vector<std::string> &svg){
    for(unsigned int i = 0; i < svg.size(); ++i){
        if(is_svg_line(svg[i]) && get_svg_line_ID(svg[i]) == -1 &&
                get_svg_line_colour(svg[i]) == "black" &&
                get_svg_line_y1(svg[i]) == get_svg_viewbox_height(svg) - 0.5 &&
                get_svg_line_y2(svg[i]) == get_svg_viewbox_height(svg) - 0.5 &&
                get_svg_line_x1(svg[i]) >= get_svg_viewbox_xmin(svg) + 0.5
                ){
           return true;
        }
        else if(is_svg_line(svg[i]) &&
                        get_svg_line_x1(svg[i]) == 0 &&
                        get_svg_line_y1(svg[i]) == 1.5 &&
                        get_svg_line_x2(svg[i]) == 1.0 &&     // can also add input to function (crown age variable?)
                        get_svg_line_y2(svg[i]) == 1.5 &&
                        get_svg_line_colour(svg[i]) == "black")

            return is_svg_line(svg[i]);
    }
  return false;
}


void elly::get_xml_declaration(std::vector<std::string>& svg){
 svg.push_back("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>");
}

void elly::initialize_svg_size(std::vector<std::string>& svg, const results& rs){
    std::stringstream ss_svg;
    //"<svg width=\"900\" height=\"400\" viewBox=\"-2 0 5 10\" xmlns=\"http://www.w3.org/2000/svg\">");

    ss_svg << "<svg width=\"900\" height=\"400\" viewBox=\""
           << -2 << " "    //x-min
           << 0  << " "   //y=min
           << 5  << " "   //width = crownage + 2?
           << rs.get().size() * 2 << " \" xmlns=\"http://www.w3.org/2000/svg\">";

    svg.push_back(ss_svg.str());
}


std::vector<std::string> elly::to_svg(const results& rs)
{
  std::vector<std::string> svg;

  get_xml_declaration(svg);
  initialize_svg_size(svg, rs);

  std::vector<std::string> svg_object = create_svg_object(rs);
  for(unsigned int i = 0; i < svg_object.size(); i++){
      svg.push_back(svg_object[i]);}

  create_time_scale_line(rs, svg);
  svg.push_back("</svg>");
  return svg;
  //STUB
  //return get_example_svg_1();
}

std::vector<std::string> elly::create_svg_object(const results& rs)
{
  std::vector<std::string> svg;
  for(unsigned int i = 0; i < rs.get().size(); i++){
      std::stringstream ssline, ssid, ssclade;

    //currently height of line and text is the same as species_id
    //Need to find different system to be able to differentiate between mainland
    //and island species
          double ext_x = 5;
          float y =  rs.get()[i].get_species().get_species_id().get_id();

         if(rs.get()[i].get_species().get_parent_id().get_id() != 0){
    //All lines get ID with species ID
    //Focal species Y coordinate has to be determined by parent species Ycoord
    //If focalspecies_ID % 2 == 0 focal species goes up 1 (even species_ID)
    //else y goes down 1
    //need to find a way to get y from line with id == parentID
        for(unsigned int j = 0; j < svg.size(); j++){
            if(is_svg_line(svg[j])){
                if(rs.get()[i].get_species().get_parent_id().get_id() == get_svg_line_ID(svg[j])){
                    y = get_svg_line_y1(svg[j]);
                }
            }
        }
          if(rs.get()[i].get_species().get_species_id().get_id() % 2 == 0) y += 0.5;
          //perhaps create scaler for splitting sister species closer at larger t.
          else y -= 0.5;
               }

          if(rs.get()[i].get_species().get_time_of_extinction_mainland() > 0){
               ext_x = rs.get()[i].get_species().get_time_of_extinction_mainland();}

         ssline << "<line x1=\"" << rs.get()[i].get_species().get_time_of_birth() + 0.5
                << "\" y1=\"" << y
                << "\" x2=\"" << ext_x + 0.5
                << "\" y2=\"" << y
                << "\" id=\"" << rs.get()[i].get_species().get_species_id()
                << "\" stroke=\"blue\" "
                << "stroke-width=\"0.2\" />";

           ssid << "<text x=\"" << ext_x + 0.6
                << "\" y=\"" << y + 0.1
                << "\" font-family=\"sans-serif\" font-size=\"0.4px\" fill=\"black\">"
                << rs.get()[i].get_species().get_species_id().get_id()
                <<"</text>";

          if(rs.get()[i].get_species().get_parent_id().get_id() == 0){
        ssclade << "<text x=\"" << - 0.5
                << "\" y=\"" << y + 0.1
                << "\" font-family=\"sans-serif\" font-weight=\"bold\" font-size=\"0.4px\" fill=\"black\">"
                << rs.get()[i].get_species().get_clade_id().get_id()
                <<"</text>";

                std::string clade = ssclade.str();
                svg.push_back(clade);
                    }
      std::string line = ssline.str();
      std::string name = ssid.str();

      svg.push_back(line);
      svg.push_back(name);

  }
  return svg;
}


//Timeline needs to be placed at bottom of viewbox
void elly::create_time_scale_line(const results&, std::vector<std::string>& svg){
    std::stringstream horizontal, vert_left, vert_right, left_digit, right_digit;

int crownage = 5;



for(int i = 0; i < crownage; i++){

    horizontal  << "<line x1=\"" << i + 0.5
                << "\" x2=\"" << i + 1.5
                << "\" y1=\"" << get_svg_viewbox_height(svg) - 0.5
                << "\" y2=\"" << get_svg_viewbox_height(svg) - 0.5
                << "\" stroke=\"black\" id=\"-1\" stroke-width=\"0.03\"/>";

    vert_left   << "<line x1=\"" << i + 0.5
                << "\" x2=\"" << i + 0.5
                << "\" y1=\"" << get_svg_viewbox_height(svg) - 0.57
                << "\" y2=\"" << get_svg_viewbox_height(svg) - 0.43
                << "\" stroke=\"black\" id=\"-1\" stroke-width=\"0.03\"/>";

    vert_right   << "<line x1=\"" << i + 1.5
                << "\" x2=\"" << i +  1.5
                << "\" y1=\"" << get_svg_viewbox_height(svg) - 0.57
                << "\" y2=\"" << get_svg_viewbox_height(svg) - 0.43
                << "\" stroke=\"black\" id=\"-1\" stroke-width=\"0.03\"/>";

    left_digit  << "<text x=\"" << i + 0.4
                << "\" y=\"" << get_svg_viewbox_height(svg) - 0.22
                << "\" font-family=\"sans-serif\" font-size=\"0.2px\" fill=\"black\">"
                << i
                << "</text>";

    if(i == crownage - 1){
    right_digit     << "<text x=\"" << i + 1.4
                    << "\" y=\"" << get_svg_viewbox_height(svg) - 0.22
                    << "\" font-family=\"sans-serif\" font-size=\"0.2px\" fill=\"black\">"
                    << i + 1
                    << "</text>";

    }
}

    std::string s_horizontal = horizontal.str();
    std::string s_vert_left = vert_left.str();
    std::string s_vert_right = vert_right.str();
    std::string s_left_digit = left_digit.str();
    std::string s_right_digit = right_digit.str();

    svg.push_back(s_horizontal);
    svg.push_back(s_vert_left);
    svg.push_back(s_vert_right);
    svg.push_back(s_left_digit);
    svg.push_back(s_right_digit);
/*
    //horizontal timeline
    svg.push_back("<line x1=\"0.5\" y1=\"1\" x2=\"2\" y2=\"1\" stroke=\"black\" id=\"-1\" stroke-width=\"0.02\"/>");   // ID -1 reserved for timescale identification. id > 0 will be used for species ID

    //vertical left
    svg.push_back("<line x1=\"0.5\" x2=\"0.5\" y1=\"1.07\" y2=\"0.92\" stroke=\"black\" id=\"-2\" stroke-width=\"0.02\" />");

    //vertical right
    svg.push_back("<line x1=\"2\" x2=\"2\" y1=\"1.07\" y2=\"0.92\" stroke=\"black\" id=\"-2\" stroke-width=\"0.02\" />");

    //left digit
    svg.push_back("<text x=\"0.40\" y=\"1.3\" font-family=\"sans-serif\" font-size=\"0.2px\" fill=\"black\">0</text>");

    // right digit
    svg.push_back("<text x=\"1.98\" y=\"1.3\" font-family=\"sans-serif\" font-size=\"0.2px\" fill=\"black\">1</text>");
*/
}

int elly::count_non_black_lines(const std::vector<std::string>& svg){
    int count = 0;

    for(unsigned int i = 0; i < svg.size(); i++){
       if(is_svg_line(svg[i]) && get_svg_line_colour(svg[i]) != "black") count += 1;

    }
    return count;
}

int elly::count_n_text_elements(const std::vector<std::string>& svg){
    int count = 0;

    for(unsigned int i = 0; i < svg.size(); i++){
        if(is_svg_text(svg[i])){

            count += 1;
        }
    }
    return count;
}

int elly::count_n_lines(const std::vector<std::string>& svg){
    int count = 0;

    for(unsigned int i = 0; i < svg.size(); i++){
        if(is_svg_line(svg[i]))
            count += 1;
    }
    return count;
}

std::vector<std::string> elly::get_example_svg_1(){
return {
  "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
  "<svg width=\"200\" height=\"10\" viewBox=\"-10 0 10 1\" xmlns=\"http://www.w3.org/2000/svg\">",
  "<line x1=\"-1.2\" y1=\"1\" x2=\"3.4\" y2=\"1\" stroke=\"blue\" />",
  "<line x1=\"0\" y1=\"1\" x2=\"1\" y2=\"1\" stroke=\"black\" />",
  "<text x=\"5\" y=\"20\" font-family=\"sans-serif\" font-size=\"0.4px\" fill=\"black\">Time (million years)</text>",
  "<text x=\"5\" y=\"19.5\" font-family=\"sans-serif\" font-size=\"0.4px\" fill=\"black\">5</text>",
  "</svg>"};
}
