//Necessary Libraries
#include <Bela.h>
#include <libraries/Scope/Scope.h>
#include <libraries/AudioFile/AudioFile.h>
#include <cmath>
#include <math.h>

//Wavetable Stuff
const int gWavetableLength = 44100;
const int gNumberOfSensors=7;
float gWavetable[gWavetableLength];										// Buffer that holds the wavetable
float gFloatPointers[gNumberOfSensors]={0,0,0,0,0,0,0};					// float position of the last frame played
int gIntPointers[gNumberOfSensors] = {0,0,0,0,0,0,0};					// Position of the last frame we played 
float gVolume=1.0;														// Global amplitude of the playback
float adjustableVolume=0.0;												//stores the volume value set by the pot
float masterFrequencies[7]={16.35,18.35,20.6,21.83,24.5,27.5,30.87};	//starting frequencies (C)

float frequency[gNumberOfSensors];									//stores the momentary frequencies being played by the sensors

int gAudioFramesPerAnalogFrame=2;						// holds how many analog frames per input frame
int gSensorInput[gNumberOfSensors]={1,2,3,4,5,6,7};		// records analog pins 1-8
float gSensorData[gNumberOfSensors]={0,0,0,0,0,0,0};	//hold the sensor data from all 8 pins
bool gSensorIsTriggered[gNumberOfSensors];				//0 if sensor is off, 1 if it is being triggered
int gNumberOfSensorsTriggered=0;						//stores how many of the sensors are being triggered
float gSensorLatency=50;								//ms of latency for the distance sensors
int framesSinceUpdate=0;

float thresholds[3]={0.17,0.2,0.45};

//Initialize the global oscilloScope
Scope gScope;

/*
Voltages and heights:




*/

bool setup(BelaContext *context, void *userData)
{
	
	//generate wavetable as a sum of various wave types
	for(unsigned int n = 0; n < int(gWavetableLength); n++) {
		//sine wave
		float sineFundamental=sin(2.0*M_PI*float(n)/float(gWavetableLength));
		float sineHarmonic1=sin(4.0*M_PI*float(n)/float(gWavetableLength));
		float sineHarmonic2=sin(8.0*M_PI*float(n)/float(gWavetableLength));
		float sineHarmonic3=sin(16.0*M_PI*float(n)/float(gWavetableLength));
		//square wave
		float squareFundamental;
		if(sin(2.0*M_PI*float(n)/float(gWavetableLength))>=0)
		{
			squareFundamental=1;
		}
		else
		{
			squareFundamental=-1;
		}
		float squareHarmonic1;
		if(sin(4.0*M_PI*float(n)/float(gWavetableLength))>=0)
		{
			squareHarmonic1=1;
		}
		else
		{
			squareHarmonic1=-1;
		}
		
		//triangle wave
		float triangleFundamental;
		if (n<gWavetableLength/4)
		{
			triangleFundamental=float(n)*1.0/(gWavetableLength/4);
		}
		if(n>=gWavetableLength/4 && n<gWavetableLength*3/4)
		{
			triangleFundamental=2.0+float(n)*-1.0/(gWavetableLength/4);
		}
		if(n>=gWavetableLength*3/4 && n<gWavetableLength)
		{
			triangleFundamental=4.0*-1.0+float(n)/(gWavetableLength/4);
		}
		
		//sawtooth wave
		float sawtoothFundamental=1.0-2.0*float(n)/(gWavetableLength);
		
		/*
		Instruments:
		Organ: 0.5 0.2 0.2 0.1 0.0 0.0 0.0 0.0
		Digital Keyboard: 0.6 0.0 0.2 0.0 0.0 0.2 0.0 0.0
		
		*/
		
		
		//write to wavetable
		float sineFundamentalFactor=		0.5;
		float sineHarmonic1Factor=			0.2;
		float sineHarmonic2Factor=			0.2;
		float sineHarmonic3Factor=			0.1;
		float squareFundamentalFactor=		0.0;
		float squareHarmonic1Factor=		0.0;
		float triangleFundamentalFactor=	0.0;
		float sawtoothFundamentalFactor=	0.0;
		gWavetable[n]=	sineFundamentalFactor*sineFundamental+
						sineHarmonic1Factor*sineHarmonic1+
						sineHarmonic2Factor*sineHarmonic2+
						sineHarmonic3Factor*sineHarmonic3+
						squareFundamentalFactor*squareFundamental+
						squareHarmonic1Factor*squareHarmonic1+
						triangleFundamentalFactor*triangleFundamental+
						sawtoothFundamentalFactor*sawtoothFundamental;
		
	}
	
	//Analog Input Stuff
	// Check if analog channels are enabled
	if(context->analogFrames == 0 || context->analogFrames >= context->audioFrames) {
		rt_printf("Error: this example needs analog enabled, with 8 channels\n");
		return false;
	}
	
	//adjust octave
	int octave=2;
	for (int i=0; i<gNumberOfSensors; i++)
	{
		masterFrequencies[i]*=pow(2.0,octave);
	}

	// Initialise the Bela oscilloscope
	gScope.setup(1, context->audioSampleRate);
	return true;
}

