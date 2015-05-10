import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

/**
 * Custom styled scrollview for Fang.
 *
 * TODO: Optimize.  It really sucks right now (run the QML profiler, see for yourself!)
 */
ScrollView {
    id: fangScrollView;
    
    anchors.fill: parent;
    
    style: ScrollViewStyle {
        transientScrollBars: true;
    }
}
