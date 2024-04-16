# Top Level Design {#did_top_level_design}

[TOC]

# Requirements Addressed {#did_top_level_requirements}

- https://jira.itg.ti.com/browse/TIOVX-25

# Top Level Directory Structure {#did_top_level_dir_structure}

Shown below is the directory structure of tiovx::

    tiovx
    ├── concerto                # makefile based build system
    ├── conformance_tests       # conformance test
    │   ├── test_conformance    # Khronos OpenVX defined conformance test (CT)
    │   ├── test_data           # input and reference data for CT
    │   ├── test_engine         # CT engine/framework
    │   ├── test_executable     # CT main for x86 PC
    │   └── test_tiovx          # Additional tests in CT defined by TI
    ├── docs                    # User documentation
    ├── include                 # User interface
    │   ├── TI                  # TI defined extension APIs
    │   └── VX                  # OpenVX defined APIs
    ├── kernels                 # OpenVX kernels (kernel wrappers)
    │   ├── common              # Common utility function used by all kernels
    │   ├── include             # TI extention kernel APIs
    │   │   └── TI
    │   ├── ivision             # Kernels using TI ivision interface
    │   └── openvx-core         # Khronos OpenVX v1.1 defined kernel wrappers
    ├── lib                     # Pre built libraries
    ├── source                  # OpenVX Framework source code
    │   ├── framework           # Framework logic agnostic of underlying OS/SoC
    │   ├── include             # Internal include files
    │   ├── platform            # platform (OS/SOC) specific logic
    │   └── vxu                 # VX utility library as defined by Khronos
    ├── tools                   # Offline tools and utilities
    │   ├── PyTIOVX             # Python based code generator module
    ├── tutorial                # OpenVX tutorials for users
    └── utils                   # Additional utilities used within OpenVX applications


# Top Level Component Interaction {#did_top_level_component_interaction}

![](TIOpenVX-PackageDiagram.jpg "TIOVX Package Diagram")

Generated from TIOpenVX.uml using StarUML 1.0
