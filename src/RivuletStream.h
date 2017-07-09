#ifndef RIVULET_STREAM_H
#define RIVULET_STREAM_H

#include "RivuletListener.h"
#include "RivuletProducer.h"
#include "RivuletArray.h"
#include "Boolean.h"
#include "RivuletProducerFromArray.h"

typedef int (*rivulet_stream_map_function) (int value);
typedef Boolean (*rivulet_stream_filter_function) (int value);

typedef struct RivuletStream {
  RivuletListenerType listener_type;
  RivuletProducerType producer_type;
  RivuletProducer *_producer;
  RivuletArray *_internal_listeners;
  int _stop_id;
  void (*rivulet_stream_add_listener) (struct RivuletStream *, RivuletListener *);
  void (*_rivulet_stream_remove_listener) (struct RivuletStream *, RivuletListener *);
  struct RivuletStream *(*rivulet_stream_map) (struct RivuletStream *, rivulet_stream_map_function);
  struct RivuletStream *(*rivulet_stream_map_to) (struct RivuletStream *, int);
  struct RivuletStream *(*rivulet_stream_filter) (struct RivuletStream *, rivulet_stream_filter_function);
  struct RivuletStream *(*rivulet_stream_take) (struct RivuletStream *, int);
  struct RivuletStream *(*rivulet_stream_drop) (struct RivuletStream *, int);
  struct RivuletStream *(*rivulet_stream_last) (struct RivuletStream *);
  struct RivuletStream *(*rivulet_stream_sample) (struct RivuletStream *, struct RivuletStream *);
  struct RivuletStream *(*rivulet_stream_delay) (struct RivuletStream *, int);
} RivuletStream;

RivuletStream *rivulet_stream_create (RivuletProducer *producer);
RivuletStream *rivulet_stream_never ();
RivuletStream *rivulet_stream_empty ();
RivuletStream *rivulet_stream_from_variable_length_array (RivuletArray *array);
RivuletStream *rivulet_stream_from_array (int *array, int size);
RivuletStream *rivulet_stream_periodic (int period);
RivuletStream *rivulet_stream_merge (int count, ...);

#endif // RIVULET_STREAM_H
