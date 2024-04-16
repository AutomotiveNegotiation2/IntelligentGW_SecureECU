UTILS_DIR := ../utils

all: EthHostApp EthVirtMacHostApp

EthHostApp: HostApp.c $(UTILS_DIR)/EthUtils.c
	gcc $^ -I$(UTILS_DIR) -o $@

EthVirtMacHostApp: HostAppVirtMac.c $(UTILS_DIR)/EthUtils.c
	gcc $^ -I$(UTILS_DIR) -o $@


EthUtilsTest: $(UTILS_DIR)/EthUtils.c $(UTILS_DIR)/EthUtils_Test.c
	gcc $^ -I${UTILS_DIR) -o $@

.PHONY: clean
clean:
	rm -f *.o EthHostApp EthUtilsTest EthVirtMacHostApp
