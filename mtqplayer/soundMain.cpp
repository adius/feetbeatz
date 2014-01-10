#include "bass/bass.h"
#include <stdlib.h>
#include <stdio.h>
#include <QObject>


HSTREAM trackA;
HSTREAM trackB;

void initSound()
{
	int device = -1; // Default Sounddevice
	int freq = 44100; // Sample rate (Hz)
	/* Initialize output device */
	BASS_Init(device, freq, 0, 0, NULL);
	/* Load your soundfile and play it */
	trackA = BASS_StreamCreateFile(FALSE, "/home/hci1/emailp.wav", 0, 0, 0);
	trackB = BASS_StreamCreateFile(FALSE, "/home/hci1/adios.wav", 0, 0, 0);


	//BASS_ChannelSetFX(streamHandle,BASS_FX_DX8_ECHO,1);
}


void playA()
{
	BASS_ChannelPlay(trackA, FALSE);
}

void playB()
{
	BASS_ChannelPlay(trackB, FALSE);
}

class Player : public QObject
{
	Q_OBJECT

public:

};
