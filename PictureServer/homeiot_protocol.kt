package test.Socket.homeiot_protocol

import java.io.Serializable

class IOT_Header
{
    var type : UShort
}
class Picture_Header
{
    var user : UShort
    var size : UInt
}

class SocketClient : Serializable {
    private lateinit var socket: Socket
    private lateinit var inputStream: InputStream
    private lateinit var outputStream: OutputStream

    fun connect(port: Int) {
        try {
            val socketAddress = InetAddress.getLocalHost()
            socket = Socket(socketAddress, port)
            outputStream = socket.getOutputStream()
            inputStream = socket.getInputStream()
        } catch (e: Exception) {
            println("socket connect exception start!!")
            println("e: $e")
        }
    }

    fun sendData(data: String) {
        outputStream.write(
            (data + "\n").toByteArray(Charsets.UTF_8)
        )
    }

    fun flush() {
        outputStream.flush()
    }

    fun read(): Boolean {
        var isRead = false
        if (inputStream.available() > 0) {
            isRead = true
        }
        inputStream.bufferedReader(Charsets.UTF_8).forEachLine {
            println(it)
        }
        return isRead
    }

    fun closeConnect() {
        outputStream.close()
        inputStream.close()
        socket.close()
    }
}