import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QuickTextAreaEx 1.0
ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

    RowLayout {
        id: rowLayout
        anchors.fill: parent

        Row {
            id: column
            width: parent.width
            height: 50
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left
            ComboBox {
                id: comboBox
                model: ["normal","hex","base64"]
            }
            CheckBox{
                id:chboxLines
                text: "multiLines"
                checked: false
            }
            Button{
                id:btnLog
                text: "Log"
                onClicked: {
//                    console.log("StrList:\n"+textArea.getStrListByLines());
//                    console.log("BytesList:\n"+textArea.getBytesListByLines());
//                    console.log("ByteArray:\n"+textArea.getByteArray());
//                    var arr = textArea.getBytesVarListByLines();
//                    console.log("arr:\n"+arr);
//                    //console.log("arr toList():\n"+arr.toList());
//                    for(var i in arr){
//                        console.log("arr ",i,":\n"+arr[i]);
//                    }

//                    textArea.append("12crqw")
                    textArea.padding = 11;
                }
            }
        }

        TextareaEx {
            id: textArea
            //text: qsTr("Text Area")
            width: parent.width
            anchors.top: column.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            Layout.fillHeight: true
            texttype: comboBox.currentIndex
            selectByMouse : true
            //placeholderText:plainRect.placeholder+"Hex..."
            wrapMode:TextInput.WrapAnywhere
            multilines: chboxLines.checked
            textFormat:TextEdit.PlainText
            focus: true
            persistentSelection:true//失去焦点保持选中
            padding: 6
            onPaddingChanged: {
                console.log("onPaddingChanged"+padding)
                var aa = preeditText;
            }
            //text: "sdrfse"
            //hoverEnabled:false
//horizontalAlignment:TextEdit.AlignLeft
//leftPadding: 5
//hoveredLink:"dsfgds"
//preeditText:"dfgdf"
        }


    }


}
