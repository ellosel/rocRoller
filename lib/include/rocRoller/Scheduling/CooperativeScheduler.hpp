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

#include <concepts>
#include <string>
#include <vector>

#include <rocRoller/Scheduling/CooperativeScheduler_fwd.hpp>
#include <rocRoller/Scheduling/Costs/Cost_fwd.hpp>
#include <rocRoller/Scheduling/Scheduler.hpp>

namespace rocRoller
{
    namespace Scheduling
    {
        /**
         * A subclass for cooperative scheduling
         *
         * This scheduler works by repeatedly choosing the next stream with
         * the minimum cost, and yielding from that stream until an
         * instruction with a non-zero cost is encountered.
         */
        class CooperativeScheduler : public Scheduler
        {
        public:
            CooperativeScheduler(ContextPtr, CostFunction);

            using Base = Scheduler;

            static const std::string Basename;
            static const std::string Name;

            static bool Match(Argument arg);

            static std::shared_ptr<Scheduler> Build(Argument arg);

            std::string name() const override;

            bool supportsAddingStreams() const override;

            Generator<Instruction> operator()(std::vector<Generator<Instruction>>& seqs) override;
        };
    }
}
