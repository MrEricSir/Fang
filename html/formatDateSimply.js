// Simple, Twitter-esque date formatter.

// Believe it or not, Javascript doesn't have this.  Major fail, Javascript.  Major. FAIL.
var monthNicknames = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'];

// Input: ms since epoch
// Output:
//     15s
//     32m
//     29 Aug
//     10 Dec 2013
function formatDateSimply(myDate) {
    //console.log("formatDateSimply(",myDate,")");
    myDate = parseInt(myDate, 10); // force int
    var currentDate = new Date();
    var currentMS = currentDate.getTime();
    var oneMinuteAgo = currentMS - 60000;
    var oneHourAgo = currentMS - 3600000;
    var oneDayAgo = currentMS - 86400000;
    
    if (currentMS <= myDate) {
        return '0s'; // Just pretend the future is zero.
    } else if (oneMinuteAgo < myDate) {
        return Math.round((currentMS - myDate) / 1000) + 's';
    } else if (oneHourAgo < myDate) {
        return Math.round((currentMS - myDate) / 60000) + 'm';
    } else if (oneDayAgo < myDate) {
        return Math.round((currentMS - myDate) / 3600000) + 'h';
    }
    
    // Do the complicated versions.
    var toFormat = new Date(myDate);
    //console.log("to format: ", toFormat.toISOString());
    var ret = toFormat.getDate() + ' ' + monthNicknames[toFormat.getMonth()];
    if (toFormat.getFullYear() != currentDate.getFullYear()) {
        ret += ' ' + toFormat.getFullYear();
    }
    
    return ret;
}
