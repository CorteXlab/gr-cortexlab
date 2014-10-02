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


#ifndef INCLUDED_CORTEXLAB_IEEE802_15_4_PACKET_SINK_H
#define INCLUDED_CORTEXLAB_IEEE802_15_4_PACKET_SINK_H

#include <cortexlab/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace cortexlab {

    /*!
     * \brief <+description of block+>
     * \ingroup cortexlab
     *
     */
    class CORTEXLAB_API ieee802_15_4_packet_sink : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<ieee802_15_4_packet_sink> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of cortexlab::ieee802_15_4_packet_sink.
       *
       * To avoid accidental use of raw pointers, cortexlab::ieee802_15_4_packet_sink's
       * constructor is in a private implementation
       * class. cortexlab::ieee802_15_4_packet_sink::make is the public interface for
       * creating new instances.
       */
      static sptr make(unsigned int th=10);
    };

  } // namespace cortexlab
} // namespace gr

#endif /* INCLUDED_CORTEXLAB_IEEE802_15_4_PACKET_SINK_H */

