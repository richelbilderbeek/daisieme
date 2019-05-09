context("test-dme_create_params_file")

test_that("use", {

  filename <- tempfile()
  expect_silent(dme_create_params_file(filename = filename))
  expect_true(file.exists(filename))
})
