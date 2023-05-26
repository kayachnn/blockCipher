import QtQuick 2.15
import QtQuick.Layouts 2.15

//orta taraf
Rectangle{
    id: middleLayout
    Layout.fillWidth: true
    Layout.fillHeight: true
    width: parent.width
    color: "gray"
    border.color: "black"
    border.width: 2
    Layout.margins: 5
    property alias plainText: myPlainTextInput.text
    property alias cipherText: myCipherTextInput.text


    RowLayout{
        width:  parent.width
        height: parent.height
        Layout.fillHeight: true
        Layout.fillWidth: true
        spacing: 2


        PlainTextInput{
            id:myPlainTextInput
        }

        CipherTextInput{
            id:myCipherTextInput
        }

        GraficOutput{

        }

    }

}