void render(BelaContext *context, void *userData)
{
	for(unsigned int n = 0; n < context->audioFrames; n++) {
		
		//collect sensor data every 16 frames (collect values and number of sensors active)
		if(framesSinceUpdate<44100*gSensorLatency/1000.0)
		{
			framesSinceUpdate++;
		}
		else
		{
			
			for (unsigned int i=0; i<gNumberOfSensors; i++)
			{
				
				gSensorData[i]=analogRead(context, n/gAudioFramesPerAnalogFrame, gSensorInput[i]);		//collect sensor data
				
				if(gSensorData[i]>thresholds[0])
				{
					gSensorIsTriggered[i]=1;														//track how many sensors are being triggered
				}
				else
				{
					gSensorIsTriggered[i]=0;
				}
				
				
				//set frequencies based on sensor data
				if (gSensorData[i]>=thresholds[0] && gSensorData[i]<thresholds[1])
				{
					frequency[i]=masterFrequencies[i];
				}
				if (gSensorData[i]>=thresholds[1] && gSensorData[i]<thresholds[2])
				{
					frequency[i]=masterFrequencies[i]*2.0;
				}
				if (gSensorData[i]>=thresholds[2])
				{
					frequency[i]=masterFrequencies[i]*4.0;
				}
				
			}
			//set the adjustableVolume:
			adjustableVolume=analogRead(context, n/gAudioFramesPerAnalogFrame, 0);
			framesSinceUpdate=0;
			
		}
		
		
		//compute output array
		float outputArray[gNumberOfSensors];
		for (int i=0; i<gNumberOfSensors; i++)
		{
			if (gSensorIsTriggered[i])
			{
				outputArray[i]=gWavetable[gIntPointers[i]];
			}
			else
			{
				outputArray[i]=0;
			}
		}
		
		
		//compute the final output float by summing and dividing by the number of triggered sensors
		float out=0;
		gNumberOfSensorsTriggered=0;
		for (int i=0; i<gNumberOfSensors; i++)
		{
			out+=outputArray[i];
			gNumberOfSensorsTriggered+=gSensorIsTriggered[i];
		}
		out = out/gNumberOfSensorsTriggered;
		
		
		//play the output
		for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// Write the sample to every audio output channel
    		audioWrite(context, n, channel, gVolume*adjustableVolume*out*(1.0/0.8));
    	}
    	
    	
    	//increment the read pointers and set to zero when they reach the end of the Wavetable
		for (int i=0; i<gNumberOfSensors; i++)
		{
			gFloatPointers[i]+=frequency[i]*float(gWavetableLength)/(float(context->audioSampleRate));
			if(gFloatPointers[i]>=float(gWavetableLength))
			{
				gFloatPointers[i]-=float(gWavetableLength);
			}
			gIntPointers[i]=int(gFloatPointers[i]);
			
		}
    	
    	// Write the sample to the oscilloscope
    	gScope.log(out);
    	
	}
}

void cleanup(BelaContext *context, void *userData)
{

}
