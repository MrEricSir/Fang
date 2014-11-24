--
-- Version 2 adds pinning!  Yay!
--

ALTER TABLE NewsItemTable ADD COLUMN pinned BOOLEAN DEFAULT FALSE;

-- Index it for quick creation of the pinned feed.
CREATE INDEX NewsItemTablePinIndex ON NewsItemTable(pinned);
