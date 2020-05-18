# Makefile for GFCATS Documentation
# Documentation built using doxygen
#

.PHONY    : all clean doxy_docs full_docs thin_docs
TOP_DIR   := ..

BUILD_TOP := $(TOP_DIR)/build
PEER_DIR  := $(BUILD_TOP)/doc



DOXY := doxygen
DOXY_FLAGS :=
DOXY_FILE := Doxyfile



### Our Doxyfile is structured such that we can export options from makefile
###
### Options for doxyfile are environment variables that we can set
### DOXY_PROJECT_NUMBER  - the version or revision default "UNVERSIONED"
DOXY_PROJECT_NUMBER := $(FULL_PROJECT_VERSION)

### DOXY_OUTPUT_DIR - Directory to build in (PEER_DIR)
DOXY_OUTPUT_DIR := $(PEER_DIR)

### DOXY_PROJECT_BRIEF - Summary of Project
DOXY_PROJECT_BRIEF := "Autonomous Sensor Board Firmware"

### DOXY_PROJECT_NAME - Name Of Project
DOXY_PROJECT_NAME := "ASB"

### DOXY_EXTRACT_ALL - Extract Everything (Private/public/protected/anon/static
### When no do extract private members and anonymous namespaces
DOXY_EXTRACT_ALL := NO

### DOXY_INPUT - space seperate list of source to process for documentation
DOXY_INPUT := " pages/main.md ../README.md ../src/ ../boards/"

### Readme
DOXY_MARKDOWN_MAINPAGE := "pages/main.md"

### DOXY_ENABLE_SOURCE - append source to documentation
DOXY_ENABLE_SOURCE := NO

### DOXY_ENABLE_CLASS_GRAPHS - Enable Class Graph Creation
DOXY_ENABLE_CLASS_GRAPHS := YES

### DOXY_ENABLE_UML - Enable UML Graph Creation
DOXY_ENABLE_UML := YES

### DOXY_ENABLE_CALL_GRAPHS - Enable Class Graph Creation
DOXY_ENABLE_CALL_GRAPHS := YES

### "Inline" Groups, more compact documentation by putting all \ingrouped classes on one page
DOXY_INLINE_GROUPS := NO

### DOXY_CREATE_HTML - create html output
DOXY_CREATE_HTML := YES

### Latex
DOXY_CREATE_LATEX := NO

### MAN
DOXY_CREATE_MAN := NO

DOXY_DISABLE_CACHE := YES

all: full_docs

publish_docs: DOXY_ENABLE_CALL_GRAPHS=YES
publish_docs: DOXY_DISABLE_CACHE=NO
publish_docs: DOXY_EXTRACT_ALL=YES
publish_docs: DOXY_ENABLE_SOURCE=NO
publish_docs: doxy_docs

full_docs: DOXY_ENABLE_CALL_GRAPHS=YES
full_docs: DOXY_EXTRACT_ALL=YES
full_docs: DOXY_ENABLE_SOURCE=YES
full_docs: DOXY_DISABLE_CACHE=NO
full_docs: DOXY_CREATE_LATEX=YES
full_docs: doxy_docs

thin_docs: DOXY_DISABLE_CACHE=NO
thin_docs: DOXY_ENABLE_UML=NO
thin_docs: DOXY_ENABLE_CLASS_GRAPHS=NO
thin_docs: DOXY_INLINE_GROUPS=YES
thin_docs: doxy_docs


doxy_docs:
	$(shell mkdir -p $(PEER_DIR))
	@echo "Starting Documentation Build"
	DOXY_PROJECT_NUMBER=$(DOXY_PROJECT_NUMBER) \
	DOXY_MARKDOWN_MAINPAGE=$(DOXY_MARKDOWN_MAINPAGE) \
	DOXY_PROJECT_NAME=$(DOXY_PROJECT_NAME) \
	DOXY_OUTPUT_DIR=$(DOXY_OUTPUT_DIR) \
	DOXY_PROJECT_BRIEF=$(DOXY_PROJECT_BRIEF) \
	DOXY_EXTRACT_ALL=$(DOXY_EXTRACT_ALL) \
	DOXY_INPUT=$(DOXY_INPUT) \
	DOXY_ENABLE_SOURCE=$(DOXY_ENABLE_SOURCE) \
	DOXY_ENABLE_CLASS_GRAPHS=$(DOXY_ENABLE_CLASS_GRAPHS) \
	DOXY_ENABLE_UML=$(DOXY_ENABLE_UML) \
	DOXY_ENABLE_CALL_GRAPHS=$(DOXY_ENABLE_CALL_GRAPHS) \
	DOXY_CREATE_HTML=$(DOXY_CREATE_HTML) \
	DOXY_CREATE_LATEX=$(DOXY_CREATE_LATEX)\
	DOXY_INLINE_GROUPS=$(DOXY_INLINE_GROUPS) \
		$(DOXY) $(DOXY_FLAGS) $(DOXY_FILE)


#export PEER_DIR
#export FULL_PROJECT_VERSION
#@echo $(PEER_DIR)
#@echo $(FULL_PROJECT_VERSION)



