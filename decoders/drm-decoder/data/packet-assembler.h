#
/*
 *    Copyright (C) 2015
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Computing
 *
 *    This file is part of the SDR-J (JSDR).
 *    SDR-J is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    SDR-J is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with SDR-J; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef	__PACKET_ASSEMBLER
#define	__PACKET_ASSEMBLER

#include	<QByteArray>
#include	<QString>
#include	<stdint.h>
class	stateDescriptor;
class	drmDecoder;
class	motHandler;
class	virtual_dataHandler;

class	packetAssembler {
public:
		packetAssembler		(stateDescriptor *,
	                                 drmDecoder *, uint16_t);
		~packetAssembler	(void);
	void	assemble	(uint8_t *, int16_t, int16_t);
private:
	stateDescriptor	*theState;
	uint16_t	applicationId;
	int16_t		mscIndex;
	bool		waitforFirst;
	int16_t		old_CI;
	QByteArray	series;
	virtual_dataHandler	*my_dataHandler;
	void		add_mscDatagroup	(QByteArray &);
};

#endif

