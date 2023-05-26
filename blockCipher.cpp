#include "blockCipher.h"

#include <QString>
#include <random>
#include <QDebug>
#include <iostream>

BlockCipher::BlockCipher(QObject *parent)
    : QObject{parent}
{
    generateSbox();
}

QString BlockCipher::generateKey(QString qTotalBytes){
    QString key ="";
    int totalBytes = std::stoi(qTotalBytes.toStdString());

    std::vector<uint8_t> arr(totalBytes, 0x00);

    generateRandomByteArray(arr.data(), totalBytes);
    this->key.clear();
    this->key.insert(this->key.begin(), arr.begin(), arr.end());
    std::string keyHex(totalBytes*2, 0x00);

    qDebug() << "generated key\n";
    for(size_t i=0; i<arr.size(); i++){
        snprintf(keyHex.data()+2*i,totalBytes*2, "%.02x", arr[i]);
        printf("%2x\n", arr[i]);
    }

    qDebug() << "key hex";
    std::cout << "key hex\n";
    printf("key hex\n");
    key = QString::fromStdString(keyHex);
    qDebug() << key;

    return key;
}


void BlockCipher::generateRandomByteArray(uint8_t* arr, size_t length){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    for(size_t i=0; i<length; i++){
        arr[i] = static_cast<uint8_t>(dis(gen));
    }

}

int BlockCipher::generateSbox(){
    this->sBox.resize(256, 0x00);
    for(size_t i=0; i<MAX_UINT; i++){
        this->sBox[i] = static_cast<uint8_t> (~i) + 10;
    }
    return 0;
}

uint8_t applySbox(SBox sbox, uint8_t val){
    return sbox[val];
}

uint8_t BlockCipher::pBox( uint8_t input) {
    uint8_t leftNibble = input & 0xF0;
    uint8_t rightNibble = input & 0x0F;
    return (leftNibble >> 4) | (rightNibble << 4);
}

QVector<uint8_t> BlockCipher::convertStringToUint8Vector(const QString &input){
    QVector<uint8_t> output;
    for (const QChar &c : input) {
        output.append(static_cast<uint8_t>(c.unicode()));
    }
    return output;
}

QString BlockCipher::convertVectorToHex(const QVector<uint8_t> &input) {
    QString output;
    for (const uint8_t &val : input) {
        output.append(QString::number(val, 16).rightJustified(2, '0'));
    }
    return output;
}


QVector<uint8_t> BlockCipher::applySPNetwork(const QVector<uint8_t> &input, const QVector<uint8_t> key) {
    QVector<uint8_t> output = input;

    if (key.size() != 8) {
            qDebug() << "keyLenght error\n";
            return QVector<uint8_t>();
        }

    QString hexOutput = convertVectorToHex(output);
    qDebug() << "giris text " << hexOutput;
    for (int round = 0; round < 12; ++round) {
        QVector<uint8_t> newOutput;
        for (int i=0; i<output.size(); i++) {
            // Apply S-box substitution
            uint8_t substituted = sBox[output[i]];
            // Apply P-box permutation
            uint8_t permuted = this->pBox(substituted);
            uint8_t keyed = permuted ^ key[i % key.size()];
            newOutput.append(keyed);
        }
        output = newOutput;
        QString hexOutput = convertVectorToHex(output);

            // Print output after each round
        qDebug() << "Output after round" << round + 1 << ":" << hexOutput;
    }

    return output;
}

QVector<uint8_t> BlockCipher::getKey(){
    QVector<uint8_t> qKey(this->key.begin(), this->key.end());

    return qKey;
}

QVector<uint8_t> BlockCipher::convertHexToVector(const QString &hexString) {
    QByteArray byteArray = QByteArray::fromHex(hexString.toUtf8());

    QVector<uint8_t> outputVector;
    for (int i = 0; i < byteArray.size(); ++i) {
        outputVector.append(static_cast<uint8_t>(byteArray.at(i)));
    }

    return outputVector;
}

QVector<uint8_t> BlockCipher::decryptSPNetwork(const QVector<uint8_t> &input, const QVector<uint8_t> &key) {
    QVector<uint8_t> output = input;

    // Check that the key length is correct
    if (key.size() != 8) {
        qDebug() << "Key length is incorrect. Must be 8 bytes.";
        return QVector<uint8_t>();
    }

    // Apply 12 rounds of transformations in reverse order
    for (int round = 0; round < 12; ++round) {
        QVector<uint8_t> newOutput;
        for (int i = 0; i < output.size(); ++i) {
            // XOR with key
            uint8_t dekeyed = output[i] ^ key[i % key.size()];
            // Apply inverse P-box permutation
            uint8_t depBoxed =  this->pBox(dekeyed);
            // Apply inverse S-box substitution
            uint8_t deSubbed = sBox[depBoxed];
            newOutput.append(deSubbed);
        }
        output = newOutput;

        // Convert output to hexadecimal string for printing
        QString hexOutput = convertVectorToHex(output);

        // Print output after each round
        qDebug() << "Output after round" << round + 1 << ":" << hexOutput;
    }

    // Unpad output (if necessary)
    while (output.size() > 0 && output.last() == 0x00) {
        output.removeLast();
    }

    return output;
}


QString BlockCipher::convertVectorToString(const QVector<uint8_t> &inputVector) {
    QByteArray byteArray;
    for (uint8_t byte : inputVector) {
        byteArray.append(static_cast<char>(byte));
    }

    return QString::fromUtf8(byteArray);
}
