# collage · [![Collage CI](https://github.com/yuxiqian/collage/actions/workflows/ci.yml/badge.svg)](https://github.com/yuxiqian/collage/actions/workflows/ci.yml)

Compare, with MySQL charset and collation rules. Scala port of [molindo-mysql-collation-lib](https://github.com/molindo/molindo-mysql-collations-lib)

## Usage

Get a MySQL collation rule:

```scala
Collation.get("utf8mb4_general_ci") // with name
Collation.get(34)                   // or index
```

And compare with various charsets:

```scala
val col = Collation.get("gb2312_bin")
col.compare("天", "地") // > 0
col.compare("A", "A")  // == 0
```

```scala
val col = Collation.get("utf8mb4_icelandic_ci")
col.compare("Norðurlandanna", "Braggahverfi") // > 0
col.compare("Reykjavík", "Þannig")            // < 0
col.compare("íslenska", "íslenska")           // == 0)
```
