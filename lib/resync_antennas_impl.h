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

#ifndef INCLUDED_CORTEXLAB_RESYNC_ANTENNAS_IMPL_H
#define INCLUDED_CORTEXLAB_RESYNC_ANTENNAS_IMPL_H

#include <cortexlab/resync_antennas.h>

namespace gr {
  namespace cortexlab {

    class resync_antennas_impl : public resync_antennas
    {
     private:
      int num_samples;
      int spread_factor;
      int waiting_samples;
      int remaining_samples;
      int delay;
      // Nothing to declare in this block.

      int argmax(std::vector<float> & c);

     public:
      int get_delay();
      resync_antennas_impl(int num_samples, int spread_factor, int waiting_samples);
      ~resync_antennas_impl();

      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace cortexlab
} // namespace gr

#endif /* INCLUDED_CORTEXLAB_RESYNC_ANTENNAS_IMPL_H */

