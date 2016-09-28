/* -*- c++ -*- */
/*
 * Copyright 2007,2012-2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_CORTEXLAB_DELAY_MSG_IMPL_H
#define INCLUDED_CORTEXLAB_DELAY_MSG_IMPL_H

#include <cortexlab/delay_msg.h>
#include <gnuradio/thread/thread.h>
#include <pmt/pmt.h>

namespace gr {
  namespace cortexlab {

    class delay_msg_impl : public delay_msg
    {
    private:
      void forecast(int noutput_items,
                    gr_vector_int &ninput_items_required);

      void handle_dly(pmt::pmt_t dly);

      size_t d_itemsize;
      int d_delta;
      gr::thread::mutex d_mutex_delay;

    public:
      delay_msg_impl(size_t itemsize, int delay);
      ~delay_msg_impl();

      int dly() const { return history()-1; }
      void set_dly(int d);

      int general_work(int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items);
    };

  } /* namespace blocks */
} /* namespace gr */

#endif /* INCLUDED_CORTEXLAB_DELAY_MSG_IMPL_H */
