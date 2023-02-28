/* Copyright (c) 2021 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#pragma once

#include "paddle/phi/common/int_array.h"
#include "paddle/phi/core/dense_tensor.h"
#include "paddle/phi/infermeta/unary.h"
#include "paddle/phi/kernels/empty_kernel.h"

namespace phi {

template <typename Context>
void ViewInferKernel(const Context& dev_ctx,
                     const DenseTensor& x,
                     const IntArray& shape,
                     DenseTensor* out);

template <typename Context>
void ViewKernel(const Context& dev_ctx,
                const DenseTensor& x,
                const IntArray& shape,
                DenseTensor* out);

template <typename T, typename Context>
DenseTensor View(const Context& dev_ctx,
                 const DenseTensor& x,
                 const std::vector<int64_t>& shape) {
  DenseTensor dense_out;
  MetaTensor meta_out(&dense_out);
  InferMetaFromVecValue(x, shape, &meta_out);
  ViewInferKernel<Context>(dev_ctx, x, IntArray(shape), &dense_out);
  return dense_out;
}

}  // namespace phi
