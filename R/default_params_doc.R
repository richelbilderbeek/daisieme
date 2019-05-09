#' This function does nothing. It is intended to inherit is parameters'
#' documentation.
#' @param filename name of the file
#' @param ana_psr anagenesis, per-species rate
#' @param clado_is_psr cladogenesis on island, per-species rate
#' @param clado_main_psr cladogenesis on mainland, per-species rate
#' @param crown_age crown age, time units
#' @param daisie_sim_results_filename name of the file to save
#'   the simulation results to
#' @param daisie_input_ideal_filename name of the file to create with
#'   a DAISIE input, based on ideal/omniscient observations
#' @param daisie_input_reality_filename name of the file to create with
#'   a DAISIE input, based on realistic observations
#' @param daisie_output_ideal_filename name of the file to create with
#'   DAISIE output, based on input with ideal/omniscient observations
#' @param daisie_output_reality_filename name of the file to create with
#'   DAISIE output, based on realistic observations
#' @param dme_params_filename name of the file with the daisieme parameters
#' @param ext_is_psr extinction rate on island, per-species rate
#' @param ext_main_psr extinction rate on mainland, per-species rate
#' @param mig_to_is_psr migratrion to island, per-species rate
#' @param carry_cap_is carrying capacity of the island, number of species
#' @param carry_cap_main carrying capacity of the mainland, number of species
#' @param rng_seed RNG seed
#' @param init_n_main_clades initial number of mainland clades
#' @param init_n_main_sps initial number of mainland species
#' @author Richèl J.C. Bilderbeek
#' @note This is an internal function, so it should be marked with
#'   \code{@noRd}. This is not done, as this will disallow all
#'   functions to find the documentation parameters
default_params_doc <- function(
  filename,
  ana_psr,
  clado_is_psr,
  clado_main_psr,
  crown_age,
  daisie_sim_results_filename,
  daisie_input_ideal_filename,
  daisie_input_reality_filename,
  daisie_output_ideal_filename,
  daisie_output_reality_filename,
  dme_params_filename,
  ext_is_psr,
  ext_main_psr,
  mig_to_is_psr,
  carry_cap_is,
  carry_cap_main,
  rng_seed,
  init_n_main_clades,
  init_n_main_sps
) {
  # Nothing
}
