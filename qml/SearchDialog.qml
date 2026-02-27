import QtQuick
import Fang 1.0

Dialog {
    id: searchDialog;
    title: "Search";

    // Set before opening to pre-populate the search field (e.g. "Edit Search...").
    property string initialQuery: "";

    onDialogOpened: {
        if (initialQuery !== "") {
            searchInput.text = initialQuery;
        }
        searchInput.forceActiveFocus();
    }

    function doSearch() {
        var query = searchInput.text.trim();
        if (query !== "") {
            close();
            news.performSearch(query);
        }
    }

    TextEntry {
        id: searchInput;
        width: parent.width;
        placeholderText: "Search news";
        onAccepted: doSearch();
    }

    DialogGroup {
        width: parent.width;

        DialogButton {
            text: "Cancel";
            onClicked: close();
        }

        DialogButton {
            isPrimary: true;
            text: "Search";
            enabled: searchInput.text.trim() !== "";
            onClicked: doSearch();
        }
    }
}
