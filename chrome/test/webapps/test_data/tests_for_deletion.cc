// Copyright 2021 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if BUILDFLAG(IS_WIN)
#define MAYBE_WAI_3Chicken_1Chicken_2ChickenGreen \
  DISABLED_WAI_3Chicken_1Chicken_2ChickenGreen
#else
#define MAYBE_WAI_3Chicken_1Chicken_2ChickenGreen \
  WAI_3Chicken_1Chicken_2ChickenGreen
#endif
IN_PROC_BROWSER_TEST_F(TestName, MAYBE_WAI_3Chicken_1Chicken_2ChickenGreen) {
  // Test contents are generated by script. Please do not modify!
  // See `docs/webapps/why-is-this-test-failing.md` or
  // `docs/webapps/integration-testing-framework` for more info.
  // Gardeners: Disabling this test is supported.
  helper_.StateChangeA(Animal::kChicken);
  helper_.CheckA(Animal::kChicken);
  helper_.CheckB(Animal::kChicken, Color::kGreen);
}

IN_PROC_BROWSER_TEST_F(TestName, WAI_TEST_TO_DELETE) {
  // Test contents are generated by script. Please do not modify!
  // See `docs/webapps/why-is-this-test-failing.md` or
  // `docs/webapps/integration-testing-framework` for more info.
  // Gardeners: Disabling this test is supported.
  helper_.StateChangeA(Animal::kChicken);
  helper_.CheckA(Animal::kChicken);
  helper_.CheckB(Animal::kChicken, Color::kGreen);
  helper_.CheckA();
}
