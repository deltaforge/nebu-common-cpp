
SUBDIRS = include src testlibs test doc

EXTRA_DIST = bootstrap

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libnebu-common.pc
$(pkgconfig_DATA): config.status

RESULTS_FOLDER=test/results
COVERAGE_BEFORE_INFO_FILE=test/results/coverage.before.info
COVERAGE_AFTER_INFO_FILE=test/results/coverage.after.info
COVERAGE_FULL_INFO_FILE=test/results/coverage.full.info
COVERAGE_INFO_FILE=test/results/coverage.info
COVERAGE_HTML_FOLDER=test/results/html
GTEST_OUTPUT_FOLDER=test/results/gtest
GTEST_OUTPUT_FOLDER_REL=results/gtest
GTEST_GCOVR_FILE=test/results/coverage.xml

clean-coverage:
	rm -rf $(COVERAGE_OUTPUT_FOLDER) $(GTEST_OUTPUT_FOLDER) $(RESULTS_FOLDER)
	find . -type f -iname '*.gc*' -delete

if TESTS_ENABLED
$(RESULTS_FOLDER):
	mkdir -p $@

$(COVERAGE_OUTPUT_FOLDER):
	mkdir -p $@

$(COVERAGE_HTML_FOLDER):
	mkdir -p $@

$(COVERAGE_BEFORE_INFO_FILE): all $(RESULTS_FOLDER)
	lcov -d src -c -i -o $@

$(COVERAGE_AFTER_INFO_FILE): $(COVERAGE_BEFORE_INFO_FILE)
	rm -rf $(GTEST_OUTPUT_FOLDER)
	mkdir -p $(GTEST_OUTPUT_FOLDER)
	-GTEST_OUTPUT="xml:$(GTEST_OUTPUT_FOLDER_REL)/" make check
	lcov -d src -d test -c -o $@

$(COVERAGE_FULL_INFO_FILE): $(COVERAGE_AFTER_INFO_FILE) $(COVERAGE_BEFORE_INFO_FILE)
	lcov -a $(COVERAGE_BEFORE_INFO_FILE) -a $(COVERAGE_AFTER_INFO_FILE) -o $@

$(COVERAGE_INFO_FILE): $(COVERAGE_FULL_INFO_FILE)
	lcov -o $@ -r $< '/usr/*' 'test/*' 'testlibs/*'

coverage: $(COVERAGE_INFO_FILE) $(COVERAGE_HTML_FOLDER)
	-gcovr -x --xml-pretty -o test/results/coverage.xml -e `pwd`'/test*' \
	-e '/usr*' -e `dirname $$PWD`'/testlibs/*' -e `pwd`'/mocks/*'
	genhtml -o $(COVERAGE_HTML_FOLDER) $(COVERAGE_INFO_FILE)

else
coverage:
	@echo "Coverage information requires configuration with tests enabled: './configure --enable-tests CXXFLAGS='"
	false
endif

.PHONY: coverage

