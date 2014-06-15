import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

/**
 * Custom styled scrollview for Fang.
 */
ScrollView {
    id: fangScrollView
    
    anchors.fill: parent
    style: ScrollViewStyle {
        transientScrollBars: true
    }
}
