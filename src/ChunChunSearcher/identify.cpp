#include "identify.h"

Identify::Identify()
{ }

quint8 Identify::IdentifyBySuffix(QString& path)
{
	QString suffix = path.mid(path.lastIndexOf('.') + 1);
	suffix = suffix.toLower();
	if ( Configuration::CompressedSuffix().contains(suffix) )
		return ccs::FILTER_COMPRESSED_ARCHIVE;
	if ( Configuration::DocumentSuffix().contains(suffix) )
		return ccs::FILTER_DOCUMENT;
	if ( Configuration::PicutreSuffix().contains(suffix) )
		return ccs::FILTER_PICTURE;
	if ( Configuration::AudioSuffix().contains(suffix) )
		return ccs::FILTER_AUDIO;
	if ( Configuration::VideoSuffix().contains(suffix) )
		return ccs::FILTER_VIDEO;
	return ccs::FILTER_ALL;
}