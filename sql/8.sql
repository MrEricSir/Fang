--
-- Version 8 adds feed_type column for sitemap-based feeds.
--

ALTER TABLE FeedItemTable ADD COLUMN feed_type INTEGER DEFAULT 0;
