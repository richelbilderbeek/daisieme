#ifndef DME_CREATE_PARAMS_FILE_CPP_H
#define DME_CREATE_PARAMS_FILE_CPP_H

#include <string>

//' Create a parameter file.
//' @param filename name of the file
//' @param ana_psr anagenesis, per-species rate
//' @param clado_is_psr cladogenesis on island, per-species rate
//' @param clado_main_psr cladogenesis on mainland, per-species rate
//' @param ext_is_psr extinction rate on island, per-species rate
//' @param ext_main_psr extinction rate on mainland, per-species rate
//' @param mig_to_is_psr migratrion to island, per-species rate
//' @param carry_cap_is carrying capacity of the island, number of species
//' @param carry_cap_main carrying capacity of the mainland, number of species
//' @param rng_seed RNG seed
//' @param init_n_main_clades initial number of mainland clades
//' @return nothing
//' @author Richel J.C. Bilderbeek
//' @export
// [[Rcpp::export]]
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
  const int rng_seed,
  const int init_n_main_clades
);

#endif // DME_CREATE_PARAMS_FILE_CPP_H
