\set ECHO none
CREATE EXTENSION hostname;
SELECT length(hostname()) > 0;
