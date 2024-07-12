package io.github.yuxiqian.libcollage

import io.github.yuxiqian.libcollage.CollationList._
import com.mysql.cj.CharsetMapping

object Collation {
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
  private val charsetName = charsetMapping(collationIndex)

  override def toString: String = {
    s"Collation{name=$collationName, id=$collationIndex, charset=$charsetName}"
  }

  def compare(lhs: String, rhs: String): Integer = {
    0
  }

  def compare(lhs: Array[Byte], rhs: Array[Byte]): Integer = {
    0
  }
}
