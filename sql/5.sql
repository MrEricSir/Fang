--
-- Version 5 adds user-entered feed URLs.
--

ALTER TABLE FeedItemTable ADD COLUMN user_url TEXT NOT NULL DEFAULT "";

-- Backfill user_url with existing URL data parsed from feed.
UPDATE FeedItemTable
SET
    user_url = (
        SELECT
        CASE WHEN t.url IS NOT NULL AND t.url <> "" THEN t.url
        ELSE t.siteURL
        END
    )
FROM (
  SELECT id, url, siteURL FROM FeedItemTable
) t
WHERE
    FeedItemTable.id = t.id AND is_folder = FALSE;
