-- Fang
-- Create first version of our database.

--
-- FeedItemTable
--

CREATE TABLE FeedItemTable (
    id INTEGER PRIMARY KEY,
    
    title TEXT NOT NULL,
    subtitle TEXT NOT NULL,
    lastUpdated INTEGER DEFAULT 0,
    minutesToUpdate INTEGER DEFAULT 0,
    url TEXT NOT NULL,
    siteURL TEXT NOT NULL,
    imageURL TEXT DEFAULT '',
    ordinal INTEGER DEFAULT 0,
    bookmark_id INTEGER DEFAULT -1
);

CREATE INDEX FeedItemTableOrdinalIndex ON FeedItemTable(ordinal);

--
-- NewsItemTable
--

CREATE TABLE NewsItemTable (
    id INTEGER PRIMARY KEY,
    feed_id INTEGER REFERENCES FeedItemTable(id) ON DELETE CASCADE,
    
    title TEXT NOT NULL,
    author TEXT NOT NULL,
    summary TEXT NOT NULL,
    content TEXT NOT NULL,
    timestamp INTEGER DEFAULT 0,
    url TEXT NOT NULL
);

CREATE INDEX NewsItemTableFeedIdIndex ON NewsItemTable(feed_id);
CREATE INDEX NewsItemTableTimestampIndex ON NewsItemTable(timestamp);

--
-- DropboxConnectorTable
-- Singleton: there will always be exactly 1 row. Use WHERE id = 0 to access it.
--
-- If authenticationToken is the empty string, we're not logged in.
--

CREATE TABLE DropboxConnectorTable (
    id INTEGER PRIMARY KEY,
    authenticationToken TEXT NOT NULL,
    revision INTEGER default 0
);

INSERT INTO DropboxConnectorTable (id, authenticationToken, revision) VALUES (0, "", 0);

