# Rainbow

### Compile

```
make all
```

### Generate a rainbow table

```
# Usage: ./gen_table [maximal_plaintext_length] [chain_length] [number of chains] [alphabet] [table_name]
./gen_table 6 300 30000 "0123456789" tab.txt
```

### Launch attack

```
# Usage: ./crack [maximal_plaintext_length] [chain_length] [alphabet] [table_name] [hash_file] [res_file]
./crack 6 300 "0123456789" tab.txt hash.txt res.txt 
```
You should prepare your MD5's in file `[hash_file]`. One MD5 per line.
The corresponding result will be printed into `[res_file]`.

