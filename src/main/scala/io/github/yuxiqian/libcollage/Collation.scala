package io.github.yuxiqian.libcollage

import io.github.yuxiqian.libcollage.CollationList._

object Collation {
  JniUtils.loadLibrary()

  def getName(index: Int): Option[String] = {
    collationMapping.get(index)
  }

  def getIndex(collation: String): Option[Int] = {
    collationInverseMapping.get(collation)
  }

  def get(collationIndex: Int): Option[Collation] = {
    collationMapping.get(collationIndex) match {
      case Some(_) => Option.apply(new Collation(collationIndex))
      case None    => Option.empty
    }
  }

  def get(collationName: String): Option[Collation] = {
    getIndex(collationName).map(i => new Collation(i))
  }
}

class Collation(val collationIndex: Int) {
  private val collationName = collationMapping(collationIndex)
  private val charset = charsetMapping(collationIndex)
  private val encoding = javaEncodingMapping(charset)

  override def toString: String = {
    s"Collation{name=$collationName, id=$collationIndex, charset=$charset, encoding=$encoding}"
  }

  def compare(lhs: String, rhs: String): Int = {
    compareBytes(charset, lhs.getBytes(encoding), rhs.getBytes(encoding))
  }

  @native def compare(
      charset: String,
      lhs: String,
      rhs: String
  ): Int

  @native def compareBytes(
      charset: String,
      lhs: Array[Byte],
      rhs: Array[Byte]
  ): Int
}
