// Copyright 2007-2019 David Robillard <d@drobilla.net>
// SPDX-License-Identifier: ISC

#include "lilv_internal.h"

#include "lilv.h"
#include "lv2/core/lv2.h"
#include <ports/serd/serd.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LilvInstance* lilv_plugin_instantiate(
		const LilvPlugin*         plugin,
		double                    sample_rate,
		const LV2_Feature* const* features) {
	lilv_plugin_load_if_necessary(plugin);
	
	if (plugin->parse_errors) {
		return NULL;
	}
	
	LilvInstance*         result     = NULL;
	
	const LilvNode* const lib_uri    = lilv_plugin_get_library_uri(plugin);
	const LilvNode* const bundle_uri = lilv_plugin_get_bundle_uri(plugin);
	
	if (!lib_uri || !bundle_uri) {
		return NULL;
	}
	
	char* const bundle_path = lilv_file_uri_parse(lilv_node_as_uri(bundle_uri), NULL);
	    
	LilvLib* lib = lilv_lib_open(plugin->world, lib_uri, bundle_path, features);
	
	if (!lib) {
		serd_free(bundle_path);
		return NULL;
	}
	
	const LV2_Feature** local_features = NULL;
	
	if (features == NULL) {
		local_features    = (const LV2_Feature**)malloc(sizeof(LV2_Feature*));
		local_features[0] = NULL;
	}
	
	// Search for plugin by URI
	
	for (uint32_t i = 0; true; ++i) {
		const LV2_Descriptor* ld = lilv_lib_get_plugin(lib, i);
		
		if (!ld) {
			LILV_ERRORF("No plugin <%s> in <%s>\n",
						lilv_node_as_uri(lilv_plugin_get_uri(plugin)),
						lilv_node_as_uri(lib_uri));
			lilv_lib_close(lib);
			break; // return NULL
		}
		
		if (!strcmp(ld->URI, lilv_node_as_uri(lilv_plugin_get_uri(plugin)))) {
			// Create LilvInstance to return
			result                 = (LilvInstance*)malloc(sizeof(LilvInstance));
			result->lv2_descriptor = ld;
			result->lv2_handle     = ld->instantiate(ld, sample_rate, bundle_path, (features) ? features : local_features);
			//if (!result->lv2_handle) continue;
			result->pimpl = lib;
			break;
		}
	}
	
	free(local_features);
	
	serd_free(bundle_path);
	
	if (result) {
		if (result->lv2_handle == NULL) {
			// Failed to instantiate
			free(result);
			lilv_lib_close(lib);
			return NULL;
		}
		
		// "Connect" all ports to NULL (catches bugs)
		
		for (uint32_t i = 0; i < lilv_plugin_get_num_ports(plugin); ++i) {
			result->lv2_descriptor->connect_port(result->lv2_handle, i, NULL);
		}
	}
	
	return result;
}

void
lilv_instance_free(LilvInstance* instance) {
	if (!instance) {
		return;
	}
	
	instance->lv2_descriptor->cleanup(instance->lv2_handle);
	
	instance->lv2_descriptor = NULL;
	lilv_lib_close((LilvLib*)instance->pimpl);
	instance->pimpl = NULL;
	free(instance);
}
