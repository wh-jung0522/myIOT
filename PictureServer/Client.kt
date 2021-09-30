package test.Socket.Client
import java.io.*
import java.lang.instrument.Instrumentation
import java.net.Socket

// JAVA, Kotlin : Big Endian
// Network : Big Endian
// C : Little Endian

data class IOT_Header(val iot_type : Int) : Serializable
{
    var type : Int = iot_type
}

data class Picture_Header(val pic_user : Int, val pic_size : Int, val pic_name : String) : Serializable
{
    var user : Int = pic_user
    var size : Int = pic_size
    var picture_name : String = pic_name.padEnd(128) // should to fix 128 bytes.
}

class SocketClient : Serializable {
    private lateinit var socket: Socket
    private lateinit var outputStream: OutputStream
    fun connect() {
        try {
            val socketAddress = "121.144.73.146"
            val port = 9091
            socket = Socket(socketAddress, port)
            outputStream = socket.getOutputStream()
        } catch (e: Exception) {
            println("socket connect exception start!!")
            println("e: $e")
        }
    }

    fun sendIOTHeader(iot_hdr : IOT_Header)
    {
        outputStream.write(iot_hdr.type) // Send 1 Byte Type
    }
    fun sendPictureHeader(pic_hdr : Picture_Header)
    {
        outputStream.write(pic_hdr.pic_user.toInt()) // Send 1 Byte User
        sendInt(pic_hdr.size) // send 4 Bytes Size        
        outputStream.write(pic_hdr.picture_name.toByteArray())
    }

    fun sendData(fileInputStream: InputStream) 
    {
        outputStream.write(fileInputStream.readBytes())
    }

    fun sendInt(value:Int)
    {
        outputStream.write((value shr 24).toInt()) // send 4 Bytes Size
        outputStream.write((value shr 16).toInt())
        outputStream.write((value shr 8).toInt())
        outputStream.write(value.toInt())
    }

    fun closeConnect() {
        outputStream.close()
        socket.close()
    }
}
fun main() {
    val filename = "test.jpg"
    val filepath = "./" + filename
    val file : File = File(filepath)
    val filesize = file.length()
    val fileInputStream  = FileInputStream(filepath)

    val iot_type : Int = 0
    val iot_hdr = IOT_Header(iot_type)

    val pic_user : Int = 0

    val pic_hdr = Picture_Header(pic_user,filesize.toInt(),filename)


    val socket = SocketClient()
    socket.connect()
    socket.sendIOTHeader(iot_hdr)
    socket.sendPictureHeader(pic_hdr)
    socket.sendData(fileInputStream)
    socket.closeConnect()


}