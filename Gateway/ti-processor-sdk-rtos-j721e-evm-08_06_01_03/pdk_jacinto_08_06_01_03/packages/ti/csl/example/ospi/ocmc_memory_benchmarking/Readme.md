## Demo Overview

* This demo provides a means of measuring the performance of a realistic application where the text of the application is sitting in various memory locations and the data is sitting in On-Chip-Memory RAM (referred to as OCM, OCMC or OCMRAM).
* The application executes 10 different configurations of the same text varying by data vs. instruction cache intensity. Each test calls 16 separate functions 500 total times in random order.
* The most instruction intensive example achieves a instruction cache miss rate (ICM/sec) of ~3-4 million per second when run entirely from OCMRAM. This is a rate that we have similarly seen in real-world customer examples.
* More data instensive tests have more repetitive code, achieving much lower ICM rates.

| Application Output | Description |
| ------ | ------ |
| ```Mem Cpy size    => 100``` | Size of the memcpy in bytes executed by each task |
| ```Exec Time in usec => 2567``` | Amount of time in microseconds |
| ```Iter            => 1``` | Number of times the test was run |
| ```Task calls      => 500``` | Number of randomly ordered calls to the 16 tasks |
| ```Inst Cache miss => 11421``` | Total instruction cache misses |
| ```Inst Cache acc  => 650207``` | Total instruction cache accesses |
| ```num switches    => 1469``` | Number of total context switches  |
| ```num instr exec  => 1029260``` | Total number of executed instructions |
| ```ICM/sec         => 4449162``` | Instruction cache misses per second |
| ```INST/sec        => 400958317``` | Instructions executed per second |
| ```ICM Percentage  => 1.110``` | instruction cache misses / instructions executed |

## Supported Configurations

|  Core             | SOC         | Supported Memory Configurations      |
| ----------------- | ----------- | ------------------------------------ |
| mcu1\_0           | j721e       | ocmc msmc ddr xip                    |
| mcu2\_0           | j721e       | ocmc msmc ddr xip                    |
| mcu1\_0 + mcu2\_0 | j721e	  	  | ddr xip                              |
| mcu1\_0           | j7200       | ocmc msmc ddr xip                    |
| mcu2\_0           | j7200       | ocmc msmc ddr xip                    |
| mcu1\_0 + mcu2\_0 | j7200	  	  | ddr xip                              |

## How to Build
* Go to the build folder, namely, <pdk_path>/packages/ti/build/

### Basic Single Core Benchmarking
* Build the bootloader
	```make sbl_lib_cust_clean SOC=j7200 BOARD=j7200_evm CORE=mcu1_0 -sj```
	```make sbl_cust_img_clean SOC=j7200 BOARD=j7200_evm CORE=mcu1_0 -sj```
  * If building for J7200 mcu2_0 or J7200 multicore:
	```make sbl_cust_img SOC=j7200 BOARD=j7200_evm CORE=mcu1_0 RAT=1 -sj```
  * Otherwise:
	```make sbl_cust_img SOC=j7200 BOARD=j7200_evm CORE=mcu1_0 -sj```

* Build the application (XIP and non-XIP): 
	```make memory_benchmarking_app CORE=[Core] SOC=[SOC] BOARD=[SOC]_evm MEM=[mem_conf] -sj```

### Multicore Core Benchmarking

* If building for XIP, edit <pdk_path>/boot/sbl/src/ospi/sbl_ospi.c - be sure to "#define BUILD_XIP" and comment out any line that may say "#undef BUILD_XIP". Then rebuild the cust sbl image as shown below.
* Run the command:
```make sbl_cust_img SOC=[SOC] BOARD=[SOC]_evm RAT=1 -sj```
  * RAT option can be ignored if building for J721e
```make memory_benchmarking_app CORE=mcu1_0 SOC=[SOC] BOARD=[SOC]_evm MEM=[mem_conf] MULTICORE=1 -sj```  
```make memory_benchmarking_app CORE=mcu2_0 SOC=[SOC] BOARD=[SOC]_evm MEM=[mem_conf] MULTICORE=1 -sj```  
```../boot/sbl/tools/multicoreImageGen/bin/MulticoreImageGen LE 55 [mem_conf]_multicore.appimage 4 ../binary/memory_benchmarking_app/bin/[SOC]_evm/[mem_conf]_perf_[SOC]_evm_mcu1_0ExampleApp_release.rprc 6 ../binary/memory_benchmarking_app/bin/j7200_evm/[mem_conf]_perf_[SOC]_evm_mcu2_0ExampleApp_release.rprc```  
* The appimage to flash or load to CCS below (line 4 of the flash command) should now be the [mem_conf]_multicore.appimage file in your build directory.

