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
    imageURL TEXT NOT NULL,
    ordinal INTEGER DEFAULT 0
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
