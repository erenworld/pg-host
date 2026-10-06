\echo Use "CREATE EXTENSION hostname" to load this file. \quit


-- 
CREATE FUNCTION hostname()
RETURNS text
AS 'MODULE_PATHNAME'
LANGUAGE C STABLE;
