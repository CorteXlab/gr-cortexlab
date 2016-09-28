/* -*- c++ -*- */

#define CORTEXLAB_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "cortexlab_swig_doc.i"

%{
#include "cortexlab/ieee802_15_4_packet_sink.h"
#include "cortexlab/ieee802_15_4_splitter.h"
#include "cortexlab/ieee802_15_4_symbol_to_chip.h"
#include "cortexlab/resync_antennas.h"
#include "cortexlab/delay_msg.h"
%}


%include "cortexlab/ieee802_15_4_packet_sink.h"
GR_SWIG_BLOCK_MAGIC2(cortexlab, ieee802_15_4_packet_sink);
%include "cortexlab/ieee802_15_4_splitter.h"
GR_SWIG_BLOCK_MAGIC2(cortexlab, ieee802_15_4_splitter);
%include "cortexlab/ieee802_15_4_symbol_to_chip.h"
GR_SWIG_BLOCK_MAGIC2(cortexlab, ieee802_15_4_symbol_to_chip);
%include "cortexlab/resync_antennas.h"
GR_SWIG_BLOCK_MAGIC2(cortexlab, resync_antennas);
%include "cortexlab/delay_msg.h"
GR_SWIG_BLOCK_MAGIC2(cortexlab, delay_msg);