* If building for XIP, run the following command as well.
```../boot/sbl/tools/multicoreImageGen/bin/MulticoreImageGen LE 55 xip_multicore.appimage_xip 4 ../binary/memory_benchmarking_app/bin/[SOC]_evm/xip_perf_[SOC]_evm_mcu1_0ExampleApp_release.rprc_xip 6 ../binary/memory_benchmarking_app/bin/[SOC]_evm/xip_perf_[SOC]_evm_mcu2_0ExampleApp_release.rprc_xip ```


### Building for CCS
* Run the command: ```make memory_benchmarking_app CORE=[Core] SOC=[SOC] BOARD=[SOC]_evm MEM=[mem_conf] CCS=1 -sj```
* Note that XIP does not work in CCS because of the way in which these applications need to be loaded into flash.


## How to Run (Linux Host Machine Assumed)
### Via OSPI
* Build the custom sbl image
* Put the EVM in UART boot mode
* From the <pdk_path>/packages/ti/build/ directory:
```make sbl_cust_img CORE=[Core] SOC=[SOC] BOARD=[SOC]_evm -sj```

* Download and install the [uniflash tool](https://www.ti.com/tool/UNIFLASH)

#### Non XIP Use Cases

If using a multicore appimage, just replace flashing step 4 with the appimage that was created.

* To flash J721e:
	```
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <uniflash_directory>/processors/FlashWriter/j721e_evm/uart_j721e_evm_flash_programmer_release.tiimage -i 0
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/boot/sbl/binary/j721e_evm/cust/bin/sbl_cust_img_mcu1_0_release.tiimage -d 3 -o 0
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/drv/sciclient/soc/V1/tifs.bin -d 3 -o 80000
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/binary/memory_benchmarking_app/bin/j721e_evm/[mem_conf]_perf_j721e_evm_[Core]ExampleApp_release.appimage -d 3 -o 100000
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/board/src/flash/nor/ospi/nor_spi_patterns.bin -d 3 -o 3FE0000
	```
* To flash J7200:
	```
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <uniflash_directory>/processors/FlashWriter/j7200_evm/uart_j7200_evm_flash_programmer_release.tiimage -i 0
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/boot/sbl/binary/j7200_evm/cust/bin/sbl_cust_img_mcu1_0_release.tiimage -d 3 -o 0
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/drv/sciclient/soc/V2/tifs.bin -d 3 -o 80000
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/binary/memory_benchmarking_app/bin/j7200_evm/[mem_conf]_perf_j7200_evm_[Core]ExampleApp_release.appimage -d 3 -o 100000
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/board/src/flash/nor/ospi/nor_spi_patterns.bin -d 3 -o 3FC0000
	```

#### Single Core XIP
* To flash single core XIP on J7200
	```
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <uniflash_directory>/processors/FlashWriter/j7200_evm/uart_j7200_evm_flash_programmer_release.tiimage -i 0
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/boot/sbl/binary/j7200_evm/cust/bin/sbl_cust_img_mcu1_0_release.tiimage -d 3 -o 0
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/drv/sciclient/soc/V2/tifs.bin -d 3 -o 80000
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/boot/sbl/example/k3MulticoreApp/binary/j7200/sbl_boot_multicore_xip_entry_[Core]_release.appimage -d 3 -o 100000
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/boot/sbl/example/k3MulticoreApp/binary/j7200/sbl_boot_multicore_xip_entry_[Core]_release.appimage_xip -d 3
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/board/src/flash/nor/ospi/nor_spi_patterns.bin -d 3 -o 3FC0000
	```
* To flash single core XIP on J721e
	```
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <uniflash_directory>/processors/FlashWriter/j721e_evm/uart_j721e_evm_flash_programmer_release.tiimage -i 0
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/boot/sbl/binary/j721e_evm/cust/bin/sbl_cust_img_mcu1_0_release.tiimage -d 3 -o 0
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/drv/sciclient/soc/V2/tifs.bin -d 3 -o 80000
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/boot/sbl/example/k3MulticoreApp/binary/j721e/sbl_boot_multicore_xip_entry_[Core]_release.appimage -d 3 -o 100000
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/boot/sbl/example/k3MulticoreApp/binary/j721e/sbl_boot_multicore_xip_entry_[Core]_release.appimage_xip -d 3
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/board/src/flash/nor/ospi/nor_spi_patterns.bin -d 3 -o 3FE0000
	```

#### Multicore XIP
* To flash multicore XIP J7200 (be sure to see the build instructions above for getting xip_multicore.appimage and xip_multicore.appimage_xip):
	```
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <uniflash_directory>/processors/FlashWriter/j7200_evm/uart_j7200_evm_flash_programmer_release.tiimage -i 0
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/boot/sbl/binary/j7200_evm/cust/bin/sbl_cust_img_mcu1_0_release.tiimage -d 3 -o 0
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/drv/sciclient/soc/V2/tifs.bin -d 3 -o 80000
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/build/xip_multicore.appimage -d 3 -o 100000
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/build/xip_multicore.appimage_xip -d 3
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/board/src/flash/nor/ospi/nor_spi_patterns.bin -d 3 -o 3FC0000
	```

* To flash multicore XIP J721e (be sure to see the build instructions above for getting xip_multicore.appimage and xip_multicore.appimage_xip):
	```
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <uniflash_directory>/processors/FlashWriter/j721e_evm/uart_j721e_evm_flash_programmer_release.tiimage -i 0
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/boot/sbl/binary/j721e_evm/cust/bin/sbl_cust_img_mcu1_0_release.tiimage -d 3 -o 0
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/drv/sciclient/soc/V2/tifs.bin -d 3 -o 80000
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/build/xip_multicore.appimage -d 3 -o 100000
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/build/xip_multicore.appimage_xip -d 3
	sudo <uniflash_directory>/dslite.sh --mode processors -c /dev/ttyUSB1 -f <pdk_path>/packages/ti/board/src/flash/nor/ospi/nor_spi_patterns.bin -d 3 -o 3FE0000
	```

* For mcu1_0: Attach USB cable to UART Terminal 1 _of the MCU UART port_ (```sudo minicom -D /dev/ttyUSB1```) to see the output of the application
* For mcu2_0: Attach USB cable to UART Terminal 0 _of the Main UART port_ (```sudo minicom -D /dev/ttyUSB0```) to see the output of the application
* Power on the EVM in OSPI boot mode

### Via CCS
* Put the EVM in CCS (No boot) mode
* Execute launch.js script which runs the GEL files that setup the SoC
1. Go to “View” on the main toolbar banner and select “Scripting Console”
2. This opens the scripting console, inside this console you will invoke the launch.js via loadJSFile() command:
```js:>  loadJSFile(“<pdk_path>/pdk/packages/ti/drv/sciclient/tools/ccsLoadDmsc/j7200/launch.js”)```
* This command will automatically load appropriate gels and put the SoC in a state ready to run test cases
 
#### Running Single Core Test cases
1. If  running on Main R5, load rat.gel first and run Configure_RAT_5000000() under “scripts” along top menu bar. No action is required for running on MCU R5.
2. To run the benchmark application, browse to “Run” along the main tool boar and select "Load" and "Load Program".
3. Browse to where demo benchmark binary location: <pdk_path>/pdk/packages/ti/binary/memory_benchmarking_app/bin/j7200_evm
4. Select the application that you would like to run

#### Running Multi-Core Test cases
###### Load binary onto MCU R5
1. Select “Run” along the main tool boar and select "Load" and "Load Program" along the menu.
2. Browse to the demo benchmark binary location: <pdk_path>/pdk/packages/ti/binary/memory_benchmarking_app/bin/j7200_evm

###### Load binary onto Main R5
1. Load rat.gel first and run Configure_RAT_5000000() under “scripts” along top menu bar  
2. Select “Run” along the main tool boar and select "Load" and "Load Program" along the menu.
3. Browse to where demo benchmark binary location: <pdk_path>/pdk/packages/ti/binary/memory_benchmarking_app/bin/j7200_evm

###### Load DSS script that will run both cores concurrently
1. Go to “View” on the main toolbar banner and select “Scripting Console”
2. This opens the scripting console, inside this console you will invoke the multicore.js via
loadJSFile() command: ```js:>  loadJS File(“<pdk_path>/multicore.js”)```
* This script will run both cores concurrently and results will be interleaved via printouts to CCS console.

#### Enabling R5 MSMC as Cache      
1. Follow directions for running on single cores depending on which core you would like to load test on
2. Load rat.gel first and run either Configure_MSMCcache_MCUR5 or Configure_MCMCcache_MainR5 depending on which core you are testing.
3. Run benchmark app as described before - you should see an improvement in performance as compared to running the memory benchmark without configuring MSMC as cache.

### Addtional Notes
* Again, XIP *_cannot run via CCS_* due to the location in memory where the application code sits.
* When building the sbl_cust_img, if you would like to see more verbose output, you may change the flag in <pdk_path>/packages/ti/boot/sbl/sbl_component.mk CUST_SBL_TEST_FLAGS called "-DSBL_LOG_LEVEL" from 1 to 3. **However**, this will cause the cache miss rate to increase substantially and performance times to decrease. So only use this for debugging reasons, but not for actual performance benchmarking.
* A "Mem Cpy size" of 0, means that no memcpy occurred and the application test was strictly instructions-based.
* When building different memory configurations, it is always a good idea to do a clean build. Some consecutive builds will work, but some also will not, so it is best to be safe by building cleanly.
