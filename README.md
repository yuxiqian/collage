# collage · [![Collage CI](https://github.com/yuxiqian/collage/actions/workflows/ci.yml/badge.svg)](https://github.com/yuxiqian/collage/actions/workflows/ci.yml)

Compare, with MySQL charset and collation rules. Scala port of [molindo-mysql-collation-lib](https://github.com/molindo/molindo-mysql-collations-lib)

## Usage

Get a MySQL collation rule:

```scala
Collation.get("utf8mb4_general_ci") // get collation with name
Collation.get(34)                   // or collation index
```

And compare with various charsets:

```scala
val col = Collation.get("latin1_general_ci").get
col.compare("Alice", "Bob")       // < 0
col.compare("Dorothy", "Carolle") // > 0
col.compare("eve", "Eve")         // == 0, case insensitive
```

```scala
val col = Collation.get("utf8mb4_icelandic_ci").get
col.compare("Norðurlandanna", "Braggahverfi") // > 0
col.compare("Reykjavík", "Þannig")            // < 0
col.compare("íSLENSKA", "íslenska")           // == 0
```
