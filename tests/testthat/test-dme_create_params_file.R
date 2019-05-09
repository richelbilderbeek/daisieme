context("test-dme_create_params_file")

test_that("use", {

  filename <- tempfile()
  ana_psr <- 1.23
  clado_is_psr <- 2.34

  expect_silent(
    dme_create_params_file(
     filename = filename,
     ana_psr = ana_psr,
     clado_is_psr = clado_is_psr
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
})
