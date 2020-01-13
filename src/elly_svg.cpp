#include "elly_svg.h"

#include "elly_results.h"

#include <regex>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>


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

bool elly::is_svg_rect(const std::string& s){
    return s.substr(0,5) == "<rect";
}


int elly::count_non_black_lines(const std::vector<std::string>& svg){
    int count = 0;

    for(unsigned int i = 0; i < svg.size(); i++){
       if(is_svg_line(svg[i]) && get_svg_line_colour(svg[i]) != "black")
           count++;

    }
    return count;
}

int elly::count_n_text_elements(const std::vector<std::string>& svg){
    int count = 0;

    for(unsigned int i = 0; i < svg.size(); i++){
        if(is_svg_text(svg[i])){

            count++;
        }
    }
    return count;
}

int elly::count_n_lines(const std::vector<std::string>& svg){
  return static_cast<int>(
    std::count_if(
      std::begin(svg),
      std::end(svg),
      is_svg_line
    )
  );
}

int elly::count_n_parents(const results &rs){
  const auto& results = rs.get();
  return static_cast<int>(
    std::count_if(
      std::begin(results),
      std::end(results),
      [](const auto& r)
      {
        // is_starting_species
        return r.get_species().get_parent_id().get_id() == 0;
      }
    )
  );
  /*
    int count = 0;

    for(unsigned int i = 0; i < rs.get().size(); i++){
        if(rs.get()[i].get_species().get_parent_id().get_id() == 0)
            count++;
    }
    return count;
  */
}

int elly::count_n_rects(const std::vector<std::string>& svg){
    int count = 0;

    for (unsigned int i = 0; i < svg.size(); i++){
        if(is_svg_rect(svg[i]))
            count++;
    }
    return count;
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
    std::regex rgx("stroke=\"(.*?)\"");
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
                )
        {
           return true;
        }
    }
  return false;
}

bool elly::has_ocean(const std::vector<std::string> &svg){
    bool water = false;

    std::regex rgx("stroke=\"(.*?)\"");
    std::smatch colour;
    for (unsigned int i = 0; i < svg.size(); i++)
    {
        if (is_svg_rect(svg[i]))
        {
            for(unsigned int j = 0; j < svg[i].size(); j++)
                std::regex_search(svg[i], colour, rgx);

            if(colour[1] == "navy")
                water = true;
        }
    }
    return water;
}


void elly::get_xml_declaration(std::vector<std::string>& svg){
 svg.push_back("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>");
}

void elly::initialize_svg_size(std::vector<std::string>& svg, const results& rs){
    std::stringstream ss_svg;
    //"<svg width=\"900\" height=\"400\" viewBox=\"-2 0 5 10\" xmlns=\"http://www.w3.org/2000/svg\">");

    int crownage = 14;

    ss_svg << "<svg width=\"900\" height=\"400\" viewBox=\""
           << 0 << " "                  //x-min
           << 0  << " "                 //y=min
           << crownage + 2  << " "      //width = crownage + 2?
           << rs.get().size() * 2       //height
           << " \" xmlns=\"http://www.w3.org/2000/svg\">";

    svg.push_back(ss_svg.str());
}


std::vector<std::string> elly::to_svg(const results& rs)
{
  std::vector<std::string> svg;

  get_xml_declaration(svg);
  initialize_svg_size(svg, rs);

  std::vector<std::string> svg_object = create_svg_object(rs, svg);
  for(unsigned int i = 0; i < svg_object.size(); i++){
      svg.push_back(svg_object[i]);}
  create_ocean(svg);
  create_time_scale_line(rs, svg);
  svg.push_back("<rect width=\"100%\" height=\"100%\" fill=\"none\" stroke-width=\"0.1\" stroke=\"purple\" />");
  svg.push_back("</svg>");
  return svg;
  //STUB
  //return get_example_svg_1();
}

std::vector<std::string> elly::create_svg_object(const results& rs, std::vector<std::string> &svg)
{
  //std::cout << rs.get().size() << std::endl;
  int n = 1;
  float divider = 1.0;
  if(rs.get().size() != 0)
      divider = count_n_parents(rs) + 1;

  std::vector<std::string> svg_object;
  for(unsigned int i = 0; i < rs.get().size(); i++){
      std::stringstream ssline, ssid, ssclade;

          double ext_x = 14;
          float y = 0.0;

          if(rs.get()[i].get_species().get_parent_id().get_id() == 0 && is_mainlander(rs.get()[i].get_species()))
          {
              y += n * ((get_svg_viewbox_height(svg) / 2.0) / divider);
              n++;
          }
          else if(rs.get()[i].get_species().get_parent_id().get_id() == 0 && is_islander(rs.get()[i].get_species()))
          {
              y+= n * ((get_svg_viewbox_height(svg) / 2.0) / divider) + ((get_svg_viewbox_height(svg) - 1) / 2.0);
              n++;
          }


          if(rs.get()[i].get_species().get_parent_id().get_id() != 0){
    //All lines get ID with species ID
    //Focal species Y coordinate has to be determined by parent species Ycoord
    //If focalspecies_ID % 2 == 0 focal species goes up 1 (even species_ID)

        for(unsigned int k = 0; k < svg_object.size(); k++)
        {
            if(is_svg_line(svg_object[k]))
            {
                if(rs.get()[i].get_species().get_parent_id().get_id() == get_svg_line_ID(svg_object[k]))
                {
                    y = get_svg_line_y1(svg_object[k]);
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
                << "\" stroke=\"green\" "
                << "stroke-width=\"0.1\" />";

           ssid << "<text x=\"" << ext_x + 0.6
                << "\" y=\"" << y + 0.1
                << "\" font-family=\"sans-serif\" font-size=\"0.4px\" fill=\"black\">"
                << rs.get()[i].get_species().get_species_id().get_id()
                <<"</text>";

          if(rs.get()[i].get_species().get_parent_id().get_id() == 0){
        ssclade << "<text x=\"" <<  0.1
                << "\" y=\"" << y + 0.1
                << "\" font-family=\"sans-serif\" font-weight=\"bold\" font-size=\"0.4px\" fill=\"black\">"
                << rs.get()[i].get_species().get_clade_id().get_id()
                <<"</text>";

                std::string clade = ssclade.str();
                svg_object.push_back(clade);
                    }
      std::string line = ssline.str();
      std::string name = ssid.str();

      svg_object.push_back(line);
      svg_object.push_back(name);
    }

  return svg_object;
}


//Timeline needs to be placed at bottom of viewbox
void elly::create_time_scale_line(const  results&, std::vector<std::string>& svg){

    std::stringstream horizontal, vert_left, vert_right, left_digit, right_digit;

int crownage = 14;

horizontal  << "<line x1=\"" <<  0.5
            << "\" x2=\"" << crownage + 0.5
            << "\" y1=\"" << get_svg_viewbox_height(svg) - 0.5
            << "\" y2=\"" << get_svg_viewbox_height(svg) - 0.5
            << "\" stroke=\"black\" id=\"-1\" stroke-width=\"0.03\"/>";


for(int i = 0; i < crownage; i++){
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

}


void elly::create_ocean(std::vector<std::string> &svg){
    std::stringstream ocean;
    float height = (get_svg_viewbox_height(svg) / 2);
    ocean << "<rect x=\"0.5\" y=\"" << height
          << "\" rx=\"1\" ry=\"1\" width =\"" << (get_svg_viewbox_width(svg) - 2)
          << "\" height=\"0.1\" id=\"-2\" stroke=\"navy\" stroke-width=\"0.5\"/>";

    std::string water = ocean.str();
    svg.push_back(water);
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
