// Copyright 2016 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifdef UNSAFE_BUFFERS_BUILD
// TODO(crbug.com/40284755): Remove this and spanify to fix the errors.
#pragma allow_unsafe_buffers
#endif

// A fuzzer that checks correctness of json parser/writer.
// The fuzzer input is passed through parsing twice,
// so that presumably valid json is parsed/written again.

#include <stddef.h>
#include <stdint.h>

#include <string>
#include <string_view>

#include "base/json/json_reader.h"
#include "base/json/json_writer.h"
#include "base/json/string_escape.h"
#include "base/logging.h"
#include "base/values.h"

// Entry point for libFuzzer.
// We will use the last byte of data as parsing options.
// The rest will be used as text input to the parser.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2)
    return 0;

  // Create a copy of input buffer, as otherwise we don't catch
  // overflow that touches the last byte (which is used in options).
  std::unique_ptr<char[]> input(new char[size - 1]);
  memcpy(input.get(), data, size - 1);

  std::string_view input_string(input.get(), size - 1);

  const int options = data[size - 1];
  auto result =
      base::JSONReader::ReadAndReturnValueWithError(input_string, options);
  if (!result.has_value())
    return 0;

  std::string parsed_output;
  bool b = base::JSONWriter::Write(*result, &parsed_output);
  LOG_ASSERT(b);

  auto double_result =
      base::JSONReader::ReadAndReturnValueWithError(parsed_output, options);
  LOG_ASSERT(double_result.has_value());
  std::string double_parsed_output;
  bool b2 = base::JSONWriter::Write(*double_result, &double_parsed_output);
  LOG_ASSERT(b2);

  LOG_ASSERT(parsed_output == double_parsed_output)
      << "Parser/Writer mismatch."
      << "\nInput=" << base::GetQuotedJSONString(parsed_output)
      << "\nOutput=" << base::GetQuotedJSONString(double_parsed_output);

  return 0;
}
