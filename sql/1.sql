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
    lastIconUpdate INTEGER DEFAULT 0,
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
    guid TEXT NOT NULL,
    
    title TEXT NOT NULL,
    author TEXT NOT NULL,
    summary TEXT NOT NULL,
    content TEXT NOT NULL,
    timestamp INTEGER DEFAULT 0,
    url TEXT NOT NULL
);

CREATE INDEX NewsItemTableFeedIdIndex ON NewsItemTable(feed_id);
CREATE INDEX NewsItemTableGuidIndex ON NewsItemTable(guid);
CREATE INDEX NewsItemTableTimestampIndex ON NewsItemTable(timestamp);
