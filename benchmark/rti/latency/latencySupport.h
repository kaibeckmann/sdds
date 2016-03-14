
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from latency.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef latencySupport_171631330_h
#define latencySupport_171631330_h

/* Uses */
#include "latency.h"



#ifdef __cplusplus
#ifndef ndds_cpp_h
  #include "ndds/ndds_cpp.h"
#endif
#else
#ifndef ndds_c_h
  #include "ndds/ndds_c.h"
#endif
#endif

        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
  */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(latencyEchoTypeSupport, latencyEcho);

DDS_DATAWRITER_CPP(latencyEchoDataWriter, latencyEcho);
DDS_DATAREADER_CPP(latencyEchoDataReader, latencyEchoSeq, latencyEcho);


#else

DDS_TYPESUPPORT_C(latencyEchoTypeSupport, latencyEcho);
DDS_DATAWRITER_C(latencyEchoDataWriter, latencyEcho);
DDS_DATAREADER_C(latencyEchoDataReader, latencyEchoSeq, latencyEcho);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif

        

/* ========================================================================= */
/**
   Uses:     T

   Defines:  TTypeSupport, TDataWriter, TDataReader

   Organized using the well-documented "Generics Pattern" for
   implementing generics in C and C++.
*/

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
  */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(latencyTypeSupport, latency);

DDS_DATAWRITER_CPP(latencyDataWriter, latency);
DDS_DATAREADER_CPP(latencyDataReader, latencySeq, latency);


#else

DDS_TYPESUPPORT_C(latencyTypeSupport, latency);
DDS_DATAWRITER_C(latencyDataWriter, latency);
DDS_DATAREADER_C(latencyDataReader, latencySeq, latency);

#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif  /* latencySupport_171631330_h */
