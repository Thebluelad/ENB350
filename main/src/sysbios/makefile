vpath % /Applications/ti/tirtos_tivac_2_12_01_33/products/bios_6_41_04_54/packages/ti/sysbios/
vpath %.c /Applications/ti/xdctools_3_31_00_24_core/packages/

CCOPTS    = -Wunused -Wunknown-pragmas -ffunction-sections -fdata-sections  -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs -g  -O3 -I/Applications/ti/tirtos_tivac_2_12_01_33/products/bios_6_41_04_54/packages/gnu/targets/arm//libs/install-native/$(GCCTARG)/include -Dfar= -D__DYNAMIC_REENT__   -Dti_sysbios_family_arm_m3_Hwi_enableException__D=TRUE -Dti_sysbios_family_arm_m3_Hwi_disablePriority__D=32U -Dti_sysbios_family_arm_m3_Hwi_numSparseInterrupts__D=0U

XDC_ROOT  = /Applications/ti/xdctools_3_31_00_24_core/packages/

BIOS_ROOT = /Applications/ti/tirtos_tivac_2_12_01_33/products/bios_6_41_04_54/packages/ti/sysbios/

BIOS_DEFS =  -Dti_sysbios_BIOS_swiEnabled__D=TRUE -Dti_sysbios_BIOS_taskEnabled__D=TRUE -Dti_sysbios_BIOS_clockEnabled__D=TRUE -Dti_sysbios_BIOS_runtimeCreatesEnabled__D=TRUE -Dti_sysbios_hal_Hwi_DISABLE_ALL_HOOKS -Dti_sysbios_knl_Swi_DISABLE_ALL_HOOKS -Dti_sysbios_BIOS_smpEnabled__D=FALSE -Dti_sysbios_Build_useHwiMacros -Dti_sysbios_knl_Swi_numPriorities__D=16 -Dti_sysbios_knl_Task_deleteTerminatedTasks__D=FALSE -Dti_sysbios_knl_Task_numPriorities__D=16 -Dti_sysbios_knl_Task_checkStackFlag__D=TRUE -Dti_sysbios_knl_Clock_TICK_SOURCE=ti_sysbios_knl_Clock_TickSource_TIMER -Dti_sysbios_knl_Clock_TICK_MODE=ti_sysbios_knl_Clock_TickMode_PERIODIC -Dti_sysbios_hal_Core_delegate_getId=ti_sysbios_hal_CoreNull_getId__E -Dti_sysbios_hal_Core_delegate_interruptCore=ti_sysbios_hal_CoreNull_interruptCore__E -Dti_sysbios_hal_Core_delegate_lock=ti_sysbios_hal_CoreNull_lock__E -Dti_sysbios_hal_Core_delegate_unlock=ti_sysbios_hal_CoreNull_unlock__E -Dti_sysbios_hal_Core_numCores__D=1 -Dti_sysbios_hal_CoreNull_numCores__D=1 -Dti_sysbios_utils_Load_taskEnabled__D=TRUE -Dti_sysbios_utils_Load_swiEnabled__D=FALSE -Dti_sysbios_family_arm_m3_Hwi_dispatcherSwiSupport__D=TRUE -Dti_sysbios_family_arm_m3_Hwi_dispatcherTaskSupport__D=TRUE -Dti_sysbios_family_arm_m3_Hwi_dispatcherAutoNestingSupport__D=TRUE -Dti_sysbios_family_arm_m3_Hwi_dispatcherIrpTrackingSupport__D=TRUE -Dti_sysbios_knl_Semaphore_supportsEvents__D=FALSE -Dti_sysbios_knl_Semaphore_supportsPriority__D=TRUE

BIOS_INC  = -I"/Applications/ti/tirtos_tivac_2_12_01_33/products/bios_6_41_04_54/packages/"

TARGET_INC = -I"/Applications/ti/tirtos_tivac_2_12_01_33/products/bios_6_41_04_54/packages/"

INCS = $(BIOS_INC) $(TARGET_INC)  

GCCTARG = arm-none-eabi

CC = /Applications/ti/ccsv6/tools/compiler/gcc-arm-none-eabi-4_8-2014q3/bin/arm-none-eabi-gcc -c -MD -MF $@.dep $(CCOPTS)
ASM = /Applications/ti/ccsv6/tools/compiler/gcc-arm-none-eabi-4_8-2014q3/bin/arm-none-eabi-gcc -c -x assembler-with-cpp $(CCOPTS)
AR = /Applications/ti/ccsv6/tools/compiler/gcc-arm-none-eabi-4_8-2014q3/bin/arm-none-eabi-ar  cr

