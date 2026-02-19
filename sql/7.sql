--
-- Version 7 adds FTS5 full-text search for news items.
--

-- FTS5 virtual table for full-text search.
-- Uses content= to avoid duplicating data (contentless FTS).
-- The content is read from NewsItemTable when needed.
CREATE VIRTUAL TABLE IF NOT EXISTS NewsItemFTS USING fts5(
    title,
    summary,
    content,
    author,
    content='NewsItemTable',
    content_rowid='id'
);

-- Rebuild FTS index from existing data.
INSERT INTO NewsItemFTS(NewsItemFTS) VALUES('rebuild');

-- Triggers: keep FTS in sync with NewsItemTable.
-- Drop first in case of partial previous migration.
DROP TRIGGER IF EXISTS NewsItemFTS_ai;
DROP TRIGGER IF EXISTS NewsItemFTS_ad;
DROP TRIGGER IF EXISTS NewsItemFTS_au;

-- Trigger: keep FTS in sync after INSERT.
CREATE TRIGGER NewsItemFTS_ai AFTER INSERT ON NewsItemTable BEGIN
    INSERT INTO NewsItemFTS(rowid, title, summary, content, author)
    VALUES (new.id, new.title, new.summary, new.content, new.author);
END;

-- Trigger: keep FTS in sync after DELETE.
CREATE TRIGGER NewsItemFTS_ad AFTER DELETE ON NewsItemTable BEGIN
    INSERT INTO NewsItemFTS(NewsItemFTS, rowid, title, summary, content, author)
    VALUES ('delete', old.id, old.title, old.summary, old.content, old.author);
END;

-- Trigger: keep FTS in sync after UPDATE.
CREATE TRIGGER NewsItemFTS_au AFTER UPDATE ON NewsItemTable BEGIN
    INSERT INTO NewsItemFTS(NewsItemFTS, rowid, title, summary, content, author)
    VALUES ('delete', old.id, old.title, old.summary, old.content, old.author);
    INSERT INTO NewsItemFTS(rowid, title, summary, content, author)
    VALUES (new.id, new.title, new.summary, new.content, new.author);
END;
