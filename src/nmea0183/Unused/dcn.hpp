/***************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  NMEA0183 Support Classes
 * Author:   Samuel R. Blackburn, David S. Register
 *
 ***************************************************************************
 *   Copyright (C) 2010 by Samuel R. Blackburn, David S Register           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *
 *   S Blackburn's original source license:                                *
 *         "You can use it any way you like."                              *
 *   More recent (2010) license statement:                                 *
 *         "It is BSD license, do with it what you will"                   *
 */


#if ! defined( DCN_CLASS_HEADER )
#define DCN_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

typedef enum
{
   BasisUnknown = 0,
   NormalPatternBasis,
   LaneIdentificationPatternBasis,
   LaneIdentificationTransmissionsBasis
}
FIX_DATA_BASIS;

class DCN : public RESPONSE
{

   public:

      DCN();
     ~DCN();

      /*
      ** Data
      */

      int              DeccaChainID;
      LINE_OF_POSITION Red;
      LINE_OF_POSITION Green;
      LINE_OF_POSITION Purple;
      NMEA0183_BOOLEAN RedLineNavigationUse;
      NMEA0183_BOOLEAN GreenLineNavigationUse;
      NMEA0183_BOOLEAN PurpleLineNavigationUse;
      double           PositionUncertaintyNauticalMiles;
      FIX_DATA_BASIS   Basis;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const DCN& operator = ( const DCN& source );
};

#endif // DCN_CLASS_HEADER
