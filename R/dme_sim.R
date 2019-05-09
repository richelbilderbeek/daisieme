#' daisieme sim
#' @inheritParams default_params_doc
#' @export
dme_sim <- function(
  ana_psr,
  clado_is_psr,
  clado_main_psr,
  ext_is_psr,
  ext_main_psr,
  mig_to_is_psr,
  carry_cap_is,
  carry_cap_main,
  rng_seed,
  init_n_main_clades,
  init_n_main_sps,
  crown_age = crown_age,
  dme_params_filename = tempfile(),
  daisie_sim_results_filename,
  daisie_input_ideal_filename,
  daisie_input_reality_filename,
  daisie_output_ideal_filename,
  daisie_output_reality_filename
) {
  dme_create_params_file(
    filename = dme_params_filename,
    ana_psr = ana_psr,
    clado_is_psr = clado_is_psr,
    clado_main_psr = clado_main_psr,
    ext_is_psr = ext_is_psr,
    ext_main_psr = ext_main_psr,
    mig_to_is_psr = mig_to_is_psr,
    carry_cap_is = carry_cap_is,
    carry_cap_main = carry_cap_main,
    rng_seed = rng_seed,
    init_n_main_clades = init_n_main_clades,
    init_n_main_sps = init_n_main_sps,
    crown_age = crown_age
  )
  dme_create_daisie_input_cpp(
    dme_params_filename = dme_params_filename,
    daisie_sim_results_filename = daisie_sim_results_filename,
    daisie_input_ideal_filename = daisie_input_ideal_filename,
    daisie_input_reality_filename = daisie_input_reality_filename,
    daisie_output_ideal_filename = daisie_output_ideal_filename,
    daisie_output_reality_filename = daisie_output_reality_filename
  )
}
