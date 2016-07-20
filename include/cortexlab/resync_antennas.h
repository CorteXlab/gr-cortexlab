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


#ifndef INCLUDED_CORTEXLAB_RESYNC_ANTENNAS_H
#define INCLUDED_CORTEXLAB_RESYNC_ANTENNAS_H

#include <cortexlab/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace cortexlab {

    /*!
     * \brief <+description of block+>
     * \ingroup cortexlab
     *
     */
    class CORTEXLAB_API resync_antennas : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<resync_antennas> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of cortexlab::resync_antennas.
       *
       * To avoid accidental use of raw pointers, cortexlab::resync_antennas's
       * constructor is in a private implementation
       * class. cortexlab::resync_antennas::make is the public interface for
       * creating new instances.
       */
      static sptr make(int num_samples = 32, int spread_factor = 2, int waiting_samples = 10000);
    };

  } // namespace cortexlab
} // namespace gr

#endif /* INCLUDED_CORTEXLAB_RESYNC_ANTENNAS_H */

