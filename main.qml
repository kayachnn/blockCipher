import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

//import QtCharts 2.3
//import app.blockCipher 1.0
import "components"



Window {
    width: 800
    height: 640
    visible: true
    title: qsTr("Proje 1")
    id: mainWindow
    color: "#808080"



    ColumnLayout{
        spacing: 1
        width: parent.width
        height: parent.height
        anchors.fill: parent


        //ust taraf
        UpperLayout{
            Layout.preferredHeight: parent.height/8
        }

        ////////
        MiddleLayout{
            id: myMiddleLayout
            Layout.preferredHeight: parent.height*3/8
            plainText: "hello"
            cipherText: ""

        }

        GenerateKeyLayout{
            Layout.preferredHeight: parent.height/8
        }

        LowerLayout{
            id: mLowerLayout
            Layout.preferredHeight: parent.height/8
            onSifreleButtonClicked:  {
                if (myMiddleLayout.plainText === ""){
                    emptyInputWarning.open()
                    return
                }

                console.log("Text input from plain text " + myMiddleLayout.plainText)
                var text = myMiddleLayout.plainText;
                var vector = blockCipher.convertStringToUint8Vector(text);
                console.log("Converted vector is: " + vector)
                var key = blockCipher.getKey();
                var cipheredVector = blockCipher.applySPNetwork(vector, key);


                var hex = blockCipher.convertVectorToHex(cipheredVector);
                console.log("result hex is: " + hex)

                myMiddleLayout.cipherText = hex


            }

            onSifreCozButtonClicked: {
                if (myMiddleLayout.cipherText === ""){
                    emptyInputWarning2.open()
                    return
                }

                console.log("Text input from cipher text " + myMiddleLayout.cipherText)
                var hexString = myMiddleLayout.cipherText;
                var vector = blockCipher.convertHexToVector(hexString);
                console.log("Converted vector is: " + vector)
                var key = blockCipher.getKey();
                var encryptedVector = blockCipher.decryptSPNetwork(vector, key);


                var encryptedAscii = blockCipher.convertVectorToString(encryptedVector);
                console.log("result hex is: " + encryptedAscii)

                myMiddleLayout.plainText = encryptedAscii
            }
        }


    }

    Dialog{
        id: emptyInputWarning
        title: "Hata"
        x: (mainWindow.width - emptyInputWarning.width) / 2
        y: (mainWindow.height - emptyInputWarning.height) / 2
        standardButtons: Dialog.Ok
        Label{
            text: "Plain Text kısmı boş olamaz"
        }
    }

    Dialog{
        id: emptyInputWarning2
        title: "Hata"
        x: (mainWindow.width - emptyInputWarning.width) / 2
        y: (mainWindow.height - emptyInputWarning.height) / 2
        standardButtons: Dialog.Ok
        Label{
            text: "Cipher Text  kısmı boş olamaz"
        }
    }



}
