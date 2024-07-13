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
    assert(CollationList.collationMapping.keys.map(Collation.get).size == 286)
    assert(
      Collation
        .get("ucs2_icelandic_ci")
        .map(_.toString)
        .contains("Collation{name=ucs2_icelandic_ci, id=129, charset=ucs2}")
    )
    assert(Collation.get("not there").isEmpty)
  }

  test("check comparison") {
    Collation.get("gb2312_bin") match {
      case Some(col) =>
        assert(col.compare("天", "地") > 0)
        assert(col.compare("玄", "黄") < 0)
        assert(col.compare("A", "A") == 0)
      case None => fail("Unrecognized charset")
    }

    Collation.get("utf8mb4_icelandic_ci") match {
      case Some(col) =>
        assert(col.compare("Norðurlandanna", "Braggahverfi") > 0)
        assert(col.compare("Reykjavík", "Þannig") < 0)
        assert(col.compare("íslenska", "íslenska") == 0)
      case None => fail("Unrecognized charset")
    }

    Collation.get("not_a_valid_collation") match {
      case Some(_) =>
        fail("Recognized unexpected collation")
      case None => "OK"
    }
  }
}
