--
-- Version 4 adds folders.
--

ALTER TABLE FeedItemTable ADD COLUMN is_folder BOOLEAN DEFAULT FALSE;
ALTER TABLE FeedItemTable ADD COLUMN folder_open BOOLEAN DEFAULT TRUE;
ALTER TABLE FeedItemTable ADD COLUMN parent_folder INTEGER DEFAULT -1;

-- Index the parent folder
CREATE INDEX FeedItemTableParentFolderIndex ON FeedItemTable(parent_folder);
