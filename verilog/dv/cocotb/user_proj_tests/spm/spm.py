# SPDX-FileCopyrightText: 2023 Efabless Corporation

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#      http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# SPDX-License-Identifier: Apache-2.0


from caravel_cocotb.caravel_interfaces import test_configure
from caravel_cocotb.caravel_interfaces import report_test
import cocotb 

@cocotb.test()
@report_test
async def spm(dut):
    caravelEnv = await test_configure(dut, timeout_cycles=159844)
    cocotb.log.info("[TEST] Start spm test")  
    # wait for start of sending
    await caravelEnv.wait_mgmt_gpio(1)
    cocotb.log.info("[TEST] start sending data to spm") 
    await caravelEnv.wait_mgmt_gpio(0)
    cocotb.log.info("[TEST] finish sending data to spm") 
    pass_code = caravelEnv.monitor_gpio(35,32).integer
    if pass_code == 0xA:
        cocotb.log.info("[TEST] spm working fine")
    elif pass_code == 0xF:
        cocotb.log.error("[TEST] spm is not working fine")
    else:
        cocotb.log.error("[TEST] recieved unkown code from firmware")
