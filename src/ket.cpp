/* MIT License
 * 
 * Copyright (c) 2020 Evandro Chagas Ribeiro da Rosa <evandro.crr@posgrad.ufsc.br>
 * Copyright (c) 2020 Rafael de Santiago <r.santiago@ufsc.br>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "../include/ket"
#include "../include/ket_bits/quant.hpp"
#include "../include/ket_bits/future.hpp"
#include "../include/ket_bits/base.hpp"
#include <iostream>

using namespace ket;

label::label(const std::string& label_name, process& _ps) : ps{_ps}, name{label_name+std::to_string(count++)} {} 

label::operator std::string() const {
    return name;
}

void label::begin() {
    auto psb = static_cast<base::_process*>(ps.ps.get());
    psb->begin_block(name);
}

void ket::jump(label& label_name) {
    auto ps = static_cast<base::_process*>(label_name.ps.ps.get());
    ps->end_block(label_name);
}

void ket::branch(future _cond, label& label_true, label& label_false) {
    auto ps = static_cast<base::_process*>(label_true.ps.ps.get());
    auto cond = static_cast<ket::_future*>(_cond.future_ptr.get());

    ps->end_block(label_true, label_false, cond->get_base_i64());
}

void ket::process_begin() {
    ket_ps_stack.push(ket_ps);
    ket_ps = new process;
}

void ket::process_end() {
    delete ket_ps;
    ket_ps = ket_ps_stack.top();
    ket_ps_stack.pop();
}

void ket::ctrl_begin(quant _q) {
    auto *q = static_cast<_quant*>(_q.quant_ptr.get());
    q->get_ps()->ctrl_begin(q->get_base_qubits());
}

void ket::ctrl_end(quant _q) {
    auto *q = static_cast<_quant*>(_q.quant_ptr.get());
    q->get_ps()->ctrl_end();
}

void ket::adj_begin(process &_ps) {
    auto ps = static_cast<base::_process*>(_ps.ps.get());
    ps->adj_begin();
}

void ket::adj_end(process &_ps) {
    auto ps = static_cast<base::_process*>(_ps.ps.get());
    ps->adj_end();
}

void ket::ctrl_adj_begin(quant _q) {
    auto *q = static_cast<_quant*>(_q.quant_ptr.get());
    q->get_ps()->ctrl_begin(q->get_base_qubits());
    q->get_ps()->adj_begin();
}

void ket::ctrl_adj_end(quant _q) {
    auto *q = static_cast<_quant*>(_q.quant_ptr.get());
    q->get_ps()->adj_end();
    q->get_ps()->ctrl_end();
}
