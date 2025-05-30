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

using size_t = long;

namespace std
{
    template <typename T>
    class shared_ptr
    {
    public:
        shared_ptr(T* ptr = nullptr) {}
    };
    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args... args)
    {
        return shared_ptr<T>(new T(args...));
    }
}

class TypeA
{
};

namespace rocRoller
{
    class TypeB
    {
    };
    using TypeBPtr = std::shared_ptr<TypeB>;
    namespace inner
    {
        class TypeC
        {
        };
        using TypeCPtr = std::shared_ptr<TypeC>;
        TypeCPtr n2; // is OK
    }
    inner::TypeCPtr               n0; // is OK
    std::shared_ptr<inner::TypeC> n1; // is OK
    auto                          n2 = std::make_shared<inner::TypeC>();
}
