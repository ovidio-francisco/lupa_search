# LUPA

Text preprocessing for Brazilian Portuguese as a MySQL / MariaDB plugin — phonetic transcription, string cleaning, and fuzzy similarity, all running inside the database engine.

```sql
SELECT nome, lupa_similarity(lupa_phoneticBr(nome), lupa_phoneticBr('Rhavi'))
FROM People
ORDER BY 2 DESC
LIMIT 10;
```

---

## What it does

| Function | Returns | Description |
|---|---|---|
| `lupa_clear(str)` | `STRING` | Normalizes text: lowercases, strips accents, removes punctuation, collapses repeated chars |
| `lupa_phoneticBr(str)` | `STRING` | Phonetic transcription tuned for Brazilian Portuguese |
| `lupa_similarity(s1, s2)` | `DOUBLE` | Cosine similarity between two phonetic strings (0.0 – 1.0) |

The typical pipeline is `clear → phoneticBr → similarity`, but each function can be used independently.

---

## Why a plugin and not just UDFs?

Loading as a server plugin means initialization happens **once at server startup**, not once per query. The lookup tables (`valids`, `chars_types`) and the cosine buffers are built when the plugin loads and stay in memory for the lifetime of the server. This avoids repeating megabyte-scale allocations on every call.

The UDFs (`lupa_similarity`, `lupa_clear`, `lupa_phoneticBr`) are still registered and used normally via SQL — the plugin is just the loader.

---

## Requirements

- MySQL 8+ or MariaDB 10.5+
- GCC
- `libmariadbd-dev` (server plugin headers — **not** `libmariadb-dev`)
- `make`

```bash
# Debian / Ubuntu
sudo apt install libmariadbd-dev

# Arch Linux
sudo pacman -S mariadb-libs
```

---

## Build & install

```bash
git clone https://github.com/yourusername/lupa_search.git
cd lupa_search

make install
```

`make install` will:
1. Compile the plugin (`lupa.so`)
2. Copy it to the server's plugin directory
3. Restart the MySQL/MariaDB service
4. Install the plugin via `INSTALL PLUGIN`
5. Register the UDFs via `CREATE FUNCTION`

To uninstall:

```bash
make uninstall
```

---

## Manual steps (if needed)

```bash
# Build only
make plugin

# Find the plugin directory
make dir

# Copy manually
sudo cp build/lupa.so /usr/lib/mysql/plugin/

# Register in MySQL/MariaDB
mysql -e "INSTALL PLUGIN lupa SONAME 'lupa.so';"
mysql < register.sql
```

---

## Usage examples

### `lupa_clear`

Strips accents, normalizes diacritics, uppercases, and removes punctuation. Handles the full range of Latin characters including Portuguese, French, German, and Nordic variants.

```sql
SELECT lupa_clear('É fácil güe o René Ångström açaí über naïve façade') AS Clear;
```
```
+------------------------------------------+
| Clear                                    |
+------------------------------------------+
| E FACIL GUE O RENE ANGSTROM ASAI UBER NAIVE FASADE |
+------------------------------------------+
```

### `lupa_phoneticBr`

Applies phonetic rules for Brazilian Portuguese — collapses homophones, handles digraphs (`lh`, `nh`, `ch`, `ss`, `rr`), and normalizes common regional spelling variations.

```sql
SELECT lupa_phoneticBr('Sousa'), lupa_phoneticBr('Souza');
-- Both return the same phonetic key
```

### `lupa_similarity` — fuzzy name matching

```sql
SELECT nome,
       lupa_similarity(lupa_phoneticBr(nome), lupa_phoneticBr('Cristiane')) AS score
FROM People
WHERE lupa_similarity(lupa_phoneticBr(nome), lupa_phoneticBr('Cristiane')) > 0.7
ORDER BY score DESC;
```

---

## Project structure

```
lupa_search/
├── src/
│   ├── lupa.c          # Core logic: clear(), similarity(), init/deinit
│   ├── phoneticBr.c    # Brazilian Portuguese phonetic rules
│   ├── lupa_in_mysql.c # UDF wrappers (init, main, deinit callbacks)
│   ├── plugin.c        # Plugin declaration and registration
│   ├── buffers.c       # Cosine similarity buffers
│   └── utf8_utils.c    # UTF-8 byte chain helpers
├── include/            # Headers
├── build/              # Compiled objects and .so
├── register.sql        # CREATE FUNCTION statements
├── unregister.sql      # DROP FUNCTION statements
└── makefile
```

---

## Platform notes

The codebase supports both MySQL and MariaDB through compile-time guards:

```c
#ifdef MARIADB_BASE_VERSION
    // MariaDB path — UDFs registered manually via SQL
#else
    // MySQL path — UDFs registered via mysql_udf_register()
#endif
```

MariaDB does not implement `mysql_udf_register()`, so on that platform the UDFs are registered through `register.sql` after plugin installation. The `make install` target handles this automatically.

### Known behavior: MariaDB row buffers

MariaDB passes row data as byte buffers — **not** null-terminated C strings. All string operations use `args->lengths[i]` as the boundary, never `strlen()` on `args->args[i]`.

---

## License

GPL-2.0



<!-- Language -->
<!-- Utilities -->
<!-- for -->
<!-- Phonetic -->
<!-- Analizer -->


<!-- Brazilian -->
<!-- Language -->
<!-- Tool -->
<!-- Search  -->
<!-- Words -->
<!-- Phonetic -->
<!-- Analizer -->


<!-- https://dev.mysql.com/doc/extending-mysql/8.0/en/adding-loadable-function.html -->
