/*This file was automatically generated. Don't modify.*/

#if !defined(BOARD_SAM3S_EK) && !defined(BOARD_SAM7X_EK) && !defined(BOARD_RCB) && !defined(BOARD_RAVEN) && !defined(BOARD_AVR32_EVK1105) && !defined(BOARD_XPLAIN) && !defined(BOARD_STK600) && !defined(BOARD_MESHBEAN) && !defined(BOARD_USB_DONGLE)
  #error unknown BOARD
#endif
#if !defined(STACK_TYPE_ALL) && !defined(STACK_TYPE_COORDINATOR) && !defined(STACK_TYPE_ROUTER) && !defined(STACK_TYPE_ENDDEVICE)
  #error unknown STACK_TYPE
#endif
#if !defined(NO_SECURITY_MODE) && !defined(STANDARD_SECURITY_MODE) && !defined(HIGH_SECURITY_MODE) && !defined(CERTICOM_SECURITY_MODE) && !defined(DUMMY_ECC_SECURITY_MODE)
  #error unknown SECURITY_MODE
#endif
#ifdef BOARD_SAM3S_EK
  #if !defined(AT86RF230) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212)
    #error unknown RFCHIP
  #endif
  #if !defined(AT91SAM3S4C)
    #error unknown HAL
  #endif
  #if !defined(HAL_4MHz) && !defined(HAL_8MHz) && !defined(HAL_16MHz) && !defined(HAL_64MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#ifdef BOARD_SAM7X_EK
  #if !defined(AT86RF230) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212)
    #error unknown RFCHIP
  #endif
  #if !defined(AT91SAM7X256)
    #error unknown HAL
  #endif
  #if !defined(HAL_18d432MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#ifdef BOARD_RCB
  #if !defined(ATMEGA128RFA1) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212) && !defined(AT86RF230)
    #error unknown RFCHIP
  #endif
  #if !defined(ATMEGA128RFA1) && !defined(ATMEGA1281)
    #error unknown HAL
  #endif
  #if !defined(HAL_4MHz) && !defined(HAL_8MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#ifdef BOARD_RAVEN
  #if !defined(AT86RF230B)
    #error unknown RFCHIP
  #endif
  #if !defined(ATMEGA1284)
    #error unknown HAL
  #endif
  #if !defined(HAL_4MHz) && !defined(HAL_8MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#ifdef BOARD_AVR32_EVK1105
  #if !defined(AT86RF230) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212)
    #error unknown RFCHIP
  #endif
  #if !defined(AT32UC3A0512)
    #error unknown HAL
  #endif
  #if !defined(HAL_48MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#ifdef BOARD_XPLAIN
  #if !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212)
    #error unknown RFCHIP
  #endif
  #if !defined(ATXMEGA128A1)
    #error unknown HAL
  #endif
  #if !defined(HAL_4MHz) && !defined(HAL_8MHz) && !defined(HAL_12MHz) && !defined(HAL_16MHz) && !defined(HAL_32MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#ifdef BOARD_STK600
  #if !defined(AT86RF230) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212)
    #error unknown RFCHIP
  #endif
  #if !defined(ATXMEGA256A3) && !defined(ATXMEGA128A1) && !defined(ATXMEGA256D3)
    #error unknown HAL
  #endif
  #if !defined(HAL_4MHz) && !defined(HAL_8MHz) && !defined(HAL_12MHz) && !defined(HAL_16MHz) && !defined(HAL_32MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#ifdef BOARD_MESHBEAN
  #if !defined(AT86RF230) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212)
    #error unknown RFCHIP
  #endif
  #if !defined(ATMEGA1281) && !defined(ATMEGA2561)
    #error unknown HAL
  #endif
  #if !defined(HAL_4MHz) && !defined(HAL_8MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#ifdef BOARD_USB_DONGLE
  #if !defined(AT86RF230B)
    #error unknown RFCHIP
  #endif
  #if !defined(AT90USB1287)
    #error unknown HAL
  #endif
  #if !defined(HAL_8MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_All_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_All_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_All_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_All_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_All_Sec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_All_Sec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_All_Sec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_All_Sec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_All_HighSec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_All_HighSec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_All_HighSec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_All_HighSec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_Sec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Sec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Sec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Sec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_HighSec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_Router_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_Router_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_Router_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_Router_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_Router_Sec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Sec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_Router_Sec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_Router_Sec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_Router_HighSec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_Router_HighSec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_Router_HighSec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_Router_HighSec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_Sec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Sec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Sec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Sec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_HighSec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM3S4C) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_At91sam3s4c_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_All_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_All_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_All_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_All_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_All_Sec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_All_Sec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_All_Sec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_All_Sec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_All_HighSec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_All_HighSec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_All_HighSec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_All_HighSec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_Sec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Sec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Sec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Sec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_HighSec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_HighSec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_HighSec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_HighSec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_Router_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_Router_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_Router_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_Router_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_Router_Sec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Sec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_Router_Sec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_Router_Sec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_Router_HighSec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_Router_HighSec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_Router_HighSec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_Router_HighSec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_Sec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Sec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Sec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Sec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_HighSec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_HighSec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_HighSec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_HighSec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT91SAM7X256) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_All_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_All_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_All_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_All_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_All_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_All_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_All_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_All_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_All_Sec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_All_Sec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_All_Sec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_All_Sec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_All_Sec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_All_Sec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_All_Sec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_All_Sec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_All_HighSec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_All_HighSec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_All_HighSec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_All_HighSec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_All_HighSec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_All_HighSec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_All_HighSec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_All_HighSec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_All_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_All_SESec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_All_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_All_SESec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Coordinator_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Coordinator_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Coordinator_Sec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Sec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Sec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Sec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Coordinator_Sec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Sec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Sec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Sec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Coordinator_HighSec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_HighSec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_HighSec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_HighSec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Coordinator_HighSec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_HighSec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_HighSec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_HighSec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Coordinator_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Coordinator_SESec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Coordinator_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Coordinator_SESec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Router_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_Router_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_Router_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Router_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_Router_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_Router_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Router_Sec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Sec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_Router_Sec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_Router_Sec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Router_Sec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Sec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_Router_Sec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_Router_Sec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Router_HighSec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_Router_HighSec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_Router_HighSec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_Router_HighSec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Router_HighSec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_Router_HighSec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_Router_HighSec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_Router_HighSec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Router_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Router_SESec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Router_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_Router_SESec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_EndDevice_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_EndDevice_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_EndDevice_Sec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Sec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Sec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Sec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_EndDevice_Sec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Sec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Sec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Sec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_EndDevice_HighSec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_HighSec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_HighSec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_HighSec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_EndDevice_HighSec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_HighSec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_HighSec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_HighSec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_EndDevice_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_EndDevice_SESec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_EndDevice_SESec_Atmega128rfa1_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_Atmega128rfa1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_Atmega128rfa1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA128RFA1) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_Atmega128rfa1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(ATMEGA128RFA1)
  #include <MakerulesBc_EndDevice_SESec_Atmega1281_Atmega128rfa1_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_All_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_All_Sec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_All_HighSec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Sec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_HighSec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Sec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_Router_HighSec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Sec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_HighSec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1284) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_Atmega1284_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_All_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_All_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_All_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_All_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_All_Sec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_All_Sec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_All_Sec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_All_Sec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_All_HighSec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_All_HighSec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_All_HighSec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_All_HighSec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_Sec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Sec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Sec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Sec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_HighSec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_Router_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_Router_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_Router_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_Router_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_Router_Sec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Sec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_Router_Sec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_Router_Sec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_Router_HighSec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_Router_HighSec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_Router_HighSec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_Router_HighSec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_Sec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Sec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Sec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Sec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_HighSec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT32UC3A0512) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_At32uc3a0512_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_All_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_All_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_All_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_All_Sec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_All_Sec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_All_Sec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_All_HighSec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_All_HighSec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_All_HighSec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Sec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Sec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Sec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_Router_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_Router_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Sec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_Router_Sec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_Router_Sec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_Router_HighSec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_Router_HighSec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_Router_HighSec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Sec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Sec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Sec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_All_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_All_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_All_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_All_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_All_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_All_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_All_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_All_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_All_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_All_Sec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_All_Sec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_All_Sec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_All_Sec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_All_Sec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_All_Sec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_All_Sec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_All_Sec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_All_Sec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_All_HighSec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_All_HighSec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_All_HighSec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_All_HighSec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_All_HighSec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_All_HighSec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_All_HighSec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_All_HighSec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_All_HighSec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_Sec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Sec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Sec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Sec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_Sec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_Sec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Sec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Sec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Sec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_HighSec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_HighSec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_HighSec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_Router_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_Router_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_Router_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_Router_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_Router_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_Router_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_Router_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_Router_Sec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Sec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_Router_Sec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_Router_Sec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_Router_Sec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_Router_Sec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Sec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_Router_Sec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_Router_Sec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_Router_HighSec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_Router_HighSec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_Router_HighSec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_Router_HighSec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_Router_HighSec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_Router_HighSec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_Router_HighSec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_Router_HighSec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_Router_HighSec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_Sec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Sec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Sec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Sec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_Sec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_Sec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Sec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Sec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Sec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_HighSec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_HighSec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_HighSec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256A3) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256a3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA128A1) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_Atxmega128a1_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATXMEGA256D3) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_Atxmega256d3_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_All_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_All_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_All_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_All_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_All_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_All_Sec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_All_Sec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_All_Sec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_All_Sec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_All_Sec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_All_HighSec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_All_HighSec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_All_HighSec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_All_HighSec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_All_HighSec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_All_SESec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_All_SESec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_All_SESec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_Sec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_Sec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Sec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_Sec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_Sec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_HighSec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_HighSec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_HighSec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_HighSec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_HighSec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_Coordinator_SESec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_Router_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_Router_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_Router_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_Router_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_Router_Sec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_Router_Sec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Sec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_Router_Sec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_Router_Sec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_Router_HighSec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_Router_HighSec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_Router_HighSec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_Router_HighSec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_Router_HighSec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_Router_SESec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_Router_SESec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_Router_SESec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_Sec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_Sec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Sec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_Sec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_Sec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_HighSec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_HighSec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_HighSec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_HighSec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_HighSec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA1281) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_Atmega1281_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230)
  #include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF231)
  #include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(ATMEGA2561) && defined(AT86RF212)
  #include <MakerulesBc_EndDevice_SESec_Atmega2561_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(NO_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_All_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(STANDARD_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_All_Sec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(HIGH_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_All_HighSec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(CERTICOM_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_All_SESec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(NO_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(STANDARD_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_Sec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(HIGH_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_HighSec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(CERTICOM_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_Coordinator_SESec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(NO_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_Router_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(STANDARD_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_Router_Sec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(HIGH_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_Router_HighSec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(CERTICOM_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_Router_SESec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(NO_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(STANDARD_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_Sec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(HIGH_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_HighSec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(CERTICOM_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(DUMMY_ECC_SECURITY_MODE) && defined(AT90USB1287) && defined(AT86RF230B)
  #include <MakerulesBc_EndDevice_SESec_At90usb1287_Rf230B_Iar.h>
#endif
