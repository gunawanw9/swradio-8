#
/*
 *    Copyright (C) 2008, 2009, 2010
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Computing
 *
 *    This file is part of the SDR-J.
 *
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

#ifndef	__FAX_DECODER__
#define	__FAX_DECODER__

#include	<QFrame>
#include	<QByteArray>
#include	<QImage>
#include	<QSettings>
#include	<QPoint>
#include	<vector>
#include	<mutex>
#include	"utilities.h"
#include	"ui_fax-decoder.h"
#include	"radio-constants.h"
#include	"virtual-decoder.h"
#include        "fax-scroller.h"
#include	"fir-filters.h"
#include	"fax-params.h"
#include	"shifter.h"
#include	"ringbuffer.h"

class	RadioInterface;
class	common_fft;
class	faxDemodulator;
class	faxImage;
/*
 *	states:
 *	we look at the bits
 */
#define	APTSTART		0001
#define	WAITING_FOR_START	0002
#define	START_RECOGNIZED	0004
#define	WAITING_FOR_PHASE	0010
#define	READ_PHASE		0020
#define	SYNCED			0040
#define	FAX_DONE		0100
#define	WAITER			0200


class	faxDecoder: public virtualDecoder, public Ui_fax_decoder {
Q_OBJECT
public:
		faxDecoder		(int32_t,
	                                 RingBuffer<std::complex<float>> *,
	                                 QSettings *);
	        ~faxDecoder ();
	void	process			(std::complex<float>);

	enum Teint {
	   FAX_COLOR		= 1,
	   FAX_GRAY		= 2,
	   FAX_BLACKWHITE	= 3
	};

	enum Mode {
	   FAX_AM	= 100,
	   FAX_FM	= 101
	};

private:
	QSettings	*faxSettings;
	int32_t		theRate;
	QFrame		myFrame;
	void		setup_faxDecoder	(QSettings *);
	int32_t		getFreq			(std::complex<float> *);
	faxParams	*getFaxParams		(QString);
	shifter		localMixer;
	faxScroller	faxContainer;
	void		fax_displayImage	(QImage, int, int);
        void		fax_displayImage	(QImage);
	void		addtoImage		(int16_t);
        void            addSampletoImage        (float, int32_t, int32_t);
	faxImage	*theImage;
	QString		saveName;

private slots:
	void		reset			(void);
	void		fax_setIOC		(const QString &);
	void		fax_setMode		(const QString &);
	void		fax_setPhase		(const QString &);
	void		fax_setColor		(const QString &);
	void		fax_setDeviation	(const QString &);
	void		fax_setsavingonDone	();
private:
	bool		checkStart		(int);
	int		checkPhase		(int, float);
	bool		checkPhaseLine		(int, float);
	int		findPhaseLine		(int, int, float);
	int		nrBlanks		();
	int		shiftBuffer		(int, int);
	void		processBuffer		();
	bool		checkStop		(int);
	int		toRead;
	int		alarmCount;
	mutex		locker;
	RingBuffer<std::complex<float>> *audioOut;
	faxDemodulator	*myDemodulator;
	LowPassFIR	*faxLowPass;
	average		*faxAverager;
	QByteArray	rawData;
	uint8_t		faxState;
	int		currentSampleIndex;
	int16_t		fax_IOC;
	float		lpm;
	float		f_lpm;
	int16_t		deviation;
	int16_t		aptCount;
	int16_t		apt_upCrossings;
	int16_t		aptStartFreq;
	int16_t		aptStopFreq;
	bool		phaseInvers;
	uint8_t		faxColor;
	bool		whiteSide;
	int16_t		carrier;
	uint8_t		faxMode;
	int32_t		samplesperLine;
	int16_t		numberofColums;
	int16_t		currentColumn;
	int		nrLines;
	int16_t		lastRow;
	int32_t		pixelValue;
	float		pixelSamples;
	std::vector<int>	faxBuffer;
	int		bufferP;
	int		bufferSize;
	int		linesRecognized;
	bool		savingRequested;
	int		stoppers;
};

#endif

