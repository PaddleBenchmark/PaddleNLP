/* Copyright (c) 2022 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#include "normalizers/utils.h"
#include "normalizers/bert.h"
#include "normalizers/replace.h"
#include "normalizers/strip.h"
#include "normalizers/unicode.h"
#include "unicode/unistr.h"

namespace tokenizers {
namespace normalizers {

void SequenceNormalizer::AppendNormalizer(Normalizer* normalizer) {
  std::shared_ptr<Normalizer> normalizer_ptr;
  if (typeid(*normalizer) == typeid(SequenceNormalizer)) {
    auto cast_normalizer = dynamic_cast<SequenceNormalizer*>(normalizer);
    normalizer_ptr = std::make_shared<SequenceNormalizer>(*cast_normalizer);
  } else if (typeid(*normalizer) == typeid(LowercaseNormalizer)) {
    auto cast_normalizer = dynamic_cast<LowercaseNormalizer*>(normalizer);
    normalizer_ptr = std::make_shared<LowercaseNormalizer>(*cast_normalizer);
  } else if (typeid(*normalizer) == typeid(StripNormalizer)) {
    auto cast_normalizer = dynamic_cast<StripNormalizer*>(normalizer);
    normalizer_ptr = std::make_shared<StripNormalizer>(*cast_normalizer);
  } else if (typeid(*normalizer) == typeid(StripAccentsNormalizer)) {
    auto cast_normalizer = dynamic_cast<StripAccentsNormalizer*>(normalizer);
    normalizer_ptr = std::make_shared<StripAccentsNormalizer>(*cast_normalizer);
  } else if (typeid(*normalizer) == typeid(NFCNormalizer)) {
    auto cast_normalizer = dynamic_cast<NFCNormalizer*>(normalizer);
    normalizer_ptr = std::make_shared<NFCNormalizer>(*cast_normalizer);
  } else if (typeid(*normalizer) == typeid(NFDNormalizer)) {
    auto cast_normalizer = dynamic_cast<NFDNormalizer*>(normalizer);
    normalizer_ptr = std::make_shared<NFDNormalizer>(*cast_normalizer);
  } else if (typeid(*normalizer) == typeid(NFKCNormalizer)) {
    auto cast_normalizer = dynamic_cast<NFKCNormalizer*>(normalizer);
    normalizer_ptr = std::make_shared<NFKCNormalizer>(*cast_normalizer);
  } else if (typeid(*normalizer) == typeid(NFKDNormalizer)) {
    auto cast_normalizer = dynamic_cast<NFKDNormalizer*>(normalizer);
    normalizer_ptr = std::make_shared<NFKDNormalizer>(*cast_normalizer);
  } else if (typeid(*normalizer) == typeid(NmtNormalizer)) {
    auto cast_normalizer = dynamic_cast<NmtNormalizer*>(normalizer);
    normalizer_ptr = std::make_shared<NmtNormalizer>(*cast_normalizer);
  } else if (typeid(*normalizer) == typeid(ReplaceNormalizer)) {
    auto cast_normalizer = dynamic_cast<ReplaceNormalizer*>(normalizer);
    normalizer_ptr = std::make_shared<ReplaceNormalizer>(*cast_normalizer);
  } else if (typeid(*normalizer) == typeid(BertNormalizer)) {
    auto cast_normalizer = dynamic_cast<BertNormalizer*>(normalizer);
    normalizer_ptr = std::make_shared<BertNormalizer>(*cast_normalizer);
  }
  normalizer_ptrs_.push_back(std::move(normalizer_ptr));
}

SequenceNormalizer::SequenceNormalizer(
    const std::vector<Normalizer*>& normalizers) {
  for (auto& normalizer : normalizers) {
    AppendNormalizer(normalizer);
  }
}

void SequenceNormalizer::operator()(NormalizedString* input) const {
  std::string result;
  for (auto& normalizer : normalizer_ptrs_) {
    normalizer->operator()(input);
  }
}
void LowercaseNormalizer::operator()(NormalizedString* input) const {
  input->Lowercase();
}

void to_json(nlohmann::json& j, const SequenceNormalizer& normalizer) {
  j = {{"type", "SequenceNormalizer"}};
}

void from_json(const nlohmann::json& j, SequenceNormalizer& normalizer) {}

void to_json(nlohmann::json& j, const LowercaseNormalizer& normalizer) {
  j = {
      {"type", "LowercaseNormalizer"},
  };
}

void from_json(const nlohmann::json& j, LowercaseNormalizer& normalizer) {}

}  // normalizers
}  // tokenizers
