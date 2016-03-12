
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from latency.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/


#ifndef NDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef ndds_cpp_h
            #include "ndds/ndds_cpp.h"
        #endif
        #ifndef dds_c_log_impl_h              
            #include "dds_c/dds_c_log_impl.h"                                
        #endif        
    #else
        #ifndef ndds_c_h
            #include "ndds/ndds_c.h"
        #endif
    #endif
    
    #ifndef cdr_type_h
        #include "cdr/cdr_type.h"
    #endif    

    #ifndef osapi_heap_h
        #include "osapi/osapi_heap.h" 
    #endif
#else
    #include "ndds_standalone_type.h"
#endif



#include "latency.h"

/* ========================================================================= */
const char *latencyEchoTYPENAME = "latencyEcho";

DDS_TypeCode* latencyEcho_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode latencyEcho_g_tc_data_string = DDS_INITIALIZE_STRING_TYPECODE(32);

    static DDS_TypeCode_Member latencyEcho_g_tc_members[2]=
    {
        {
            (char *)"time",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"data",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode latencyEcho_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"latencyEcho", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        2, /* Number of members */
        latencyEcho_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for latencyEcho*/

    if (is_initialized) {
        return &latencyEcho_g_tc;
    }


    latencyEcho_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    latencyEcho_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&latencyEcho_g_tc_data_string;

    is_initialized = RTI_TRUE;

    return &latencyEcho_g_tc;
}


RTIBool latencyEcho_initialize(
    latencyEcho* sample) {
  return latencyEcho_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}
        
RTIBool latencyEcho_initialize_ex(
    latencyEcho* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{
    struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;
        
    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;
    
    return latencyEcho_initialize_w_params(
        sample,&allocParams);
}

RTIBool latencyEcho_initialize_w_params(
        latencyEcho* sample,
        const struct DDS_TypeAllocationParams_t * allocParams)
{
        
    
    if (allocParams) {} /* To avoid warnings */
        

    if (!RTICdrType_initLong(&sample->time)) {
        return RTI_FALSE;
    }                
            

    if (allocParams->allocate_memory) {
        sample->data = DDS_String_alloc((32));
        if (sample->data == NULL) {
            return RTI_FALSE;
        }
    } else {
        if (sample->data != NULL) { 
            sample->data[0] = '\0';
        }
    }
            


    return RTI_TRUE;
}

void latencyEcho_finalize(
    latencyEcho* sample)
{
    latencyEcho_finalize_ex(sample,RTI_TRUE);
}
        
void latencyEcho_finalize_ex(
    latencyEcho* sample,RTIBool deletePointers)
{        
    struct DDS_TypeDeallocationParams_t deallocParams =
            DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample) { } /* To avoid warnings */
    
    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    latencyEcho_finalize_w_params(
        sample,&deallocParams);
}

void latencyEcho_finalize_w_params(
        latencyEcho* sample,
        const struct DDS_TypeDeallocationParams_t * deallocParams)
{    
    if (sample) { } /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */



    if (sample->data != NULL) {    
        DDS_String_free(sample->data);
        sample->data = NULL;
    }
            

}

void latencyEcho_finalize_optional_members(
    latencyEcho* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;
    if (sample) { } /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */

        

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;    
             



}

RTIBool latencyEcho_copy(
    latencyEcho* dst,
    const latencyEcho* src)
{

    if (!RTICdrType_copyLong(
        &dst->time, &src->time)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyString(
        dst->data, src->data, (32) + 1)) {
        return RTI_FALSE;
    }
            


    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'latencyEcho' sequence class.
 */
#define T latencyEcho
#define TSeq latencyEchoSeq
#define T_initialize_w_params latencyEcho_initialize_w_params
#define T_finalize_w_params   latencyEcho_finalize_w_params
#define T_copy       latencyEcho_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#endif
#else
#include "dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp_sequence_TSeq.gen"
#endif
#endif

#undef T_copy
#undef T_finalize_w_params
#undef T_initialize_w_params
#undef TSeq
#undef T

/* ========================================================================= */
const char *latencyTYPENAME = "latency";

DDS_TypeCode* latency_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode latency_g_tc_data_string = DDS_INITIALIZE_STRING_TYPECODE(32);

    static DDS_TypeCode_Member latency_g_tc_members[2]=
    {
        {
            (char *)"time",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        },
        {
            (char *)"data",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Member flags */
            DDS_PRIVATE_MEMBER,/* Ignored */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode latency_g_tc =
    {{
        DDS_TK_STRUCT,/* Kind */
        DDS_BOOLEAN_FALSE, /* Ignored */
        -1,/* Ignored */
        (char *)"latency", /* Name */
        NULL, /* Ignored */
        0, /* Ignored */
        0, /* Ignored */
        NULL, /* Ignored */
        2, /* Number of members */
        latency_g_tc_members, /* Members */
        DDS_VM_NONE /* Ignored */
    }}; /* Type code for latency*/

    if (is_initialized) {
        return &latency_g_tc;
    }


    latency_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    latency_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&latency_g_tc_data_string;

    is_initialized = RTI_TRUE;

    return &latency_g_tc;
}


RTIBool latency_initialize(
    latency* sample) {
  return latency_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}
        
RTIBool latency_initialize_ex(
    latency* sample,RTIBool allocatePointers,RTIBool allocateMemory)
{
    struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;
        
    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;
    
    return latency_initialize_w_params(
        sample,&allocParams);
}

RTIBool latency_initialize_w_params(
        latency* sample,
        const struct DDS_TypeAllocationParams_t * allocParams)
{
        
    
    if (allocParams) {} /* To avoid warnings */
        

    if (!RTICdrType_initLong(&sample->time)) {
        return RTI_FALSE;
    }                
            

    if (allocParams->allocate_memory) {
        sample->data = DDS_String_alloc((32));
        if (sample->data == NULL) {
            return RTI_FALSE;
        }
    } else {
        if (sample->data != NULL) { 
            sample->data[0] = '\0';
        }
    }
            


    return RTI_TRUE;
}

void latency_finalize(
    latency* sample)
{
    latency_finalize_ex(sample,RTI_TRUE);
}
        
void latency_finalize_ex(
    latency* sample,RTIBool deletePointers)
{        
    struct DDS_TypeDeallocationParams_t deallocParams =
            DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample) { } /* To avoid warnings */
    
    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    latency_finalize_w_params(
        sample,&deallocParams);
}

void latency_finalize_w_params(
        latency* sample,
        const struct DDS_TypeDeallocationParams_t * deallocParams)
{    
    if (sample) { } /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */



    if (sample->data != NULL) {    
        DDS_String_free(sample->data);
        sample->data = NULL;
    }
            

}

void latency_finalize_optional_members(
    latency* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;
    if (sample) { } /* To avoid warnings */
    if (deallocParams) {} /* To avoid warnings */

        

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;    
             



}

RTIBool latency_copy(
    latency* dst,
    const latency* src)
{

    if (!RTICdrType_copyLong(
        &dst->time, &src->time)) {
        return RTI_FALSE;
    }
            

    if (!RTICdrType_copyString(
        dst->data, src->data, (32) + 1)) {
        return RTI_FALSE;
    }
            


    return RTI_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 * Configure and implement 'latency' sequence class.
 */
#define T latency
#define TSeq latencySeq
#define T_initialize_w_params latency_initialize_w_params
#define T_finalize_w_params   latency_finalize_w_params
#define T_copy       latency_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#endif
#else
#include "dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp_sequence_TSeq.gen"
#endif
#endif

#undef T_copy
#undef T_finalize_w_params
#undef T_initialize_w_params
#undef TSeq
#undef T

