// Copyright (c) 2021 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "lite/kernels/nnadapter/converter/converter.h"

namespace paddle {
namespace lite {
namespace kernels {
namespace nnadapter {

int ConvertDropout(Converter* converter, OpInfo* op, Scope* scope) {
  // Extract op attributes
  // Input
  auto x_name = op->Input("X").front();
  auto x_scale_name = "X0_scale";
  std::vector<float> x_scales;
  if (op->HasInputScale(x_scale_name, true)) {
    x_scales = op->GetInputScale(x_scale_name, true);
  }
  // Scale
  auto dropout_implementation =
      op->GetAttr<std::string>("dropout_implementation");
  float scale = dropout_implementation == "upscale_in_train"
                    ? 1.f
                    : 1 - op->GetAttr<float>("dropout_prob");
  // Output
  auto output_name = op->Output("Out").front();
  auto output_scale_name = "Out0_scale";
  std::vector<float> output_scales;
  if (op->HasOutputScale(output_scale_name, true)) {
    output_scales = op->GetOutputScale(output_scale_name, true);
  }

  // Convert to NNAdapter operands and operation
  // Input operand
  auto input_operand = converter->AddInputOperand(scope, x_name, {}, x_scales);
  // Prob operand
  auto prob_operand = converter->AddConstantOperand(scale);
  // Fuse code operand
  auto fuse_code_operand =
      converter->AddConstantOperand(static_cast<int32_t>(NNADAPTER_FUSED_NONE));
  // output
  auto output_operand = converter->AddOutputOperand(output_name, output_scales);
  // Mul operation
  converter->AddOperation(NNADAPTER_MUL,
                          {input_operand, prob_operand, fuse_code_operand},
                          {output_operand});
  return NO_ERROR;
}

}  // namespace nnadapter
}  // namespace kernels
}  // namespace lite
}  // namespace paddle
