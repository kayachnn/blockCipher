#ifndef BLOCKCIPHER_H
#define BLOCKCIPHER_H

#include <QObject>
#define MAX_UINT 256

typedef std::vector<uint8_t> SBox;

class BlockCipher : public QObject
{
    Q_OBJECT
    SBox sBox;
    std::vector<uint8_t> key;
public:
    explicit BlockCipher(QObject *parent = nullptr);

    Q_INVOKABLE QString generateKey(QString totalBytes);

    void generateRandomByteArray(uint8_t *arr, size_t arrSize);


    uint8_t pBox(uint8_t data);
    int generateSbox();
    uint8_t applySbox(SBox& sbox, uint8_t val);

    Q_INVOKABLE QVector<uint8_t> getKey();
    Q_INVOKABLE QVector<uint8_t> convertStringToUint8Vector(const QString &input);
    Q_INVOKABLE QString convertVectorToHex(const QVector<uint8_t> &input);
    Q_INVOKABLE QVector<uint8_t> applySPNetwork(const QVector<uint8_t> &input, const QVector<uint8_t> key);
    Q_INVOKABLE QVector<uint8_t> convertHexToVector(const QString &hexString);
    Q_INVOKABLE QVector<uint8_t> decryptSPNetwork(const QVector<uint8_t> &input, const QVector<uint8_t> &key);
    Q_INVOKABLE QString convertVectorToString(const QVector<uint8_t> &inputVector);

signals:

};

#endif // BLOCKCIPHER_H
