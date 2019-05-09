#include "dme_create_daisie_input_cpp.h"
#include "elly_parameters.h"
#include "elly_experiment.h"

#include <cassert>
#include <fstream>

void dme_create_daisie_input_cpp(
  const std::string& dme_params_filename,
  const std::string& daisie_sim_results_filename,
  const std::string& daisie_input_ideal_filename,
  const std::string& daisie_input_reality_filename,
  const std::string& daisie_output_ideal_filename,
  const std::string& daisie_output_reality_filename
)
{
  const elly::parameters p = elly::load_parameters_from_file(dme_params_filename);

  elly::experiment e(p);
  e.run_sim();

  {
    std::ofstream f(daisie_sim_results_filename.c_str());
    f << e.get_sim_results() << '\n';
  }

  e.create_daisie_input();

  {
    std::ofstream f(daisie_input_ideal_filename.c_str());
    f << e.get_input_ideal() << '\n';
  }
  {
    std::ofstream f(daisie_input_reality_filename.c_str());
    f << e.get_input_reality() << '\n';
  }

  e.run_daisie();

  {
    std::ofstream f(daisie_output_ideal_filename.c_str());
    f << daic::get_output_header() << '\n'
      << e.get_output_ideal() << '\n'
    ;
  }
  {
    std::ofstream f(daisie_output_reality_filename.c_str());
    f << daic::get_output_header() << '\n'
      << e.get_output_reality() << '\n'
    ;
  }
}
