#include "AudioCodec.hpp"

#include <cassert>

namespace avtranscoder
{

AudioCodec::AudioCodec( const std::string& codecName )
	: ICodec( codecName )
{
}

AudioCodec::AudioCodec( const AVCodecID codecId )
	: ICodec( codecId )
{
}

AudioCodec::AudioCodec( const ICodec& essenceDesc )
	: ICodec( essenceDesc.getCodecId() )
{
	_codec = essenceDesc.getAVCodec();
	_codecContext = essenceDesc.getAVCodecContext();
}

AudioFrameDesc AudioCodec::getFrameDesc() const
{
	assert( _codecContext != NULL );
	AudioFrameDesc audioFrameDesc;
	
	audioFrameDesc.setChannels( _codecContext->channels );
	audioFrameDesc.setSampleRate( _codecContext->sample_rate );
	audioFrameDesc.setSampleFormat( _codecContext->sample_fmt );
	// audioFrameDesc.setFps( 25 );
	
	return audioFrameDesc;
}

const size_t AudioCodec::getSampleRate() const
{
	assert( _codecContext != NULL );
	return _codecContext->sample_rate;
}

const size_t AudioCodec::getChannels() const
{
	assert( _codecContext != NULL );
	return _codecContext->channels;
}

const AVSampleFormat AudioCodec::getSampleFormat() const
{
	assert( _codecContext != NULL );
	return _codecContext->sample_fmt;
}

void AudioCodec::setAudioParameters( const AudioFrameDesc& audioFrameDesc )
{
	setAudioParameters( audioFrameDesc.getSampleRate(), audioFrameDesc.getChannels(), audioFrameDesc.getSampleFormat() );
}

void AudioCodec::setAudioParameters( const size_t sampleRate, const size_t channels, const AVSampleFormat sampleFormat )
{
	_codecContext->sample_rate = sampleRate;
	_codecContext->channels    = channels;
	_codecContext->sample_fmt  = sampleFormat;
}

}
