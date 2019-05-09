context("test-dme_sim")

test_that("use, no call to DAISIE", {

  dme_params_filename <- tempfile()
  ana_psr <- 1.23
  clado_is_psr <- 2.34
  clado_main_psr <- 3.45
  ext_is_psr <- 0.12
  ext_main_psr <- 0.23
  mig_to_is_psr <- 0.001
  carry_cap_is <- 42
  carry_cap_main <- 314
  rng_seed <- 421
  init_n_main_clades <- 1
  init_n_main_sps <- 9
  crown_age <- 12.34
  daisie_sim_results_filename <- tempfile()
  daisie_input_ideal_filename <- tempfile()
  daisie_input_reality_filename <- tempfile()
  daisie_output_ideal_filename <- ""
  daisie_output_reality_filename <- ""

  dme_sim(
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
    crown_age = crown_age,
    dme_params_filename = dme_params_filename,
    daisie_sim_results_filename = daisie_sim_results_filename,
    daisie_input_ideal_filename = daisie_input_ideal_filename,
    daisie_input_reality_filename = daisie_input_reality_filename,
    daisie_output_ideal_filename = daisie_output_ideal_filename,
    daisie_output_reality_filename = daisie_output_reality_filename
  )
  expect_true(file.exists(dme_params_filename))
  expect_true(file.exists(daisie_sim_results_filename))
  expect_true(file.exists(daisie_input_ideal_filename))
  expect_true(file.exists(daisie_input_reality_filename))
  expect_false(file.exists(daisie_output_ideal_filename))
  expect_false(file.exists(daisie_output_reality_filename))
})

test_that("use, with DAISIE", {

  skip("Takes too long")
  dme_params_filename <- tempfile()
  ana_psr <- 1.23
  clado_is_psr <- 2.34
  clado_main_psr <- 3.45
  ext_is_psr <- 0.12
  ext_main_psr <- 0.23
  mig_to_is_psr <- 0.001
  carry_cap_is <- 42
  carry_cap_main <- 314
  rng_seed <- 227
  init_n_main_clades <- 1
  init_n_main_sps <- 9
  crown_age <- 12.34
  daisie_sim_results_filename <- tempfile()
  daisie_input_ideal_filename <- tempfile()
  daisie_input_reality_filename <- tempfile()
  daisie_output_ideal_filename <- tempfile()
  daisie_output_reality_filename <- tempfile()

  dme_sim(
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
    crown_age = crown_age,
    dme_params_filename = dme_params_filename,
    daisie_sim_results_filename = daisie_sim_results_filename,
    daisie_input_ideal_filename = daisie_input_ideal_filename,
    daisie_input_reality_filename = daisie_input_reality_filename,
    daisie_output_ideal_filename = daisie_output_ideal_filename,
    daisie_output_reality_filename = daisie_output_reality_filename
  )
  expect_true(file.exists(dme_params_filename))
  expect_true(file.exists(daisie_sim_results_filename))
  expect_true(file.exists(daisie_input_ideal_filename))
  expect_true(file.exists(daisie_input_reality_filename))
  expect_true(file.exists(daisie_output_ideal_filename))
  expect_true(file.exists(daisie_output_reality_filename))
})
