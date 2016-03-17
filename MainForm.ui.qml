import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    width: 640
    height: 480

    TableView {
      anchors.fill: parent
      TableViewColumn {
        role: "id"
        title: "Id"
        width: parent.width/3
      }
      TableViewColumn {
        role: "firstname"
        title: "First Name"
        width: parent.width/3
      }
      TableViewColumn {
        role: "lastname"
        title: "Last Name"
        width: parent.width/3
      }
      model: mymodel
    }
}

