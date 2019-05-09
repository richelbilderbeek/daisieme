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
  const double mig_to_is_psr
);

#endif // DME_CREATE_PARAMS_FILE_CPP_H
