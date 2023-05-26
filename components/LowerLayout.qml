import QtQuick 2.15
import QtQuick.Layouts 2.15

//lower layout
Rectangle{
    id: lowerLayout
    Layout.fillHeight: true
    Layout.fillWidth: true
    height: parent.height
    width: parent.width
    color: "gray"

    signal sifreleButtonClicked()
    signal sifreCozButtonClicked()

    RowLayout{
        Layout.fillWidth: true
        Layout.fillHeight: true
        height:  parent.height
        width: parent.width


        /////////////
        SelectLanguage{
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: parent.width/10
        }

        ///////////
        SifreleButton{
            id: sifreleButton
            buttonText: "Encrypt"
            onButtonClicked: {
                lowerLayout.sifreleButtonClicked()
            }
        }

        ///////
        SifreCozButton{
            id: sifreCozButton
            buttonText: "Decrypt"
            onSifreCozButtonClicked:  {
                lowerLayout.sifreCozButtonClicked()
            }
        }


    }

}
