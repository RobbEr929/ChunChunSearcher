#ifndef CCS_GLOBAL_H
#define CCS_GLOBAL_H
#include <QVector>
#include <QString>
#include <QStringLiteral>
#include <QReadWriteLock>

QReadWriteLock m;

namespace ccs
{
#ifndef CCS_FLAG_FILTER
#define CCS_FLAG_FILTER
	constexpr quint8 FILTER_ALL = 0b00000000;
	constexpr quint8 FILTER_DIRECTORY = 0b00010000;
	constexpr quint8 FILTER_COMPRESSED_ARCHIVE = 0b00100000;
	constexpr quint8 FILTER_DOCUMENT = 0b00110000;
	constexpr quint8 FILTER_PICTURE = 0b01000000;
	constexpr quint8 FILTER_AUDIO = 0b01010000;
	constexpr quint8 FILTER_VIDEO = 0b01100000;
#endif
#ifndef CCS_FLAG_VOLUME
#define CCS_FLAG_VOLUME
	constexpr __int8 VOLUME_NOT_NTFS = 0b00000001;
	constexpr __int8 VOLUME_IS_NTFS = 0b00000010;
	constexpr __int8 VOLUME_USEING = 0b00000100;
	constexpr __int8 VOLUME_DISCARD = 0b00001000;
#endif
}
#endif // CCS_GLOBAL_H
