#include "elly_svg_test.h"

#include <vector>
#include <cassert>
#include "elly_clade.h"
#include "elly_parameters.h"
#include "elly_simulation.h"
#include "elly_svg.h"
#include <regex>

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

void elly::svg_test() //!OCLINT tests may be long
{
  //elly_is_xml_declaration
  {
    assert(
      is_xml_declaration(
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" // From https://en.wikipedia.org/wiki/Scalable_Vector_Graphics#Example
      )
    );
    assert(!is_xml_declaration("nonsense"));
    assert(!is_xml_declaration(""));
  }
  //elly_is_svg_start_tag
  {
    assert(
      is_svg_start_tag(
        "<svg width=\"391\" height=\"391\" viewBox=\"-70.5 -70.5 391 391\" xmlns=\"http://www.w3.org/2000/svg\">" // From https://en.wikipedia.org/wiki/Scalable_Vector_Graphics#Example
      )
    );
    assert(!is_svg_start_tag("nonsense"));
    assert(!is_svg_start_tag(""));
  }
  //elly_is_svg_close_tag
  {
    assert(
      is_svg_close_tag(
        "</svg>" // From https://en.wikipedia.org/wiki/Scalable_Vector_Graphics#Example
      )
    );
    assert(!is_svg_close_tag("nonsense"));
    assert(!is_svg_close_tag(""));
  }
  //elly_is_svg_line
  {
    assert(
      is_svg_line(
        "<line x1=\"-1.2\" y1=\"1\" x2=\"3.4\" y2=\"1\" stroke=\"black\" />" // From https://en.wikipedia.org/wiki/Scalable_Vector_Graphics#Example
      )
    );
    assert(!is_svg_line("nonsense"));
    assert(!is_svg_line(""));
  }
  //elly_to_results_svg
  {
    //First line of SVG must be an XML declaration
    {
       const results no_results;
       const std::vector<std::string> svg = to_svg(no_results);
       assert(is_xml_declaration(svg[0]));
    }
    //Second line of SVG must be an SVG opening tag
    {
       const results no_results;
       const std::vector<std::string> svg = to_svg(no_results);
       assert(is_svg_start_tag(svg[1]));
    }
    //Last line of SVG must be an SVG closing tag
    {
       const results no_results;
       const std::vector<std::string> svg = to_svg(no_results);
       assert(is_svg_close_tag(svg.back()));
    }
    //Example SVG 1 must be recognized as an SVG
    {
     assert(is_svg(get_example_svg_1()));
    }
    //Depends on Issue 17
    //One species on mainland
    {
     const species a = create_new_test_species(location::mainland);
     const std::vector<species> population = {a};
     const results sim_results = get_results(population);
     const std::vector<std::string> svg = to_svg(sim_results);
     assert(is_svg_line(svg[2])); //Brittle test
    }
    // User can specify the crown age. By default this is 1.0
    {

    }
    #define FIX_ISSUE_28
    #ifdef FIX_ISSUE_28
    // Get the width of the SVG
    {
      assert(get_svg_width(get_example_svg_1()) == 200);
    }
    #endif // FIX_ISSUE_28
    #define FIX_ISSUE_29
    #ifdef FIX_ISSUE_29
    // Get the height of the SVG
    {
      assert(get_svg_height(get_example_svg_1()) == 10);
    }
    #endif // FIX_ISSUE_29
    #ifdef FIX_ISSUE_31
    // Get the coordinats of the viewbox
    {
      const std::vector<std::string> svg = {
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
        "<svg width=\"200\" height=\"10\" viewBox=\"-10 0 10 1\" xmlns=\"http://www.w3.org/2000/svg\">",
        "</svg>"
      };
      assert(!get_svg_viewbox_x1(svg) == -10.0);
      assert(!get_svg_viewbox_y1(svg) ==   0.0);
      assert(!get_svg_viewbox_x2(svg) ==  10.0);
      assert(!get_svg_viewbox_y2(svg) ==   1.0);
    }
    #endif // FIX_ISSUE_31
    #ifdef FIX_ISSUE_30
    // An empty SVG has no time scale line
    {
      const std::vector<std::string> svg = {
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
        "<svg width=\"200\" height=\"10\" viewBox=\"-10 0 10 1\" xmlns=\"http://www.w3.org/2000/svg\">",
        "</svg>"
      };
      assert(!has_time_scale_line(svg));
    }
    // A time scale must be in the viewbox
    //
    //  (-1,-1)---------------------+
    //     |                        |
    //     | Viewbox                |
    //     |                        |
    //     |   (0,0)------+         |
    //     |     | Graph  |         |
    //     |     +------(1,1)       |
    //     |                        |
    //     +----------------------(2,2)
    //
    //
    // Time scale line at the bottom of graph, as a horizontal line:
    //
    //          (0,1)    (1,1)
    //
    //           +--------+
    //
    {
      const std::vector<std::string> svg = {
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
        "<svg width=\"200\" height=\"10\" viewBox=\"-1 -1 2 2\" xmlns=\"http://www.w3.org/2000/svg\">",
        "<line x1=\"0\" y1=\"1\" x2=\"1\" y2=\"1\" stroke=\"black\" />",
        "</svg>"
      };
      assert(has_time_scale_line(svg));
    }
    // Time scale must be at the bottom
    {
      const std::vector<std::string> svg = {
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
        "<svg width=\"200\" height=\"10\" viewBox=\"-1 -1 2 2\" xmlns=\"http://www.w3.org/2000/svg\">",
        "<line x1=\"0\" y1=\"0\" x2=\"1\" y2=\"0\" stroke=\"black\" />", //Changed y coordinats
        "</svg>"
      };
      assert(!has_time_scale_line(svg));
    }
    // Left side of time scale line has an x (equals t) of zero
    {
      const std::vector<std::string> svg = {
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
        "<svg width=\"200\" height=\"10\" viewBox=\"-1 -1 2 2\" xmlns=\"http://www.w3.org/2000/svg\">",
        "<line x1=\"-123\" y1=\"0\" x2=\"1\" y2=\"0\" stroke=\"black\" />", //Changed x1 coordinat
        "</svg>"
      };
      assert(!has_time_scale_line(svg));
    }
    // Right side of time scale line has an x (equals t) of the crown age of (by default) one
    {
      const std::vector<std::string> svg = {
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
        "<svg width=\"200\" height=\"10\" viewBox=\"-1 -1 2 2\" xmlns=\"http://www.w3.org/2000/svg\">",
        "<line x1=\"0\" y1=\"0\" x2=\"123\" y2=\"0\" stroke=\"black\" />", //Changed x2 coordinat
        "</svg>"
      };
      assert(!has_time_scale_line(svg));
    }
    // Time scale must be black
    {
      const std::vector<std::string> svg = {
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
        "<svg width=\"200\" height=\"10\" viewBox=\"-1 -1 2 2\" xmlns=\"http://www.w3.org/2000/svg\">",
        "<line x1=\"0\" y1=\"1\" x2=\"1\" y2=\"1\" stroke=\"blue\" />", //Changed stroke
        "</svg>"
      };
      assert(!has_time_scale_line(svg));
    }
    // to_svg must produce an SVG with a timescale line
    {
      const results no_results;
      const std::vector<std::string> svg = to_svg(no_results);
      assert(has_time_scale_line(svg));
    }
    #endif // FIX_ISSUE_30
    #ifdef FIX_ISSUE_32
    // 1 mainland species, 1 clade ID, nothing happening
    {
      const auto species_id = create_new_species_id(); //217 in picture
      const auto parent_id = create_null_species_id();
      const auto clade_id = create_new_clade_id(); // 57 in picture
      const result r(species(species_id, parent_id, clade_id, 0.0, location::mainland));
      const results rs( { r } );
      const std::vector<std::string> svg = to_svg(rs);
      assert(count_non_black_lines(svg) == 1);
      assert(count_n_text_elements(svg) >= 2); //At least 2, as time scale will also get some
    }
    #endif // FIX_ISSUE_32
    #ifdef FIX_ISSUE_33
    // 2 mainland species, 1 clade ID, nothing happening
    {
      const auto species_id_1 = create_new_species_id(); //316 in picture
      const auto species_id_2 = create_new_species_id(); //317 in picture
      const auto parent_id = create_null_species_id();
      const auto clade_id = create_new_clade_id(); // 80 in picture
      const result r_1(species(species_id_1, parent_id, clade_id, 0.0, location::mainland));
      const result r_2(species(species_id_2, parent_id, clade_id, 0.0, location::mainland));
      const results rs( { r_1, r_2 } );
      const std::vector<std::string> svg = to_svg(rs);
      assert(count_non_black_lines(svg) == 2);
      assert(count_n_text_elements(svg) >= 2); //At least 2, as time scale will also get some
    }
    #endif // FIX_ISSUE_33
    #ifdef FIX_ISSUE_34
    // 3 mainland species, 1 clade ID, 1 extinction
    {
      const auto species_id_1 = create_new_species_id(); //126 in picture
      const auto species_id_2 = create_new_species_id(); //127 in picture
      const auto species_id_3 = create_new_species_id(); //128 in picture
      const auto parent_id = create_null_species_id();
      const auto clade_id = create_new_clade_id(); // 45 in picture
      const result r_1(species(species_id_1, parent_id, clade_id, 0.0, location::mainland));
      const result r_2(species(species_id_2, parent_id, clade_id, 0.5, location::mainland));
      const result r_3(species(species_id_3, parent_id, clade_id, 2.6, location::mainland));
      const results rs( { r_1, r_2, r_3 } );
      const std::vector<std::string> svg = to_svg(rs);
      assert(count_non_black_lines(svg) == 3);
      assert(count_n_text_elements(svg) >= 3); //At least 3, as time scale will also get some
    }
    #endif // FIX_ISSUE_34
  }
}
