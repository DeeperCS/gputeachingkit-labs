---
title: CUDA Tiled Matrix Multiplication
author: GPU Teaching Kit -- Accelerated Computing
---

## Objective

Implement a tiled dense matrix multiplication routine using shared memory.

## Prerequisites

Before starting this lab, make sure that:

* You have completed "Matrix Multiplication" Lab

* You have completed the required module lectures

## Instructions

Edit the code in the code tab to perform the following:

- allocate device memory
- copy host memory to device
- initialize thread block and kernel grid dimensions
- invoke CUDA kernel
- copy results from device to host
- deallocate device memory
- implement the matrix-matrix multiplication routine using shared memory and tiling

Instructions about where to place each part of the code is
demarcated by the `//@@` comment lines.

## Running Locally

Run `./TiledMatrixMultiplication_Template -e <expected.raw> -i <input0.raw>,<input1.raw> -o <output.raw> -t matrix`.