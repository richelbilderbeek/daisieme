#ifndef DME_CREATE_DAISIE_INPUT_CPP_H
#define DME_CREATE_DAISIE_INPUT_CPP_H

#include <string>

//' Create a parameter file.
//' @param dme_params_filename name of the file with the daisieme parameters
//' @param daisie_input_ideal_filename name of the file to create with
//'   a DAISIE input, based on ideal/omniscient observations
//' @param daisie_input_ideal_filename name of the file to create with
//'   a DAISIE input, based on realistic observations
//' @return nothing
//' @author Richel J.C. Bilderbeek
//' @export
// [[Rcpp::export]]
void dme_create_daisie_input_cpp(
  const std::string& dme_params_filename,
  const std::string& daisie_input_ideal_filename,
  const std::string& daisie_input_reality_filename
);

#endif // DME_CREATE_DAISIE_INPUT_CPP_H
