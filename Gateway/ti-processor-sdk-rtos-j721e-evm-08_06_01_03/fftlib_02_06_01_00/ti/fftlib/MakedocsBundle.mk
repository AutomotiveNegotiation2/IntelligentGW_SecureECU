# ==============================================================================
# File            : MakedocsBundle.mk
# Description     : 
#
#   GNU makefile to generate VXLIB bundle documentation using Doxygen
#
# ==============================================================================


# Common paths
MASPATH = ../..
SWMPATH = docs/manifest
DOXPATH = docs/doxygen
DOXHTML = $(DOXPATH)/html
ECOHTML = $(DOXPATH)/html
SWMHTML = $(SWMPATH)/html

# Document targets 
USAGE_DOC          = ./docs/VXLIB_Users_Manual.chm
MANIFEST_DOC       = ./docs/VXLIB_Software_Manifest.chm
RELEASE_DOC_BUNDLE = ./$(DOXPATH)/release.chm
ECLIPSE_DIR        = ./eclipse/plugins

# Redirection script
REDIRECT = $(MASPATH)/mas/swtools/redirect.js

release: $(USAGE_DOC) $(MANIFEST_DOC) $(ECLIPSE_DIR)

releasenotes: $(RELEASE_DOC_BUNDLE)



$(ECLIPSE_DIR): ./eclipse/vxlib.xml ./eclipse/vxlib_toc.xml
	-@echo generating Eclipse Plugin ...
	-xs xdc.tools.eclipsePluginGen -o . -x ./eclipse/vxlib.xml -c ./eclipse/vxlib_toc.xml

$(RELEASE_DOC_BUNDLE): ./docs/doxygen/release.h
	-@echo generating Release Notes ...
	if test ! -d ./docs/doxygen/tmp; then mkdir ./docs/doxygen/tmp; fi
	cp $(TI_DOXYGEN_TEMPLATES)/*.* ./docs/doxygen/tmp
	doxygen $(MASPATH)/mas/swtools/docs/doxygen/bundlerelDoxyfile
	@xs -f $(MASPATH)/mas/swtools/bundlerelease.js
	$(RMDIR) ./docs/doxygen/tmp

genbundledocs $(USAGE_DOC): ./$(DOXPATH)/doxygen.h
	-@echo Generating VXLIB bundle documentation ...
	if test ! -d $(DOXHTML); then mkdir $(DOXHTML); fi
	cp $(TI_DOXYGEN_TEMPLATES)/*.* $(DOXHTML)
	@echo Pulling in VXLIB API Documentation ...
	@cp -fru $(MASPATH)/vxlib/$(ECOHTML) $(DOXHTML)/vxlib_html
	doxygen ./$(DOXPATH)/Doxyfile
	xs -f $(REDIRECT) ./doxygen/html/index.html > ./docs/VXLIB_Users_Manual.html

$(MANIFEST_DOC): ./$(SWMPATH)/manifest.h
	-@echo generating Software Manifest ...
	if test ! -d ./$(SWMHTML); then mkdir ./$(SWMHTML); fi
	@cp $(TI_DOXYGEN_TEMPLATES)/*.* ./$(SWMHTML)
	doxygen ./$(SWMPATH)/Doxyfile
	xs -f $(REDIRECT) ./manifest/html/index.html > ./docs/VXLIB_Software_Manifest.html

# End of Makedocs.mk
