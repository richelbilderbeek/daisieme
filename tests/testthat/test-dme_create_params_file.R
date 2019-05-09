context("test-dme_create_params_file")

test_that("use", {

  filename <- tempfile()
  ana_psr <- 1.23
  clado_is_psr <- 2.34
  clado_main_psr <- 3.45
  ext_is_psr <- 0.12
  ext_main_psr <- 0.23
  mig_to_is_psr <- 4.56
  carry_cap_is <- 42
  carry_cap_main <- 314
  rng_seed <- 227
  init_n_main_clades <- 1

  expect_silent(
    dme_create_params_file(
      filename = filename,
      ana_psr = ana_psr,
      clado_is_psr = clado_is_psr,
      clado_main_psr = clado_main_psr,
      ext_is_psr = ext_is_psr,
      ext_main_psr = ext_main_psr,
      mig_to_is_psr = mig_to_is_psr,
      carry_cap_is = carry_cap_is,
      carry_cap_main = carry_cap_main,
      rng_seed = rng_seed,
      init_n_main_clades = init_n_main_clades
    )
  )
  expect_true(file.exists(filename))

  # ana rate is present once, be carefull with the floating point numbers
  expect_equal(1,
    sum(!is.na(stringr::str_match(string = readLines(filename),
      pattern = paste0("ana: ", ana_psr)))
    )
  )
  expect_equal(1,
    sum(!is.na(stringr::str_match(string = readLines(filename),
      pattern = paste0("clado_is: ", clado_is_psr)))
    )
  )
  expect_equal(1,
    sum(!is.na(stringr::str_match(string = readLines(filename),
      pattern = paste0("clado_main: ", clado_main_psr)))
    )
  )
  expect_equal(1,
    sum(!is.na(stringr::str_match(string = readLines(filename),
      pattern = paste0("ext_is: ", ext_is_psr)))
    )
  )
  expect_equal(1,
    sum(!is.na(stringr::str_match(string = readLines(filename),
      pattern = paste0("ext_main: ", ext_main_psr)))
    )
  )
  expect_equal(1,
    sum(!is.na(stringr::str_match(string = readLines(filename),
      pattern = paste0("mig_to_is: ", mig_to_is_psr)))
    )
  )
  expect_equal(1,
    sum(!is.na(stringr::str_match(string = readLines(filename),
      pattern = paste0("carryingcap_is: ", carry_cap_is)))
    )
  )
  expect_equal(1,
    sum(!is.na(stringr::str_match(string = readLines(filename),
      pattern = paste0("carryingcap_main: ", carry_cap_main)))
    )
  )
  expect_equal(1,
    sum(!is.na(stringr::str_match(string = readLines(filename),
      pattern = paste0("rng_seed: ", rng_seed)))
    )
  )
  expect_equal(1,
    sum(!is.na(stringr::str_match(string = readLines(filename),
      pattern = paste0("init_n_main_cls: ", init_n_main_clades)))
    )
  )

})
