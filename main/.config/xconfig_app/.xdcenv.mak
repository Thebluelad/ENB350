#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /Applications/ti/tirtos_tivac_2_12_01_33/packages;/Applications/ti/tirtos_tivac_2_12_01_33/products/bios_6_41_04_54/packages;/Applications/ti/tirtos_tivac_2_12_01_33/products/ndk_2_24_02_31/packages;/Applications/ti/tirtos_tivac_2_12_01_33/products/uia_2_00_02_39/packages;/Applications/ti/ccsv6/ccs_base;/Users/Daniel/Documents/CCS/ENB350/A01/main/.config
override XDCROOT = /Applications/ti/xdctools_3_31_00_24_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /Applications/ti/tirtos_tivac_2_12_01_33/packages;/Applications/ti/tirtos_tivac_2_12_01_33/products/bios_6_41_04_54/packages;/Applications/ti/tirtos_tivac_2_12_01_33/products/ndk_2_24_02_31/packages;/Applications/ti/tirtos_tivac_2_12_01_33/products/uia_2_00_02_39/packages;/Applications/ti/ccsv6/ccs_base;/Users/Daniel/Documents/CCS/ENB350/A01/main/.config;/Applications/ti/xdctools_3_31_00_24_core/packages;..
HOSTOS = MacOS
endif
