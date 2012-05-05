/* -*- c++ -*- */
/*
 * Copyright 2012 Dimitri Stolnikov <horiz0n@gmx.net>
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
#ifndef INCLUDED_OSMOSDR_SOURCE_C_H
#define INCLUDED_OSMOSDR_SOURCE_C_H

#include <osmosdr_api.h>
#include <osmosdr_ranges.h>
#include <gr_hier_block2.h>

class osmosdr_source_c;

/*
 * We use boost::shared_ptr's instead of raw pointers for all access
 * to gr_blocks (and many other data structures).  The shared_ptr gets
 * us transparent reference counting, which greatly simplifies storage
 * management issues.  This is especially helpful in our hybrid
 * C++ / Python system.
 *
 * See http://www.boost.org/libs/smart_ptr/smart_ptr.htm
 *
 * As a convention, the _sptr suffix indicates a boost::shared_ptr
 */
typedef boost::shared_ptr<osmosdr_source_c> osmosdr_source_c_sptr;

/*!
 * \brief Return a shared_ptr to a new instance of osmosdr_source_c.
 *
 * To avoid accidental use of raw pointers, osmosdr_source_c's
 * constructor is private.  osmosdr_make_source_c is the public
 * interface for creating new instances.
 */
OSMOSDR_API osmosdr_source_c_sptr osmosdr_make_source_c ( const std::string & args = "" );

/*!
 * \brief Provides a stream of complex samples.
 * \ingroup block
 *
 * This uses the preferred technique: subclassing gr_hier_block2.
 */
class OSMOSDR_API osmosdr_source_c : virtual public gr_hier_block2
{
public:
  /*!
   * Get the number of channels the underlying radio hardware offers.
   * \return the number of available channels
   */
  virtual size_t get_num_channels( void ) = 0;

  /*!
   * Get the possible sample rates for the underlying radio hardware.
   * \return a range of rates in Sps
   */
  virtual osmosdr::meta_range_t get_sample_rates( void ) = 0;

  /*!
   * Set the sample rate for the underlying radio hardware.
   * This also will select the appropriate IF bandpass, if applicable.
   * \param rate a new rate in Sps
   */
  virtual double set_sample_rate( double rate ) = 0;

  /*!
   * Get the sample rate for the underlying radio hardware.
   * This is the actual sample rate and may differ from the rate set.
   * \return the actual rate in Sps
   */
  virtual double get_sample_rate( void ) = 0;

  /*!
   * Get the tunable frequency range for the underlying radio hardware.
   * \param chan the channel index 0 to N-1
   * \return the frequency range in Hz
   */
  virtual osmosdr::freq_range_t get_freq_range( size_t chan = 0 ) = 0;

  /*!
   * Tune the underlying radio hardware to the desired center frequency.
   * This also will select the appropriate RF bandpass.
   * \param freq the desired frequency in Hz
   * \param chan the channel index 0 to N-1
   * \return the actual frequency in Hz
   */
  virtual double set_center_freq( double freq, size_t chan = 0 ) = 0;

  /*!
   * Get the center frequency the underlying radio hardware is tuned to.
   * This is the actual frequency and may differ from the frequency set.
   * \param chan the channel index 0 to N-1
   * \return the frequency in Hz
   */
  virtual double get_center_freq( size_t chan = 0 ) = 0;

  /*!
   * Set the frequency correction value in parts per million.
   * \param ppm the desired correction value in parts per million
   * \param chan the channel index 0 to N-1
   * \return correction value in parts per million
   */
  virtual double set_freq_corr( double ppm, size_t chan = 0 ) = 0;

  /*!
   * Get the frequency correction value.
   * \param chan the channel index 0 to N-1
   * \return correction value in parts per million
   */
  virtual double get_freq_corr( size_t chan = 0 ) = 0;

  /*!
   * Get the gain stage names of the underlying radio hardware.
   * \param chan the channel index 0 to N-1
   * \return a vector of strings containing the names of gain stages
   */
  virtual std::vector<std::string> get_gain_names( size_t chan = 0 ) = 0;

  /*!
   * Get the settable overall gain range for the underlying radio hardware.
   * \param chan the channel index 0 to N-1
   * \return the gain range in dB
   */
  virtual osmosdr::gain_range_t get_gain_range( size_t chan = 0 ) = 0;

  /*!
   * Get the settable gain range for a specific gain stage.
   * \param name the name of the gain stage
   * \param chan the channel index 0 to N-1
   * \return the gain range in dB
   */
  virtual osmosdr::gain_range_t get_gain_range( const std::string & name,
                                                size_t chan = 0 ) = 0;

  /*!
   * Set the gain mode for the underlying radio hardware.
   * This might be supported only for certain hardware types.
   * \param mode the gain mode (true means automatic gain mode)
   * \param chan the channel index 0 to N-1
   * \return the actual gain mode
   */
  virtual bool set_gain_mode( bool mode, size_t chan = 0 ) = 0;

  /*!
   * Get the gain mode selected for the underlying radio hardware.
   * \param chan the channel index 0 to N-1
   * \return the actual gain mode
   */
  virtual bool get_gain_mode( size_t chan = 0 ) = 0;

  /*!
   * Set the gain for the underlying radio hardware.
   * This function will automatically distribute the desired gain value over
   * available gain stages in an appropriate way and return the actual value.
   * \param gain the gain in dB
   * \param chan the channel index 0 to N-1
   * \return the actual gain in dB
   */
  virtual double set_gain( double gain, size_t chan = 0 ) = 0;

  /*!
   * Set the named gain on the underlying radio hardware.
   * \param gain the gain in dB
   * \param name the name of the gain stage
   * \param chan the channel index 0 to N-1
   * \return the actual gain in dB
   */
  virtual double set_gain( double gain,
                           const std::string & name,
                           size_t chan = 0 ) = 0;

  /*!
   * Get the actual gain setting of the underlying radio hardware.
   * \param chan the channel index 0 to N-1
   * \return the actual gain in dB
   */
  virtual double get_gain( size_t chan = 0 ) = 0;

  /*!
   * Get the actual gain setting of a named stage.
   * \param name the name of the gain stage
   * \param chan the channel index 0 to N-1
   * \return the actual gain in dB
   */
  virtual double get_gain( const std::string & name, size_t chan = 0 ) = 0;

  /*!
   * Get the available antennas of the underlying radio hardware.
   * \param chan the channel index 0 to N-1
   * \return a vector of strings containing the names of available antennas
   */
  virtual std::vector< std::string > get_antennas( size_t chan = 0 ) = 0;

  /*!
   * Select the active antenna of the underlying radio hardware.
   * \param antenna name of the antenna to be selected
   * \param chan the channel index 0 to N-1
   * \return the actual antenna's name
   */
  virtual std::string set_antenna( const std::string & antenna,
                                   size_t chan = 0 ) = 0;

  /*!
   * Get the actual underlying radio hardware antenna setting.
   * \param chan the channel index 0 to N-1
   * \return antenna the actual antenna's name
   */
  virtual std::string get_antenna( size_t chan = 0 ) = 0;
};

#endif /* INCLUDED_OSMOSDR_SOURCE_C_H */
