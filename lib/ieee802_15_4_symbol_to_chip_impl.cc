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
#include "ieee802_15_4_symbol_to_chip_impl.h"

static const unsigned int PNS_TAB[16] = {3653456430,
					 3986437410,
					  786023250,
					  585997365,
					 1378802115,
					  891481500,
					 3276943065,
					 2620728045,
					 2358642555,
					 3100205175,
					 2072811015,
					 2008598880,
					  125537430,
					 1618458825,
					 2517072780,
					 3378542520};


namespace gr {
  namespace cortexlab {

    ieee802_15_4_symbol_to_chip::sptr
    ieee802_15_4_symbol_to_chip::make()
    {
      return gnuradio::get_initial_sptr
        (new ieee802_15_4_symbol_to_chip_impl());
    }

    /*
     * The private constructor
     */
    ieee802_15_4_symbol_to_chip_impl::ieee802_15_4_symbol_to_chip_impl()
      : gr::sync_interpolator("ieee802_15_4_symbol_to_chip",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
	      gr::io_signature::make(2, 2, sizeof(float)),16)
    {
	set_history(1);
    }

    /*
     * Our virtual destructor.
     */
    ieee802_15_4_symbol_to_chip_impl::~ieee802_15_4_symbol_to_chip_impl()
    {
    }

    int
    ieee802_15_4_symbol_to_chip_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const unsigned char *in = (const unsigned char *) input_items[0];
        float *outi = (float *) output_items[0];
        float *outq = (float *) output_items[1];
	//gr_complex *out = (gr_complex *) output_items[0];
	
	unsigned int bits[32];

        for(int i=0;i<noutput_items/interpolation();i++)
	{
	   for(int k=31; k>=0; k--)
	       bits[k] = (PNS_TAB[(int) in[i]] & (1<<k))>>k;

	   for(int j=15;j>=0;j--){
	       outi[i*16+15-j] = (float) 2.0*bits[2*j+1]-1.0;
	       outq[i*16+15-j] = (float) 2.0*bits[2*j]-1.0;
	   }	
	}

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace cortexlab */
} /* namespace gr */

