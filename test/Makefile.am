
if TESTS_ENABLED
AM_CPPFLAGS += -std=c++0x -Wall -Wextra --coverage -O0 -g -fno-default-inline -fno-inline
else
AM_CPPFLAGS += -std=c++0x -Wall -Wextra
endif

nebuincludedir = $(includedir)/nebu/
nobase_nebuinclude_HEADERS = mocks/*.h

include MakefileTestList.am

TESTS = $(unit_TESTS) $(factory_TESTS) $(integration_TESTS)
check_PROGRAMS = $(TESTS)
AM_LDFLAGS = -Wl,--whole-archive $(top_srcdir)/src/.libs/libnebu-common.a -Wl,--no-whole-archive \
	$(TINYXML2_LIBS) -lrestclient-cpp $(top_srcdir)/testlibs/gmock.a -lgcov
AM_CPPFLAGS += -Itest/ -I$(top_srcdir)/include -isystem $(top_srcdir)/testlibs/gtest/include \
	-isystem $(top_srcdir)/testlibs/gmock/include $(TINYXML2_CFLAGS)

