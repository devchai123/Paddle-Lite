# Copyright (c) 2021 PaddlePaddle Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import sys
sys.path.append('../')

from auto_scan_test import AutoScanTest, IgnoreReasons
from program_config import TensorConfig, ProgramConfig, OpConfig, CxxConfig, TargetType, PrecisionType, DataLayoutType, Place
import unittest

import hypothesis
from hypothesis import given, settings, seed, example, assume
import hypothesis.strategies as st
import argparse
import numpy as np
from functools import partial


class TestHardActivationOp(AutoScanTest):
    def __init__(self, *args, **kwargs):
        AutoScanTest.__init__(self, *args, **kwargs)
        self.enable_testing_on_place(
            TargetType.X86,
            PrecisionType.FP32,
            DataLayoutType.NCHW,
            thread=[1, 2])
        self.enable_testing_on_place(
            TargetType.ARM,
            PrecisionType.FP32,
            DataLayoutType.NCHW,
            thread=[1, 2, 4])
        self.enable_testing_on_place(
            TargetType.Host,
            PrecisionType.FP32,
            DataLayoutType.NCHW,
            thread=[1, 2])

    def is_program_valid(self,
                         program_config: ProgramConfig,
                         predictor_config: CxxConfig) -> bool:
        return True

    def sample_program_configs(self, draw):
        in_shape = draw(
            st.lists(
                st.integers(
                    min_value=1, max_value=64), min_size=4, max_size=4))
        alpha_data = draw(st.floats(min_value=0.1, max_value=0.9))
        threshold_data = draw(st.floats(min_value=0.5, max_value=0.9))
        scale_data = draw(st.floats(min_value=0.7, max_value=0.9))
        offset_data = draw(st.floats(min_value=0.01, max_value=0.1))

        op_type_str = draw(st.sampled_from(["hard_swish", "hard_sigmoid"]))

        def generate_input(*args, **kwargs):
            return 2 * np.random.random(in_shape).astype(np.float32) - 1

        def get_attr_np(op_type):
            attr = {}
            if op_type == "hard_swish":
                attr = {
                    "threshold": threshold_data,
                    "scale": scale_data,
                    "offset": offset_data
                }
            else:
                attr = {"slope": scale_data, "offset": offset_data}
            return attr

        build_ops = OpConfig(
            type=op_type_str,
            inputs={"X": ["input_data"], },
            outputs={"Out": ["output_data"], },
            attrs=get_attr_np(op_type_str))
        program_config = ProgramConfig(
            ops=[build_ops],
            weights={},
            inputs={
                "input_data": TensorConfig(data_gen=partial(generate_input)),
            },
            outputs=["output_data"])
        return program_config

    def sample_predictor_configs(self):
        return self.get_predictor_configs(), ["hard_swish_and_sigmoid"], (1e-5,
                                                                          1e-5)

    def add_ignore_pass_case(self):
        pass

    def test(self, *args, **kwargs):
        self.run_and_statis(quant=False, max_examples=25)


if __name__ == "__main__":
    unittest.main(argv=[''])
