# Introduction {#mainpage}

[TOC]

TIOVX is TI's implementation of OpenVX Standard.

TIOVX allows users to create vision and compute applications using OpenVX API.
These OpenVX applications can be executed on TI SoCs like TDA2x, TDA3x. TIOVX is fully conformant
to OpenVX v1.1 specification. TIOVX also provides optimized OpenVX kernels for C66x DSP. An extension API
allows users to integrate their own natively developed custom kernels and call them using OpenVX APIs.

Top level block diagram of TIOVX is shown below.

![](tiovx_block_diagram.png "TIOVX Block Diagram")

This document describes the design of TIOVX component.

# Functional Overview {#did_intro_overview}

1. TIOVX is TI's implementation of OpenVX standard. Currently supported
   OpenVX version is v1.1.

2. TIOVX can be built for Embedded Linux, TI-RTOS as well
   as x86 Linux PC's. Not all applications will work on all operating
   systems

4. TIOVX consists of framework implementation which represents the OpenVX APIs.
   It also consists of OpenVX v1.1 specified "kernel wrappers".
   The kernel library implementation is part of VXLIB. A platform layer/library
   allows TIOVX to be ported to different SoC/SW environments.

5. TIOVX also consists of OpenVX conformance test to verify that TI's implementation
   is compliant to Khronos specification.

6. TIOVX also has step by step tutorials for users to quickly learn and
   get started on OpenVX.

# Assumptions and Constraints {#did_intro_assumptions}

1. Code is written using ANSI C language

2. Code uses stdint.h data types.

3. Below basic Misra-C rules are followed to allow Misra-C compatibility
   in future

   1. No multiple return in a function
   2. No continue in a loop
   3. No multiple break in a loop

5. The application assumes below basic services are avaiable to it

   1. printf API which redirects logs to UART console or CCS console
   2. fopen, fclose, fseek, fread, fwrite stdio.h for file IO to a
      removeable media like SD card
   3. Memory allocation, OS services like task, semaphore and IPC
      services are assumed

# Features Not Supported {#did_intro_features_not_supported}

1.

# Revision History {#did_rev_history}

Revision | Date          | Author             | Description
---------|---------------|--------------------|-----------------------------------------------------------------
0.1      | 1 Sept  2018  | Kedar C            | First draft
