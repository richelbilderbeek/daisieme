#include "elly_svg_test.h"

#include <vector>
#include <cassert>
#include "elly_clade.h"
#include "elly_parameters.h"
#include "elly_simulation.h"
#include "elly_svg.h"
#include <fstream>


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
       const parameters pars = create_parameters_set1();
       const std::vector<std::string> svg = to_svg(no_results, pars);
       assert(is_xml_declaration(svg[0]));
    }
    //Second line of SVG must be an SVG opening tag
    {
       const results no_results;
       const parameters pars = create_parameters_set1();
       const std::vector<std::string> svg = to_svg(no_results, pars);
       assert(is_svg_start_tag(svg[1]));
    }
    //Last line of SVG must be an SVG closing tag
    {
       const results no_results;
       const parameters pars = create_parameters_set1();
       const std::vector<std::string> svg = to_svg(no_results, pars);
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
     const parameters pars = create_parameters_set1();
     const std::vector<std::string> svg = to_svg(sim_results, pars);
     assert(is_svg_line(svg[3])); //Brittle test
    }
    // User can specify the crown age. By default this is 1.0
    {

    }
    // Get the width of the SVG
    {
      assert(get_svg_width(get_example_svg_1()) == 200);
    }

    // Get the height of the SVG
    {
      assert(get_svg_height(get_example_svg_1()) == 10);
    }

    // Get the coordinats of the viewbox
    {
      const std::vector<std::string> svg = {
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
        "<svg width=\"1200\" height=\"900\" viewBox=\"-1 -1 3 3\" xmlns=\"http://www.w3.org/2000/svg\">",
        "</svg>"
      };
      assert(get_svg_viewbox_xmin(svg) == -1.0);
      assert(get_svg_viewbox_ymin(svg) == -1.0);
      assert(get_svg_viewbox_width(svg) ==  3.0);
      assert(get_svg_viewbox_height(svg) == 3.0);
    }

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
        "<line x1=\"0\" y1=\"1.5\" x2=\"1\" y2=\"1.5\" id=\"-1\" stroke=\"black\" />",       // ID = -1 reserved for timescale
        "</svg>"
      };
      assert(has_time_scale_line(svg));
    }
    // Time scale must be at the bottom
    {
      const std::vector<std::string> svg = {
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
        "<svg width=\"200\" height=\"10\" viewBox=\"-1 -1 2 2\" xmlns=\"http://www.w3.org/2000/svg\">",
        "<line x1=\"0\" y1=\"0\" x2=\"1\" y2=\"0\" id=\"-1\" stroke=\"black\" />", //Changed y coordinats
        "</svg>"
      };
     assert(!has_time_scale_line(svg));
    }
    // Left side of time scale line has an x (equals t) of zero
    {
      const std::vector<std::string> svg = {
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
        "<svg width=\"200\" height=\"10\" viewBox=\"-1 -1 2 2\" xmlns=\"http://www.w3.org/2000/svg\">",
        "<line x1=\"-123\" y1=\"0\" x2=\"1\" y2=\"0\" id=\"-1\" stroke=\"black\" />", //Changed x1 coordinat
        "</svg>"
      };
     assert(!has_time_scale_line(svg));
    }
    // Right side of time scale line has an x (equals t) of the crown age of (by default) one
    {
      const std::vector<std::string> svg = {
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
        "<svg width=\"200\" height=\"10\" viewBox=\"-1 -1 2 2\" xmlns=\"http://www.w3.org/2000/svg\">",
        "<line x1=\"0\" y1=\"0\" x2=\"123\" y2=\"0\" id=\"-1\" stroke=\"black\" />", //Changed x2 coordinat
        "</svg>"
      };
     assert(!has_time_scale_line(svg));
    }
    // Time scale must be black
    {
      const std::vector<std::string> svg = {
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>",
        "<svg width=\"200\" height=\"10\" viewBox=\"-1 -1 2 2\" xmlns=\"http://www.w3.org/2000/svg\">",
        "<line x1=\"0\" y1=\"1\" x2=\"1\" y2=\"1\" id=\"-1\" stroke=\"blue\" />", //Changed stroke
        "</svg>"
      };
    assert(!has_time_scale_line(svg));
    }
    // to_svg must produce an SVG with a timescale line
    {
      const results no_results;
      const parameters pars = create_parameters_set1();
      const std::vector<std::string> svg = to_svg(no_results, pars);
   assert(has_time_scale_line(svg));
    }
    // 1 mainland species, 1 clade ID, nothing happening
    {
      const auto species_id = create_new_species_id(); //217 in picture
      const auto parent_id = create_null_species_id();
      const auto clade_id = create_new_clade_id(); // 57 in picture
      const result r(species(species_id, parent_id, clade_id, 0.0, location::mainland));
      const results rs( { r } );
      const parameters pars = create_parameters_set1();
      const std::vector<std::string> svg = to_svg(rs, pars);
      assert(count_non_black_lines(svg) == 1);
      assert(count_n_text_elements(svg) >= 2); //At least 2, as time scale will also get some
    }
    // 2 mainland species, 1 clade ID, nothing happening
    {
      const auto species_id_1 = create_new_species_id(); //316 in picture
      const auto species_id_2 = create_new_species_id(); //317 in picture
      const auto parent_id = create_null_species_id();
      const auto clade_id = create_new_clade_id(); // 80 in picture
      const result r_1(species(species_id_1, parent_id, clade_id, 0.0, location::mainland));
      const result r_2(species(species_id_2, parent_id, clade_id, 0.0, location::mainland));
      const results rs( { r_1, r_2 } );
      const parameters pars = create_parameters_set1();
      const std::vector<std::string> svg = to_svg(rs, pars);
      assert(count_non_black_lines(svg) == 2);
      assert(count_n_text_elements(svg) >= 2); //At least 2, as time scale will also get some
    }
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
      const parameters pars = create_parameters_set1();
      const std::vector<std::string> svg = to_svg(rs, pars);
      assert(count_non_black_lines(svg) == 3);
      assert(count_n_text_elements(svg) >= 3); //At least 3, as time scale will also get some
    }

    #define FIX_ISSUE_35
    #ifdef FIX_ISSUE_35
    // 1 mainland species + 1 cladogenesis into 2 mainland species
    {
     elly::species parent = create_new_test_species(location::mainland);
     parent.go_extinct(1.5, location::mainland);
     elly::species focal1 = create_descendant(parent, 1.5, location::mainland);
     elly::species focal2 = create_descendant(parent, 1.5, location::mainland);
     elly::species newspec = create_new_test_species(location::mainland);
     focal1.go_extinct(2.7, location::mainland);
     elly::species focal3 = create_descendant(focal1, 2.7, location::mainland);
     elly::species focal4 = create_descendant(focal1, 2.7, location::mainland);
     elly::species newspec2 = create_new_test_species(location::mainland);
     newspec.migrate_to_island(2.0);
     newspec2.migrate_to_island(6.0);
     const result r_1(parent);
     const result r_2(focal1);
     const result r_3(focal2);
     const result r_4(focal3);
     const result r_5(focal4);
     const result r_6(newspec);
     const result r_7(newspec2);
     const results rs( { r_1, r_2, r_3, r_4, r_5, r_6, r_7 } );
     const parameters pars = create_parameters_set1();
     const std::vector<std::string> svg = to_svg(rs, pars);

     //std::cout << "Number of lines= " << count_n_lines(svg) << std::endl;
     assert(count_n_lines(svg) >= 4);   //At least 4, time scale and 6 species
     assert(has_time_scale_line(svg));
     assert(has_ocean(svg));
     assert(count_n_parents(rs) != 2);
     assert(count_n_rects(svg) >= 1);

     #define SHOW_35_OUTPUT
     #ifdef SHOW_35_OUTPUT
            std::ofstream ofs("issue35.svg");
               if (!ofs.is_open())
                throw std::runtime_error("Unable to open or create the file. \n");

            for(unsigned int i = 0; i < svg.size(); i++){
                ofs << svg[i] << "\n";
              }
            ofs.close();

     //change path to a suitable program to open .svg files
     //std::system("firefox issue35.svg");
     #endif

    }
    #endif

    #define FIX_ISSUE_36
    #ifdef FIX_ISSUE_36
    // 1 mainland species + 1 island species
    {
     elly::species mainland = create_new_test_species(location::mainland);
     elly::species island = create_new_test_species(location::island);
     mainland.migrate_to_island(4);
     const result r_1(mainland);
     const result r_2(island);
     const results rs( { r_1, r_2 } );
     const parameters pars = create_parameters_set1();
     const std::vector<std::string> svg = to_svg(rs, pars);
     assert(count_n_lines(svg) >= 3);   //At least 4, time scale and 2 species
     assert(has_time_scale_line(svg));
     assert(has_ocean(svg));
     assert(count_n_parents(rs) == 2);
     //#define SHOW_36_OUTPUT
     #ifdef SHOW_36_OUTPUT
            std::ofstream ofs("issue36.svg");
               if (!ofs.is_open())
                throw std::runtime_error("Unable to open or create the file. \n");

            for(unsigned int i = 0; i < svg.size(); i++){
                ofs << svg[i] << "\n";
              }
            ofs.close();

     //change path to a suitable program to open .svg files
     //std::system("firefox issue36.svg");
     #endif
    }
    #endif


    #define FIX_ISSUE_56
    #ifdef FIX_ISSUE_56
    // Fix migration drawing
    {
     const parameters pars = create_parameters_set1();
     elly::species mainland = create_new_test_species(location::mainland);
     elly::species mainland2 = create_new_test_species(location::mainland);
     mainland.migrate_to_island(4);
     mainland.go_extinct(6.2, location::island);
     const result r_1(mainland);
     const result r_2(mainland2);
     const results rs( { r_1, r_2 } );
     const std::vector<std::string> svg = to_svg(rs, pars);
     assert(count_n_lines(svg) >= 3);   //At least 4, time scale and 2 species
     assert(has_time_scale_line(svg));
     assert(has_ocean(svg));
     assert(count_n_parents(rs) == 2);

     //#define SHOW_56_OUTPUT
     #ifdef SHOW_56_OUTPUT
            std::ofstream ofs("issue56.svg");
               if (!ofs.is_open())
                throw std::runtime_error("Unable to open or create the file. \n");

            for(unsigned int i = 0; i < svg.size(); i++){
                ofs << svg[i] << "\n";
              }
            ofs.close();

     //change path to a suitable program to open .svg files
     //std::system("firefox issue56.svg");
     #endif
    }
    #endif

    }

}
