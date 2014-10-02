/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ieee802_15_4_splitter_impl.h"

namespace gr {
  namespace cortexlab {

    ieee802_15_4_splitter::sptr
    ieee802_15_4_splitter::make()
    {
      return gnuradio::get_initial_sptr
        (new ieee802_15_4_splitter_impl());
    }

    /*
     * The private constructor
     */
    ieee802_15_4_splitter_impl::ieee802_15_4_splitter_impl()
      : gr::sync_interpolator("ieee802_15_4_splitter",
              gr::io_signature::make(1,1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)),2)
    {}

    /*
     * Our virtual destructor.
     */
    ieee802_15_4_splitter_impl::~ieee802_15_4_splitter_impl()
    {
    }

    int
    ieee802_15_4_splitter_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const unsigned char *in = (const unsigned char *) input_items[0];
        unsigned char *out = (unsigned char *) output_items[0];

	for(int i=0;i<noutput_items;i+=2)
	{
	    out[i] = (unsigned char)(in[i/2]&0x0F);
	    out[i+1] = (unsigned char)((in[i/2]>>4)&0x0F);	
	}

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace cortexlab */
} /* namespace gr */

