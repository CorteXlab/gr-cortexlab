/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
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
#include "resync_antennas_impl.h"
#include <algorithm>

namespace gr {
  namespace cortexlab {

    resync_antennas::sptr
    resync_antennas::make(int num_samples, int spread_factor, int waiting_samples)
    {
      return gnuradio::get_initial_sptr
        (new resync_antennas_impl(num_samples, spread_factor, waiting_samples));
    }

    /*
     * The private constructor
     */
    resync_antennas_impl::resync_antennas_impl(int i_num_samples, int i_spread_factor, int i_waiting_samples)
      : gr::block("resync_antennas",
              gr::io_signature::make(2, 2, sizeof(float)),
              gr::io_signature::make(0, 0, 0)),
      num_samples(i_num_samples), 
      spread_factor(i_spread_factor), 
      waiting_samples(i_waiting_samples),
      remaining_samples(i_waiting_samples),
      delay(5)
    {
    	message_port_register_out(pmt::mp("delay") );
    	message_port_pub(pmt::mp("delay"), pmt::mp(5));
    }

    /*
     * Our virtual destructor.
     */
    resync_antennas_impl::~resync_antennas_impl()
    {
    }

    int
    resync_antennas_impl::get_delay()
    {
    	return delay;
    }

    void
    resync_antennas_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
    	//std::cout << noutput_items << std::endl;

    	if (remaining_samples > 8192)
    	{
    		ninput_items_required[0] = 8192;
    		ninput_items_required[1] = 8192;
    	}
    	else
    	{
    		ninput_items_required[0] = remaining_samples + num_samples;
    		ninput_items_required[0] = remaining_samples + num_samples* (spread_factor + 1)/2;
    	}	
    }

	int 
	resync_antennas_impl::argmax(std::vector<float> & c)
	{
		if (c.begin() == c.end())
		{
			return -1;
		}
		else
		{
			int idx = 0;
			int res = 0;
			float tmp = *c.begin();
			for(std::vector<float>::iterator it = c.begin(); it != c.end(); ++it) {
				//std::cout << *it << std::endl;
				//std::cout << tmp << std::endl;
			    if (*it > tmp)
			    {
			    	res = idx;
			    	tmp = *it;
			    }
			    idx++;
			}
			return res;
		}
	}

    int
    resync_antennas_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
    	int ninput_items_0 = (int )ninput_items[0];
    	int ninput_items_1 = (int )ninput_items[1];

    	int mini = std::min(std::min(ninput_items_0, ninput_items_1), remaining_samples);
    	if (mini == ninput_items_0 or mini == ninput_items_1)
    	{
    		consume_each(mini);
    		remaining_samples -= mini;
    		return 0;
    	}
    	else
    	{
    		remaining_samples = waiting_samples;
    		consume_each(waiting_samples);
    		if ((ninput_items_0 < mini + num_samples) or (ninput_items_1 < mini + num_samples * (spread_factor + 1)/2))
    		{
    			return 0;
    		}
    		const float* input_items_0 = (const float*) input_items[0];
    		const float* input_items_1 = (const float*) input_items[1];

    		std::vector<float> results;
    		float sum = 0;
    		for (int i = mini - num_samples * (spread_factor - 1)/2 - 1; i < mini - 1 + num_samples * (spread_factor - 1)/2; i++)
    		{
    			sum = 0;
    			for (int j = 0; j < num_samples; j++)
    			{
    				sum += input_items_0[mini + j - 1] * input_items_1[i + j];
    			}
    			results.push_back(sum);
    			//std::cout << sum << std::endl;
    		}

    		std::cout << "indice : " << argmax(results) << std::endl;

    		delay = argmax(results) - num_samples * (spread_factor -1)/2;

    		message_port_pub(pmt::mp("delay"), pmt::mp(delay));

    		return 0;


    	}



		// idx = 0
		// res = np.zeros(self.num_samples*(self.search_factor - 1) +1)


		// for i in range(a - self.num_samples* (self.search_factor - 1)/2 -1, a -1 + self.num_samples*(self.search_factor - 1)/2	):
		// 	sum = 0
		// 	for j in range(self.num_samples):
		// 		sum = sum + in0[a + j - 1] * in1[i + j]
		// 	res[idx] = sum
		// 	idx += 1

		// self.delay = int(np.argmax(res) - self.num_samples* (self.search_factor - 1)/2.)
		// return 0

  //     const float *in = (const float *) input_items[0];
		// message_port_pub(pmt::mp("delay"), pmt::mp(5));
		// consume_each((int )ninput_items[0]);
		// std::cout << (int )ninput_items[0] << std::endl;
      // Do <+signal processing+>

      // Tell runtime system how many output items we produced.
      return 0;
    }

  } /* namespace cortexlab */
} /* namespace gr */

