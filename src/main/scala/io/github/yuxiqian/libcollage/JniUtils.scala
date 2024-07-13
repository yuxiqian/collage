package io.github.yuxiqian.libcollage

object JniUtils {

  private def getPlatform: String = {
    System.getProperty("os.name").toLowerCase match {
      case mac if mac.contains("mac")       => "darwin"
      case win if win.contains("win")       => "win32"
      case linux if linux.contains("linux") => "linux"
      case osName =>
        throw new RuntimeException(s"Unknown operating system $osName")
    }
  }

  private def getArchitecture: String = {
    System.getProperty("os.arch").toLowerCase
  }

  private def getExtensionName: String = {
    getPlatform match {
      case "darwin" => "dylib"
      case "win32"  => "dll"
      case "linux"  => "so"
    }
  }

  def loadLibrary(): Unit = {
    val url = getClass.getResource(
      s"/libcollage/$getPlatform/$getArchitecture/libcollage.$getExtensionName"
    )
    if (url.eq(null))
      throw new NotImplementedError(
        s"No binaries provided for $getPlatform ($getArchitecture) yet"
      )
    System.load(url.getFile)
  }
}
