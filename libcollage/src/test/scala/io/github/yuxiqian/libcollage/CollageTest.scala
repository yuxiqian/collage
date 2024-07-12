package io.github.yuxiqian.libcollage

import org.scalatest.funsuite.AnyFunSuite

class CollageTest extends AnyFunSuite {

  test("check collation resource loading") {
    assert(CollationList.collationMapping.size == 286)
    assert(CollationList.charsetMapping.size == 286)
  }

  test("check collation list lookup") {
    assert(Collation.getIndex("utf8mb4_general_ci").contains(45))
    assert(Collation.getName(13).contains("sjis_japanese_ci"))

    assert(Collation.getIndex("not there").isEmpty)
    assert(Collation.getName(11037).isEmpty)
  }

  test("check collation lookup") {
    assert(
      Collation
        .get("ucs2_icelandic_ci")
        .map(_.toString)
        .contains("Collation{name=ucs2_icelandic_ci, id=129, charset=ucs2}")
    )
    assert(Collation.get("not there").isEmpty)
  }
}
