/* Copyright 2020, 2021 Evandro Chagas Ribeiro da Rosa <evandro.crr@posgrad.ufsc.br>
 * Copyright 2020, 2021 Rafael de Santiago <r.santiago@ufsc.br>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "../include/ket"

using namespace ket;

#define GATE(x) void ket::x(const quant& q) {\
    if (not *(q.process_on_top))\
        throw std::runtime_error("process out of scope");\
    for (auto i : q.qubits)\
        process_stack.top()->add_gate(process::x, i);\
}

GATE(x)
GATE(y)
GATE(z)
GATE(h)
GATE(s)
GATE(sd)
GATE(t)
GATE(td)

#define GATER(r) void ket::r(double lambda, const quant& q) {\
    if (not *(q.process_on_top))\
        throw std::runtime_error("process out of scope");\
    for (auto i : q.qubits)\
        process_stack.top()->add_gate(process::r, i, lambda);\
}

GATER(p)
GATER(rx)
GATER(ry)
GATER(rz)

