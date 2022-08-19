
EXECUTE_PROCESS(COMMAND uname -r COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
message(STATUS "Architecture: ${ARCHITECTURE}")

include_directories(/lib/modules/${ARCHITECTURE}/build/include)
add_executable(usb_monitor_drv usb_monitor_drv.c)