**`pg_trgm`** is a trusted PostgreSQL extension that enables fast text similarity searches and fuzzy string matching based on trigram matching. A trigram is a group of three consecutive characters taken from a string. By breaking text down into these building blocks, the module can determine how alike two pieces of text are, making it highly effective for catching typos, implementing autocomplete, and auto-suggesting corrections. 

### How Trigrams Work

When extracting trigrams, `pg_trgm` treats each word as having two prefixed spaces and one suffixed space while ignoring non-alphanumeric characters. 

For example, the string `"cat"` breaks down into four individual trigrams:
* `"  c"`
* `" ca"`
* `"cat"`
* `"at "`

The similarity score between two strings is calculated based on the number of unique trigrams they share (using the Jaccard index algorithm). This yields a score between `0.0` (completely different) and `1.0` (identical).

### Core Functions and Operators

The extension adds several functions and unique operators to your database:

* **`similarity(text, text)`**: Returns a `real` number representing the overall similarity between two strings.
* **`word_similarity(text, text)`**: Measures the highest similarity between the first string and any substring of the second string.
* **`text % text`**: The similarity operator. Returns `true` if the similarity score is above the database's `pg_trgm.similarity_threshold` (default is `0.3`).
* **`text <-> text`**: The distance operator. It calculates `1 - similarity(text, text)`. It is ideally used in `ORDER BY` clauses to sort results with the closest match first.

### Indexing for High Performance

Without an index, calculating string similarity forces PostgreSQL to perform a slow sequential scan across your entire table. `pg_trgm` solves this by introducing specialized index operator classes that make lookups incredibly fast, even across millions of rows. It supports two index types:

1. **GIN (Generalized Inverted Index)**: Faster to search but slower to build and update. Best for mostly static data read-heavy tables.
2. **GiST (Generalized Search Tree)**: Faster to build and update but slower to search compared to GIN. Best for frequently updated tables.

Additionally, creating a trigram index automatically accelerates standard `LIKE`, `ILIKE`, and regular expression queries, bypassing the traditional limitation where standard B-Tree indexes fail on leading wildcards (e.g., `LIKE '%keyword%'`).

### Basic Implementation Example

```sql
-- 1. Enable the extension in your database
CREATE EXTENSION IF NOT EXISTS pg_trgm;

-- 2. Create a fast GIN index on your text column
CREATE INDEX idx_users_name_trgm ON users USING gin (name gin_trgm_ops);

-- 3. Perform a fuzzy search sorted by closest match
SELECT name, similarity(name, 'Jonh') AS score
FROM users
WHERE name % 'Jonh'
ORDER BY name <-> 'Jonh' ASC;
```
