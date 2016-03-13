
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from latency.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef latency_171631330_h
#define latency_171631330_h

#ifndef NDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef ndds_cpp_h
            #include "ndds/ndds_cpp.h"
        #endif
    #else
        #ifndef ndds_c_h
            #include "ndds/ndds_c.h"
        #endif
    #endif
#else
    #include "ndds_standalone_type.h"
#endif


#define latencyEcho_LAST_MEMBER_ID 1
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *latencyEchoTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct latencyEchoSeq;

#ifndef NDDS_STANDALONE_TYPE
    class latencyEchoTypeSupport;
    class latencyEchoDataWriter;
    class latencyEchoDataReader;
#endif

#endif

            
    typedef struct latencyEcho
{

    DDS_LongLong  time;

    char*  data; /* maximum length = (65536) */

            
} latencyEcho;                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* latencyEcho_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(latencyEchoSeq, latencyEcho);
        
NDDSUSERDllExport
RTIBool latencyEcho_initialize(
        latencyEcho* self);
        
NDDSUSERDllExport
RTIBool latencyEcho_initialize_ex(
        latencyEcho* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool latencyEcho_initialize_w_params(
        latencyEcho* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void latencyEcho_finalize(
        latencyEcho* self);
                        
NDDSUSERDllExport
void latencyEcho_finalize_ex(
        latencyEcho* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void latencyEcho_finalize_w_params(
        latencyEcho* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void latencyEcho_finalize_optional_members(
        latencyEcho* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool latencyEcho_copy(
        latencyEcho* dst,
        const latencyEcho* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif


#define latency_LAST_MEMBER_ID 1
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *latencyTYPENAME;
        

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    struct latencySeq;

#ifndef NDDS_STANDALONE_TYPE
    class latencyTypeSupport;
    class latencyDataWriter;
    class latencyDataReader;
#endif

#endif

            
    typedef struct latency
{

    DDS_LongLong  time;

    char*  data; /* maximum length = (65536) */

            
} latency;                        
    
                            
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, start exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport __declspec(dllexport)
#endif

    
NDDSUSERDllExport DDS_TypeCode* latency_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(latencySeq, latency);
        
NDDSUSERDllExport
RTIBool latency_initialize(
        latency* self);
        
NDDSUSERDllExport
RTIBool latency_initialize_ex(
        latency* self,
        RTIBool allocatePointers,RTIBool allocateMemory);
        
NDDSUSERDllExport
RTIBool latency_initialize_w_params(
        latency* self,
        const struct DDS_TypeAllocationParams_t * allocParams);

NDDSUSERDllExport
void latency_finalize(
        latency* self);
                        
NDDSUSERDllExport
void latency_finalize_ex(
        latency* self,RTIBool deletePointers);
       
NDDSUSERDllExport
void latency_finalize_w_params(
        latency* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);
        
NDDSUSERDllExport
void latency_finalize_optional_members(
        latency* self, RTIBool deletePointers);        
        
NDDSUSERDllExport
RTIBool latency_copy(
        latency* dst,
        const latency* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
  /* If the code is building on Windows, stop exporting symbols.
   */
  #undef NDDSUSERDllExport
  #define NDDSUSERDllExport
#endif



#endif /* latency_171631330_h */
