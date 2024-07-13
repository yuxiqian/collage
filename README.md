# collage

Compare, with MySQL charset and collation rules

## Usage

Get a MySQL collation rule:

```scala
Collation.get("utf8mb4_general_ci") // with name
Collation.get(34)                   // or index
```

And compare with various charsets:

```scala
col.compare("天", "地") // > 0
col.compare("A", "A")  // == 0
```

```scala
col.compare("Norðurlandanna", "Braggahverfi") // > 0
col.compare("Reykjavík", "Þannig")            // < 0
col.compare("íslenska", "íslenska")           // == 0)
```