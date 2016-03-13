
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from latency.idl using "rtiddsgen".
  The rtiddsgen tool is part of the RTI Connext distribution.
  For more information, type 'rtiddsgen -help' at a command shell
  or consult the RTI Connext manual.
*/

#ifndef latencyPlugin_171631328_h
#define latencyPlugin_171631328_h

#include "latency.h"



struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif


#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif


#ifdef __cplusplus
extern "C" {
#endif


#define latencyEchoPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample  
#define latencyEchoPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define latencyEchoPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define latencyEchoPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define latencyEchoPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern latencyEcho*
latencyEchoPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern latencyEcho*
latencyEchoPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern latencyEcho*
latencyEchoPluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
latencyEchoPluginSupport_copy_data(
    latencyEcho *out,
    const latencyEcho *in);

NDDSUSERDllExport extern void 
latencyEchoPluginSupport_destroy_data_w_params(
    latencyEcho *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
latencyEchoPluginSupport_destroy_data_ex(
    latencyEcho *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
latencyEchoPluginSupport_destroy_data(
    latencyEcho *sample);

NDDSUSERDllExport extern void 
latencyEchoPluginSupport_print_data(
    const latencyEcho *sample,
    const char *desc,
    unsigned int indent);


/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
latencyEchoPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
latencyEchoPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
latencyEchoPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
latencyEchoPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);
    
NDDSUSERDllExport extern void    
latencyEchoPlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    latencyEcho *sample,
    void *handle);    
 

NDDSUSERDllExport extern RTIBool 
latencyEchoPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    latencyEcho *out,
    const latencyEcho *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
latencyEchoPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const latencyEcho *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
latencyEchoPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    latencyEcho *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
latencyEchoPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    latencyEcho **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);




NDDSUSERDllExport extern RTIBool
latencyEchoPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
latencyEchoPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
latencyEchoPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
latencyEchoPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const latencyEcho * sample);



/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
latencyEchoPlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
latencyEchoPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
latencyEchoPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const latencyEcho *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
latencyEchoPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    latencyEcho * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
latencyEchoPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    latencyEcho ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
latencyEchoPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    latencyEcho *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
latencyEchoPlugin_new(void);

NDDSUSERDllExport extern void
latencyEchoPlugin_delete(struct PRESTypePlugin *);


#define latencyPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample  
#define latencyPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define latencyPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define latencyPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define latencyPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
    Support functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern latency*
latencyPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern latency*
latencyPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern latency*
latencyPluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
latencyPluginSupport_copy_data(
    latency *out,
    const latency *in);

NDDSUSERDllExport extern void 
latencyPluginSupport_destroy_data_w_params(
    latency *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
latencyPluginSupport_destroy_data_ex(
    latency *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
latencyPluginSupport_destroy_data(
    latency *sample);

NDDSUSERDllExport extern void 
latencyPluginSupport_print_data(
    const latency *sample,
    const char *desc,
    unsigned int indent);


/* ----------------------------------------------------------------------------
    Callback functions:
 * ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
latencyPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
latencyPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
NDDSUSERDllExport extern PRESTypePluginEndpointData 
latencyPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
latencyPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);
    
NDDSUSERDllExport extern void    
latencyPlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    latency *sample,
    void *handle);    
 

NDDSUSERDllExport extern RTIBool 
latencyPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    latency *out,
    const latency *in);

/* --------------------------------------------------------------------------------------
    (De)Serialize functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool 
latencyPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const latency *sample,
    struct RTICdrStream *stream, 
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
latencyPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    latency *sample, 
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
latencyPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    latency **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);




NDDSUSERDllExport extern RTIBool
latencyPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct RTICdrStream *stream, 
    RTIBool skip_encapsulation,  
    RTIBool skip_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern unsigned int 
latencyPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
latencyPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int
latencyPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const latency * sample);



/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginKeyKind 
latencyPlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
latencyPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
latencyPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const latency *sample,
    struct RTICdrStream *stream,
    RTIBool serialize_encapsulation,
    RTIEncapsulationId encapsulation_id,
    RTIBool serialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool 
latencyPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    latency * sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

 
NDDSUSERDllExport extern RTIBool 
latencyPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    latency ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);


NDDSUSERDllExport extern RTIBool
latencyPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    latency *sample,
    struct RTICdrStream *stream, 
    RTIBool deserialize_encapsulation,  
    RTIBool deserialize_key, 
    void *endpoint_plugin_qos);

     
/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
latencyPlugin_new(void);

NDDSUSERDllExport extern void
latencyPlugin_delete(struct PRESTypePlugin *);

#ifdef __cplusplus
}
#endif

        
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif        

#endif /* latencyPlugin_171631328_h */
