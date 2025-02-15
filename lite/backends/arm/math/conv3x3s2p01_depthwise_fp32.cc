// Copyright (c) 2019 PaddlePaddle Authors. All Rights Reserved.
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

#include <arm_neon.h>
#include "lite/backends/arm/math/conv_block_utils.h"
#include "lite/backends/arm/math/conv_depthwise.h"
#include "lite/core/parallel_defines.h"

namespace paddle {
namespace lite {
namespace arm {
namespace math {
void conv_depthwise_3x3s2p0_bias_relu6(float* dout,
                                       const float* din,
                                       const float* weights,
                                       const float* bias,
                                       const float* six,
                                       bool flag_bias,
                                       const int num,
                                       const int ch_in,
                                       const int h_in,
                                       const int w_in,
                                       const int h_out,
                                       const int w_out,
                                       ARMContext* ctx);

void conv_depthwise_3x3s2p0_bias_leakyRelu(float* dout,
                                           const float* din,
                                           const float* weights,
                                           const float* bias,
                                           const float* scale,
                                           bool flag_bias,
                                           const int num,
                                           const int ch_in,
                                           const int h_in,
                                           const int w_in,
                                           const int h_out,
                                           const int w_out,
                                           ARMContext* ctx);

void conv_depthwise_3x3s2p0_bias_s_relu6(float* dout,
                                         const float* din,
                                         const float* weights,
                                         const float* bias,
                                         const float* six,
                                         bool flag_bias,
                                         const int num,
                                         const int ch_in,
                                         const int h_in,
                                         const int w_in,
                                         const int h_out,
                                         const int w_out,
                                         ARMContext* ctx);

void conv_depthwise_3x3s2p0_bias_s_leakyRelu(float* dout,
                                             const float* din,
                                             const float* weights,
                                             const float* bias,
                                             const float* scale,
                                             bool flag_bias,
                                             const int num,
                                             const int ch_in,
                                             const int h_in,
                                             const int w_in,
                                             const int h_out,
                                             const int w_out,
                                             ARMContext* ctx);

void conv_depthwise_3x3s2p1_bias_relu6(float* dout,
                                       const float* din,
                                       const float* weights,
                                       const float* bias,
                                       const float* six,
                                       bool flag_bias,
                                       const int num,
                                       const int ch_in,
                                       const int h_in,
                                       const int w_in,
                                       const int h_out,
                                       const int w_out,
                                       ARMContext* ctx);

void conv_depthwise_3x3s2p1_bias_leakyRelu(float* dout,
                                           const float* din,
                                           const float* weights,
                                           const float* bias,
                                           const float* scale,
                                           bool flag_bias,
                                           const int num,
                                           const int ch_in,
                                           const int h_in,
                                           const int w_in,
                                           const int h_out,
                                           const int w_out,
                                           ARMContext* ctx);

void conv_depthwise_3x3s2p1_bias_s_relu6(float* dout,
                                         const float* din,
                                         const float* weights,
                                         const float* bias,
                                         const float* six,
                                         bool flag_bias,
                                         const int num,
                                         const int ch_in,
                                         const int h_in,
                                         const int w_in,
                                         const int h_out,
                                         const int w_out,
                                         ARMContext* ctx);

void conv_depthwise_3x3s2p1_bias_s_leakyRelu(float* dout,
                                             const float* din,
                                             const float* weights,
                                             const float* bias,
                                             const float* scale,
                                             bool flag_bias,
                                             const int num,
                                             const int ch_in,
                                             const int h_in,
                                             const int w_in,
                                             const int h_out,
                                             const int w_out,
                                             ARMContext* ctx);

void conv_depthwise_3x3s2_fp32(const float* din,
                               float* dout,
                               int num,
                               int ch_out,
                               int h_out,
                               int w_out,
                               int ch_in,
                               int h_in,
                               int w_in,
                               const float* weights,
                               const float* bias,
                               int pad,
                               bool flag_bias,
                               const operators::ActivationParam act_param,
                               ARMContext* ctx) {
  bool has_active = act_param.has_active;
  auto act_type = act_param.active_type;
  float tmp = act_param.Relu_clipped_coef;
  float ss = act_param.Leaky_relu_alpha;
  float vsix[4] = {tmp, tmp, tmp, tmp};
  float vscale[4] = {ss, ss, ss, ss};
  if (has_active) {
    switch (act_type) {
      case lite_api::ActivationType::kRelu:
        if (pad == 0) {
          if (w_in > 8) {
            conv_depthwise_3x3s2p0_bias_relu(dout,
                                             din,
                                             weights,
                                             bias,
                                             flag_bias,
                                             true,
                                             num,
                                             ch_in,
                                             h_in,
                                             w_in,
                                             h_out,
                                             w_out,
                                             ctx);
          } else {
            conv_depthwise_3x3s2p0_bias_s_relu(dout,
                                               din,
                                               weights,
                                               bias,
                                               flag_bias,
                                               true,
                                               num,
                                               ch_in,
                                               h_in,
                                               w_in,
                                               h_out,
                                               w_out,
                                               ctx);
          }
        }
        if (pad == 1) {
          if (w_in > 7) {
            conv_depthwise_3x3s2p1_bias_relu(dout,
                                             din,
                                             weights,
                                             bias,
                                             flag_bias,
                                             true,
                                             num,
                                             ch_in,
                                             h_in,
                                             w_in,
                                             h_out,
                                             w_out,
                                             ctx);
          } else {
            conv_depthwise_3x3s2p1_bias_s_relu(dout,
                                               din,
                                               weights,
                                               bias,
                                               flag_bias,
                                               true,
                                               num,
                                               ch_in,
                                               h_in,
                                               w_in,
                                               h_out,
                                               w_out,
                                               ctx);
          }
        }
        break;
      case lite_api::ActivationType::kRelu6:
        if (pad == 0) {
          if (w_in > 8) {
            conv_depthwise_3x3s2p0_bias_relu6(dout,
                                              din,
                                              weights,
                                              bias,
                                              vsix,
                                              flag_bias,
                                              num,
                                              ch_in,
                                              h_in,
                                              w_in,
                                              h_out,
                                              w_out,
                                              ctx);
          } else {
            conv_depthwise_3x3s2p0_bias_s_relu6(dout,
                                                din,
                                                weights,
                                                bias,
                                                vsix,
                                                flag_bias,
                                                num,
                                                ch_in,
                                                h_in,
                                                w_in,
                                                h_out,
                                                w_out,
                                                ctx);
          }
        }
        if (pad == 1) {
          if (w_in > 7) {
            conv_depthwise_3x3s2p1_bias_relu6(dout,
                                              din,
                                              weights,
                                              bias,
                                              vsix,
                                              flag_bias,
                                              num,
                                              ch_in,
                                              h_in,
                                              w_in,
                                              h_out,
                                              w_out,
                                              ctx);
          } else {
            conv_depthwise_3x3s2p1_bias_s_relu6(dout,
                                                din,
                                                weights,
                                                bias,
                                                vsix,
                                                flag_bias,
                                                num,
                                                ch_in,
                                                h_in,
                                                w_in,
                                                h_out,
                                                w_out,
                                                ctx);
          }
        }
        break;
      case lite_api::ActivationType::kLeakyRelu:
        if (pad == 0) {
          if (w_in > 8) {
            conv_depthwise_3x3s2p0_bias_leakyRelu(dout,
                                                  din,
                                                  weights,
                                                  bias,
                                                  vscale,
                                                  flag_bias,
                                                  num,
                                                  ch_in,
                                                  h_in,
                                                  w_in,
                                                  h_out,
                                                  w_out,
                                                  ctx);
          } else {
            conv_depthwise_3x3s2p0_bias_s_leakyRelu(dout,
                                                    din,
                                                    weights,
                                                    bias,
                                                    vscale,
                                                    flag_bias,
                                                    num,
                                                    ch_in,
                                                    h_in,
                                                    w_in,
                                                    h_out,
                                                    w_out,
                                                    ctx);
          }
        }
        if (pad == 1) {
          if (w_in > 7) {
            conv_depthwise_3x3s2p1_bias_leakyRelu(dout,
                                                  din,
                                                  weights,
                                                  bias,
                                                  vscale,
                                                  flag_bias,
                                                  num,
                                                  ch_in,
                                                  h_in,
                                                  w_in,
                                                  h_out,
                                                  w_out,
                                                  ctx);
          } else {
            conv_depthwise_3x3s2p1_bias_s_leakyRelu(dout,
                                                    din,
                                                    weights,
                                                    bias,
                                                    vscale,
                                                    flag_bias,
                                                    num,
                                                    ch_in,
                                                    h_in,
                                                    w_in,
                                                    h_out,
                                                    w_out,
                                                    ctx);
          }
        }
        break;
      default:
        LOG(FATAL) << "this act_type: " << static_cast<int>(act_type)
                   << " fuse not support";
    }
  } else {
    if (pad == 0) {
      if (w_in > 8) {
        conv_depthwise_3x3s2p0_bias_no_relu(dout,
                                            din,
                                            weights,
                                            bias,
                                            flag_bias,
                                            false,
                                            num,
                                            ch_in,
                                            h_in,
                                            w_in,
                                            h_out,
                                            w_out,
                                            ctx);
      } else {
        conv_depthwise_3x3s2p0_bias_s_no_relu(dout,
                                              din,
                                              weights,
                                              bias,
                                              flag_bias,
                                              false,
                                              num,
                                              ch_in,
                                              h_in,
                                              w_in,
                                              h_out,
                                              w_out,
                                              ctx);
      }
    }
    if (pad == 1) {
      if (w_in > 7) {
        conv_depthwise_3x3s2p1_bias_no_relu(dout,
                                            din,
                                            weights,
                                            bias,
                                            flag_bias,
                                            false,
                                            num,
                                            ch_in,
                                            h_in,
                                            w_in,
                                            h_out,
                                            w_out,
                                            ctx);
      } else {
        conv_depthwise_3x3s2p1_bias_s_no_relu(dout,
                                              din,
                                              weights,
                                              bias,
                                              flag_bias,
                                              false,
                                              num,
                                              ch_in,
                                              h_in,
                                              w_in,
                                              h_out,
                                              w_out,
                                              ctx);
      }
    }
  }
}
// clang-format off
#ifdef __aarch64__
#define INIT_S2                                  \
  "prfm pldl1keep, [%[inptr0]]             \n"   \
  "prfm pldl1keep, [%[inptr1]]             \n"   \
  "prfm pldl1keep, [%[inptr2]]             \n"   \
  "prfm pldl1keep, [%[inptr3]]             \n"   \
  "prfm pldl1keep, [%[inptr4]]             \n"   \
  "ld2  {v0.4s, v1.4s}, [%[inptr0]], #32    \n"  \
  "ld2  {v2.4s, v3.4s}, [%[inptr1]], #32    \n"  \
  "ld2  {v4.4s, v5.4s}, [%[inptr2]], #32    \n"  \
  "ld2  {v6.4s, v7.4s}, [%[inptr3]], #32    \n"  \
  "ld2  {v8.4s, v9.4s}, [%[inptr4]], #32    \n"  \
                                                 \
  "and  v16.16b, %[vbias].16b, %[vbias].16b  \n" \
  "and  v17.16b, %[vbias].16b, %[vbias].16b  \n"

#define LEFT_COMPUTE_S2                                                   \
  "ext  v10.16b, %[vzero].16b, v1.16b, #12     \n" /* r0 */               \
  "fmul v11.4s, v0.4s, %[w0].s[1]            \n"   /*  {0,2,4,6} * w01 */ \
  "fmul v12.4s, v1.4s, %[w0].s[2]            \n"   /* {1,3,5,7} * w02 */  \
  "fmla v16.4s, v10.4s, %[w0].s[0]            \n"  /* {0,1,3,5} * w00*/   \
                                                                          \
  "ext  v10.16b, %[vzero].16b, v3.16b, #12     \n" /* v10 = {0,1,3,5} */  \
                                                                          \
  "sub %[inptr0], %[inptr0], #4            \n"                            \
  "sub %[inptr1], %[inptr1], #4             \n" /* r1 */                  \
  "fmla v11.4s, v2.4s, %[w1].s[1]            \n"                          \
  "fmla v12.4s, v3.4s, %[w1].s[2]            \n"                          \
  "fmla v16.4s, v10.4s, %[w1].s[0]            \n"                         \
                                                                          \
  "ext  v10.16b, %[vzero].16b, v5.16b, #12     \n"                        \
                                                                          \
  "sub %[inptr2], %[inptr2], #4            \n"                            \
  "sub %[inptr3], %[inptr3], #4             \n" /* r2 */                  \
  "fmul v13.4s, v4.4s, %[w0].s[1]            \n"                          \
  "fmla v11.4s, v4.4s, %[w2].s[1]            \n"                          \
                                                                          \
  "fmul v14.4s, v5.4s, %[w0].s[2]            \n"                          \
  "fmla v12.4s, v5.4s, %[w2].s[2]            \n"                          \
                                                                          \
  "fmla v17.4s, v10.4s, %[w0].s[0]            \n"                         \
  "fmla v16.4s, v10.4s, %[w2].s[0]            \n"                         \
                                                                          \
  "ext  v10.16b, %[vzero].16b, v7.16b, #12     \n"                        \
                                                                          \
  "sub %[inptr4], %[inptr4], #4            \n" /* r3 */                   \
  "fmla v13.4s, v6.4s, %[w1].s[1]            \n"                          \
  "fmla v14.4s, v7.4s, %[w1].s[2]            \n"                          \
  "fmla v17.4s, v10.4s, %[w1].s[0]            \n"                         \
                                                                          \
  "ext  v10.16b, %[vzero].16b, v9.16b, #12     \n"                        \
  "fadd v16.4s, v16.4s, v11.4s                  \n"                       \
  "fadd v16.4s, v16.4s, v12.4s                  \n" /* r4 */              \
  "fmla v13.4s, v8.4s, %[w2].s[1]            \n"                          \
  "fmla v14.4s, v9.4s, %[w2].s[2]            \n"                          \
  "fmla v17.4s, v10.4s, %[w2].s[0]            \n"

#define LEFT_RESULT_S2                              \
  "st1 {v16.4s}, [%[outptr0]], #16              \n" \
                                                    \
  "ld2  {v0.4s, v1.4s}, [%[inptr0]], #32    \n"     \
  "ld2  {v2.4s, v3.4s}, [%[inptr1]], #32    \n"     \
  "ld2  {v4.4s, v5.4s}, [%[inptr2]], #32    \n"     \
                                                    \
  "fadd v17.4s, v17.4s, v13.4s                  \n" \
                                                    \
  "ld2  {v6.4s, v7.4s}, [%[inptr3]], #32    \n"     \
  "ld2  {v8.4s, v9.4s}, [%[inptr4]], #32    \n"     \
  "ld1 {v15.4s}, [%[inptr0]]                 \n"    \
  "and  v16.16b, %[vbias].16b, %[vbias].16b  \n"    \
                                                    \
  "fadd v17.4s, v17.4s, v14.4s                  \n" \
                                                    \
  "ld1 {v18.4s}, [%[inptr1]]                 \n"    \
  "ld1 {v19.4s}, [%[inptr2]]                 \n"    \
                                                    \
  "ext  v10.16b, v0.16b, v15.16b, #4     \n"        \
                                                    \
  "ld1 {v20.4s}, [%[inptr3]]                 \n"    \
  "ld1 {v21.4s}, [%[inptr4]]                 \n"    \
                                                    \
  "st1 {v17.4s}, [%[outptr1]], #16              \n" \
                                                    \
  "cmp %w[cnt], #1                             \n"  \
                                                    \
  "and  v17.16b, %[vbias].16b, %[vbias].16b  \n"    \
                                                    \
  "blt 1f                                     \n"

#define MID_COMPUTE_S2                                       \
  "2:                                          \n" /* r0 */  \
  "fmul v11.4s, v0.4s, %[w0].s[0]            \n"             \
  "fmul v12.4s, v1.4s, %[w0].s[1]            \n"             \
  "fmla v16.4s, v10.4s, %[w0].s[2]            \n"            \
                                                             \
  "ext  v10.16b, v2.16b, v18.16b, #4     \n"                 \
  "ld2  {v0.4s, v1.4s}, [%[inptr0]], #32    \n" /* r1 */     \
  "fmla v11.4s, v2.4s, %[w1].s[0]            \n"             \
  "fmla v12.4s, v3.4s, %[w1].s[1]            \n"             \
  "fmla v16.4s, v10.4s, %[w1].s[2]            \n"            \
                                                             \
  "ext  v10.16b, v4.16b, v19.16b, #4     \n"                 \
                                                             \
  "ld2  {v2.4s, v3.4s}, [%[inptr1]], #32    \n" /* r2 */     \
  "fmul v13.4s, v4.4s, %[w0].s[0]            \n"             \
  "fmla v11.4s, v4.4s, %[w2].s[0]            \n"             \
                                                             \
  "fmul v14.4s, v5.4s, %[w0].s[1]            \n"             \
  "fmla v12.4s, v5.4s, %[w2].s[1]            \n"             \
                                                             \
  "fmla v17.4s, v10.4s, %[w0].s[2]            \n"            \
  "fmla v16.4s, v10.4s, %[w2].s[2]            \n"            \
                                                             \
  "ext  v10.16b, v6.16b, v20.16b, #4     \n"                 \
                                                             \
  "ld2  {v4.4s, v5.4s}, [%[inptr2]], #32    \n" /* r3 */     \
  "fmla v13.4s, v6.4s, %[w1].s[0]            \n"             \
  "fmla v14.4s, v7.4s, %[w1].s[1]            \n"             \
  "fmla v17.4s, v10.4s, %[w1].s[2]            \n"            \
                                                             \
  "ext  v10.16b, v8.16b, v21.16b, #4     \n"                 \
                                                             \
  "ld2  {v6.4s, v7.4s}, [%[inptr3]], #32    \n"              \
                                                             \
  "fadd v16.4s, v16.4s, v11.4s                  \n"          \
  "fadd v16.4s, v16.4s, v12.4s                  \n" /* r4 */ \
  "fmla v13.4s, v8.4s, %[w2].s[0]            \n"             \
  "fmla v14.4s, v9.4s, %[w2].s[1]            \n"             \
  "fmla v17.4s, v10.4s, %[w2].s[2]            \n"            \
                                                             \
  "ld2  {v8.4s, v9.4s}, [%[inptr4]], #32    \n"              \
  "ld1 {v15.4s}, [%[inptr0]]                 \n"             \
  "ld1 {v18.4s}, [%[inptr1]]                 \n"

#define MID_RESULT_S2                               \
  "st1 {v16.4s}, [%[outptr0]], #16              \n" \
                                                    \
  "fadd v17.4s, v17.4s, v13.4s                  \n" \
                                                    \
  "ld1 {v19.4s}, [%[inptr2]]                 \n"    \
  "ld1 {v20.4s}, [%[inptr3]]                 \n"    \
  "ld1 {v21.4s}, [%[inptr4]]                 \n"    \
                                                    \
  "fadd v17.4s, v17.4s, v14.4s                  \n" \
                                                    \
  "ext  v10.16b, v0.16b, v15.16b, #4     \n"        \
  "and  v16.16b, %[vbias].16b, %[vbias].16b  \n"    \
  "subs %w[cnt], %w[cnt], #1                    \n" \
                                                    \
  "st1 {v17.4s}, [%[outptr1]], #16              \n" \
                                                    \
  "and  v17.16b, %[vbias].16b, %[vbias].16b  \n"    \
                                                    \
  "bne  2b                                    \n"

#define RIGHT_COMPUTE_S2                                   \
  "1:                                          \n"         \
  "cmp %w[remain], #1                           \n"        \
  "blt 4f                                     \n"          \
  "3:                                         \n"          \
  \
  /* Avoid thread write conflicts */ \
  "sub %[inptr0], %[inptr0], #32 \n"                         \
  "sub %[inptr1], %[inptr1], #32 \n"                         \
  "sub %[inptr2], %[inptr2], #32 \n"                         \
  "sub %[inptr3], %[inptr3], #32 \n"                         \
  "sub %[inptr4], %[inptr4], #32 \n"                         \
  "sub %[inptr0], %[inptr0], %[right_pad_num_in] \n"               \
  "sub %[inptr1], %[inptr1], %[right_pad_num_in] \n"            \
  "sub %[inptr2], %[inptr2], %[right_pad_num_in] \n"               \
  "sub %[inptr3], %[inptr3], %[right_pad_num_in] \n"                  \
  "sub %[inptr4], %[inptr4], %[right_pad_num_in] \n"                \
  "ld2  {v0.4s, v1.4s}, [%[inptr0]], #32 \n"\
  "ld2  {v2.4s, v3.4s}, [%[inptr1]], #32 \n"\
  "ld2  {v4.4s, v5.4s}, [%[inptr2]], #32 \n"\
  "ld2  {v6.4s, v7.4s}, [%[inptr3]], #32 \n"\
  "ld2  {v8.4s, v9.4s}, [%[inptr4]], #32 \n"\
  "ld1 {v15.4s}, [%[inptr0]] \n"\
  "ld1 {v18.4s}, [%[inptr1]] \n"\
  "ld1 {v19.4s}, [%[inptr2]] \n"\
  "ld1 {v20.4s}, [%[inptr3]] \n"\
  "ld1 {v21.4s}, [%[inptr4]] \n"\
  "bif  v15.16b, %[vzero].16b, %[mask3].16b    \n"          \
  "bif  v18.16b, %[vzero].16b, %[mask3].16b    \n"          \
  "bif  v19.16b, %[vzero].16b, %[mask3].16b    \n"          \
  "bif  v20.16b, %[vzero].16b, %[mask3].16b    \n"          \
  "bif  v21.16b, %[vzero].16b, %[mask3].16b    \n"          \
  "sub %[outptr0], %[outptr0], %[right_pad_num_out] \n"  \
  "sub %[outptr1], %[outptr1], %[right_pad_num_out] \n"  \
  /* conflicts ends */ \
  \
  "bif  v0.16b, %[vzero].16b, %[mask1].16b    \n"          \
  "bif  v1.16b, %[vzero].16b, %[mask2].16b    \n"          \
                                                           \
  "bif  v2.16b, %[vzero].16b, %[mask1].16b    \n"          \
  "bif  v3.16b, %[vzero].16b, %[mask2].16b    \n"          \
                                                           \
  "bif  v4.16b, %[vzero].16b, %[mask1].16b    \n"          \
  "bif  v5.16b, %[vzero].16b, %[mask2].16b    \n"          \
                                                           \
  "ext  v10.16b, v0.16b, v15.16b, #4     \n"          \
                                                           \
  "bif  v6.16b, %[vzero].16b, %[mask1].16b    \n"          \
  "bif  v7.16b, %[vzero].16b, %[mask2].16b    \n" /* r0 */ \
  "fmul v11.4s, v0.4s, %[w0].s[0]            \n"           \
  "fmul v12.4s, v1.4s, %[w0].s[1]            \n"           \
  "fmla v16.4s, v10.4s, %[w0].s[2]            \n"          \
                                                           \
  "ext  v10.16b, v2.16b, v18.16b, #4     \n"          \
  "bif  v8.16b, %[vzero].16b, %[mask1].16b    \n"          \
  "bif  v9.16b, %[vzero].16b, %[mask2].16b    \n" /* r1 */ \
  "fmla v11.4s, v2.4s, %[w1].s[0]            \n"           \
  "fmla v12.4s, v3.4s, %[w1].s[1]            \n"           \
  "fmla v16.4s, v10.4s, %[w1].s[2]            \n"          \
                                                           \
  "ext  v10.16b, v4.16b, v19.16b, #4     \n" /* r2 */ \
  "fmul v13.4s, v4.4s, %[w0].s[0]            \n"           \
  "fmla v11.4s, v4.4s, %[w2].s[0]            \n"           \
                                                           \
  "fmul v14.4s, v5.4s, %[w0].s[1]            \n"           \
  "fmla v12.4s, v5.4s, %[w2].s[1]            \n"           \
                                                           \
  "fmla v17.4s, v10.4s, %[w0].s[2]            \n"          \
  "fmla v16.4s, v10.4s, %[w2].s[2]            \n"          \
                                                           \
  "ext  v10.16b, v6.16b, v20.16b, #4     \n" /* r3 */ \
  "fmla v13.4s, v6.4s, %[w1].s[0]            \n"           \
  "fmla v14.4s, v7.4s, %[w1].s[1]            \n"           \
  "fmla v17.4s, v10.4s, %[w1].s[2]            \n"          \
                                                           \
  "ext  v10.16b, v8.16b, v21.16b, #4     \n"          \
  "ld1 {v0.4s}, [%[outptr0]]                  \n"          \
                                                           \
  "fadd v16.4s, v16.4s, v11.4s                  \n"        \
  "fadd v16.4s, v16.4s, v12.4s                  \n"        \
  "ld1 {v1.4s}, [%[outptr1]]                  \n" /* r4 */ \
  "fmla v13.4s, v8.4s, %[w2].s[0]            \n"           \
  "fmla v14.4s, v9.4s, %[w2].s[1]            \n"           \
  "fmla v17.4s, v10.4s, %[w2].s[2]            \n"

#define RIGHT_RESULT_S2                             \
                                                    \
  "fadd v17.4s, v17.4s, v13.4s                  \n" \
                                                    \
  "st1 {v16.4s}, [%[outptr0]], #16              \n" \
                                                    \
  "fadd v17.4s, v17.4s, v14.4s                  \n" \
                                                    \
  "st1 {v17.4s}, [%[outptr1]], #16              \n" \
  "4:                                          \n"

#define LEFT_RESULT_S2_RELU                         \
  "fmax v16.4s, v16.4s, %[vzero].4s            \n"  \
                                                    \
  "ld2  {v0.4s, v1.4s}, [%[inptr0]], #32    \n"     \
  "ld2  {v2.4s, v3.4s}, [%[inptr1]], #32    \n"     \
  "ld2  {v4.4s, v5.4s}, [%[inptr2]], #32    \n"     \
                                                    \
  "fadd v17.4s, v17.4s, v13.4s                  \n" \
                                                    \
  "st1 {v16.4s}, [%[outptr0]], #16              \n" \
                                                    \
  "ld2  {v6.4s, v7.4s}, [%[inptr3]], #32    \n"     \
  "ld2  {v8.4s, v9.4s}, [%[inptr4]], #32    \n"     \
  "ld1 {v15.4s}, [%[inptr0]]                 \n"    \
                                                    \
  "fadd v17.4s, v17.4s, v14.4s                  \n" \
                                                    \
  "and  v16.16b, %[vbias].16b, %[vbias].16b  \n"    \
                                                    \
  "ld1 {v18.4s}, [%[inptr1]]                 \n"    \
  "ld1 {v19.4s}, [%[inptr2]]                 \n"    \
                                                    \
  "ext  v10.16b, v0.16b, v15.16b, #4     \n"        \
                                                    \
  "fmax v17.4s, v17.4s, %[vzero].4s            \n"  \
                                                    \
  "ld1 {v20.4s}, [%[inptr3]]                 \n"    \
  "ld1 {v21.4s}, [%[inptr4]]                 \n"    \
                                                    \
  "st1 {v17.4s}, [%[outptr1]], #16              \n" \
                                                    \
  "cmp %w[cnt], #1                             \n"  \
                                                    \
  "and  v17.16b, %[vbias].16b, %[vbias].16b  \n"    \
                                                    \
  "blt 1f                                     \n"
#define LEFT_RESULT_S2_RELU6                        \
  "fmax v16.4s, v16.4s, %[vzero].4s            \n"  \
  "ld1 {v22.4s}, [%[six_ptr]]                  \n"  \
                                                    \
  "ld2  {v0.4s, v1.4s}, [%[inptr0]], #32    \n"     \
  "ld2  {v2.4s, v3.4s}, [%[inptr1]], #32    \n"     \
  "ld2  {v4.4s, v5.4s}, [%[inptr2]], #32    \n"     \
                                                    \
  "fadd v17.4s, v17.4s, v13.4s                  \n" \
  "fmin v16.4s, v16.4s, v22.4s                  \n" \
                                                    \
  "ld2  {v6.4s, v7.4s}, [%[inptr3]], #32    \n"     \
  "ld2  {v8.4s, v9.4s}, [%[inptr4]], #32    \n"     \
  "ld1 {v15.4s}, [%[inptr0]]                 \n"    \
                                                    \
  "fadd v17.4s, v17.4s, v14.4s                  \n" \
  "st1 {v16.4s}, [%[outptr0]], #16              \n" \
                                                    \
  "ld1 {v18.4s}, [%[inptr1]]                 \n"    \
  "ld1 {v19.4s}, [%[inptr2]]                 \n"    \
                                                    \
  "ext  v10.16b, v0.16b, v15.16b, #4     \n"        \
                                                    \
  "and  v16.16b, %[vbias].16b, %[vbias].16b  \n"    \
  "fmax v17.4s, v17.4s, %[vzero].4s            \n"  \
                                                    \
  "ld1 {v20.4s}, [%[inptr3]]                 \n"    \
  "ld1 {v21.4s}, [%[inptr4]]                 \n"    \
                                                    \
  "fmin v17.4s, v17.4s, v22.4s                  \n" \
                                                    \
  "cmp %w[cnt], #1                             \n"  \
                                                    \
  "st1 {v17.4s}, [%[outptr1]], #16              \n" \
  "and  v17.16b, %[vbias].16b, %[vbias].16b  \n"    \
                                                    \
  "blt 1f                                     \n"

#define LEFT_RESULT_S2_LEAKY_RELU                         \
  "ld1 {v22.4s}, [%[scale_ptr]]                  \n"      \
  "fcmge v11.4s, v16.4s,  %[vzero].4s \n" /* vcgeq_f32 */ \
                                                          \
  "ld2  {v0.4s, v1.4s}, [%[inptr0]], #32    \n"           \
  "ld2  {v2.4s, v3.4s}, [%[inptr1]], #32    \n"           \
  "ld2  {v4.4s, v5.4s}, [%[inptr2]], #32    \n"           \
                                                          \
  "fmul v12.4s, v16.4s, v22.4s                  \n"       \
  "fadd v17.4s, v17.4s, v13.4s                  \n"       \
                                                          \
  "ld2  {v6.4s, v7.4s}, [%[inptr3]], #32    \n"           \
  "ld2  {v8.4s, v9.4s}, [%[inptr4]], #32    \n"           \
  "ld1 {v15.4s}, [%[inptr0]]                 \n"          \
                                                          \
  "fadd v17.4s, v17.4s, v14.4s                  \n"       \
  "bif  v16.16b, v12.16b, v11.16b \n" /* choose*/         \
                                                          \
  "ld1 {v18.4s}, [%[inptr1]]                 \n"          \
  "ld1 {v19.4s}, [%[inptr2]]                 \n"          \
                                                          \
  "ext  v10.16b, v0.16b, v15.16b, #4     \n"              \
                                                          \
  "st1 {v16.4s}, [%[outptr0]], #16              \n"       \
  "fcmge v11.4s, v17.4s,  %[vzero].4s \n" /* vcgeq_u32 */ \
  "fmul v12.4s, v17.4s, v22.4s                  \n"       \
                                                          \
  "ld1 {v20.4s}, [%[inptr3]]                 \n"          \
  "ld1 {v21.4s}, [%[inptr4]]                 \n"          \
                                                          \
  "and  v16.16b, %[vbias].16b, %[vbias].16b  \n"          \
  "bif v17.16b, v12.16b, v11.16b \n" /* choose*/          \
                                                          \
  "cmp %w[cnt], #1                             \n"        \
                                                          \
  "st1 {v17.4s}, [%[outptr1]], #16              \n"       \
  "and  v17.16b, %[vbias].16b, %[vbias].16b  \n"          \
                                                          \
  "blt 1f                                     \n"

#define MID_RESULT_S2_RELU                                    \
  "fmax v16.4s, v16.4s, %[vzero].4s            \n" /* relu */ \
                                                              \
  "fadd v17.4s, v17.4s, v13.4s                  \n"           \
                                                              \
  "ld1 {v19.4s}, [%[inptr2]]                 \n"              \
  "ld1 {v20.4s}, [%[inptr3]]                 \n"              \
  "ld1 {v21.4s}, [%[inptr4]]                 \n"              \
                                                              \
  "st1 {v16.4s}, [%[outptr0]], #16              \n"           \
                                                              \
  "fadd v17.4s, v17.4s, v14.4s                  \n"           \
                                                              \
  "ext  v10.16b, v0.16b, v15.16b, #4     \n"                  \
  "and  v16.16b, %[vbias].16b, %[vbias].16b  \n"              \
  "subs %w[cnt], %w[cnt], #1                    \n"           \
                                                              \
  "fmax v17.4s, v17.4s, %[vzero].4s            \n" /* relu */ \
                                                              \
  "st1 {v17.4s}, [%[outptr1]], #16              \n"           \
                                                              \
  "and  v17.16b, %[vbias].16b, %[vbias].16b  \n"              \
                                                              \
  "bne  2b                                    \n"

#define MID_RESULT_S2_RELU6                                   \
  "fmax v16.4s, v16.4s, %[vzero].4s            \n" /* relu */ \
                                                              \
  "fadd v17.4s, v17.4s, v13.4s                  \n"           \
                                                              \
  "ld1 {v19.4s}, [%[inptr2]]                 \n"              \
  "ld1 {v20.4s}, [%[inptr3]]                 \n"              \
  "ld1 {v21.4s}, [%[inptr4]]                 \n"              \
                                                              \
  "fmin v16.4s, v16.4s, v22.4s                  \n"           \
                                                              \
  "fadd v17.4s, v17.4s, v14.4s                  \n"           \
                                                              \
  "ext  v10.16b, v0.16b, v15.16b, #4     \n"                  \
  "st1 {v16.4s}, [%[outptr0]], #16              \n"           \
  "subs %w[cnt], %w[cnt], #1                    \n"           \
                                                              \
  "fmax v17.4s, v17.4s, %[vzero].4s            \n" /* relu */ \
  "and  v16.16b, %[vbias].16b, %[vbias].16b  \n"              \
  "fmin v17.4s, v17.4s, v22.4s                  \n"           \
  "st1 {v17.4s}, [%[outptr1]], #16              \n"           \
                                                              \
  "and  v17.16b, %[vbias].16b, %[vbias].16b  \n"              \
                                                              \
  "bne  2b                                    \n"

#define MID_RESULT_S2_LEAKY_RELU                          \
  "fcmge v11.4s, v16.4s,  %[vzero].4s \n" /* vcgeq_u32 */ \
  "fmul v12.4s, v16.4s, v22.4s                  \n"       \
                                                          \
  "fadd v17.4s, v17.4s, v13.4s                  \n"       \
                                                          \
  "ld1 {v19.4s}, [%[inptr2]]                 \n"          \
  "ld1 {v20.4s}, [%[inptr3]]                 \n"          \
  "ld1 {v21.4s}, [%[inptr4]]                 \n"          \
                                                          \
  "fadd v17.4s, v17.4s, v14.4s                  \n"       \
  "bif  v16.16b, v12.16b, v11.16b \n" /* choose*/         \
  "ext  v10.16b, v0.16b, v15.16b, #4     \n"              \
  "fcmge v11.4s, v17.4s,  %[vzero].4s \n" /* vcgeq_u32 */ \
  "fmul v12.4s, v17.4s, v22.4s                  \n"       \
                                                          \
  "st1 {v16.4s}, [%[outptr0]], #16              \n"       \
  "subs %w[cnt], %w[cnt], #1                    \n"       \
                                                          \
  "and  v16.16b, %[vbias].16b, %[vbias].16b  \n"          \
  "bif  v17.16b, v12.16b, v11.16b \n" /* choose*/         \
  "st1 {v17.4s}, [%[outptr1]], #16              \n"       \
                                                          \
  "and  v17.16b, %[vbias].16b, %[vbias].16b  \n"          \
                                                          \
  "bne  2b                                    \n"

#define RIGHT_RESULT_S2_RELU                                  \
  "fmax v16.4s, v16.4s, %[vzero].4s            \n" /* relu */ \
                                                              \
  "fadd v17.4s, v17.4s, v13.4s                  \n"           \
                                                              \
  "fadd v17.4s, v17.4s, v14.4s                  \n"           \
                                                              \
  "st1 {v16.4s}, [%[outptr0]], #16              \n"           \
                                                              \
  "fmax v17.4s, v17.4s, %[vzero].4s            \n" /* relu */ \
                                                              \
  "st1 {v17.4s}, [%[outptr1]], #16              \n"           \
  "4:                                          \n"

#define RIGHT_RESULT_S2_RELU6                                 \
  "fmax v16.4s, v16.4s, %[vzero].4s            \n" /* relu */ \
                                                              \
  "fadd v17.4s, v17.4s, v13.4s                  \n"           \
                                                              \
  "fmin v16.4s, v16.4s, v22.4s                  \n"           \
                                                              \
  "fadd v17.4s, v17.4s, v14.4s                  \n"           \
                                                              \
  "fmax v17.4s, v17.4s, %[vzero].4s            \n" /* relu */ \
                                                              \
  "st1 {v16.4s}, [%[outptr0]], #16              \n"           \
  "fmin v17.4s, v17.4s, v22.4s                  \n"           \
                                                              \
  "st1 {v17.4s}, [%[outptr1]], #16              \n"           \
  "4:                                          \n"

#define RIGHT_RESULT_S2_LEAKY_RELU                        \
  "fcmge v11.4s, v16.4s,  %[vzero].4s \n" /* vcgeq_u32 */ \
  "fmul v12.4s, v16.4s, v22.4s                  \n"       \
  "fadd v17.4s, v17.4s, v13.4s                  \n"       \
                                                          \
  "bif  v16.16b, v12.16b, v11.16b \n" /* choose*/         \
                                                          \
  "fadd v17.4s, v17.4s, v14.4s                  \n"       \
                                                          \
  "fcmge v11.4s, v17.4s,  %[vzero].4s \n" /* vcgeq_u32 */ \
  "fmul v12.4s, v17.4s, v22.4s                  \n"       \
                                                          \
  "st1 {v16.4s}, [%[outptr0]], #16              \n"       \
  "bif  v17.16b, v12.16b, v11.16b \n" /* choose*/         \
                                                          \
  "st1 {v17.4s}, [%[outptr1]], #16              \n"       \
  "4:                                          \n"

#define COMPUTE_S_S2                                  \
  "movi v9.4s, #0                                 \n" \
  "ld1  {v6.4s, v7.4s}, [%[mask_ptr]], #32        \n" \
                                                      \
  "ld2  {v10.4s, v11.4s}, [%[din0_ptr]], #32      \n" \
  "ld2  {v12.4s, v13.4s}, [%[din1_ptr]], #32      \n" \
  "ld2  {v14.4s, v15.4s}, [%[din2_ptr]], #32      \n" \
                                                      \
  "bif v10.16b, v9.16b, v6.16b                    \n" \
  "bif v11.16b, v9.16b, v7.16b                    \n" \
  "bif v12.16b, v9.16b, v6.16b                    \n" \
  "bif v13.16b, v9.16b, v7.16b                    \n" \
  "bif v14.16b, v9.16b, v6.16b                    \n" \
  "bif v15.16b, v9.16b, v7.16b                    \n" \
                                                      \
  "ext v6.16b, v9.16b, v11.16b, #12               \n" \
  "ext v7.16b, v9.16b, v13.16b, #12               \n" \
  "ext v8.16b, v9.16b, v15.16b, #12               \n" \
                                                      \
  "fmul v4.4s, v10.4s, %[wr0].s[1]                \n" \
  "fmul v5.4s, v11.4s, %[wr0].s[2]                \n" \
  "fmul v6.4s, v6.4s,  %[wr0].s[0]                \n" \
                                                      \
  "fmla v4.4s, v12.4s, %[wr1].s[1]                \n" \
  "fmla v5.4s, v13.4s, %[wr1].s[2]                \n" \
  "fmla v6.4s, v7.4s,  %[wr1].s[0]                \n" \
                                                      \
  "fmla v4.4s, v14.4s, %[wr2].s[1]                \n" \
  "fmla v5.4s, v15.4s, %[wr2].s[2]                \n" \
  "fmla v6.4s, v8.4s,  %[wr2].s[0]                \n" \
                                                      \
  "fadd v4.4s, v4.4s, v5.4s                       \n" \
  "fadd v4.4s, v4.4s, v6.4s                       \n"

#define RESULT_S_S2                                   \
  "fadd v4.4s, v4.4s, %[bias].4s                  \n" \
                                                      \
  "st1 {v4.4s}, [%[out]]                          \n"

#define RESULT_S_S2_RELU                              \
  "fadd v4.4s, v4.4s, %[bias].4s                  \n" \
  "fmax v4.4s, v4.4s, v9.4s                       \n" \
                                                      \
  "st1 {v4.4s}, [%[out]]                          \n"
#define RESULT_S_S2_RELU6                             \
  "fadd v4.4s, v4.4s, %[bias].4s                  \n" \
  "fmax v4.4s, v4.4s, v9.4s                       \n" \
  "fmin v4.4s, v4.4s, %[vsix].4s                  \n" \
                                                      \
  "st1 {v4.4s}, [%[out]]                          \n"
#define RESULT_S_S2_LEAKY_RELU                        \
  "fadd v4.4s, v4.4s, %[bias].4s                  \n" \
  "fcmge v11.4s, v4.4s, %[vzero].4s \n"/* vcgeq_u32 */\
  "fmul v12.4s, v4.4s, %[vscale].4s                \n"\
  "bif  v4.16b, v12.16b, v11.16b \n" /* choose*/      \
  "st1 {v4.4s}, [%[out]]                          \n"
#define COMPUTE_S_S2_P0                                \
  "movi v9.4s, #0                                 \n"  \
  "ld1  {v6.4s, v7.4s}, [%[mask_ptr]], #32        \n"  \
                                                       \
  "ld2  {v10.4s, v11.4s}, [%[din0_ptr]], #32      \n"  \
  "ld2  {v12.4s, v13.4s}, [%[din1_ptr]], #32      \n"  \
  "ld2  {v14.4s, v15.4s}, [%[din2_ptr]], #32      \n"  \
  "and  v4.16b, %[bias].16b, %[bias].16b  \n"          \
                                                       \
  "bif v10.16b, v9.16b, v6.16b                    \n"  \
  "bif v11.16b, v9.16b, v7.16b                    \n"  \
  "bif v12.16b, v9.16b, v6.16b                    \n"  \
  "bif v13.16b, v9.16b, v7.16b                    \n"  \
  "bif v14.16b, v9.16b, v6.16b                    \n"  \
  "bif v15.16b, v9.16b, v7.16b                    \n"  \
                                                       \
  "ext v6.16b, v10.16b, v9.16b, #4               \n"   \
  "ext v7.16b, v12.16b, v9.16b, #4               \n"   \
  "ext v8.16b, v14.16b, v9.16b, #4               \n"   \
                                                       \
  "fmla v4.4s, v10.4s, %[wr0].s[0]                \n"  \
  "fmul v5.4s, v11.4s, %[wr0].s[1]                \n"  \
  "fmul v16.4s, v6.4s,  %[wr0].s[2]                \n" \
                                                       \
  "fmla v4.4s, v12.4s, %[wr1].s[0]                \n"  \
  "fmla v5.4s, v13.4s, %[wr1].s[1]                \n"  \
  "fmla v16.4s, v7.4s,  %[wr1].s[2]                \n" \
                                                       \
  "fmla v4.4s, v14.4s, %[wr2].s[0]                \n"  \
  "fmla v5.4s, v15.4s, %[wr2].s[1]                \n"  \
  "fmla v16.4s, v8.4s,  %[wr2].s[2]                \n" \
                                                       \
  "fadd v4.4s, v4.4s, v5.4s                       \n"  \
  "fadd v4.4s, v4.4s, v16.4s                       \n"

#define RESULT_S_S2_P0 "st1 {v4.4s}, [%[out]]                          \n"
#define RESULT_S_S2_P0_RELU                           \
  "fmax v4.4s, v4.4s, v9.4s                       \n" \
  "st1 {v4.4s}, [%[out]]                          \n"
#define RESULT_S_S2_P0_RELU6                          \
  "fmax v4.4s, v4.4s, v9.4s                       \n" \
  "fmin v4.4s, v4.4s, %[vsix].4s                  \n" \
  "st1 {v4.4s}, [%[out]]                          \n"
#define RESULT_S_S2_P0_LEAKY_RELU                      \
  "fcmge v11.4s, v4.4s, %[vzero].4s \n"/* vcgeq_u32 */\
  "fmul v12.4s, v4.4s, %[vscale].4s                \n"\
  "bif  v4.16b, v12.16b, v11.16b \n" /* choose*/      \
  "st1 {v4.4s}, [%[out]]                          \n"

#define PARAM1 \
[inptr0] "+r"(din0_ptr), [inptr1] "+r"(din1_ptr), \
[inptr2] "+r"(din2_ptr), [inptr3] "+r"(din3_ptr), \
[inptr4] "+r"(din4_ptr), \
[outptr0] "+r"(doutr0_ptr), [outptr1] "+r"(doutr1_ptr), \
[cnt] "+r"(cnt)

#define PARAM2 \
[vzero] "w"(vzero), \
[w0] "w"(wr0), [w1] "w"(wr1), [w2] "w"(wr2), \
[remain] "r"(cnt_remain),  \
[mask1] "w"(vmask_rp1), [mask2] "w"(vmask_rp2), [mask3] "w"(vmask_rp3), \
[vbias] "w"(wbias), \
  [right_pad_num_in] "r"(right_pad_num_in), \
  [right_pad_num_out] "r"(right_pad_num_out)


#define ASM_PARAM \
"cc", "memory", \
"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", \
"v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19", "v20", "v21", "v22"


#else
#define INIT_S2                                                     \
  "vmov.u32 q9, #0                                \n"               \
  "vld2.32  {d20-d23}, [%[din0_ptr]]!             @ load din r1\n"  \
  "vld2.32  {d24-d27}, [%[din1_ptr]]!             @ load din r1\n"  \
  "vld2.32  {d28-d31}, [%[din2_ptr]]!             @ load din r1\n"  \
  "pld [%[din0_ptr]]                              @ preload data\n" \
  "pld [%[din1_ptr]]                              @ preload data\n" \
  "pld [%[din2_ptr]]                              @ preload data\n" \
                                                                    \
  "vdup.32 q3, %[bias]                            @ and \n"

#define LEFT_COMPUTE_S2                                                   \
  "vext.32 q6, q9, q11, #3                        @ shift right 1 data\n" \
  "vext.32 q7, q9, q13, #3                        @ shift right 1 data\n" \
  "vext.32 q8, q9, q15, #3                        @ shift right 1 data\n" \
  "vmul.f32 q4, q10, %e[wr0][1]                   @ mul weight 1, out0\n" \
  "vmul.f32 q5, q11, %f[wr0][0]                   @ mul weight 1, out0\n" \
  "vmla.f32 q3,  q6, %e[wr0][0]                   @ mul weight 1, out0\n" \
                                                                          \
  "sub %[din0_ptr], #4                            @ inpitr0 - 1\n"        \
  "sub %[din1_ptr], #4                            @ inpitr1 - 1\n"        \
  "sub %[din2_ptr], #4                            @ inpitr2 - 1\n"        \
                                                                          \
  "vld2.32  {d20-d23}, [%[din0_ptr]]!             @ load din r0\n"        \
                                                                          \
  "vmla.f32 q4, q12, %e[wr1][1]                   @ mul weight 1, out0\n" \
  "vmla.f32 q5, q13, %f[wr1][0]                   @ mul weight 1, out0\n" \
  "vmla.f32 q3,  q7, %e[wr1][0]                   @ mul weight 1, out0\n" \
                                                                          \
  "vld2.32  {d24-d27}, [%[din1_ptr]]!             @ load din r1\n"        \
                                                                          \
  "vmla.f32 q4, q14, %e[wr2][1]                   @ mul weight 1, out1\n" \
  "vmla.f32 q5, q15, %f[wr2][0]                   @ mul weight 1, out1\n" \
  "vmla.f32 q3,  q8, %e[wr2][0]                   @ mul weight 1, out1\n" \
                                                                          \
  "vld2.32  {d28-d31}, [%[din2_ptr]]!             @ load din r1\n"

#define LEFT_RESULT_S2                                     \
  "vadd.f32 q3, q3, q4                            @ add \n"\
  "vadd.f32 q3, q3, q5                            @ add \n"\
  "vst1.32 {d6-d7}, [%[outptr]]!                  \n"      \
  "cmp %[cnt], #1                                 \n"      \
  "blt 1f                                         \n"

#define MID_COMPUTE_S2                                                    \
  "2:                                             \n"                     \
  "vld1.32  {d16}, [%[din0_ptr]]                  @ load din r0\n"        \
  "vdup.32  q3, %[bias]                           @ and \n"               \
  "vext.32  q6, q10, q8, #1                       @ shift left 1 \n"      \
  "vld1.32 {d16}, [%[din1_ptr]]                   @ load din r1\n"        \
                                                                          \
  "vmul.f32 q4, q10, %e[wr0][0]                   @ mul weight 0, out0\n" \
  "vmul.f32 q5, q11, %e[wr0][1]                   @ mul weight 0, out0\n" \
  "vmla.f32 q3,  q6, %f[wr0][0]                   @ mul weight 0, out0\n" \
                                                                          \
  "vext.32  q7, q12, q8, #1                       @ shift left 1 \n"      \
  "vld1.32 {d16}, [%[din2_ptr]]                   @ load din r1\n"        \
                                                                          \
  "vld2.32  {d20-d23}, [%[din0_ptr]]!             @ load din r0\n"        \
                                                                          \
  "vmla.f32 q4, q12, %e[wr1][0]                   @ mul weight 1, out0\n" \
  "vmla.f32 q5, q13, %e[wr1][1]                   @ mul weight 1, out0\n" \
  "vmla.f32 q3,  q7, %f[wr1][0]                   @ mul weight 1, out0\n" \
                                                                          \
  "vext.32  q6, q14, q8, #1                       @ shift left 1 \n"      \
                                                                          \
  "vld2.32  {d24-d27}, [%[din1_ptr]]!             @ load din r1\n"        \
                                                                          \
  "vmla.f32 q4, q14, %e[wr2][0]                   @ mul weight 2, out0\n" \
  "vmla.f32 q5, q15, %e[wr2][1]                   @ mul weight 2, out0\n" \
  "vmla.f32 q3,  q6, %f[wr2][0]                   @ mul weight 2, out0\n" \
                                                                          \
  "vld2.32  {d28-d31}, [%[din2_ptr]]!             @ load din r2\n"

#define MID_RESULT_S2                                 \
  "vadd.f32 q3, q3, q4                       @ add \n"\
  "vadd.f32 q3, q3, q5                       @ add \n"\
  "subs %[cnt], #1                                \n" \
                                                      \
  "vst1.32 {d6-d7}, [%[outptr]]!                  \n" \
  "bne  2b                                        \n"

#define RIGHT_COMPUTE_S2                                                    \
  "1:                                             \n"                       \
  "cmp %[remain], #1                              \n"                       \
  "blt 3f                                         \n"                       \
  \
  /* Avoid thread write conflicts */ \
  "subs %[din0_ptr], #32 \n"                               \
  "subs %[din1_ptr], #32 \n"                               \
  "subs %[din2_ptr], #32 \n"                               \
  "subs %[din0_ptr], %[right_pad_num_in] \n"                               \
  "subs %[din1_ptr], %[right_pad_num_in] \n"                               \
  "subs %[din2_ptr], %[right_pad_num_in] \n"                               \
  \
  /* q10:[0,2,4,6] q11:[1,3,5,7] */     \
  /* q12:[0,2,4,6] q13:[1,3,5,7] */     \
  /* q14:[0,2,4,6] q15:[1,3,5,7] */     \
  "vld2.32  {d20-d23}, [%[din0_ptr]]!            \n"        \
  "vld2.32  {d24-d27}, [%[din1_ptr]]!             \n"        \
  "vld2.32  {d28-d31}, [%[din2_ptr]]!             \n"        \
  \
  /* make outut pointer smaller */ \
  "subs %[outptr], %[right_pad_num_out] \n"        \
  /* conflicts ends */ \
  \
  \
  \
                                      \
  "vld1.f32   {d12-d15}, [%[mask_ptr]]!           @ load mask\n"            \
  "vdup.32  q3, %[bias]                           @ and \n"                 \
                                                                            \
  "vbif q10, q9, q6                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q11, q9, q7                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q12, q9, q6                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q13, q9, q7                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q14, q9, q6                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q15, q9, q7                               @ bit select, deal with " \
  "right pad\n"                                                             \
  \
    /* generate q6, i.e. [2,4,6,8] */                               \
  "vld1.f32   {d8-d9}, [%[mask_ptr]]          \n"        \
  "vld1.32  {d16-d17}, [%[din0_ptr]]                \n"       \
  "vbit q9, q8, q4                               \n"                        \
  "vext.32 q6, q10, q9, #1                        @ shift left 1 \n"        \
  \
  /* generate q7, i.e. [2,4,6,8] */ \
  "vld1.32  {d16-d17}, [%[din1_ptr]]                  @ load din r0\n"        \
  "vbit q9, q8, q4                               \n"                        \
  "vext.32 q7, q12, q9, #1                        @ shift left 1 \n"        \
  \
  "vmul.f32 q4, q10, %e[wr0][0]                   @ mul weight 0, out0\n"   \
  "vmul.f32 q5, q11, %e[wr0][1]                   @ mul weight 0, out0\n"   \
  "vmla.f32 q3,  q6, %f[wr0][0]                   @ mul weight 0, out0\n"   \
            \
  /* generate q6, i.e. [2,4,6,8] */      \
  /* q4 has been occupied. I have to reload [mask_ptr] to q11 */ \
  /* remember zero q9!!!!!!!!!!!!!!!!!! */                                   \
  "vld1.f32   {d22-d23}, [%[mask_ptr]]           @ load mask\n"            \
  "vld1.32  {d16-d17}, [%[din2_ptr]]                  @ load din r0\n"        \
  "vbit q9, q8, q11                               \n"                        \
  "vext.32 q6, q14, q9, #1                        @ shift left 1 \n"        \
  "vmov.u32 q9, #0                                \n"               \
                                                                            \
  "vmla.f32 q4, q12, %e[wr1][0]                   @ mul weight 1, out0\n"   \
  "vmla.f32 q5, q13, %e[wr1][1]                   @ mul weight 1, out0\n"   \
  "vmla.f32 q3,  q7, %f[wr1][0]                   @ mul weight 1, out0\n"   \
                                                                            \
  "vmla.f32 q4, q14, %e[wr2][0]                   @ mul weight 2, out0\n"   \
  "vmla.f32 q5, q15, %e[wr2][1]                   @ mul weight 2, out0\n"   \
  "vmla.f32 q3,  q6, %f[wr2][0]                   @ mul weight 2, out0\n"

#define RIGHT_RESULT_S2                                           \
  "vadd.f32 q3, q3, q4                            @ add \n"       \
  "vadd.f32 q3, q3, q5                            @ add \n"       \
                                                                  \
  "vst1.32 {d6-d7}, [%[outptr]]!                  \n"             \
  "3:                                             \n"

#define LEFT_RESULT_S2_RELU                                \
  "vadd.f32 q3, q3, q4                            @ add \n"\
  "vadd.f32 q3, q3, q5                            @ add \n"\
  "vmax.f32 q3, q3, q9                                  \n"\
  "cmp %[cnt], #1                                       \n"\
  "vst1.32 {d6-d7}, [%[outptr]]!                        \n"\
  "blt 1f                                               \n"
#define LEFT_RESULT_S2_RELU6                            \
  "vadd.f32 q3, q3, q4                         @ add \n"\
  "vld1.f32 {d12-d13}, [%[six_ptr]] @ load six       \n"\
  "vadd.f32 q3, q3, q5                         @ add \n"\
  "vmax.f32 q3, q3, q9                        @ relu \n"\
  "cmp %[cnt], #1                                    \n"\
  "vmin.f32 q3, q3, q6                        @ relu \n"\
  "vst1.32 {d6-d7}, [%[outptr]]!                     \n"\
  "blt 1f                                            \n"
#define LEFT_RESULT_S2_LEAKY_RELU                       \
  "vadd.f32 q3, q3, q4                               \n"\
  "vld1.f32 {d12-d13}, [%[scale_ptr]]                \n"\
  "vadd.f32 q3, q3, q5                               \n"\
  "vcge.f32 q7, q3, q9                               \n"\
  "vmul.f32 q8, q3, q6                               \n"\
  "cmp %[cnt], #1                                    \n"\
  "vbif q3, q8, q7 @ choose                          \n"\
  "vst1.32 {d6-d7}, [%[outptr]]!                     \n"\
  "blt 1f                                            \n"
#define MID_RESULT_S2_RELU                              \
  "vadd.f32 q3, q3, q4                         @ add \n"\
  "vadd.f32 q3, q3, q5                         @ add \n"\
  "subs %[cnt], #1                                   \n"\
  "vmax.f32 q3, q3, q9                        @ relu \n"\
                                                        \
  "vst1.32 {d6-d7}, [%[outptr]]!                     \n"\
  "bne  2b                                             \n"

#define MID_RESULT_S2_RELU6                             \
  "vadd.f32 q3, q3, q4                         @ add \n"\
  "vld1.f32 {d12-d13}, [%[six_ptr]] @ load six       \n"\
  "vadd.f32 q3, q3, q5                         @ add \n"\
  "vmax.f32 q3, q3, q9                        @ relu \n"\
  "subs %[cnt], #1                                   \n"\
  "vmin.f32 q3, q3, q6                        @ relu \n"\
                                                        \
  "vst1.32 {d6-d7}, [%[outptr]]!                     \n"\
  "bne  2b                                             \n"
#define MID_RESULT_S2_LEAKY_RELU                       \
  "vadd.f32 q3, q3, q4                         @ add \n"\
  "vld1.f32 {d12-d13}, [%[scale_ptr]]                \n"\
  "vadd.f32 q3, q3, q5                         @ add \n"\
  "vcge.f32 q7, q3, q9                               \n"\
  "vmul.f32 q8, q3, q6                               \n"\
  "subs %[cnt], #1                                   \n"\
  "vbif q3, q8, q7 @ choose                          \n"\
                                                        \
  "vst1.32 {d6-d7}, [%[outptr]]!                     \n"\
  "bne  2b                                             \n"

#define RIGHT_RESULT_S2_RELU                            \
  "vadd.f32 q3, q3, q4                         @ add \n"\
  "vadd.f32 q3, q3, q5                         @ add \n"\
  "vmax.f32 q3, q3, q9                         @ relu\n"\
                                                        \
  "vst1.32 {d6-d7}, [%[outptr]]!                     \n"\
  "3:                                                 \n"

#define RIGHT_RESULT_S2_RELU6                           \
  "vadd.f32 q3, q3, q4                         @ add \n"\
  "vld1.f32 {d12-d13}, [%[six_ptr]] @ load six       \n"\
  "vadd.f32 q3, q3, q5                         @ add \n"\
  "vmax.f32 q3, q3, q9                         @ relu\n"\
  "vmin.f32 q3, q3, q6                        @ relu \n"\
                                                        \
  "vst1.32 {d6-d7}, [%[outptr]]!                     \n"\
  "3:                                                 \n"
#define RIGHT_RESULT_S2_LEAKY_RELU                      \
  "vadd.f32 q3, q3, q4                         @ add \n"\
  "vld1.f32 {d12-d13}, [%[scale_ptr]]                \n"\
  "vadd.f32 q3, q3, q5                         @ add \n"\
  "vcge.f32 q7, q3, q9                               \n"\
  "vmul.f32 q8, q3, q6                               \n"\
  "vbif q3, q8, q7 @ choose                          \n"\
                                                        \
  "vst1.32 {d6-d7}, [%[outptr]]!                     \n"\
  "3:                                                 \n"
#define COMPUTE_S_S2                                                        \
  "vmov.u32 q9, #0                                \n"                       \
  "vld1.f32   {d12-d15}, [%[mask_ptr]]!           @ load mask\n"            \
  "vdup.32  q3, %[bias]                           @ and \n"                 \
                                                                            \
  "vld2.32  {d20-d23}, [%[din0_ptr]]!             @ load din r0\n"          \
  "vld2.32  {d24-d27}, [%[din1_ptr]]!             @ load din r1\n"          \
  "vld2.32  {d28-d31}, [%[din2_ptr]]!             @ load din r2\n"          \
                                                                            \
  "vbif q10, q9, q6                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q11, q9, q7                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q12, q9, q6                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q13, q9, q7                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q14, q9, q6                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q15, q9, q7                               @ bit select, deal with " \
  "right pad\n"                                                             \
                                                                            \
  "vext.32 q6, q9, q11, #3                        @ shift left 1 \n"        \
  "vext.32 q7, q9, q13, #3                        @ shift left 1 \n"        \
  "vext.32 q8, q9, q15, #3                        @ shift left 1 \n"        \
                                                                            \
  "vmul.f32 q4, q10, %e[wr0][1]                   @ mul weight 0, out0\n"   \
  "vmul.f32 q5, q11, %f[wr0][0]                   @ mul weight 0, out0\n"   \
  "vmla.f32 q3, q6,  %e[wr0][0]                   @ mul weight 0, out0\n"   \
                                                                            \
  "vmla.f32 q4, q12, %e[wr1][1]                   @ mul weight 1, out0\n"   \
  "vmla.f32 q5, q13, %f[wr1][0]                   @ mul weight 1, out0\n"   \
  "vmla.f32 q3, q7,  %e[wr1][0]                   @ mul weight 1, out0\n"   \
                                                                            \
  "vmla.f32 q4, q14, %e[wr2][1]                   @ mul weight 2, out0\n"   \
  "vmla.f32 q5, q15, %f[wr2][0]                   @ mul weight 2, out0\n"   \
  "vmla.f32 q3, q8,  %e[wr2][0]                   @ mul weight 2, out0\n"

#define RESULT_S_S2                                        \
  "vadd.f32 q3, q3, q4                            @ add \n"\
  "vadd.f32 q3, q3, q5                            @ add \n"\
  "vst1.32 {d6-d7}, [%[out]]                            \n"
#define RESULT_S_S2_RELU                                   \
  "vadd.f32 q3, q3, q4                            @ add \n"\
  "vadd.f32 q3, q3, q5                            @ add \n"\
  "vmax.f32 q3, q3, q9                            @ relu\n"\
                                                           \
  "vst1.32 {d6-d7}, [%[out]]                            \n"

#define RESULT_S_S2_RELU6                                  \
  "vadd.f32 q3, q3, q4                            @ add \n"\
  "vld1.f32 {d12-d13}, [%[six_ptr]] @ load six          \n"\
  "vadd.f32 q3, q3, q5                            @ add \n"\
  "vmax.f32 q3, q3, q9                            @ relu\n"\
  "vmin.f32 q3, q3, q6                            @ relu\n"\
                                                           \
  "vst1.32 {d6-d7}, [%[out]]                            \n"
#define RESULT_S_S2_LEAKY_RELU                            \
  "vadd.f32 q3, q3, q4                            @ add \n"\
  "vld1.f32 {d12-d13}, [%[scale_ptr]]                   \n"\
  "vadd.f32 q3, q3, q5                            @ add \n"\
  "vcge.f32 q7, q3, q9                                  \n"\
  "vmul.f32 q8, q3, q6                                  \n"\
  "vbif q3, q8, q7 @ choose                             \n"\
                                                           \
  "vst1.32 {d6-d7}, [%[out]]                            \n"
#define COMPUTE_S_S2_P0                                                     \
  "vmov.u32 q9, #0                                \n"                       \
  "vld1.f32   {d12-d15}, [%[mask_ptr]]           @ load mask\n"             \
  "vdup.32  q3, %[bias]                           @ and \n"                 \
                                                                            \
  "vld2.32  {d20-d23}, [%[din0_ptr]]!             @ load din r0\n"          \
  "vld2.32  {d24-d27}, [%[din1_ptr]]!             @ load din r1\n"          \
  "vld2.32  {d28-d31}, [%[din2_ptr]]!             @ load din r2\n"          \
                                                                            \
  "vbif q10, q9, q6                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q11, q9, q7                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q12, q9, q6                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q13, q9, q7                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q14, q9, q6                               @ bit select, deal with " \
  "right pad\n"                                                             \
  "vbif q15, q9, q7                               @ bit select, deal with " \
  "right pad\n"                                                             \
                                                                            \
  "vext.32 q6, q10, q9, #1                        @ shift left 1 \n"        \
  "vext.32 q7, q12, q9, #1                        @ shift left 1 \n"        \
  "vext.32 q8, q14, q9, #1                        @ shift left 1 \n"        \
                                                                            \
  "vmul.f32 q4, q10, %e[wr0][0]                   @ mul weight 0, out0\n"   \
  "vmul.f32 q5, q11, %e[wr0][1]                   @ mul weight 0, out0\n"   \
  "vmla.f32 q3, q6,  %f[wr0][0]                   @ mul weight 0, out0\n"   \
                                                                            \
  "vmla.f32 q4, q12, %e[wr1][0]                   @ mul weight 1, out0\n"   \
  "vmla.f32 q5, q13, %e[wr1][1]                   @ mul weight 1, out0\n"   \
  "vmla.f32 q3, q7,  %f[wr1][0]                   @ mul weight 1, out0\n"   \
                                                                            \
  "vmla.f32 q4, q14, %e[wr2][0]                   @ mul weight 2, out0\n"   \
  "vmla.f32 q5, q15, %e[wr2][1]                   @ mul weight 2, out0\n"   \
  "vmla.f32 q3, q8,  %f[wr2][0]                   @ mul weight 2, out0\n"

#define RESULT_S_S2_P0                                      \
  "vadd.f32 q3, q3, q4                            @ add \n" \
  "vadd.f32 q3, q3, q5                            @ add \n" \
  "vst1.32 {d6-d7}, [%[out]]                            \n"
#define RESULT_S_S2_P0_RELU                                 \
  "vadd.f32 q3, q3, q4                            @ add \n" \
  "vadd.f32 q3, q3, q5                            @ add \n" \
  "vmax.f32 q3, q3, q9                            @ relu \n" \
  "vst1.32 {d6-d7}, [%[out]]                             \n"
#define RESULT_S_S2_P0_RELU6                                \
  "vadd.f32 q3, q3, q4                            @ add \n" \
  "vld1.f32 {d12-d13}, [%[six_ptr]] @ load six          \n" \
  "vadd.f32 q3, q3, q5                            @ add \n" \
  "vmax.f32 q3, q3, q9                            @ relu\n" \
  "vmin.f32 q3, q3, q6                            @ relu\n" \
  "vst1.32 {d6-d7}, [%[out]]                             \n"
#define RESULT_S_S2_P0_LEAKY_RELU                           \
  "vadd.f32 q3, q3, q4                            @ add \n" \
  "vld1.f32 {d12-d13}, [%[scale_ptr]] @ load six        \n" \
  "vadd.f32 q3, q3, q5                            @ add \n" \
  "vcge.f32 q7, q3, q9                                  \n" \
  "vmul.f32 q8, q3, q6                                  \n" \
  "vbif q3, q8, q7 @ choose                             \n" \
  "vst1.32 {d6-d7}, [%[out]]                            \n"


#define PARAM1 \
[din0_ptr] "+r"(din0_ptr), [din1_ptr] "+r"(din1_ptr), \
[din2_ptr] "+r"(din2_ptr), \
[outptr] "+r"(doutr0_ptr), \
[cnt] "+r"(cnt), [mask_ptr] "+r"(mask_ptr)

#define PARAM2 \
[remain] "r"(cnt_remain), \
[wr0] "w"(wr0), [wr1] "w"(wr1), \
[wr2] "w"(wr2),  \
[bias] "r"(bias_c), \
  [right_pad_num_in] "r"(right_pad_num_in), \
  [right_pad_num_out] "r"(right_pad_num_out)

#define ASM_PARAM \
"cc", "memory", \
"q3", "q4", "q5", "q6", \
"q7", "q8", "q9", "q10", \
"q11", "q12", "q13", "q14", "q15"



#endif
// clang-format on

inline std::pair<uint32_t, uint32_t> right_mask_3x3s2_fp32(
    int w_in,
    int w_out,
    int left_padding,
    uint32x4_t* vmask_rp1,
    uint32x4_t* vmask_rp2,
    uint32x4_t* vmask_rp3) {
  int right_pad_idx[12] = {0, 2, 4, 6, 1, 3, 5, 7, 8, 0xffff, 0xffff, 0xffff};

  int cnt_col;
  int tile_w = w_out >> 2;
  int size_right_remain;
  // size_right_remain: When we process the last cnt_remain([1,4]) outputs, the
  // number of valid data
  // Obviously, it should be within (0, 8]!
  int cnt_remain;
  if (left_padding > 0) {
    cnt_col = tile_w - 2;
    size_right_remain = w_in - ((8 - left_padding) + cnt_col * 8);
  } else {
    cnt_col = tile_w - 1;
    size_right_remain = w_in - (cnt_col * 8);
  }

  if (size_right_remain >= 9) {
    cnt_col++;
    size_right_remain -= 8;
  }
  // This judgment statement is not good.
  // Change it later
  cnt_remain = (size_right_remain == 8 && w_out % 4 == 0) ? 4 : (w_out % 4);

  // make size_right_remain larger
  size_right_remain += (4 - cnt_remain) * 2;

  *vmask_rp1 = vcgtq_s32(vdupq_n_s32(size_right_remain),
                         vld1q_s32(right_pad_idx));  // 0 2 4 6
  *vmask_rp2 = vcgtq_s32(vdupq_n_s32(size_right_remain),
                         vld1q_s32(right_pad_idx + 4));  // 1 3 5 7
  *vmask_rp3 = vcgtq_s32(vdupq_n_s32(size_right_remain),
                         vld1q_s32(right_pad_idx + 8));  // 8!

  return std::make_pair(cnt_col, cnt_remain);
}

/**
 * \brief depthwise convolution kernel 3x3, stride 2
 * w_in > 7
 */
void conv_depthwise_3x3s2p1_bias_relu6(float* dout,
                                       const float* din,
                                       const float* weights,
                                       const float* bias,
                                       const float* six,
                                       bool flag_bias,
                                       const int num,
                                       const int ch_in,
                                       const int h_in,
                                       const int w_in,
                                       const int h_out,
                                       const int w_out,
                                       ARMContext* ctx) {
  uint32x4_t vmask_rp1, vmask_rp2, vmask_rp3;
  auto&& res =
      right_mask_3x3s2_fp32(w_in, w_out, 1, &vmask_rp1, &vmask_rp2, &vmask_rp3);
  int cnt_col = res.first;
  int cnt_remain = res.second;

  uint32_t right_pad_num_in = (4 - cnt_remain) * sizeof(float) * 2;
  uint32_t right_pad_num_out = (4 - cnt_remain) * sizeof(float);

  int size_in_channel = w_in * h_in;
  int size_out_channel = w_out * h_out;
  float* zero_ptr = ctx->workspace_data<float>();
  memset(zero_ptr, 0, (w_in + 9) * sizeof(float));
  float* write_ptr = zero_ptr + (w_in + 9);

  unsigned int dmask[12];
  vst1q_u32(dmask, vmask_rp1);
  vst1q_u32(dmask + 4, vmask_rp2);
  vst1q_u32(dmask + 8, vmask_rp3);

  for (int n = 0; n < num; ++n) {
    const float* din_batch = din + n * ch_in * size_in_channel;
    float* dout_batch = dout + n * ch_in * size_out_channel;

    LITE_PARALLEL_BEGIN(i, tid, ch_in) {
      const float* din_channel = din_batch + i * size_in_channel;
      float* dout_channel = dout_batch + i * size_out_channel;

      const float* weight_ptr = weights + i * 9;
      float32x4_t wr0 = vld1q_f32(weight_ptr);
      float32x4_t wr1 = vld1q_f32(weight_ptr + 3);
      float32x4_t wr2 = vld1q_f32(weight_ptr + 6);

      float32x4_t vzero = vdupq_n_f32(0.f);
#ifdef __aarch64__
      float32x4_t wbias;
      if (flag_bias) {
        wbias = vdupq_n_f32(bias[i]);
      } else {
        wbias = vdupq_n_f32(0.f);
      }
#else
      float bias_c = 0.f;
      if (flag_bias) {
        bias_c = bias[i];
      }
#endif  // __aarch64__

      const float* dr0 = din_channel;
      const float* dr1 = dr0 + w_in;
      const float* dr2 = dr1 + w_in;
      const float* dr3 = dr2 + w_in;
      const float* dr4 = dr3 + w_in;

      const float* din0_ptr = dr0;
      const float* din1_ptr = dr1;
      const float* din2_ptr = dr2;
      const float* din3_ptr = dr3;
      const float* din4_ptr = dr4;

      float* doutr0 = dout_channel;
      float* doutr0_ptr = nullptr;
      float* doutr1_ptr = nullptr;

#ifdef __aarch64__
      for (int i = 0; i < h_out; i += 2) {
        din0_ptr = dr0;
        din1_ptr = dr1;
        din2_ptr = dr2;
        din3_ptr = dr3;
        din4_ptr = dr4;

        doutr0_ptr = doutr0;
        doutr1_ptr = doutr0 + w_out;

        if (i == 0) {
          din0_ptr = zero_ptr;
          din1_ptr = dr0;
          din2_ptr = dr1;
          din3_ptr = dr2;
          din4_ptr = dr3;
          dr0 = dr3;
          dr1 = dr4;
        } else {
          dr0 = dr4;
          dr1 = dr0 + w_in;
        }
        dr2 = dr1 + w_in;
        dr3 = dr2 + w_in;
        dr4 = dr3 + w_in;

        //! process bottom pad
        if (i * 2 + 4 > h_in) {
          switch (i * 2 + 4 - h_in) {
            case 4:
              din1_ptr = zero_ptr;
            case 3:
              din2_ptr = zero_ptr;
            case 2:
              din3_ptr = zero_ptr;
            case 1:
              din4_ptr = zero_ptr;
            default:
              break;
          }
        }
        //! process output pad
        if (i + 2 > h_out) {
          doutr1_ptr = write_ptr;
        }
        int cnt = cnt_col;
        asm volatile(
            INIT_S2 LEFT_COMPUTE_S2 LEFT_RESULT_S2_RELU6 MID_COMPUTE_S2
                MID_RESULT_S2_RELU6 RIGHT_COMPUTE_S2 RIGHT_RESULT_S2_RELU6
            : PARAM1
            : PARAM2, [six_ptr] "r"(six)
            : ASM_PARAM);
        doutr0 = doutr0 + 2 * w_out;
      }
#else
      for (int i = 0; i < h_out; i++) {
        din0_ptr = dr0;
        din1_ptr = dr1;
        din2_ptr = dr2;

        doutr0_ptr = doutr0;

        if (i == 0) {
          din0_ptr = zero_ptr;
          din1_ptr = dr0;
          din2_ptr = dr1;
          dr0 = dr1;
          dr1 = dr2;
          dr2 = dr1 + w_in;
        } else {
          dr0 = dr2;
          dr1 = dr0 + w_in;
          dr2 = dr1 + w_in;
        }

        //! process bottom pad
        if (i * 2 + 2 > h_in) {
          switch (i * 2 + 2 - h_in) {
            case 2:
              din1_ptr = zero_ptr;
            case 1:
              din2_ptr = zero_ptr;
            default:
              break;
          }
        }
        int cnt = cnt_col;
        unsigned int* mask_ptr = dmask;
        asm volatile(
            INIT_S2 LEFT_COMPUTE_S2 LEFT_RESULT_S2_RELU6 MID_COMPUTE_S2
                MID_RESULT_S2_RELU6 RIGHT_COMPUTE_S2 RIGHT_RESULT_S2_RELU6
            : PARAM1
            : PARAM2, [six_ptr] "r"(six)
            : ASM_PARAM);
        doutr0 = doutr0 + w_out;
      }
#endif
    }
    LITE_PARALLEL_END()
  }
}
void conv_depthwise_3x3s2p1_bias_leakyRelu(float* dout,
                                           const float* din,
                                           const float* weights,
                                           const float* bias,
                                           const float* scale,
                                           bool flag_bias,
                                           const int num,
                                           const int ch_in,
                                           const int h_in,
                                           const int w_in,
                                           const int h_out,
                                           const int w_out,
                                           ARMContext* ctx) {
  uint32x4_t vmask_rp1, vmask_rp2, vmask_rp3;
  auto&& res =
      right_mask_3x3s2_fp32(w_in, w_out, 1, &vmask_rp1, &vmask_rp2, &vmask_rp3);
  int cnt_col = res.first;
  int cnt_remain = res.second;

  uint32_t right_pad_num_in = (4 - cnt_remain) * sizeof(float) * 2;
  uint32_t right_pad_num_out = (4 - cnt_remain) * sizeof(float);

  int size_in_channel = w_in * h_in;
  int size_out_channel = w_out * h_out;
  float* zero_ptr = ctx->workspace_data<float>();
  memset(zero_ptr, 0, (w_in + 9) * sizeof(float));
  float* write_ptr = zero_ptr + (w_in + 9);

  unsigned int dmask[12];
  vst1q_u32(dmask, vmask_rp1);
  vst1q_u32(dmask + 4, vmask_rp2);
  vst1q_u32(dmask + 8, vmask_rp3);

  for (int n = 0; n < num; ++n) {
    const float* din_batch = din + n * ch_in * size_in_channel;
    float* dout_batch = dout + n * ch_in * size_out_channel;

    LITE_PARALLEL_BEGIN(i, tid, ch_in) {
      const float* din_channel = din_batch + i * size_in_channel;
      float* dout_channel = dout_batch + i * size_out_channel;

      const float* weight_ptr = weights + i * 9;
      float32x4_t wr0 = vld1q_f32(weight_ptr);
      float32x4_t wr1 = vld1q_f32(weight_ptr + 3);
      float32x4_t wr2 = vld1q_f32(weight_ptr + 6);

      float32x4_t vzero = vdupq_n_f32(0.f);
#ifdef __aarch64__
      float32x4_t wbias;
      if (flag_bias) {
        wbias = vdupq_n_f32(bias[i]);
      } else {
        wbias = vdupq_n_f32(0.f);
      }
#else
      float bias_c = 0.f;
      if (flag_bias) {
        bias_c = bias[i];
      }
#endif  // __aarch64__

      const float* dr0 = din_channel;
      const float* dr1 = dr0 + w_in;
      const float* dr2 = dr1 + w_in;
      const float* dr3 = dr2 + w_in;
      const float* dr4 = dr3 + w_in;

      const float* din0_ptr = dr0;
      const float* din1_ptr = dr1;
      const float* din2_ptr = dr2;
      const float* din3_ptr = dr3;
      const float* din4_ptr = dr4;

      float* doutr0 = dout_channel;
      float* doutr0_ptr = nullptr;
      float* doutr1_ptr = nullptr;

#ifdef __aarch64__
      for (int i = 0; i < h_out; i += 2) {
        din0_ptr = dr0;
        din1_ptr = dr1;
        din2_ptr = dr2;
        din3_ptr = dr3;
        din4_ptr = dr4;

        doutr0_ptr = doutr0;
        doutr1_ptr = doutr0 + w_out;

        if (i == 0) {
          din0_ptr = zero_ptr;
          din1_ptr = dr0;
          din2_ptr = dr1;
          din3_ptr = dr2;
          din4_ptr = dr3;
          dr0 = dr3;
          dr1 = dr4;
        } else {
          dr0 = dr4;
          dr1 = dr0 + w_in;
        }
        dr2 = dr1 + w_in;
        dr3 = dr2 + w_in;
        dr4 = dr3 + w_in;

        //! process bottom pad
        if (i * 2 + 4 > h_in) {
          switch (i * 2 + 4 - h_in) {
            case 4:
              din1_ptr = zero_ptr;
            case 3:
              din2_ptr = zero_ptr;
            case 2:
              din3_ptr = zero_ptr;
            case 1:
              din4_ptr = zero_ptr;
            default:
              break;
          }
        }
        //! process output pad
        if (i + 2 > h_out) {
          doutr1_ptr = write_ptr;
        }
        int cnt = cnt_col;
        asm volatile(INIT_S2 LEFT_COMPUTE_S2 LEFT_RESULT_S2_LEAKY_RELU
                         MID_COMPUTE_S2 MID_RESULT_S2_LEAKY_RELU
                             RIGHT_COMPUTE_S2 RIGHT_RESULT_S2_LEAKY_RELU
                     : PARAM1
                     : PARAM2, [scale_ptr] "r"(scale)
                     : ASM_PARAM);
        doutr0 = doutr0 + 2 * w_out;
      }
#else
      for (int i = 0; i < h_out; i++) {
        din0_ptr = dr0;
        din1_ptr = dr1;
        din2_ptr = dr2;

        doutr0_ptr = doutr0;

        if (i == 0) {
          din0_ptr = zero_ptr;
          din1_ptr = dr0;
          din2_ptr = dr1;
          dr0 = dr1;
          dr1 = dr2;
          dr2 = dr1 + w_in;
        } else {
          dr0 = dr2;
          dr1 = dr0 + w_in;
          dr2 = dr1 + w_in;
        }

        //! process bottom pad
        if (i * 2 + 2 > h_in) {
          switch (i * 2 + 2 - h_in) {
            case 2:
              din1_ptr = zero_ptr;
            case 1:
              din2_ptr = zero_ptr;
            default:
              break;
          }
        }
        int cnt = cnt_col;
        unsigned int* mask_ptr = dmask;
        asm volatile(INIT_S2 LEFT_COMPUTE_S2 LEFT_RESULT_S2_LEAKY_RELU
                         MID_COMPUTE_S2 MID_RESULT_S2_LEAKY_RELU
                             RIGHT_COMPUTE_S2 RIGHT_RESULT_S2_LEAKY_RELU
                     : PARAM1
                     : PARAM2, [scale_ptr] "r"(scale)
                     : ASM_PARAM);
        doutr0 = doutr0 + w_out;
      }
#endif
    }
    LITE_PARALLEL_END()
  }
}

/**
 * \brief depthwise convolution kernel 3x3, stride 2, width <= 4
 */
void conv_depthwise_3x3s2p1_bias_s_relu6(float* dout,
                                         const float* din,
                                         const float* weights,
                                         const float* bias,
                                         const float* six,
                                         bool flag_bias,
                                         const int num,
                                         const int ch_in,
                                         const int h_in,
                                         const int w_in,
                                         const int h_out,
                                         const int w_out,
                                         ARMContext* ctx) {
  int right_pad_idx[8] = {0, 2, 4, 6, 1, 3, 5, 7};
  int out_pad_idx[4] = {0, 1, 2, 3};
  float zeros[8] = {0.0f};

  uint32x4_t vmask_rp1 =
      vcgtq_s32(vdupq_n_s32(w_in), vld1q_s32(right_pad_idx));  // 0 2 4 6
  uint32x4_t vmask_rp2 =
      vcgtq_s32(vdupq_n_s32(w_in), vld1q_s32(right_pad_idx + 4));  // 1 3 5 7

  int size_in_channel = w_in * h_in;
  int size_out_channel = w_out * h_out;

  unsigned int dmask[8];
  vst1q_u32(dmask, vmask_rp1);
  vst1q_u32(dmask + 4, vmask_rp2);
#ifdef __aarch64__
  float32x4_t vsix = vld1q_f32(six);
#endif
  for (int n = 0; n < num; ++n) {
    const float* din_batch = din + n * ch_in * size_in_channel;
    float* dout_batch = dout + n * ch_in * size_out_channel;

    LITE_PARALLEL_BEGIN(i, tid, ch_in) {
      const float* din_channel = din_batch + i * size_in_channel;
      float* dout_channel = dout_batch + i * size_out_channel;

      const float* weight_ptr = weights + i * 9;
      float32x4_t wr0 = vld1q_f32(weight_ptr);
      float32x4_t wr1 = vld1q_f32(weight_ptr + 3);
      float32x4_t wr2 = vld1q_f32(weight_ptr + 6);

      float bias_c = 0.f;

      if (flag_bias) {
        bias_c = bias[i];
      }
      float32x4_t vbias = vdupq_n_f32(bias_c);
      int hs = -1;
      int he = 2;
      float out_buf[4];
      for (int j = 0; j < h_out; ++j) {
        const float* dr0 = din_channel + hs * w_in;
        const float* dr1 = dr0 + w_in;
        const float* dr2 = dr1 + w_in;
        if (hs == -1) {
          dr0 = zeros;
        }
        if (he > h_in) {
          dr2 = zeros;
        }
        const float* din0_ptr = dr0;
        const float* din1_ptr = dr1;
        const float* din2_ptr = dr2;

        unsigned int* mask_ptr = dmask;
#ifdef __aarch64__
        asm volatile(COMPUTE_S_S2 RESULT_S_S2_RELU6
                     : [din0_ptr] "+r"(din0_ptr),
                       [din1_ptr] "+r"(din1_ptr),
                       [din2_ptr] "+r"(din2_ptr),
                       [mask_ptr] "+r"(mask_ptr)
                     : [wr0] "w"(wr0),
                       [wr1] "w"(wr1),
                       [wr2] "w"(wr2),
                       [bias] "w"(vbias),
                       [vsix] "w"(vsix),
                       [out] "r"(out_buf)
                     : "v4",
                       "v5",
                       "v6",
                       "v7",
                       "v8",
                       "v9",
                       "v10",
                       "v11",
                       "v12",
                       "v13",
                       "v14",
                       "v15");
#else
        asm volatile(COMPUTE_S_S2 RESULT_S_S2_RELU6
                     : [din0_ptr] "+r"(din0_ptr),
                       [din1_ptr] "+r"(din1_ptr),
                       [din2_ptr] "+r"(din2_ptr),
                       [mask_ptr] "+r"(mask_ptr)
                     : [wr0] "w"(wr0),
                       [wr1] "w"(wr1),
                       [wr2] "w"(wr2),
                       [bias] "r"(bias_c),
                       [six_ptr] "r"(six),
                       [out] "r"(out_buf)
                     : "cc",
                       "memory",
                       "q3",
                       "q4",
                       "q5",
                       "q6",
                       "q7",
                       "q8",
                       "q9",
                       "q10",
                       "q11",
                       "q12",
                       "q13",
                       "q14",
                       "q15");
#endif
        for (int w = 0; w < w_out; ++w) {
          *dout_channel++ = out_buf[w];
        }
        hs += 2;
        he += 2;
      }
    }
    LITE_PARALLEL_END()
  }
}
void conv_depthwise_3x3s2p1_bias_s_leakyRelu(float* dout,
                                             const float* din,
                                             const float* weights,
                                             const float* bias,
                                             const float* scale,
                                             bool flag_bias,
                                             const int num,
                                             const int ch_in,
                                             const int h_in,
                                             const int w_in,
                                             const int h_out,
                                             const int w_out,
                                             ARMContext* ctx) {
  int right_pad_idx[8] = {0, 2, 4, 6, 1, 3, 5, 7};
  int out_pad_idx[4] = {0, 1, 2, 3};
  float zeros[8] = {0.0f};

  uint32x4_t vmask_rp1 =
      vcgtq_s32(vdupq_n_s32(w_in), vld1q_s32(right_pad_idx));  // 0 2 4 6
  uint32x4_t vmask_rp2 =
      vcgtq_s32(vdupq_n_s32(w_in), vld1q_s32(right_pad_idx + 4));  // 1 3 5 7

  int size_in_channel = w_in * h_in;
  int size_out_channel = w_out * h_out;

  unsigned int dmask[8];
  vst1q_u32(dmask, vmask_rp1);
  vst1q_u32(dmask + 4, vmask_rp2);
#ifdef __aarch64__
  float32x4_t vscale = vld1q_f32(scale);
  float32x4_t vzero = vdupq_n_f32(0.f);
#endif
  for (int n = 0; n < num; ++n) {
    const float* din_batch = din + n * ch_in * size_in_channel;
    float* dout_batch = dout + n * ch_in * size_out_channel;

    LITE_PARALLEL_BEGIN(i, tid, ch_in) {
      const float* din_channel = din_batch + i * size_in_channel;
      float* dout_channel = dout_batch + i * size_out_channel;

      const float* weight_ptr = weights + i * 9;
      float32x4_t wr0 = vld1q_f32(weight_ptr);
      float32x4_t wr1 = vld1q_f32(weight_ptr + 3);
      float32x4_t wr2 = vld1q_f32(weight_ptr + 6);

      float bias_c = 0.f;

      if (flag_bias) {
        bias_c = bias[i];
      }
      float32x4_t vbias = vdupq_n_f32(bias_c);
      int hs = -1;
      int he = 2;
      float out_buf[4];
      for (int j = 0; j < h_out; ++j) {
        const float* dr0 = din_channel + hs * w_in;
        const float* dr1 = dr0 + w_in;
        const float* dr2 = dr1 + w_in;
        if (hs == -1) {
          dr0 = zeros;
        }
        if (he > h_in) {
          dr2 = zeros;
        }
        const float* din0_ptr = dr0;
        const float* din1_ptr = dr1;
        const float* din2_ptr = dr2;

        unsigned int* mask_ptr = dmask;
#ifdef __aarch64__
        asm volatile(COMPUTE_S_S2 RESULT_S_S2_LEAKY_RELU
                     : [din0_ptr] "+r"(din0_ptr),
                       [din1_ptr] "+r"(din1_ptr),
                       [din2_ptr] "+r"(din2_ptr),
                       [mask_ptr] "+r"(mask_ptr)
                     : [wr0] "w"(wr0),
                       [wr1] "w"(wr1),
                       [wr2] "w"(wr2),
                       [bias] "w"(vbias),
                       [vzero] "w"(vzero),
                       [vscale] "w"(vscale),
                       [out] "r"(out_buf)
                     : "v4",
                       "v5",
                       "v6",
                       "v7",
                       "v8",
                       "v9",
                       "v10",
                       "v11",
                       "v12",
                       "v13",
                       "v14",
                       "v15");
#else
        asm volatile(COMPUTE_S_S2 RESULT_S_S2_LEAKY_RELU
                     : [din0_ptr] "+r"(din0_ptr),
                       [din1_ptr] "+r"(din1_ptr),
                       [din2_ptr] "+r"(din2_ptr),
                       [mask_ptr] "+r"(mask_ptr)
                     : [wr0] "w"(wr0),
                       [wr1] "w"(wr1),
                       [wr2] "w"(wr2),
                       [bias] "r"(bias_c),
                       [scale_ptr] "r"(scale),
                       [out] "r"(out_buf)
                     : "cc",
                       "memory",
                       "q3",
                       "q4",
                       "q5",
                       "q6",
                       "q7",
                       "q8",
                       "q9",
                       "q10",
                       "q11",
                       "q12",
                       "q13",
                       "q14",
                       "q15");
#endif
        for (int w = 0; w < w_out; ++w) {
          *dout_channel++ = out_buf[w];
        }
        hs += 2;
        he += 2;
      }
    }
    LITE_PARALLEL_END()
  }
}
/**
 * \brief depthwise convolution kernel 3x3, stride 2
 */
// w_in > 7
void conv_depthwise_3x3s2p0_bias_relu6(float* dout,
                                       const float* din,
                                       const float* weights,
                                       const float* bias,
                                       const float* six,
                                       bool flag_bias,
                                       const int num,
                                       const int ch_in,
                                       const int h_in,
                                       const int w_in,
                                       const int h_out,
                                       const int w_out,
                                       ARMContext* ctx) {
  uint32x4_t vmask_rp1, vmask_rp2, vmask_rp3;
  auto&& res =
      right_mask_3x3s2_fp32(w_in, w_out, 0, &vmask_rp1, &vmask_rp2, &vmask_rp3);
  int cnt_col = res.first;
  int cnt_remain = res.second;

  uint32_t right_pad_num_in = (4 - cnt_remain) * sizeof(float) * 2;
  uint32_t right_pad_num_out = (4 - cnt_remain) * sizeof(float);

  int size_in_channel = w_in * h_in;
  int size_out_channel = w_out * h_out;
  float* zero_ptr = ctx->workspace_data<float>();
  memset(zero_ptr, 0, (w_in + 9) * sizeof(float));
  float* write_ptr = zero_ptr + (w_in + 9);

  unsigned int dmask[12];
  vst1q_u32(dmask, vmask_rp1);
  vst1q_u32(dmask + 4, vmask_rp2);
  vst1q_u32(dmask + 8, vmask_rp3);

  for (int n = 0; n < num; ++n) {
    const float* din_batch = din + n * ch_in * size_in_channel;
    float* dout_batch = dout + n * ch_in * size_out_channel;

    LITE_PARALLEL_BEGIN(i, tid, ch_in) {
      const float* din_channel = din_batch + i * size_in_channel;
      float* dout_channel = dout_batch + i * size_out_channel;

      const float* weight_ptr = weights + i * 9;
      float32x4_t wr0 = vld1q_f32(weight_ptr);
      float32x4_t wr1 = vld1q_f32(weight_ptr + 3);
      float32x4_t wr2 = vld1q_f32(weight_ptr + 6);

      float32x4_t vzero = vdupq_n_f32(0.f);

#ifdef __aarch64__
      float32x4_t wbias;
      if (flag_bias) {
        wbias = vdupq_n_f32(bias[i]);
      } else {
        wbias = vdupq_n_f32(0.f);
      }
#else
      float bias_c = 0.f;
      if (flag_bias) {
        bias_c = bias[i];
      }
#endif  // __aarch64__

      const float* dr0 = din_channel;
      const float* dr1 = dr0 + w_in;
      const float* dr2 = dr1 + w_in;
      const float* dr3 = dr2 + w_in;
      const float* dr4 = dr3 + w_in;

      const float* din0_ptr = dr0;
      const float* din1_ptr = dr1;
      const float* din2_ptr = dr2;
      const float* din3_ptr = dr3;
      const float* din4_ptr = dr4;

      float* doutr0 = dout_channel;
      float* doutr0_ptr = nullptr;
      float* doutr1_ptr = nullptr;

#ifdef __aarch64__
      for (int i = 0; i < h_out; i += 2) {
        din0_ptr = dr0;
        din1_ptr = dr1;
        din2_ptr = dr2;
        din3_ptr = dr3;
        din4_ptr = dr4;

        doutr0_ptr = doutr0;
        doutr1_ptr = doutr0 + w_out;

        dr0 = dr4;
        dr1 = dr0 + w_in;
        dr2 = dr1 + w_in;
        dr3 = dr2 + w_in;
        dr4 = dr3 + w_in;

        //! process bottom pad
        if (i * 2 + 5 > h_in) {
          switch (i * 2 + 5 - h_in) {
            case 4:
              din1_ptr = zero_ptr;
            case 3:
              din2_ptr = zero_ptr;
            case 2:
              din3_ptr = zero_ptr;
            case 1:
              din4_ptr = zero_ptr;
            case 0:
              din4_ptr = zero_ptr;
            default:
              break;
          }
        }
        //! process output pad
        if (i + 2 > h_out) {
          doutr1_ptr = write_ptr;
        }
        int cnt = cnt_col;
        asm volatile(
            INIT_S2
            "ld1 {v15.4s}, [%[inptr0]]                 \n"
            "ld1 {v18.4s}, [%[inptr1]]                 \n"
            "ld1 {v19.4s}, [%[inptr2]]                 \n"
            "ld1 {v20.4s}, [%[inptr3]]                 \n"
            "ld1 {v21.4s}, [%[inptr4]]                 \n"
            "ext  v10.16b, v0.16b, v15.16b, #4     \n"  // v10 = {2,4,6,8}
            "ld1 {v22.4s}, [%[six_ptr]]                  \n" MID_COMPUTE_S2
                MID_RESULT_S2_RELU6
            "cmp %w[remain], #1                           \n"
            "blt 4f                                     \n" RIGHT_COMPUTE_S2
                RIGHT_RESULT_S2_RELU6
            "4:                                          \n"
            : PARAM1
            : PARAM2, [six_ptr] "r"(six)
            : ASM_PARAM);
        doutr0 = doutr0 + 2 * w_out;
      }
#else
      for (int i = 0; i < h_out; i++) {
        din0_ptr = dr0;
        din1_ptr = dr1;
        din2_ptr = dr2;

        doutr0_ptr = doutr0;

        dr0 = dr2;
        dr1 = dr0 + w_in;
        dr2 = dr1 + w_in;

        //! process bottom pad
        if (i * 2 + 3 > h_in) {
          switch (i * 2 + 3 - h_in) {
            case 2:
              din1_ptr = zero_ptr;
            case 1:
              din2_ptr = zero_ptr;
            default:
              break;
          }
        }
        int cnt = cnt_col;
        unsigned int* mask_ptr = dmask;
        asm volatile(INIT_S2 MID_COMPUTE_S2 MID_RESULT_S2_RELU6 RIGHT_COMPUTE_S2
                         RIGHT_RESULT_S2_RELU6
                     : PARAM1
                     : PARAM2, [six_ptr] "r"(six)
                     : ASM_PARAM);
        doutr0 = doutr0 + w_out;
      }
#endif
    }
    LITE_PARALLEL_END()
  }
}

void conv_depthwise_3x3s2p0_bias_leakyRelu(float* dout,
                                           const float* din,
                                           const float* weights,
                                           const float* bias,
                                           const float* scale,
                                           bool flag_bias,
                                           const int num,
                                           const int ch_in,
                                           const int h_in,
                                           const int w_in,
                                           const int h_out,
                                           const int w_out,
                                           ARMContext* ctx) {
  uint32x4_t vmask_rp1, vmask_rp2, vmask_rp3;
  auto&& res =
      right_mask_3x3s2_fp32(w_in, w_out, 0, &vmask_rp1, &vmask_rp2, &vmask_rp3);
  int cnt_col = res.first;
  int cnt_remain = res.second;

  uint32_t right_pad_num_in = (4 - cnt_remain) * sizeof(float) * 2;
  uint32_t right_pad_num_out = (4 - cnt_remain) * sizeof(float);

  int size_in_channel = w_in * h_in;
  int size_out_channel = w_out * h_out;
  float* zero_ptr = ctx->workspace_data<float>();
  memset(zero_ptr, 0, (w_in + 9) * sizeof(float));
  float* write_ptr = zero_ptr + (w_in + 9);

  unsigned int dmask[12];
  vst1q_u32(dmask, vmask_rp1);
  vst1q_u32(dmask + 4, vmask_rp2);
  vst1q_u32(dmask + 8, vmask_rp3);

  for (int n = 0; n < num; ++n) {
    const float* din_batch = din + n * ch_in * size_in_channel;
    float* dout_batch = dout + n * ch_in * size_out_channel;

    LITE_PARALLEL_BEGIN(i, tid, ch_in) {
      const float* din_channel = din_batch + i * size_in_channel;
      float* dout_channel = dout_batch + i * size_out_channel;

      const float* weight_ptr = weights + i * 9;
      float32x4_t wr0 = vld1q_f32(weight_ptr);
      float32x4_t wr1 = vld1q_f32(weight_ptr + 3);
      float32x4_t wr2 = vld1q_f32(weight_ptr + 6);

      float32x4_t vzero = vdupq_n_f32(0.f);

#ifdef __aarch64__
      float32x4_t wbias;
      if (flag_bias) {
        wbias = vdupq_n_f32(bias[i]);
      } else {
        wbias = vdupq_n_f32(0.f);
      }
#else
      float bias_c = 0.f;
      if (flag_bias) {
        bias_c = bias[i];
      }
#endif  // __aarch64__

      const float* dr0 = din_channel;
      const float* dr1 = dr0 + w_in;
      const float* dr2 = dr1 + w_in;
      const float* dr3 = dr2 + w_in;
      const float* dr4 = dr3 + w_in;

      const float* din0_ptr = dr0;
      const float* din1_ptr = dr1;
      const float* din2_ptr = dr2;
      const float* din3_ptr = dr3;
      const float* din4_ptr = dr4;

      float* doutr0 = dout_channel;
      float* doutr0_ptr = nullptr;
      float* doutr1_ptr = nullptr;

#ifdef __aarch64__
      for (int i = 0; i < h_out; i += 2) {
        din0_ptr = dr0;
        din1_ptr = dr1;
        din2_ptr = dr2;
        din3_ptr = dr3;
        din4_ptr = dr4;

        doutr0_ptr = doutr0;
        doutr1_ptr = doutr0 + w_out;

        dr0 = dr4;
        dr1 = dr0 + w_in;
        dr2 = dr1 + w_in;
        dr3 = dr2 + w_in;
        dr4 = dr3 + w_in;

        //! process bottom pad
        if (i * 2 + 5 > h_in) {
          switch (i * 2 + 5 - h_in) {
            case 4:
              din1_ptr = zero_ptr;
            case 3:
              din2_ptr = zero_ptr;
            case 2:
              din3_ptr = zero_ptr;
            case 1:
              din4_ptr = zero_ptr;
            case 0:
              din4_ptr = zero_ptr;
            default:
              break;
          }
        }
        //! process output pad
        if (i + 2 > h_out) {
          doutr1_ptr = write_ptr;
        }
        int cnt = cnt_col;
        asm volatile(
            INIT_S2
            "ld1 {v15.4s}, [%[inptr0]]                 \n"
            "ld1 {v18.4s}, [%[inptr1]]                 \n"
            "ld1 {v19.4s}, [%[inptr2]]                 \n"
            "ld1 {v20.4s}, [%[inptr3]]                 \n"
            "ld1 {v21.4s}, [%[inptr4]]                 \n"
            "ext  v10.16b, v0.16b, v15.16b, #4     \n"  // v10 = {2,4,6,8}
            "ld1 {v22.4s}, [%[scale_ptr]]                  \n" MID_COMPUTE_S2
                MID_RESULT_S2_LEAKY_RELU
            "cmp %w[remain], #1                           \n"
            "blt 4f                                     \n" RIGHT_COMPUTE_S2
                RIGHT_RESULT_S2_LEAKY_RELU
            "4:                                          \n"
            : PARAM1
            : PARAM2, [scale_ptr] "r"(scale)
            : ASM_PARAM);
        doutr0 = doutr0 + 2 * w_out;
      }
#else
      for (int i = 0; i < h_out; i++) {
        din0_ptr = dr0;
        din1_ptr = dr1;
        din2_ptr = dr2;

        doutr0_ptr = doutr0;

        dr0 = dr2;
        dr1 = dr0 + w_in;
        dr2 = dr1 + w_in;

        //! process bottom pad
        if (i * 2 + 3 > h_in) {
          switch (i * 2 + 3 - h_in) {
            case 2:
              din1_ptr = zero_ptr;
            case 1:
              din2_ptr = zero_ptr;
            default:
              break;
          }
        }
        int cnt = cnt_col;
        unsigned int* mask_ptr = dmask;
        asm volatile(INIT_S2 MID_COMPUTE_S2 MID_RESULT_S2_LEAKY_RELU
                         RIGHT_COMPUTE_S2 RIGHT_RESULT_S2_LEAKY_RELU
                     : PARAM1
                     : PARAM2, [scale_ptr] "r"(scale)
                     : ASM_PARAM);
        doutr0 = doutr0 + w_out;
      }
#endif
    }
    LITE_PARALLEL_END()
  }
}

/**
 * \brief depthwise convolution kernel 3x3, stride 2, width <= 4
 */
void conv_depthwise_3x3s2p0_bias_s_relu6(float* dout,
                                         const float* din,
                                         const float* weights,
                                         const float* bias,
                                         const float* six,
                                         bool flag_bias,
                                         const int num,
                                         const int ch_in,
                                         const int h_in,
                                         const int w_in,
                                         const int h_out,
                                         const int w_out,
                                         ARMContext* ctx) {
  int right_pad_idx[8] = {0, 2, 4, 6, 1, 3, 5, 7};
  int out_pad_idx[4] = {0, 1, 2, 3};
  float zeros[8] = {0.0f};
  const float zero_ptr[4] = {0.f, 0.f, 0.f, 0.f};

  uint32x4_t vmask_rp1 =
      vcgtq_s32(vdupq_n_s32(w_in), vld1q_s32(right_pad_idx));  // 0 2 4 6
  uint32x4_t vmask_rp2 =
      vcgtq_s32(vdupq_n_s32(w_in), vld1q_s32(right_pad_idx + 4));  // 1 3 5 7

  int size_in_channel = w_in * h_in;
  int size_out_channel = w_out * h_out;

  unsigned int dmask[8];
  vst1q_u32(dmask, vmask_rp1);
  vst1q_u32(dmask + 4, vmask_rp2);
#ifdef __aarch64__
  float32x4_t vsix = vld1q_f32(six);
  float32x4_t vzero = vdupq_n_f32(0.f);
#endif

  for (int n = 0; n < num; ++n) {
    const float* din_batch = din + n * ch_in * size_in_channel;
    float* dout_batch = dout + n * ch_in * size_out_channel;

    LITE_PARALLEL_BEGIN(i, tid, ch_in) {
      const float* din_channel = din_batch + i * size_in_channel;
      float* dout_channel = dout_batch + i * size_out_channel;

      const float* weight_ptr = weights + i * 9;
      float32x4_t wr0 = vld1q_f32(weight_ptr);
      float32x4_t wr1 = vld1q_f32(weight_ptr + 3);
      float32x4_t wr2 = vld1q_f32(weight_ptr + 6);

      float bias_c = 0.f;

      if (flag_bias) {
        bias_c = bias[i];
      }
      float32x4_t vbias = vdupq_n_f32(bias_c);
      float out_buf[4];
      const float* dr0 = din_channel;
      const float* dr1 = dr0 + w_in;
      const float* dr2 = dr1 + w_in;
      for (int j = 0; j < h_out; j++) {
        const float* din0_ptr = dr0;
        const float* din1_ptr = dr1;
        const float* din2_ptr = dr2;
        if (j * 2 + 2 >= h_in) {
          switch (j + 2 - h_in) {
            case 1:
              din1_ptr = zero_ptr;
            case 0:
              din2_ptr = zero_ptr;
            default:
              break;
          }
        }
        dr0 = dr2;
        dr1 = dr0 + w_in;
        dr2 = dr1 + w_in;

        unsigned int* mask_ptr = dmask;
#ifdef __aarch64__
        asm volatile(COMPUTE_S_S2_P0 RESULT_S_S2_P0_RELU6
                     : [din0_ptr] "+r"(din0_ptr),
                       [din1_ptr] "+r"(din1_ptr),
                       [din2_ptr] "+r"(din2_ptr),
                       [mask_ptr] "+r"(mask_ptr)
                     : [wr0] "w"(wr0),
                       [wr1] "w"(wr1),
                       [wr2] "w"(wr2),
                       [bias] "w"(vbias),
                       [vzero] "w"(vzero),
                       [vsix] "w"(vsix),
                       [out] "r"(out_buf)
                     : "cc",
                       "memory",
                       "v4",
                       "v5",
                       "v6",
                       "v7",
                       "v8",
                       "v9",
                       "v10",
                       "v11",
                       "v12",
                       "v13",
                       "v14",
                       "v15",
                       "v16");

#else
        asm volatile(COMPUTE_S_S2_P0 RESULT_S_S2_P0_RELU6
                     : [din0_ptr] "+r"(din0_ptr),
                       [din1_ptr] "+r"(din1_ptr),
                       [din2_ptr] "+r"(din2_ptr)
                     : [wr0] "w"(wr0),
                       [wr1] "w"(wr1),
                       [wr2] "w"(wr2),
                       [bias] "r"(bias_c),
                       [out] "r"(out_buf),
                       [six_ptr] "r"(six),
                       [mask_ptr] "r"(dmask)
                     : "cc",
                       "memory",
                       "q3",
                       "q4",
                       "q5",
                       "q6",
                       "q7",
                       "q8",
                       "q9",
                       "q10",
                       "q11",
                       "q12",
                       "q13",
                       "q14",
                       "q15");
#endif
        for (int w = 0; w < w_out; ++w) {
          *dout_channel++ = out_buf[w];
        }
      }
    }
    LITE_PARALLEL_END()
  }
}
void conv_depthwise_3x3s2p0_bias_s_leakyRelu(float* dout,
                                             const float* din,
                                             const float* weights,
                                             const float* bias,
                                             const float* scale,
                                             bool flag_bias,
                                             const int num,
                                             const int ch_in,
                                             const int h_in,
                                             const int w_in,
                                             const int h_out,
                                             const int w_out,
                                             ARMContext* ctx) {
  int right_pad_idx[8] = {0, 2, 4, 6, 1, 3, 5, 7};
  int out_pad_idx[4] = {0, 1, 2, 3};
  float zeros[8] = {0.0f};
  const float zero_ptr[4] = {0.f, 0.f, 0.f, 0.f};

  uint32x4_t vmask_rp1 =
      vcgtq_s32(vdupq_n_s32(w_in), vld1q_s32(right_pad_idx));  // 0 2 4 6
  uint32x4_t vmask_rp2 =
      vcgtq_s32(vdupq_n_s32(w_in), vld1q_s32(right_pad_idx + 4));  // 1 3 5 7

  int size_in_channel = w_in * h_in;
  int size_out_channel = w_out * h_out;

  unsigned int dmask[8];
  vst1q_u32(dmask, vmask_rp1);
  vst1q_u32(dmask + 4, vmask_rp2);
#ifdef __aarch64__
  float32x4_t vscale = vld1q_f32(scale);
  float32x4_t vzero = vdupq_n_f32(0.f);
#endif

  for (int n = 0; n < num; ++n) {
    const float* din_batch = din + n * ch_in * size_in_channel;
    float* dout_batch = dout + n * ch_in * size_out_channel;

    LITE_PARALLEL_BEGIN(i, tid, ch_in) {
      const float* din_channel = din_batch + i * size_in_channel;
      float* dout_channel = dout_batch + i * size_out_channel;

      const float* weight_ptr = weights + i * 9;
      float32x4_t wr0 = vld1q_f32(weight_ptr);
      float32x4_t wr1 = vld1q_f32(weight_ptr + 3);
      float32x4_t wr2 = vld1q_f32(weight_ptr + 6);

      float bias_c = 0.f;

      if (flag_bias) {
        bias_c = bias[i];
      }
      float32x4_t vbias = vdupq_n_f32(bias_c);
      float out_buf[4];
      const float* dr0 = din_channel;
      const float* dr1 = dr0 + w_in;
      const float* dr2 = dr1 + w_in;
      for (int j = 0; j < h_out; j++) {
        const float* din0_ptr = dr0;
        const float* din1_ptr = dr1;
        const float* din2_ptr = dr2;
        if (j * 2 + 2 >= h_in) {
          switch (j + 2 - h_in) {
            case 1:
              din1_ptr = zero_ptr;
            case 0:
              din2_ptr = zero_ptr;
            default:
              break;
          }
        }
        dr0 = dr2;
        dr1 = dr0 + w_in;
        dr2 = dr1 + w_in;

        unsigned int* mask_ptr = dmask;
#ifdef __aarch64__
        asm volatile(COMPUTE_S_S2_P0 RESULT_S_S2_P0_LEAKY_RELU
                     : [din0_ptr] "+r"(din0_ptr),
                       [din1_ptr] "+r"(din1_ptr),
                       [din2_ptr] "+r"(din2_ptr),
                       [mask_ptr] "+r"(mask_ptr)
                     : [wr0] "w"(wr0),
                       [wr1] "w"(wr1),
                       [wr2] "w"(wr2),
                       [bias] "w"(vbias),
                       [vzero] "w"(vzero),
                       [vscale] "w"(vscale),
                       [out] "r"(out_buf)
                     : "cc",
                       "memory",
                       "v4",
                       "v5",
                       "v6",
                       "v7",
                       "v8",
                       "v9",
                       "v10",
                       "v11",
                       "v12",
                       "v13",
                       "v14",
                       "v15",
                       "v16");
#else
        asm volatile(COMPUTE_S_S2_P0 RESULT_S_S2_P0_LEAKY_RELU
                     : [din0_ptr] "+r"(din0_ptr),
                       [din1_ptr] "+r"(din1_ptr),
                       [din2_ptr] "+r"(din2_ptr)
                     : [wr0] "w"(wr0),
                       [wr1] "w"(wr1),
                       [wr2] "w"(wr2),
                       [bias] "r"(bias_c),
                       [out] "r"(out_buf),
                       [scale_ptr] "r"(scale),
                       [mask_ptr] "r"(dmask)
                     : "cc",
                       "memory",
                       "q3",
                       "q4",
                       "q5",
                       "q6",
                       "q7",
                       "q8",
                       "q9",
                       "q10",
                       "q11",
                       "q12",
                       "q13",
                       "q14",
                       "q15");
#endif
        for (int w = 0; w < w_out; ++w) {
          *dout_channel++ = out_buf[w];
        }
      }
    }
    LITE_PARALLEL_END()
  }
}
}  // namespace math
}  // namespace arm
}  // namespace lite
}  // namespace paddle
