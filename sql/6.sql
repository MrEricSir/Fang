--
-- Version 6 adds compound indexes for optimization.
--

-- Remove old indexes that we no longer need.
DROP INDEX IF EXISTS NewsItemTableTimestampIndex;
DROP INDEX IF EXISTS NewsItemTableFeedIdIndex;
DROP INDEX IF EXISTS FeedItemTableOrdinalIndex;

-- Index for loading single feeds.
CREATE INDEX NewsItemTableFeedTimestampIdIndex ON NewsItemTable(feed_id, timestamp, id);

-- Index for loading folder feeds.
CREATE INDEX FeedItemTableFolderOrdinalIndex ON FeedItemTable(parent_folder, ordinal);

-- Index for loading All News.
CREATE INDEX NewsItemTableTimestampIdIndex ON NewsItemTable(timestamp, id);

-- Index for deleting expired news.
CREATE INDEX NewsItemTableFeedPinnedTimestampIndex ON NewsItemTable(feed_id, pinned, timestamp);
