/******************************************************************************
 * FILE PURPOSE: SA LLD DOCS Module specification file.
 ******************************************************************************
 * FILE NAME: module.xs
 *
 * DESCRIPTION: 
 *  This file contains the module specification for the SA LLD Documentation.
 *
 * Copyright (C) 2009-2013, Texas Instruments, Inc.
 *****************************************************************************/

/* Load the library utility. */
var libUtility = xdc.loadCapsule ("../build/buildlib.xs");

/**************************************************************************
 * FUNCTION NAME : modBuild
 **************************************************************************
 * DESCRIPTION   :
 *  The function is used to build all the components of the documentation
 **************************************************************************/
function modBuild() 
{
    /* Create the actual PROLOGUE Section for the Documentation.*/
    Pkg.makePrologue += "release: sa_lld_document_generation\n";
    Pkg.makePrologue += "sa_lld_document_generation:\n";
    Pkg.makePrologue += "\t @echo -------------------------------------------------------\n";
    Pkg.makePrologue += "\t @echo Generating SA LLD Documentation\n";
    Pkg.makePrologue += "\t doxygen docs/Doxyfile\n";
    Pkg.makePrologue += "\t @echo SA LLD Documentation Generated \n";
    Pkg.makePrologue += "\t @echo -------------------------------------------------------\n";

    /* Add the documentation file to the package. */
   /*  Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/doxygen/sa_lld_docs.chm"; */
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/UserGuide_SA_LLD.pdf";
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/doxygen/tifooter.htm";
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/doxygen/tiheader.htm";
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/doxygen/tilogo.gif";
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/doxygen/titagline.gif";
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/SA_LLD_SoftwareManifest.html"
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/ReleaseNotes_SA_LLD.pdf"
    /* Add the HTML documentation to the package */
    Pkg.otherFiles[Pkg.otherFiles.length++] = "docs/doxygen/html";

    /* Generate the ECLIPSE Plugin Generation: Only for SETUP Releases. */
    if (lldInstallType == "SETUP")
    {
        Pkg.makePrologue += "all: eclipse_plugin_generation\n";
        Pkg.makePrologue += "eclipse_plugin_generation:\n";
        Pkg.makePrologue += "\t @echo ----------------------------\n";
        Pkg.makePrologue += "\t @echo SA LLD Eclipse Plugin Generation\n";
        Pkg.makePrologue += "\t xs xdc.tools.eclipsePluginGen -o . -x ./eclipse/sample.xml -c ./eclipse/toc_cdoc_sample.xml\n";
        Pkg.makePrologue += "\t @echo SA LLD Eclipse Plugin Generated \n";
        Pkg.makePrologue += "\t @echo ----------------------------\n";
    }
}

