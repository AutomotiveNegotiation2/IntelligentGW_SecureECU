/*
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/



/*
 * This is a little header file which doxygen parses to generate the main
 * documentation page
 */ 
  
/**
 *  @mainpage 
 *  <p align="center"> 
 *  <a href="#Introduction">Introduction</a>,
 *  <a href="#License_Standard_ExportControl">License, Standard, and Export Control Information</a>
 *  <a href="#Known_Issues">Known Issues</a>,
 *  <a href="#Documentation">Documentation</a>,
 *  <a href="#New_This_Release">New This Release</a>,
 *  <a href="#Compatibility">Upgrade and Compatibility Information</a>,
 *  <a href="#Host_Support">Host Support</a>,
 *  <a href="#Device_Support">Device Support</a>,
 *  <a href="#Validation">Validation Information</a>,
 *  <a href="#Benchmarks">Benchmarks</a>,
 *  <a href="#Version">Versioning</a>,
 *  <a href="#Support">Technical Support and Product Updates</a>
 *  </p>
 *
 *  <!--****Introduction**********************************************************************************-->
 *
 *  <hr>
 *
 *  <h2><a name="Introduction">Introduction</a></h2>
 *
 *  The Security Accelerator (SA) also known as cp_ace (Adaptive Cryptographic Engine) is designed to 
 *  provide packet security as part of IPSEC, SRTP and 3GPP industry standard. The security accelerator 
 *  low level driver (referred to as the module) provides APIs for the configuration and control of 
 *  the security accelerator sub-system. The SA low level driver provides an abstraction layer between 
 *  the application and the Security Accelerator Sub System (SASS). It provides both the system level 
 *  interface and the channel level interface with a set of APIs defined here.
 *
 *  <a href="#XDC_TOP">back to top</a>
 *
 *  <!--****License, Standard, and Export Control Information***************************************************-->
 *
 *  <hr>
 *
 *  <h2><a name="License_Standard_ExportControl">License, Standard, and Export Control Information</a></h2>
 *
 *  License Information:
 *   - The SA LLD code provided within this package is based on the TI license.  The MD5 and SHA2 algorithms used by SA LLD 
 *      and provided within this package are based on the open source MD5 and SHA2 code provided by OpenSSL release 0.9.8h,
 *      which can be found at <a href="http://www.openssl.org/source/">http://www.openssl.org/source/</a>.  License
 *      information for all source provided in this component can be found in the 
 *      <a href="docs/SA_LLD_1_0_SoftwareManifest.pdf">Software Manifest</a>.  All advertising materials mentioning features or use
 *      of the MD5 software must display the following acknowledgement: "This product includes cryptographic software written by
 *      Eric Young (eay@cryptsoft.com)".
 *
 *  Standards Information:
 *
 *  Export Control Information:
 *   - This component contains cryptographic elements subject to export control.  At the time of providing this component all
 *      software-related elements are classified under the general ECCN# 5D002.  All documentation-related elements are
 *      classified under the general ECCN# 5E002.  <b>It is the responsibility of the shipping party to obtain necessary export
 *      control approvals based upon the component's end-use application.</b>
 *
 *  <a href="#XDC_TOP">back to top</a>
 *
 *  <!--****Known Issues**********************************************************************************-->
 *
 *  <hr>
 *
 *  <h2><a name="Known_Issues">Known Issues</a></h2>
 *
 *  None.
 *
 *  <a href="#XDC_TOP">back to top</a>
 *
 *  <!--****Documentation*********************************************************************************-->
 *
 *  <hr>
 *
 *  <h2><a name="Documentation">Documentation</a></h2>
 *  <p>The following documentation is available:
 *   - <a href="docs/doxygen/sa_lld_docs.chm">SA LLD API Documentation</a>
 *   - <a href="docs/salld_sds.chm">SA LLD Software Design Specification</a>
 *   - <a href="docs/SA_LLD_1_0_SoftwareManifest.pdf"> SA LLD Software Manifest Documentation</a>
 *
 *  <a href="#XDC_TOP">back to top</a> 
 *
 *  <!--****New This Release*******************************************************************************-->
 *
 *  <hr>
 *
 *  <h2><a name="New_This_Release">New This Release</a></h2>
 *  
 *  <p><b>Current Changes</b>
 *  <p>The following changes have been made in release 1.0.0.1:
 *   - Modifications to the PDSP firmware to support the latest Nyquist/Shannon functional simulator  0.8.0.0
 *   - Modifications to the examples and unit tests to support the new CPPI specification (4.2.9)
 *
 *  <p><b>Previous Changes</b>
 *  <p>Release 1.0.0.0 provided the following:
 *
 *  <a href="#XDC_TOP">back to top</a>
 *
 *  <!--****Upgrade and Compatibility Information**************************************************************-->
 *
 *  <hr>
 *
 *  <h2><a name="Compatibility">Upgrade and Compatibility Information</a></h2>
 *
 *  Please note that the package compatibility keys are independent of XDC product release numbers. 
 * 
 *  Package compatibility keys are intended to: 
 * 
 *   -# Enable tooling to identify incompatibilities between components, and 
 *   -# Convey a level of compatibility between different releases to set end user expectations. 
 * 
 * Package compatibility keys are composed of 4 comma-delimited numbers - M, S, R, P - where: 
 *
 * - <b>M = Major</b> - A difference in M indicates a break in compatibility. The package consumer is required to re-write its source code in order to use the package.
 * - <b>S = Source</b> - A difference in S indicates source compatibility. The package consumer’s source code doesn't require change, but does require a recompile. 
 * - <b>R = Radix</b> - A difference in R indicates an introduction of new features, but compatibility with previous interfaces is not broken. If libraries are provided by the package, an application must re-link with the new libraries, but is not required to recompile its source.
 * - <b>P = Patch</b> - A difference in P indicates that only bugs have been fixed in the latest package and no new features have been introduced. If libraries are provided by the package, an application must re-link with the new libraries, but is not required to recompile its source. 
 *
 *  <a href="#XDC_TOP">back to top</a>
 *
 *  <!--****Host Support***********************************************************************************-->
 *
 *  <hr>
 *
 *  <h2><a name="Host_Support">Host Support</a></h2>
 *
 *  The current XDC toolset can be used to build components on the following hosts:
 *   - Windows XP 
 *
 *  <a href="#XDC_TOP">back to top</a>
 *
 *  <!--****Device Support*********************************************************************************-->
 *
 *  <hr>
 *
 *  <h2><a name="Device_Support">Device Support</a></h2>
 *
 *  This release supports the following device families: 
 *  - C64P 
 *
 *  <a href="#XDC_TOP">back to top</a>
 *
 *  <!--****Validation Information****************************************************************************-->
 *
 *  <hr>
 *
 *  <h2><a name="Validation">Validation Information</a></h2>
 *
 *  This release was built and validated using the following components:
 *
 *  <p><b>Component Dependencies</b>
 *
 *  <p>SA LLD
 *  <p>SA LLD Test Simulation
 *   - ti.drv.sa 1.0.0.1 (SA LLD to be tested)
 *   - ti.drv.pa 1.0.0.6 (PA LLD) 
 *   - ti.drv.cppi 1.0.0.4 (CPPI LLD) 
 *   - ti.drv.qmss 1.0.0.4 (QMSS LLD) 
 *
 *  <p><b>Tool Dependencies for Source Release</b>
 *
 *  - XDC Tools version 3.10.2
 *  - RTSC Packaging Standard version 1.00.00
 *  - XDAIS version 5.23
 *  - C6x Code Generation Tools version 6.1.12
 *
 *  <a href="#XDC_TOP">back to top</a>
 *
 *  <!--****Benchmarks************************************************************************************-->
 *
 *  <hr>
 *
 *  <h2><a name="Benchmarks">Benchmarks</a></h2>
 *  <b> TBD </b>
 *
 *  <a href="#XDC_TOP">back to top</a>
 *
 *  <!--****Versioning*************************************************************************************-->
 *
 *  <hr>
 *
 *  <h2><a name="Version">Versioning</a></h2>
 *
 *  This product's version follows a version format, <b>M.m.x.p</b>,
 *  where <b>M</b> is a single digit Major number, <b>m</b> is single digit minor number,
 *  <b>x</b> is single digit vertical numbner and <b>p</b> is a single digit patch number
 *
 *  <p>Please note that version numbers and compatibility keys are
 *  NOT the same. For an explanation of compatibility keys, please refer to
 *  the '<a href="#Compatibility">Upgrade and Compatibility Information</a>' section.
 *
 *  <a href="#XDC_TOP">back to top</a>
 *
 *  <!--****Technical Support and Product Updates*************************************************************-->
 *
 *  <hr>
 *
 *  <h2><a name="Support">Technical Support and Product Updates</a></h2>
 *
 *  Contact local TI Field Application Engineer for technical support.
 *
 *  <a href="#XDC_TOP">back to top</a>
 *
 */
