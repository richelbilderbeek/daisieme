#include "elly_svg_test.h"

#include <vector>
#include <cassert>
#include "elly_clade.h"
#include "elly_parameters.h"
#include "elly_simulation.h"
#include "elly_svg.h"

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


void elly::svg_test() //!OCLINT tests may be long
{
  //elly_is_xml_declaration
  {
    //Uncomment this line to start working on the test
    #define FIX_ISSUE_14
    #ifdef FIX_ISSUE_14
    assert(
      is_xml_declaration(
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" // From https://en.wikipedia.org/wiki/Scalable_Vector_Graphics#Example
      )
    );
    assert(!is_xml_declaration("nonsense"));
    assert(!is_xml_declaration(""));
    //If the test works, remove the preprocessor statements (#define, #ifdef, #endif)
    #endif // FIX_ISSUE_14
  }
  //elly_is_svg_start_tag
  {
    //Uncomment this line to start working on the test
    #define FIX_ISSUE_15
    #ifdef FIX_ISSUE_15
    assert(
      is_svg_start_tag(
        "<svg width=\"391\" height=\"391\" viewBox=\"-70.5 -70.5 391 391\" xmlns=\"http://www.w3.org/2000/svg\">" // From https://en.wikipedia.org/wiki/Scalable_Vector_Graphics#Example
      )
    );
    assert(!is_svg_start_tag("nonsense"));
    assert(!is_svg_start_tag(""));
    //If the test works, remove the preprocessor statements (#define, #ifdef, #endif)
    #endif // FIX_ISSUE_15
  }
  //elly_is_svg_close_tag
  {
    //Uncomment this line to start working on the test
    #define FIX_ISSUE_16
    #ifdef FIX_ISSUE_16
    assert(
      is_svg_close_tag(
        "</svg>" // From https://en.wikipedia.org/wiki/Scalable_Vector_Graphics#Example
      )
    );
    assert(!is_svg_close_tag("nonsense"));
    assert(!is_svg_close_tag(""));
    //If the test works, remove the preprocessor statements (#define, #ifdef, #endif)
    #endif // FIX_ISSUE_16
  }
  //elly_is_svg_line
  {
    //Uncomment this line to start working on the test
    #define FIX_ISSUE_17
    #ifdef FIX_ISSUE_17
    assert(
      is_svg_line(
        "<line x1=\"-1.2\" y1=\"1\" x2=\"3.4\" y2=\"1\" stroke=\"black\" />" // From https://en.wikipedia.org/wiki/Scalable_Vector_Graphics#Example
      )
    );
    assert(!is_svg_line("nonsense"));
    assert(!is_svg_line(""));
    //If the test works, remove the preprocessor statements (#define, #ifdef, #endif)
    #endif // FIX_ISSUE_17
  }
  //elly_to_results_svg
  {
    #ifdef FIX_ISSUE_14
    //Depends on Issue 14
    //First line of SVG must be an XML declaration
    {
       const results no_results;
       const std::vector<std::string> svg = to_svg(no_results);
       assert(is_xml_declaration(svg[0]));
    }
    #endif // FIX_ISSUE_14
    #ifdef FIX_ISSUE_15
    //Depends on Issue 15
    //Second line of SVG must be an SVG opening tag
    {
       const results no_results;
       const std::vector<std::string> svg = to_svg(no_results);
       assert(is_svg_start_tag(svg[1]));
    }
    #endif // FIX_ISSUE_15
    #ifdef FIX_ISSUE_16
    //Depends on Issue 16
    //Last line of SVG must be an SVG closing tag
    {
       const results no_results;
       const std::vector<std::string> svg = to_svg(no_results);
       assert(is_svg_close_tag(svg.back()));
    }
    #endif // FIX_ISSUE_16

    #ifdef FIX_ISSUE_27
    //Example SVG 1 must be recognized as an SVG
    {
      assert(is_svg(get_example_svg_1()));
    }
    #endif
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
    #ifdef FIX_ISSUE_28
    // Get the width of the SVG
    {
      assert(get_svg_width(get_svg_example_1()) == 200);
    }
    #endif // FIX_ISSUE_28
    #ifdef FIX_ISSUE_29
    // Get the height of the SVG
    {
      assert(get_svg_height(get_svg_example_1()) == 10);
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
      const auto species_id = create_new_species_id();
      const auto parent_id = create_null_species_id();
      const auto clade_id = create_new_clade_id();
      const result r(species(species_id, parent_id, clade_id, 0.0, location::mainland));
      const results rs( { r } );
      const std::vector<std::string> svg = to_svg(rs);
      assert(count_non_black_lines(svg) == 1);
      assert(count_n_text_elements(svg) >= 2); //At least 2, as time scale will also get some
    }
    #endif // FIX_ISSUE_32
  }
}
