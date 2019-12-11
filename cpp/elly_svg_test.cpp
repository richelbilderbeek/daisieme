#include "elly_svg_test.h"

#include <vector>
#include "elly_clade.h"
#include "elly_parameters.h"
#include "elly_simulation.h"

void elly::svg_test() //!OCLINT tests may be long
{
  //elly_is_xml_declaration
  {
    //Uncomment this line to start working on the test
    //#define FIX_ISSUE_14
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
    //#define FIX_ISSUE_15
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
    //#define FIX_ISSUE_16
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
    //#define FIX_ISSUE_17
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
       const std::vector<std::string> svg = to_svg(sim_results);
       assert(is_xml_declaration(svg[0]);
    }
    #endif // FIX_ISSUE_14
    #ifdef FIX_ISSUE_15
    //Depends on Issue 15
    //Second line of SVG must be an SVG opening tag
    {
       const results no_results;
       const std::vector<std::string> svg = to_svg(sim_results);
       assert(is_svg_start_tag(svg[1]);
    }
    #endif // FIX_ISSUE_15
    #ifdef FIX_ISSUE_16
    //Depends on Issue 16
    //Last line of SVG must be an SVG closing tag
    {
       const results no_results;
       const std::vector<std::string> svg = to_svg(sim_results);
       assert(is_svg_close_tag(svg.back());
    }
    #endif // FIX_ISSUE_16
    #ifdef FIX_ISSUE_17
    //Depends on Issue 17
    //One species on mainland
    {
     species a = create_new_test_species(location::mainland);
     const std::vector<species> population = {a};
     const results sim_results = get_results(population);
     const std::vector<std::string> svg = to_svg(sim_results);
     assert(is_svg_line(svg[2]);
    }
    #endif // FIX_ISSUE_17
  }
}