DEL = rm -f
CP = cp -f

define RM
	$(if $(wildcard $1),$(DEL) $1,:)
endef

define ASSEMBLE
	@echo asmm4fg $< ...
	@$(ASM) $(BIOS_DEFS) -I "/Applications/ti/xdctools_3_31_00_24_core/packages/" -Dxdc_target_types__=/Applications/ti/tirtos_tivac_2_12_01_33/products/bios_6_41_04_54/packages/gnu/targets/arm/std.h -Dxdc_target_name__=M4F $(INCS) $<
endef

define COMPILE
	@echo clm4fg $< ...
	@$(CC) $(BIOS_DEFS) -I "/Applications/ti/xdctools_3_31_00_24_core/packages/" -Dxdc_target_types__=/Applications/ti/tirtos_tivac_2_12_01_33/products/bios_6_41_04_54/packages/gnu/targets/arm/std.h -Dxdc_target_name__=M4F $(INCS) $<
endef


all: sysbios.am4fg

m3_Hwi_asm_gnu.o: family/arm/m3/Hwi_asm_gnu.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) -o m3_Hwi_asm_gnu.o

m3_Hwi_asm_switch_gnu.o: family/arm/m3/Hwi_asm_switch_gnu.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) -o m3_Hwi_asm_switch_gnu.o

m3_IntrinsicsSupport_asm_gnu.o: family/arm/m3/IntrinsicsSupport_asm_gnu.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) -o m3_IntrinsicsSupport_asm_gnu.o

m3_TaskSupport_asm_gnu.o: family/arm/m3/TaskSupport_asm_gnu.sv7M makefile
	@-$(call RM, $@)
	$(ASSEMBLE) -o m3_TaskSupport_asm_gnu.o


_BIOS.o: BIOS.c makefile
	@-$(call RM, _BIOS.o)
	$(COMPILE) -o _BIOS.o
knl_Clock.o: knl/Clock.c makefile
	@-$(call RM, knl_Clock.o)
	$(COMPILE) -o knl_Clock.o
knl_Idle.o: knl/Idle.c makefile
	@-$(call RM, knl_Idle.o)
	$(COMPILE) -o knl_Idle.o
knl_Intrinsics.o: knl/Intrinsics.c makefile
	@-$(call RM, knl_Intrinsics.o)
	$(COMPILE) -o knl_Intrinsics.o
knl_Queue.o: knl/Queue.c makefile
	@-$(call RM, knl_Queue.o)
	$(COMPILE) -o knl_Queue.o
knl_Semaphore.o: knl/Semaphore.c makefile
	@-$(call RM, knl_Semaphore.o)
	$(COMPILE) -o knl_Semaphore.o
knl_Swi.o: knl/Swi.c makefile
	@-$(call RM, knl_Swi.o)
	$(COMPILE) -o knl_Swi.o
knl_Swi_andn.o: knl/Swi_andn.c makefile
	@-$(call RM, knl_Swi_andn.o)
	$(COMPILE) -o knl_Swi_andn.o
knl_Task.o: knl/Task.c makefile
	@-$(call RM, knl_Task.o)
	$(COMPILE) -o knl_Task.o
hal_Hwi.o: hal/Hwi.c makefile
	@-$(call RM, hal_Hwi.o)
	$(COMPILE) -o hal_Hwi.o
hal_Hwi_stack.o: hal/Hwi_stack.c makefile
	@-$(call RM, hal_Hwi_stack.o)
	$(COMPILE) -o hal_Hwi_stack.o
hal_Hwi_startup.o: hal/Hwi_startup.c makefile
	@-$(call RM, hal_Hwi_startup.o)
	$(COMPILE) -o hal_Hwi_startup.o
gnu_ReentSupport.o: rts/gnu/ReentSupport.c makefile
	@-$(call RM, gnu_ReentSupport.o)
	$(COMPILE) -o gnu_ReentSupport.o
m3_Hwi.o: family/arm/m3/Hwi.c makefile
	@-$(call RM, m3_Hwi.o)
	$(COMPILE) -o m3_Hwi.o
m3_TaskSupport.o: family/arm/m3/TaskSupport.c makefile
	@-$(call RM, m3_TaskSupport.o)
	$(COMPILE) -o m3_TaskSupport.o
lm4_TimestampProvider.o: family/arm/lm4/TimestampProvider.c makefile
	@-$(call RM, lm4_TimestampProvider.o)
	$(COMPILE) -o lm4_TimestampProvider.o
