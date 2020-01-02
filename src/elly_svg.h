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

//tests if line is SVG part
bool is_svg_line(const std::string& s);
bool is_svg_text(const std::string& s);
bool is_svg_rect(const std::string& s);
bool is_svg_start_tag(const std::string& s);

//Test if svg follows the svg conventions
bool is_svg(const std::vector<std::string>& svg);

//Test if svg contains ocean
bool has_ocean(const std::vector<std::string>& svg);


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

//gets ID of svg-line
int get_svg_line_ID(const std::string &svg);

//Checks if svg has a timescale line
//Needs to be modified once we implement crown age.
bool has_time_scale_line(const std::vector<std::string> &svg);

//Gives an example svg
std::vector<std::string> get_example_svg_1();

///Functions to create an SVG of a list of DAISIE events
void get_xml_declaration(std::vector<std::string>& svg);

void initialize_svg_size(std::vector<std::string>& svg, const results& rs);

void create_time_scale_line(const results&, std::vector<std::string>& svg);

void create_ocean(std::vector<std::string>&svg);

std::vector<std::string> create_svg_object(const results&, std::vector<std::string>& svg);



///Convert the results to the text of an SVG,
///each element being a line of text.
///First line will be the XML declarator
std::vector<std::string> to_svg(const results& r);


//checks number of black lines in the SVG
//only timescale line is black
int count_non_black_lines(const std::vector<std::string>& svg);

//counts number of text elements (species_id/ clade_id etc.)
int count_n_text_elements(const std::vector<std::string>& svg);

//counts number of lines in svg
//Should be n_species + Timescale
int count_n_lines(const std::vector<std::string>& svg);

//count number of parentspecies
int count_n_parents(const results& rs);

} //~namespace elly

#endif // ELLY_SVG_H
