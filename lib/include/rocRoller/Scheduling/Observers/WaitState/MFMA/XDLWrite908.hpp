/*******************************************************************************
 *
 * MIT License
 *
 * Copyright 2024-2025 AMD ROCm(TM) Software
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#pragma once

#include <rocRoller/Scheduling/Observers/WaitState/WaitStateObserver.hpp>

namespace rocRoller
{
    namespace Scheduling
    {
        /**
         * @brief 908 rules for XDL Write Hazards.
         *
         * | Arch | 1st Inst                | 2nd Inst                     | NOPs |
         * | ---- | ----------------------- | ---------------------------- | ---- |
         * | 908  | v_mfma* write           | v_mfma* read SrcC same       | 0    |
         * | 908  | v_mfma* write           | v_mfma* read SrcC overlapped | 2    |
         * | 908  | v_mfma* write           | v_mfma* read SrcA/B          | 4    |
         * | 908  | v_mfma* write (2 pass)  | v_accvgpr_read read          | 4    |
         * | 908  | v_mfma* write (8 pass)  | v_accvgpr_read read          | 10   |
         * | 908  | v_mfma* write (16 pass) | v_accvgpr_read read          | 18   |
         * | 908  | v_mfma* write (2 pass)  | v_accvgpr_write write        | 1    |
         * | 908  | v_mfma* write (8 pass)  | v_accvgpr_write write        | 7    |
         * | 908  | v_mfma* write (16 pass) | v_accvgpr_write write        | 15   |
         *
         */
        class XDLWrite908 : public WaitStateObserver<XDLWrite908>
        {
        public:
            XDLWrite908() {}
            XDLWrite908(ContextPtr context)
                : WaitStateObserver<XDLWrite908>(context){};

            constexpr static bool required(GPUArchitectureTarget const& target)
            {
                return target.isCDNA1GPU();
            }

            int                   getMaxNops(Instruction const& inst) const;
            bool                  trigger(Instruction const& inst) const;
            static constexpr bool writeTrigger()
            {
                return true;
            }
            int         getNops(Instruction const& inst) const;
            std::string getComment() const
            {
                return "XDL Write Hazard";
            }

        private:
            std::unordered_map<int, int> m_maxLatencyAndNops = {{2, 4}, {8, 10}, {16, 18}};
        };

        static_assert(CWaitStateObserver<XDLWrite908>);
    }
}