lm4_Timer.o: family/arm/lm4/Timer.c makefile
	@-$(call RM, lm4_Timer.o)
	$(COMPILE) -o lm4_Timer.o
gates_GateHwi.o: gates/GateHwi.c makefile
	@-$(call RM, gates_GateHwi.o)
	$(COMPILE) -o gates_GateHwi.o
gates_GateMutex.o: gates/GateMutex.c makefile
	@-$(call RM, gates_GateMutex.o)
	$(COMPILE) -o gates_GateMutex.o
heaps_HeapMem.o: heaps/HeapMem.c makefile
	@-$(call RM, heaps_HeapMem.o)
	$(COMPILE) -o heaps_HeapMem.o

sysbios.am4fg: m3_Hwi_asm_gnu.o m3_Hwi_asm_switch_gnu.o m3_IntrinsicsSupport_asm_gnu.o m3_TaskSupport_asm_gnu.o _BIOS.o knl_Clock.o knl_Idle.o knl_Intrinsics.o knl_Queue.o knl_Semaphore.o knl_Swi.o knl_Swi_andn.o knl_Task.o hal_Hwi.o hal_Hwi_stack.o hal_Hwi_startup.o gnu_ReentSupport.o m3_Hwi.o m3_TaskSupport.o lm4_TimestampProvider.o lm4_Timer.o gates_GateHwi.o gates_GateMutex.o heaps_HeapMem.o
	@echo arm4fg $^ ...
	@-$(call RM, $@)
	@$(AR) $@ $^


clean:
	@-$(call RM, sysbios.am4fg)
	@-$(call RM, m3_Hwi_asm_gnu.o)
	@-$(call RM, m3_Hwi_asm_gnu.o.dep)
	@-$(call RM, m3_Hwi_asm_switch_gnu.o)
	@-$(call RM, m3_Hwi_asm_switch_gnu.o.dep)
	@-$(call RM, m3_IntrinsicsSupport_asm_gnu.o)
	@-$(call RM, m3_IntrinsicsSupport_asm_gnu.o.dep)
	@-$(call RM, m3_TaskSupport_asm_gnu.o)
	@-$(call RM, m3_TaskSupport_asm_gnu.o.dep)
	@-$(call RM, _BIOS.o)
	@-$(call RM, _BIOS.o.dep)
	@-$(call RM, knl_Clock.o)
	@-$(call RM, knl_Clock.o.dep)
	@-$(call RM, knl_Idle.o)
	@-$(call RM, knl_Idle.o.dep)
	@-$(call RM, knl_Intrinsics.o)
	@-$(call RM, knl_Intrinsics.o.dep)
	@-$(call RM, knl_Queue.o)
	@-$(call RM, knl_Queue.o.dep)
	@-$(call RM, knl_Semaphore.o)
	@-$(call RM, knl_Semaphore.o.dep)
	@-$(call RM, knl_Swi.o)
	@-$(call RM, knl_Swi.o.dep)
	@-$(call RM, knl_Swi_andn.o)
	@-$(call RM, knl_Swi_andn.o.dep)
	@-$(call RM, knl_Task.o)
	@-$(call RM, knl_Task.o.dep)
	@-$(call RM, hal_Hwi.o)
	@-$(call RM, hal_Hwi.o.dep)
	@-$(call RM, hal_Hwi_stack.o)
	@-$(call RM, hal_Hwi_stack.o.dep)
	@-$(call RM, hal_Hwi_startup.o)
	@-$(call RM, hal_Hwi_startup.o.dep)
	@-$(call RM, gnu_ReentSupport.o)
	@-$(call RM, gnu_ReentSupport.o.dep)
	@-$(call RM, m3_Hwi.o)
	@-$(call RM, m3_Hwi.o.dep)
	@-$(call RM, m3_TaskSupport.o)
	@-$(call RM, m3_TaskSupport.o.dep)
	@-$(call RM, lm4_TimestampProvider.o)
	@-$(call RM, lm4_TimestampProvider.o.dep)
	@-$(call RM, lm4_Timer.o)
	@-$(call RM, lm4_Timer.o.dep)
	@-$(call RM, gates_GateHwi.o)
	@-$(call RM, gates_GateHwi.o.dep)
	@-$(call RM, gates_GateMutex.o)
	@-$(call RM, gates_GateMutex.o.dep)
	@-$(call RM, heaps_HeapMem.o)
	@-$(call RM, heaps_HeapMem.o.dep)

