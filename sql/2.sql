--
-- Version 2 adds pinning!  Yay!
--

ALTER TABLE NewsItemTable ADD COLUMN pinned INTEGER DEFAULT 0;

-- Index it for quick creation of the pinned feed.
CREATE INDEX NewsItemTablePinIndex ON NewsItemTable(pinned);
