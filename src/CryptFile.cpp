#include "CryptFile.hpp"

const char key[] = "Please do not pirate this. We are a small company that depend on a tiny market. http://learngreenlandic.com/";
const qint64 kl = sizeof(key);

inline void xor_wrap(char *data, qint64 size, qint64 offset) {
    offset %= kl;

    for (qint64 i=0 ; i<size ; ++i) {
        data[i] ^= key[offset++];
        if (offset >= kl) {
            offset -= kl;
        }
    }
}

CryptFile::CryptFile(QString fname, QObject *parent) :
QFile(fname, parent)
{
}

qint64 CryptFile::readData(char *data, qint64 maxSize) {
    qint64 p = pos();
    qint64 r = QFile::readData(data, maxSize);

    xor_wrap(data, r, p);

    return r;
}

const size_t bz = 16384;
char buf[bz];

qint64 CryptFile::writeData(const char *data, qint64 maxSize) {
    qint64 r = 0;

    qint64 i = 0;
    for ( ; i+bz < maxSize ; i += bz) {
        memcpy(buf, &data[i], bz);
        xor_wrap(buf, bz, pos());
        r += QFile::writeData(buf, bz);
    }

    memcpy(buf, &data[i], maxSize-i);
    xor_wrap(buf, maxSize-i, pos());
    r += QFile::writeData(buf, maxSize-i);

    return r;
}
