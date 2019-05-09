#include "dme_create_params_file_cpp.h"
#include "elly_parameters.h"
#include "elly_n_species.h"
#include "elly_carrying_capacity.h"
#include "elly_per_species_rate.h"
#include "elly_per_species_rates.h"

#include <cassert>
#include <fstream>

void dme_create_params_file_cpp(
  const std::string& filename,
  const double ana_psr,
  const double clado_is_psr,
  const double clado_main_psr,
  const double ext_is_psr,
  const double ext_main_psr,
  const double mig_to_is_psr,
  const int carry_cap_is,
  const int carry_cap_main,
  const int rng_seed
)
{
  const elly::per_species_rate ana = elly::per_species_rate(ana_psr);
  const elly::per_species_rate clado_is = elly::per_species_rate(clado_is_psr);
  const elly::per_species_rate clado_main = elly::per_species_rate(clado_main_psr);
  const elly::per_species_rate ext_is = elly::per_species_rate(ext_is_psr);
  const elly::per_species_rate ext_main = elly::per_species_rate(ext_main_psr);
  const elly::per_species_rate mig_to_is = elly::per_species_rate(mig_to_is_psr);
  const elly::per_species_rates rates(
    ana,
    clado_is,
    clado_main,
    ext_is,
    ext_main,
    mig_to_is
  );
  assert(carry_cap_is > 0);
  const elly::n_species carry_cap_is_n_species(carry_cap_is);
  const elly::carrying_capacity carryingcap_is(carry_cap_is_n_species);

  assert(carry_cap_main > 0);
  const elly::n_species carry_cap_main_n_species(carry_cap_main);
  const elly::carrying_capacity carryingcap_main(carry_cap_main_n_species);

  const int init_n_main_clades = 1;
  assert(init_n_main_clades > 0);

  const int init_n_main_sps = 1;
  assert(init_n_main_sps > 0);

  const double crown_age = 1.0;
  assert(crown_age > 0.0);

  const elly::parameters p(
    rates,
    carryingcap_is,
    carryingcap_main,
    rng_seed,
    init_n_main_clades,
    init_n_main_sps,
    crown_age
  );
  std::ofstream f(filename.c_str());
  f << p;
}
