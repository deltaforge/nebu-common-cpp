
if TESTS_ENABLED
AM_CPPFLAGS += -std=c++0x -Wall -Wextra --coverage -O0 -g -fno-default-inline -fno-inline
else
AM_CPPFLAGS += -std=c++0x -Wall -Wextra
endif

util_SOURCES = util/arguments.cpp \
	util/stringUtil.cpp \
	util/xmlUtil.cpp
topology_SOURCES = topology/physicalDataCenter.cpp \
	topology/physicalDataCenterFactory.cpp \
	topology/physicalHost.cpp \
	topology/physicalHostFactory.cpp \
	topology/physicalLocalStoreFactory.cpp \
	topology/physicalNetworkStoreFactory.cpp \
	topology/physicalRack.cpp \
	topology/physicalRackFactory.cpp \
	topology/physicalRoot.cpp \
	topology/physicalRootFactory.cpp
src_SOURCES = appPhysRequest.cpp \
	appVirtRequest.cpp \
	nebuClient.cpp \
	restClientAdapter.cpp \
	virtualMachine.cpp \
	virtualMachineFactory.cpp

lib_LTLIBRARIES = libnebu-common.la
libnebu_common_la_SOURCES = $(src_SOURCES) $(util_SOURCES) $(topology_SOURCES)
